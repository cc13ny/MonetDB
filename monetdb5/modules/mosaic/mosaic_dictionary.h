/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0.  If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright 1997 - July 2008 CWI, August 2008 - 2019 MonetDB B.V.
 */

/*
 * authors Martin Kersten, Aris Koning
 */
#ifndef _MOSAIC_DICTIONARY_ 
#define _MOSAIC_DICTIONARY_ 

#include "gdk.h"
#include "gdk_bitvector.h"
#include "mal_exception.h"

 /*TODO: assuming (for now) that bats have nils during compression*/
static const bool nil = true;

#define calculateBits(RES, COUNT)\
{\
	unsigned char bits = 0;\
	while ((COUNT) >> bits) {\
		bits++;\
	}\
	(RES) = bits;\
}

typedef struct _EstimationParameters {
	BUN count;
	unsigned char bits;
	BUN delta_count;
	unsigned char bits_extended; // number of bits required to index the info after the delta would have been merged.
} EstimationParameters;

typedef struct _GlobalDictionaryInfo {
	BAT* dict;
	/* admin: the admin column is aligned with the full dictionary column dict.
	 * Each entry in the admin column represents a tuple consisting of
	 * the frequency of the corresponding dictionary value in the current estimation run
	 * and a bit which represents the final choice to include the corresponding dictionary value in the final dictionary. */
	BAT* admin;
	BAT* selection_vector;
	BAT* increments;
	BUN previous_start;
	BUN previous_limit;
	BUN count;
	EstimationParameters parameters;
} GlobalDictionaryInfo;


#define GET_COUNT(INFO)				((INFO)->count)
#define GET_DELTA_COUNT(INFO)		((INFO)->parameters.delta_count)
#define GET_BITS(INFO)				((INFO)->parameters.bits)
#define GET_BITS_EXTENDED(INFO)		((INFO)->parameters.bits_extended)
#define GetTypeWidth(INFO)			((INFO)->dict->twidth)
#define GetSizeInBytes(INFO)		(GET_COUNT(INFO) * GetTypeWidth(INFO))

// task dependent macro's
#define GET_FINAL_DICT(task, NAME, TPE) (((TPE*) (task)->bsrc->tvmosaic->base) + (task)->hdr->CONCAT2(pos_, NAME))
#define GET_FINAL_BITS(task, NAME) ((task)->hdr->CONCAT2(bits_, NAME))
#define GET_FINAL_DICT_COUNT(task, NAME) ((task)->hdr->CONCAT2(length_, NAME))

#define find_value_DEF(TPE) \
static inline \
BUN find_value_##TPE(TPE* dict, BUN dict_count, TPE val) {\
	BUN m, f= 0, l = dict_count, offset = 0;\
	/* This function assumes that the implementation of a dictionary*/\
	/* is that of a sorted array with nils starting first.*/\
	if (IS_NIL(TPE, val)) return 0;\
	if (dict_count > 0 && IS_NIL(TPE, dict[0])) {\
		/*If the dictionary starts with a nil,*/\
		/*the actual sorted dictionary starts an array entry later.*/\
		dict++;\
		offset++;\
		l--;\
	}\
	while( l-f > 0 ) {\
		m = f + (l-f)/2;\
		if ( val < dict[m]) l=m-1; else f= m;\
		if ( val > dict[m]) f=m+1; else l= m;\
	}\
	return f + offset;\
}

#define merge_delta_Into_dictionary_DEF(TPE) \
static \
void merge_delta_Into_dictionary_##TPE(GlobalDictionaryInfo* info) {\
\
	MosaicBlkRec* bytevector	= Tloc(info->admin, 0);\
\
	BUN delta_count = 0;\
\
	BUN i;\
	for (i = 0; i < BATcount(info->admin); i++) {\
		if (!bytevector[i].tag && bytevector[i].cnt) {\
			 bytevector[i].tag = 1;\
			 delta_count++;\
			 bytevector[i].cnt = 0;\
		}\
	}\
	info->count += delta_count;\
	GET_BITS(info) = GET_BITS_EXTENDED(info);\
}

#define decompress_dictionary_DEF(TPE) \
static void \
decompress_dictionary_##TPE(TPE* dict, bte bits, BitVector base, BUN limit, TPE** dest) {\
	for(BUN i = 0; i < limit; i++){\
		BUN key = getBitVector(base,i,(int) bits);\
		(*dest)[i] = dict[key];\
	}\
	*dest += limit;\
}

#define MosaicBlkHeader_DEF_dictionary(NAME, TPE)\
typedef struct {\
	MosaicBlkRec rec;\
	char padding;\
	BitVectorChunk bitvector; /*First chunk of bitvector to force correct alignment.*/\
} MOSBlockHeader_##NAME##_##TPE;

#define DICTBlockHeaderTpe(NAME, TPE) MOSBlockHeader_##NAME##_##TPE

// MOStask object dependent macro's

#define MOScodevectorDict(task, NAME, TPE) ((BitVector) &((DICTBlockHeaderTpe(NAME, TPE)*) (task)->blk)->bitvector)

#define advance_dictionary(NAME, TPE)\
{\
	BUN cnt = MOSgetCnt(task->blk);\
\
	assert(cnt > 0);\
	task->start += (oid) cnt;\
\
	char* blk = (char*)task->blk;\
	blk += sizeof(MOSBlockHeaderTpe(NAME, TPE));\
	blk += BitVectorSize(cnt, GET_FINAL_BITS(task, NAME));\
	blk += GET_PADDING(task->blk, NAME, TPE);\
\
	task->blk = (MosaicBlk) blk;\
}

// insert a series of values into the compressor block using dictionary
#define DICTcompress(NAME, TPE)\
{\
	ALIGN_BLOCK_HEADER(task,  NAME, TPE);\
\
	TPE *val = getSrc(TPE, (task));\
	BUN cnt = estimate->cnt;\
	BitVector base = MOScodevectorDict(task, NAME, TPE);\
	BUN i;\
	TPE* dict = GET_FINAL_DICT(task, NAME, TPE);\
	BUN dict_size = GET_FINAL_DICT_COUNT(task, NAME);\
	bte bits = GET_FINAL_BITS(task, NAME);\
	compress_dictionary_##TPE(dict, dict_size, &i, val, cnt, base, bits);\
	MOSsetCnt(task->blk, i);\
}

// the inverse operator, extend the src
#define DICTdecompress(NAME, TPE)\
{	BUN cnt = MOSgetCnt((task)->blk);\
	BitVector base = MOScodevectorDict(task, NAME, TPE);\
	bte bits = GET_FINAL_BITS(task, NAME);\
	TPE* dict = GET_FINAL_DICT(task, NAME, TPE);\
	TPE* dest = (TPE*) (task)->src;\
	decompress_dictionary_##TPE(dict, bits, base, cnt, &dest);\
	(task)->src = (char*) dest;\
}

#define scan_loop_dictionary(NAME, TPE, CANDITER_NEXT, TEST) {\
    TPE* dict = GET_FINAL_DICT(task, NAME, TPE);\
	BitVector base = MOScodevectorDict(task, NAME, TPE);\
    bte bits = GET_FINAL_BITS(task, NAME);\
    for (oid c = canditer_peekprev(task->ci); !is_oid_nil(c) && c < last; c = CANDITER_NEXT(task->ci)) {\
        BUN i = (BUN) (c - first);\
        BitVectorChunk j = getBitVector(base,i,bits); \
        v = dict[j];\
        /*TODO: change from control to data dependency.*/\
        if (TEST)\
            *o++ = c;\
    }\
}

#define projection_loop_dictionary(NAME, TPE, CANDITER_NEXT)\
{\
	TPE* dict = GET_FINAL_DICT(task, NAME, TPE);\
	BitVector base = MOScodevectorDict(task, NAME, TPE);\
    bte bits = GET_FINAL_BITS(task, NAME);\
	for (oid o = canditer_peekprev(task->ci); !is_oid_nil(o) && o < last; o = CANDITER_NEXT(task->ci)) {\
        BUN i = (BUN) (o - first);\
        BitVectorChunk j = getBitVector(base,i,bits); \
		*bt++ = dict[j];\
		task->cnt++;\
	}\
}

#define outer_loop_dictionary(HAS_NIL, NIL_MATCHES, NAME, TPE, LEFT_CI_NEXT, RIGHT_CI_NEXT) \
{\
	bte bits		= GET_FINAL_BITS(task, NAME);\
	TPE* dict		= GET_FINAL_DICT(task, NAME, TPE);\
	BitVector base	= MOScodevectorDict(task, NAME, TPE);\
    for (oid lo = canditer_peekprev(task->ci); !is_oid_nil(lo) && lo < last; lo = LEFT_CI_NEXT(task->ci)) {\
        BUN i = (BUN) (lo - first);\
		BitVectorChunk j= getBitVector(base,i,bits);\
        TPE lval = dict[j];\
		if (HAS_NIL && !NIL_MATCHES) {\
			if ((IS_NIL(TPE, lval))) {continue;};\
		}\
		INNER_LOOP_UNCOMPRESSED(HAS_NIL, TPE, RIGHT_CI_NEXT);\
	}\
}

#define join_inner_loop_dictionary(NAME, TPE, HAS_NIL, RIGHT_CI_NEXT)\
{\
	bte bits		= GET_FINAL_BITS(task, NAME);\
	TPE* dict		= GET_FINAL_DICT(task, NAME, TPE);\
	BitVector base	= MOScodevectorDict(task, NAME, TPE);\
    for (oid ro = canditer_peekprev(task->ci); !is_oid_nil(ro) && ro < last; ro = RIGHT_CI_NEXT(task->ci)) {\
        BUN i = (BUN) (ro - first);\
		BitVectorChunk j= getBitVector(base,i,bits);\
        TPE rval = dict[j];\
        IF_EQUAL_APPEND_RESULT(HAS_NIL, TPE);\
	}\
}

#endif /* _MOSAIC_DICTIONARY_  */

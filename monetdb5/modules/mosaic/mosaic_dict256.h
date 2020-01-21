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

#ifndef _MOSAIC_DICT256_
#define _MOSAIC_DICT256_

#include <mal.h>
#include "mal_interpreter.h"
#include "mal_client.h"
#include "mosaic_utility.h"
#include "mosaic_dictionary.h"

#define DICTTHRESHOLD 4192
#define DICTSIZE 256

bool MOStypes_dict256(BAT* b);
mal_export str MOScreateCappedInfo(MOStask* task);
mal_export void MOSlayout_dict256(MOStask* task, BAT *btech, BAT *bcount, BAT *binput, BAT *boutput, BAT *bproperties);
mal_export void MOSlayout_dict256_hdr(MOStask* task, BAT *btech, BAT *bcount, BAT *binput, BAT *boutput, BAT *bproperties);

#define MosaicBlkHeader_DEF_dict256(TPE) MosaicBlkHeader_DEF_dictionary(dict256, TPE)

ALGEBRA_INTERFACES_ALL_TYPES_WITH_DICTIONARY(dict256);

#define DO_OPERATION_ON_dict256(OPERATION, TPE, ...) DO_OPERATION_ON_ALL_TYPES(OPERATION, dict256, TPE, __VA_ARGS__)

#define join_inner_loop_dict256(TPE, HAS_NIL, RIGHT_CI_NEXT) join_inner_loop_dictionary(dict256, TPE, HAS_NIL, RIGHT_CI_NEXT)

#endif /* _MOSAIC_DICT256_ */

/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0.  If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright 1997 - July 2008 CWI, August 2008 - 2019 MonetDB B.V.
 */

/*
 * (c) Martin Kersten
 *  MonetDB Basic Definitions
 * Definitions that need to included in every file of the Monet system, as well as in user defined module implementations.
 */
#ifndef _MAL_H
#define _MAL_H

#include "gdk.h"

#ifdef WIN32
#if !defined(LIBMAL) && !defined(LIBATOMS) && !defined(LIBKERNEL) && !defined(LIBMAL) && !defined(LIBOPTIMIZER) && !defined(LIBSCHEDULER) && !defined(LIBMONETDB5) && !defined(LIBMOSAIC)
#define mal_export extern __declspec(dllimport)
#else
#define mal_export extern __declspec(dllexport)
#endif
#else
#define mal_export extern
#endif

#ifdef HAVE_SYS_TIMES_H
# include <sys/times.h>
#endif

/*
 * MonetDB Calling Options
 * The number of invocation arguments is kept to a minimum.
 * See `man mserver5` or tools/mserver/mserver5.1
 * for additional system variable settings.
 */
#define MAXSCRIPT 64

/* The compile time debugging flags are turned into bit masks, akin to GDK */
mal_export lng OPTdebug;

#define OPTaliases			(1 )
#define OPTcandidates		((lng)1 << 1)
#define OPTcoercion			((lng)1 << 2)
#define OPTcommonterms		((lng)1 << 3)
#define OPTconstants		((lng)1 << 4)
#define OPTcostmodel		((lng)1 << 5)
#define OPTdataflow			((lng)1 << 6)
#define OPTdeadcode			((lng)1 << 7)
#define OPTemptybind		((lng)1 << 8)
#define OPTevaluate			((lng)1 << 9)
#define OPTgarbagecollector	((lng)1 << 10)
#define OPTgenerator		((lng)1 << 11)
#define OPTinline			((lng)1 << 12)
#define OPTjit				((lng)1 << 13)
#define OPTjson				((lng)1 << 14)
#define OPTmacros			((lng)1 << 15)
#define OPTmatpack			((lng)1 << 15)
#define OPTmergetable		((lng)1 << 16)
#define OPTmitosis			((lng)1 << 17)
#define OPTmultiplex		((lng)1 << 18)
#define OPToltp				((lng)1 << 19)
#define OPTpipes			((lng)1 << 20)
#define OPTpostfix			((lng)1 << 21)
#define OPTprelude			((lng)1 << 22)
#define OPTprofiler			((lng)1 << 23)
#define OPTprojectionpath	((lng)1 << 24)
#define OPTpushselect		((lng)1 << 25)
#define OPTquerylog			((lng)1 << 26)
#define OPTreduce			((lng)1 << 27)
#define OPTremap			((lng)1 << 28)
#define OPTremotequeries	((lng)1 << 29)
#define OPTreorder			((lng)1 << 30)
#define OPTsupport			((lng)1 << 31)
#define OPTvolcano			((lng)1 << 32)
#define OPTwlc				((lng)1 << 33)

mal_export lng MALdebug;

/*
 * MonetDB assumes it can use most of the machines memory,
 * leaving a small portion for other programs.
 */
#define GB (((lng)1024)*1024*1024)
#define MEMORY_THRESHOLD  (0.2 * GDK_mem_maxsize > 8 * GB?  GDK_mem_maxsize - 8 * GB: 0.8 * GDK_mem_maxsize)

mal_export char     monet_cwd[FILENAME_MAX];
mal_export char 	monet_characteristics[4096];
mal_export stream	*maleventstream;

#ifdef HAVE_HGE
mal_export int have_hge;
#endif

/*
   See gdk/gdk.h for the definition of all debug masks.
   See `man mserver5` or tools/mserver/mserver5.1
   for a documentation of all debug options.
*/
#define GRPthreads (THRDMASK | PARMASK)
#define GRPmemory (MEMMASK | ALLOCMASK )
#define GRPproperties (CHECKMASK | PROPMASK | BATMASK )
#define GRPio (IOMASK | PERFMASK )
#define GRPheaps (HEAPMASK)
#define GRPtransactions (TMMASK | DELTAMASK | TEMMASK)
#define GRPmodules (LOADMASK)
#define GRPalgorithms (ALGOMASK | ESTIMASK)
#define GRPperformance (DEADBEEFMASK)
#define GRPoptimizers  (OPTMASK)
#define GRPforcemito (FORCEMITOMASK | NOSYNCMASK)

mal_export MT_Lock  mal_contextLock;
mal_export MT_Lock  mal_remoteLock;
mal_export MT_Lock  mal_profileLock ;
mal_export MT_Lock  mal_copyLock ;
mal_export MT_Lock  mal_delayLock ;
mal_export MT_Lock  mal_oltpLock ;

mal_export int mal_init(void);
mal_export _Noreturn void mal_exit(int status);
mal_export void mserver_reset(void);

/* This should be here, but cannot, as "Client" isn't known, yet ... |-(
 * For now, we move the prototype declaration to src/mal/mal_client.c,
 * the only place where it is currently used. Maybe, we should concider
 * also moving the implementation there...
 */

/* Listing modes are globally known */
#define LIST_INPUT      1       /* echo original input */
#define LIST_MAL_NAME   2       /* show variable name */
#define LIST_MAL_TYPE   4       /* show type resolutoin */
#define LIST_MAL_VALUE  8       /* list bat tuple count */
#define LIST_MAL_PROPS 16       /* show variable properties */
#define LIST_MAL_MAPI  32       /* output Mapi compatible output */
#define LIST_MAL_REMOTE  64       /* output MAL for remote execution */
#define LIST_MAL_CALL  (LIST_MAL_NAME | LIST_MAL_VALUE )
#define LIST_MAL_DEBUG (LIST_MAL_NAME | LIST_MAL_VALUE | LIST_MAL_TYPE | LIST_MAL_PROPS)
#define LIST_MAL_ALL   (LIST_MAL_NAME | LIST_MAL_VALUE | LIST_MAL_TYPE | LIST_MAL_PROPS | LIST_MAL_MAPI)

/* type check status is kept around to improve type checking efficiency */
#define TYPE_ERROR      -1
#define TYPE_UNKNOWN     0
#define TYPE_RESOLVED    2
#define GARBAGECONTROL   3

#define VARARGS 1				/* deal with variable arguments */
#define VARRETS 2

typedef int malType;
typedef str (*MALfcn) ();

typedef struct SYMDEF {
	struct SYMDEF *peer;		/* where to look next */
	struct SYMDEF *skip;		/* skip to next different symbol */
	str name;
	int kind;					/* what kind of symbol */
	struct MALBLK *def;			/* the details of the MAL fcn */
} *Symbol, SymRecord;

typedef struct VARRECORD {
	char id[IDLENGTH];			/* use the space for the full name */
	malType type;				/* internal type signature */
    bool constant:1,
            typevar:1,
            fixedtype:1,
            udftype:1,
            cleanup:1,
            initialized:1,
            used:1,
            disabled:1;
	short depth;				/* scope block depth, set to -1 if not used */
	short worker;				/* thread id of last worker producing it */
	ValRecord value;
	int declared;				/* pc index when it was first assigned */
	int updated;				/* pc index when it was first updated */
	int eolife;					/* pc index when it should be garbage collected */
	int stc;				    /* pc index for rendering schema.table.column  */
	BUN rowcnt;					/* estimated row count*/
} *VarPtr, VarRecord;

/* For performance analysis we keep track of the number of calls and
 * the total time spent while executing the instruction. (See
 * mal_profiler.c) 
 */

typedef struct {
	bte token;					/* instruction type */
	bit barrier;				/* flow of control modifier takes:
								   BARRIER, LEAVE, REDO, EXIT, CATCH, RAISE */
	bit typechk;				/* type check status */
	bte gc;						/* garbage control flags */
	bit polymorphic;			/* complex type analysis */
	bit varargs;				/* variable number of arguments */
	int jump;					/* controlflow program counter */
	int pc;						/* location in MAL plan for profiler*/
	MALfcn fcn;					/* resolved function address */
	struct MALBLK *blk;			/* resolved MAL function address */
	/* inline statistics */
	lng clock;					/* when the last call was started */
	lng ticks;					/* total micro seconds spent in last call */
	int calls;					/* number of calls made to this instruction */
	lng totticks;				/* total time spent on this instruction. */
	lng wbytes;					/* number of bytes produced in last instruction */
	/* the core admin */
	str modname;				/* module context, reference into namespace */
	str fcnname;				/* function name, reference into namespace */
	int argc, retc, maxarg;		/* total and result argument count */
	int argv[FLEXIBLE_ARRAY_MEMBER]; /* at least a few entries */
} *InstrPtr, InstrRecord;

typedef struct MALBLK {
	char binding[IDLENGTH];	/* related C-function */
	str help;				/* supportive commentary */
	oid tag;				/* unique block tag */
	struct MALBLK *alternative;
	int vtop;				/* next free slot */
	int vsize;				/* size of variable arena */
	int vid;	 			/* generate local variable counter */
	VarRecord *var;			/* Variable table */
	int stop;				/* next free slot */
	int ssize;				/* byte size of arena */
	InstrPtr *stmt;				/* Instruction location */

	bool inlineProp:1,		/* inline property */
		     unsafeProp:1,		/* unsafe property */
		     sealedProp:1;		/* sealed property (opertions for sealed object should be on the full object once) */

	str errors;				/* left over errors */
	struct MALBLK *history;	/* of optimizer actions */
	short keephistory;		/* do we need the history at all */
	int maxarg;				/* keep track on the maximal arguments used */
	ptr replica;			/* for the replicator tests */
	lng starttime;			/* track when the query started, for resource management */
	lng runtime;			/* average execution time of block in ticks */
	int calls;				/* number of calls */
	lng optimize;			/* total optimizer time */
	int activeClients;		/* load during mitosis optimization */
} *MalBlkPtr, MalBlkRecord;

#define STACKINCR   128
#define MAXGLOBALS  (4 * STACKINCR)

typedef int (*DFhook) (void *, void *, void *, void *);

typedef struct MALSTK {
	int stksize;
	int stktop;
	int stkbot;			/* the first variable to be initialized */
	int stkdepth;		/* to protect against runtime stack overflow */
	int calldepth;		/* to protect against runtime stack overflow */
	short keepAlive;	/* do not garbage collect when set */
	/*
	 * Parallel processing is mostly driven by dataflow, but within this context
	 * there may be different schemes to take instructions into execution.
	 * The admission scheme (and wrapup) are the necessary scheduler hooks.
	 */
	DFhook admit;
	DFhook wrapup;

/*
 * It is handy to administer the timing in the stack frame
 * for use in profiling instructions.
 */
	struct timeval clock;	/* time this stack was created */
	char cmd;				/* debugger and runtime communication */
	char status;			/* srunning 'R' suspended 'S', quiting 'Q' */
	int pcup;				/* saved pc upon a recursive all */
	oid tag;				/* unique invocation call tag */
	int	workers;			/* Actual number of concurrent workers */
	lng	memory;				/* Actual memory claim highwater mark */

	struct MALSTK *up;		/* stack trace list */
	struct MALBLK *blk;		/* associated definition */
	ValRecord stk[FLEXIBLE_ARRAY_MEMBER];
} MalStack, *MalStkPtr;

#define MAXOLTPLOCKS  1024
typedef unsigned char OLTPlocks[MAXOLTPLOCKS];

#define OLTPclear(X)  memset((char*)X, 0, sizeof(X))

#endif /*  _MAL_H*/

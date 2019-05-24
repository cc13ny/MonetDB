/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0.  If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright 1997 - July 2008 CWI, August 2008 - 2019 MonetDB B.V.
 */

/* This file should not be included in any file outside of this directory */

#ifndef LIBMAL
#error this file should not be included outside its source directory
#endif

#ifdef _MAL_CLIENT_H_
/* _MAL_CLIENT_H_ is defined in the same file as Client */
__hidden void MCexitClient(Client c)
	__attribute__((__visibility__("hidden")));
__hidden void MCfreeClient(Client c)
	__attribute__((__visibility__("hidden")));
__hidden int MCreadClient(Client c)
	__attribute__((__visibility__("hidden")));
__hidden void MCpopClientInput(Client c)
	__attribute__((__visibility__("hidden")));
__hidden str defaultScenario(Client c)	/* used in src/mal/mal_session.c */
	__attribute__((__visibility__("hidden")));

#ifndef HAVE_EMBEDDED
__hidden void mdbStep(Client cntxt, MalBlkPtr mb, MalStkPtr stk, int pc)
	__attribute__((__visibility__("hidden")));

__hidden str runFactory(Client cntxt, MalBlkPtr mb, MalBlkPtr mbcaller, MalStkPtr stk, InstrPtr pci)
	__attribute__((__visibility__("hidden")));
__hidden int yieldResult(MalBlkPtr mb, InstrPtr p, int pc)
	__attribute__((__visibility__("hidden")));
__hidden str yieldFactory(MalBlkPtr mb, InstrPtr p, int pc)
	__attribute__((__visibility__("hidden")));
__hidden str callFactory(Client cntxt, MalBlkPtr mb, ValPtr argv[],char flag)
	__attribute__((__visibility__("hidden")));
#endif
#endif

#ifndef NDEBUG
__hidden bool mdbInit(void)
	__attribute__((__visibility__("hidden")));
__hidden void mdbExit(void)
	__attribute__((__visibility__("hidden")));
#endif

#ifndef HAVE_EMBEDDED
__hidden void malGarbageCollector(MalBlkPtr mb)
	__attribute__((__visibility__("hidden")));
__hidden mal_export void AUTHreset(void)
	__attribute__((__visibility__("hidden")));
__hidden mal_export void mal_runtime_reset(void)
	__attribute__((__visibility__("hidden")));
__hidden void initResource(void)
	__attribute__((__visibility__("hidden")));
#endif

__hidden str malAtomDefinition(str name,int tpe)
	__attribute__((__visibility__("hidden")));
__hidden str malAtomProperty(MalBlkPtr mb, InstrPtr pci)
	__attribute__((__visibility__("hidden")));
__hidden void setqptimeout(lng usecs)
	__attribute__((__visibility__("hidden")));

#ifdef MAXSCOPE
/* MAXSCOPE is defined in the same file as Module */
__hidden Symbol cloneFunction(Module scope, Symbol proc, MalBlkPtr mb, InstrPtr p)
	__attribute__((__visibility__("hidden")));
#endif

__hidden int getBarrierEnvelop(MalBlkPtr mb)
	__attribute__((__visibility__("hidden")));

__hidden void listFunction(stream *fd, MalBlkPtr mb, MalStkPtr stk, int flg, int first, int step)
	__attribute__((__visibility__("hidden")));

/* mal_linker.h */
__hidden char *MSP_locate_script(const char *mod_name)
	__attribute__((__visibility__("hidden")));

__hidden mal_export void mal_client_reset(void)
	__attribute__((__visibility__("hidden")));

__hidden mal_export void mal_dataflow_reset(void)
	__attribute__((__visibility__("hidden")));

__hidden mal_export void mal_factory_reset(void)
	__attribute__((__visibility__("hidden")));

__hidden mal_export void mal_linker_reset(void)
	__attribute__((__visibility__("hidden")));

__hidden mal_export void mal_module_reset(void)
	__attribute__((__visibility__("hidden")));

__hidden mal_export void mal_namespace_reset(void)
	__attribute__((__visibility__("hidden")));

__hidden mal_export void mal_resource_reset(void)
	__attribute__((__visibility__("hidden")));

__hidden extern MT_Lock mal_namespaceLock;

extern ATOMIC_TYPE mal_running;

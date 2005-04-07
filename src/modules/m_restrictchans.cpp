/*       +------------------------------------+
 *       | Inspire Internet Relay Chat Daemon |
 *       +------------------------------------+
 *
 *  Inspire is copyright (C) 2002-2004 ChatSpike-Dev.
 *                       E-mail:
 *                <brain@chatspike.net>
 *           	  <Craig@chatspike.net>
 *     
 * Written by Craig Edwards, Craig McLure, and others.
 * This program is free but copyrighted software; see
 *            the file COPYING for details.
 *
 * ---------------------------------------------------
 */

#include <stdio.h>
#include "users.h"
#include "channels.h"
#include "modules.h"

/* $ModDesc: Only opers may create new channels if this module is loaded */

Server *Srv;
	 
class ModuleRestrictChans : public Module
{
 public:
	ModuleRestrictChans()
	{
		Srv = new Server;
	}
	
	virtual int OnUserPreJoin(userrec* user, chanrec* chan, const char* cname)
	{
		// user is not an oper
		if (!strchr(user->modes,'o'))
		{
			// channel does not yet exist (record is null, about to be created IF we were to allow it)
			if (!chan)
			{
				WriteServ(user->fd,"530 %s %s :Only IRC operators may create new channels",user->nick,cname,cname);
				return 1;
			}
		}
		return 0;
	}
	
    	virtual ~ModuleRestrictChans()
	{
		delete Srv;
	}
	
	virtual Version GetVersion()
	{
		return Version(1,0,0,0,0);
	}
};


class ModuleRestrictChansFactory : public ModuleFactory
{
 public:
	ModuleRestrictChansFactory()
	{
	}
	
	~ModuleRestrictChansFactory()
	{
	}
	
	virtual Module * CreateModule()
	{
		return new ModuleRestrictChans;
	}
	
};


extern "C" void * init_module( void )
{
	return new ModuleRestrictChansFactory;
}


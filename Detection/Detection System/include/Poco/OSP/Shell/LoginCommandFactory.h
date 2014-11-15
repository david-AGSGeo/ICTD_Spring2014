//
// LoginCommandFactory.h
//
// $Id: //poco/1.4/OSP/Shell/include/Poco/OSP/Shell/LoginCommandFactory.h#1 $
//
// Library: OSP/Shell
// Package: Shell
// Module:  LoginCommand
//
// Definition of the LoginCommandFactory class.
//
// Copyright (c) 2009, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef OSP_Shell_LoginCommandFactory_INCLUDED
#define OSP_Shell_LoginCommandFactory_INCLUDED


#include "Poco/OSP/Shell/CommandFactory.h"


namespace Poco {
namespace OSP {
namespace Shell {


class OSPShell_API LoginCommandFactory: public CommandFactory
	/// The factory for LoginCommand objects.
{
public:
	LoginCommandFactory();
		/// Creates the LoginCommandFactory.
		
	~LoginCommandFactory();
		/// Destroys the LoginCommandFactory.
		
	// CommandFactory
	Command* createCommand();
};


} } } // namespace Poco::OSP::Shell


#endif // OSP_Shell_LoginCommandFactory_INCLUDED

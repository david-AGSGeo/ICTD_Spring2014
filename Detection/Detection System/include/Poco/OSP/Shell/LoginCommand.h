//
// LoginCommand.h
//
// $Id: //poco/1.4/OSP/Shell/include/Poco/OSP/Shell/LoginCommand.h#1 $
//
// Library: OSP/Shell
// Package: Shell
// Module:  LoginCommand
//
// Definition of the LoginCommand class.
//
// Copyright (c) 2009, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef OSP_Shell_LoginCommand_INCLUDED
#define OSP_Shell_LoginCommand_INCLUDED


#include "Poco/OSP/Shell/AbstractCommand.h"
#include "Poco/OSP/BundleContext.h"


namespace Poco {
namespace OSP {
namespace Shell {


class OSPShell_API LoginCommand: public AbstractCommand
	/// LoginCommand implements the "login" command,
	/// with the help of the Session object.
	///
	/// The login command takes two arguments, a user
	/// name and a password, and passes them to the
	/// login() member function of Session.
	///
	/// The help text of the login command can be
	/// customized by providing the following bundle
	/// properties:
	///    - login.description: The description of the command.
	///    - login.usage: The usage string.
{
public:
	LoginCommand(Poco::OSP::BundleContext::Ptr pContext);
		/// Creates the LoginCommand.
		
	~LoginCommand();
		/// Destroys the LoginCommand.

protected:		
	// AbstractCommand
	virtual int executeImpl(Session& session, const std::vector<std::string>& args, std::ostream& ostr);
	
private:
	Poco::OSP::BundleContext::Ptr _pContext;
};


} } } // namespace Poco::OSP::Shell


#endif // OSP_Shell_LoginCommand_INCLUDED

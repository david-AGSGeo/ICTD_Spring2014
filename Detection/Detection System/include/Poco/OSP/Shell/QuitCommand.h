//
// QuitCommand.h
//
// $Id: //poco/1.4/OSP/Shell/include/Poco/OSP/Shell/QuitCommand.h#1 $
//
// Library: OSP/Shell
// Package: Shell
// Module:  QuitCommand
//
// Definition of the QuitCommand class.
//
// Copyright (c) 2009, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef OSP_Shell_QuitCommand_INCLUDED
#define OSP_Shell_QuitCommand_INCLUDED


#include "Poco/OSP/Shell/AbstractCommand.h"
#include "Poco/OSP/BundleContext.h"


namespace Poco {
namespace OSP {
namespace Shell {


class OSPShell_API QuitCommand: public AbstractCommand
	/// QuitCommand implements the "quit" command.
	///
	/// Executing the command returns a negative
	/// return code, which causes the ShellConnection
	/// object to close the connection.
	///
	/// The help text of the quit command can be
	/// customized by providing the following bundle
	/// properties:
	///    - quit.description: The description of the command.
	///    - quit.usage: The usage string.
{
public:
	QuitCommand(Poco::OSP::BundleContext::Ptr pContext);
		/// Creates the QuitCommand.
		
	~QuitCommand();
		/// Destroys the QuitCommand.

protected:		
	// AbstractCommand
	virtual int executeImpl(Session& session, const std::vector<std::string>& args, std::ostream& ostr);
	
private:
	Poco::OSP::BundleContext::Ptr _pContext;
};


} } } // namespace Poco::OSP::Shell


#endif // OSP_Shell_QuitCommand_INCLUDED

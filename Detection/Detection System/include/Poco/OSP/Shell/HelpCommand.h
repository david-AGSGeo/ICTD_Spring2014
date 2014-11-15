//
// HelpCommand.h
//
// $Id: //poco/1.4/OSP/Shell/include/Poco/OSP/Shell/HelpCommand.h#1 $
//
// Library: OSP/Shell
// Package: Shell
// Module:  HelpCommand
//
// Definition of the HelpCommand class.
//
// Copyright (c) 2009, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef OSP_Shell_HelpCommand_INCLUDED
#define OSP_Shell_HelpCommand_INCLUDED


#include "Poco/OSP/Shell/Command.h"
#include "Poco/OSP/BundleContext.h"


namespace Poco {
namespace OSP {
namespace Shell {


class CommandProcessor;


class OSPShell_API HelpCommand: public Command
	/// HelpCommand implements the "help" command,
	/// with the help of the CommandProcessor.
	///
	/// The help command produces a list of commands
	/// known by the CommandProcessor, as well as their aliases.
	///
	/// The output of the command can be customized with
	/// the following bundle properties:
	///   - help.header: the header text displayed before the list
	///     of commands.
	///   - help.footer: the footer text displayed after the list
	///     of commands.
{
public:
	HelpCommand(Poco::OSP::BundleContext::Ptr pContext, CommandProcessor& commandProcessor);
		/// Creates the HelpCommand, using the given command processor.
		
	~HelpCommand();
		/// Destroys the HelpCommand.
		
	// Command
	virtual int execute(Session& session, const std::vector<std::string>& args, std::ostream& ostr);

private:
	Poco::OSP::BundleContext::Ptr _pContext;
	CommandProcessor& _commandProcessor;
};


} } } // namespace Poco::OSP::Shell


#endif // OSP_Shell_HelpCommand_INCLUDED

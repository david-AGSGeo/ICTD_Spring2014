//
// HelpCommandFactory.h
//
// $Id: //poco/1.4/OSP/Shell/include/Poco/OSP/Shell/HelpCommandFactory.h#1 $
//
// Library: OSP/Shell
// Package: Shell
// Module:  HelpCommand
//
// Definition of the HelpCommandFactory class.
//
// Copyright (c) 2009, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef OSP_Shell_HelpCommandFactory_INCLUDED
#define OSP_Shell_HelpCommandFactory_INCLUDED


#include "Poco/OSP/Shell/CommandFactory.h"


namespace Poco {
namespace OSP {
namespace Shell {


class CommandProcessor;


class OSPShell_API HelpCommandFactory: public CommandFactory
	/// The factory for HelpCommand objects.
{
public:
	HelpCommandFactory(CommandProcessor& commandProcessor);
		/// Creates the HelpCommandFactory, using the given command processor.
		
	~HelpCommandFactory();
		/// Destroys the HelpCommandFactory.
		
	// CommandFactory
	Command* createCommand();

private:
	CommandProcessor& _commandProcessor;
};


} } } // namespace Poco::OSP::Shell


#endif // OSP_Shell_HelpCommandFactory_INCLUDED

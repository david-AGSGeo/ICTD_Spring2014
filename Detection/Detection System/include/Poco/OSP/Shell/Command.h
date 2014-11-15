//
// Command.h
//
// $Id: //poco/1.4/OSP/Shell/include/Poco/OSP/Shell/Command.h#1 $
//
// Library: OSP/Shell
// Package: Shell
// Module:  Command
//
// Definition of the Command class.
//
// Copyright (c) 2009, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef OSP_Shell_Command_INCLUDED
#define OSP_Shell_Command_INCLUDED


#include "Poco/OSP/Shell/Shell.h"
#include <vector>
#include <ostream>


namespace Poco {
namespace OSP {
namespace Shell {


class Session;


class OSPShell_API Command
	/// Command defines the interface every shell command must implement.
	///
	/// The interface is quite simple, consisting only of a single member
	/// function that subclasses must override.
{
public:
	enum CommandStatus
	{
		STATUS_OK     = 0, /// successful execution
		STATUS_USAGE  = 1, /// command line usage error
		STATUS_ERROR  = 2, /// command execution error
		STATUS_DENIED = 3  /// bad credentials or insufficient permissions to execute the command
	};
	
	Command();
		/// Creates the Command.
		
	virtual ~Command();
		/// Destroys the Command.
		
	virtual int execute(Session& session, const std::vector<std::string>& args, std::ostream& ostr) = 0;
		/// Execute the command, using the given arguments, within
		/// the given session.
		/// The first element of the args vector is the command name.
		///
		/// Any output produced by executing the command can be
		/// written to the given output stream.
		///
		/// An integer must be returned that denotes success or failure of the command.
		/// Upon success, 0 shall be returned. The CommandStatus enumeration defines
		/// a few commonly used error codes that should be used. Other statis codes in
		/// the range 0 - 99 can be used as well. Negative status codes are reserved
		/// for internal use.

private:
	Command(const Command&);
	Command& operator = (const Command&);
};


} } } // namespace Poco::OSP::Shell


#endif // OSP_Shell_Command_INCLUDED

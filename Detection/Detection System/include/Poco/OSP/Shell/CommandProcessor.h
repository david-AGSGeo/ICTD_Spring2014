//
// CommandProcessor.h
//
// $Id: //poco/1.4/OSP/Shell/include/Poco/OSP/Shell/CommandProcessor.h#1 $
//
// Library: OSP/Shell
// Package: Shell
// Module:  CommandProcessor
//
// Definition of the CommandProcessor class.
//
// Copyright (c) 2009, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef OSP_Shell_CommandProcessor_INCLUDED
#define OSP_Shell_CommandProcessor_INCLUDED


#include "Poco/OSP/Shell/Shell.h"
#include "Poco/OSP/Shell/CommandFactory.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/SharedPtr.h"
#include "Poco/Mutex.h"
#include <map>
#include <set>


namespace Poco {
namespace OSP {
namespace Shell {


class Session;


class OSPShell_API CommandProcessor
	/// The CommandProcessor parses command lines and invokes
	/// commands.
{
public:
	typedef Poco::SharedPtr<CommandFactory> FactoryPtr;

	CommandProcessor(Poco::OSP::BundleContext::Ptr pContext);
		/// Creates the CommandProcessor, using the given bundle context.

	~CommandProcessor();
		/// Destroys the CommandProcessor.

	int execute(Session& session, const std::string& commandLine, std::ostream& ostr);
		/// Executes the command given in commandLine in the given session.
		///
		/// Throws a Poco::NotFoundException if the given command
		/// is not known.
		///
		/// The following commands are builtin:
		///   - .login <userName> <credentials>: 
		///     Attempts to log the user into the current session with the given userName and credentials (password).
		///   - .help
		///     Displays a list of all registered commands.
		///   - .quit
		///     Ends the session.
		
	void addCommand(const std::string& command, const std::set<std::string>& aliases, FactoryPtr pFactory, const std::string& permission);
		/// Adds a command to the command processor.
		///
		/// The given command name must be unique, otherwise an ExistsException will be thrown.
		/// The given aliases set can be empty.
		/// Upon execution of the command, the given permission is checked against
		/// the current user's permissions. It can be empty to disable the check.

	void removeCommand(const std::string& command);
		/// Removes the given command.

	void removeBundle(Poco::OSP::Bundle::Ptr pBundle);
		/// Removes all commands defined by the given bundle.

	void listCommands(std::vector<std::string>& commands) const;
		/// Fills the given vector with the names of all registered commands.
		
	void aliases(const std::string& command, std::set<std::string>& aliases) const;
		/// Fills the given set with all aliases for the given command.

	Poco::OSP::BundleContext::Ptr context() const;
		/// Returns the BundleContext used by the CommandProcessor.

	static const std::string COMMAND_LOGIN;
	static const std::string COMMAND_HELP;
	static const std::string COMMAND_QUIT;

protected:
	Command* createCommand(const Session& session, const std::string& command);
		/// Creates a Command object for the given command name.
		///
		/// Throws a Poco::NotFoundException if the given command is unknown.
		/// Returns a new command object, or a null pointer if the user
		/// is not authorized to call the command.
		
	void parseCommandLine(const std::string& commandLine, std::vector<std::string>& items);
		/// Parses the command line into single items.
		///
		/// The first item is used as command name. Remaining items are arguments
		/// to the command. Items are separated by one or more space or tab characters.
		/// An item can be enclosed in single or double quotes.
		/// Characters can be escaped with a backslash.
		
private:
	struct CommandInfo
	{
		std::string name;
		std::set<std::string> aliases;
		std::string permission;
		FactoryPtr pFactory;
	};
	typedef std::map<std::string, CommandInfo> CommandMap;
	
	Poco::OSP::BundleContext::Ptr _pContext;
	CommandMap  _commandMap;
	mutable Poco::FastMutex _mutex;
};


//
// inlines
//
inline Poco::OSP::BundleContext::Ptr CommandProcessor::context() const
{
	return _pContext;
}


} } } // namespace Poco::OSP::Web


#endif // OSP_Shell_CommandProcessor_INCLUDED

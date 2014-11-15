//
// AbstractCommand.h
//
// $Id: //poco/1.4/OSP/Shell/include/Poco/OSP/Shell/AbstractCommand.h#1 $
//
// Library: OSP/Shell
// Package: Shell
// Module:  AbstractCommand
//
// Definition of the AbstractCommand class.
//
// Copyright (c) 2009, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef OSP_Shell_AbstractCommand_INCLUDED
#define OSP_Shell_AbstractCommand_INCLUDED


#include "Poco/OSP/Shell/Command.h"
#include "Poco/Util/OptionSet.h"


namespace Poco {
namespace OSP {
namespace Shell {


class OSPShell_API AbstractCommand: public Command
	/// AbstractCommand provides a partial implementation of Command,
	/// doing automatic argument handling based on the options handling
	/// framework from the Util library.
	///
	/// Options must be given in Unix-style syntax (-o or --option).
	///
	/// Option handling for commands works in a similar way to
	/// command line options handling in the Poco::Util::Application 
	/// class.
{
public:	
	// Command
	virtual int execute(Session& session, const std::vector<std::string>& args, std::ostream& ostr);

protected:
	AbstractCommand();
		/// Creates the AbstractCommand.

	AbstractCommand(const std::string& description, const std::string& usage);
		/// Creates the AbstractCommand, using the given description and usage hint.
		///
		/// The given description and usage hint is used in the help text given
		/// if the command is invoked with the --help option.
		
	virtual ~AbstractCommand();
		/// Destroys the AbstractCommand.
		
	virtual int executeImpl(Session& session, const std::vector<std::string>& args, std::ostream& ostr) = 0;
		/// Execute the command, using the given arguments.
		/// Called by AbstractCommand::execute() after options have been handled.
		///
		/// Any output produced by executing the command can be
		/// written to the given output stream.
		///
		/// An integer must be returned that denotes success or failure of the command.
		/// Upon success, 0 shall be returned. The CommandStatus enumeration defines
		/// a few commonly used error codes that should be used.

	virtual void defineOptions(Poco::Util::OptionSet& options);
		/// Called before command line processing begins.
		/// If a Command wants to support command line arguments,
		/// it must override this method and call the base class
		/// implementation as well.
		///
		/// The default implementation only defines the --help option.
		///
		/// A Command should specify a callback to handle the option.
		
	const Poco::Util::OptionSet& options() const;
		/// Returns the application's option set.

	void processOptions(std::vector<std::string>& args);
		/// Processes command-line options.
		
	void stopOptionsProcessing();
		/// If called from an option callback, stops all further
		/// options processing.
		///
		/// If called, the following options on the command line
		/// will not be processed, and required options will not
		/// be checked.
		///
		/// This is useful, for example, if an option for displaying
		/// help information has been encountered and no other things
		/// besides displaying help shall be done.
	
	virtual void handleOption(const std::string& name, const std::string& value);
		/// Called when the option with the given name is encountered
		/// during command line arguments processing.
		///
		/// The default implementation does option validation, bindings
		/// and callback handling.
		///
		/// Overriding implementations must call the base class implementation.

	const std::string& commandName() const;
		/// Returns the command name.

	void handleHelp(const std::string& name, const std::string& value);
		/// Handles the --help command line option.
		
	void displayHelp(std::ostream& ostr);
		/// Writes a help text to the given stream.
	
private:	
	std::string           _description;
	std::string           _usage;
	Poco::Util::OptionSet _options;
	bool                  _stopOptionsProcessing;
	bool                  _showHelp;
	std::string           _commandName;
};


//
// inlines
//
inline const Poco::Util::OptionSet& AbstractCommand::options() const
{
	return _options;
}


inline const std::string& AbstractCommand::commandName() const
{
	return _commandName;
}


} } } // namespace Poco::OSP::Shell


#endif // OSP_Shell_AbstractCommand_INCLUDED

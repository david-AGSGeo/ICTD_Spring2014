//
// ShellConnectionFactory.h
//
// $Id: //poco/1.4/OSP/Shell/include/Poco/OSP/Shell/ShellConnectionFactory.h#1 $
//
// Library: OSP/Shell
// Package: Shell
// Module:  ShellConnection
//
// Definition of the ShellConnectionFactory class.
//
// Copyright (c) 2009, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef OSP_Shell_ShellConnectionFactory_INCLUDED
#define OSP_Shell_ShellConnectionFactory_INCLUDED


#include "Poco/OSP/Shell/Shell.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/Net/TCPServerConnectionFactory.h"


namespace Poco {
namespace OSP {
namespace Shell {


class CommandProcessor;


class OSPShell_API ShellConnectionFactory: public Poco::Net::TCPServerConnectionFactory
	/// The factory for ShellConnection objects.
{
public:
	ShellConnectionFactory(CommandProcessor& processor, const std::string& authServiceName);
		/// Creates the ShellConnectionFactory.
		
	~ShellConnectionFactory();
		/// Destroys the ShellConnectionFactory.
		
	// TCPServerConnectionFactory
	Poco::Net::TCPServerConnection* createConnection(const Poco::Net::StreamSocket& socket);

private:
	ShellConnectionFactory();
	
	CommandProcessor& _commandProcessor;
	std::string _authServiceName;
};


} } } // namespace Poco::OSP::Shell


#endif // OSP_Shell_ShellConnectionFactory_INCLUDED

//
// QuitCommandFactory.h
//
// $Id: //poco/1.4/OSP/Shell/include/Poco/OSP/Shell/QuitCommandFactory.h#1 $
//
// Library: OSP/Shell
// Package: Shell
// Module:  QuitCommand
//
// Definition of the QuitCommandFactory class.
//
// Copyright (c) 2009, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef OSP_Shell_QuitCommandFactory_INCLUDED
#define OSP_Shell_QuitCommandFactory_INCLUDED


#include "Poco/OSP/Shell/CommandFactory.h"


namespace Poco {
namespace OSP {
namespace Shell {


class OSPShell_API QuitCommandFactory: public CommandFactory
	/// The factory for QuitCommand objects.
{
public:
	QuitCommandFactory();
		/// Creates the QuitCommandFactory.
		
	~QuitCommandFactory();
		/// Destroys the QuitCommandFactory.
		
	// CommandFactory
	Command* createCommand();
};


} } } // namespace Poco::OSP::Shell


#endif // OSP_Shell_QuitCommandFactory_INCLUDED

//
// CommandFactory.h
//
// $Id: //poco/1.4/OSP/Shell/include/Poco/OSP/Shell/CommandFactory.h#1 $
//
// Library: OSP/Shell
// Package: Shell
// Module:  CommandFactory
//
// Definition of the CommandFactory class.
//
// Copyright (c) 2009, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef OSP_Shell_CommandFactory_INCLUDED
#define OSP_Shell_CommandFactory_INCLUDED


#include "Poco/OSP/Shell/Shell.h"
#include "Poco/OSP/BundleContext.h"


namespace Poco {
namespace OSP {
namespace Shell {


class Command;


class OSPShell_API CommandFactory
	/// A factory for Command objects.
{
public:
	CommandFactory();
		/// Creates the CommandFactory.
		
	virtual ~CommandFactory();
		/// Destroys the CommandFactory.
		
	virtual Command* createCommand() = 0;
		/// Create a Command object.

	void init(Poco::OSP::BundleContext::Ptr pContext);
		/// Initializes the factory with the given BundleContext.

	Poco::OSP::BundleContext::Ptr context() const;
		/// Returns the context. The pointer is guaranteed to be valid.

protected:	
	virtual void initImpl();
		/// Add extra initialization code by overriding this method in your subclass.

private:
	CommandFactory(const CommandFactory&);
	CommandFactory& operator = (const CommandFactory&);
	
	BundleContext::Ptr _pContext;
};


//
// inlines
//
inline Poco::OSP::BundleContext::Ptr CommandFactory::context() const
{
	return _pContext;
}


} } } // namespace Poco::OSP::Shell


#endif // OSP_Shell_CommandFactory_INCLUDED

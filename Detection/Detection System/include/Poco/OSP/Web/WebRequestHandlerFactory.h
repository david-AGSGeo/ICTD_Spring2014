//
// WebRequestHandlerFactory.h
//
// $Id: //poco/1.4/OSP/Web/include/Poco/OSP/Web/WebRequestHandlerFactory.h#1 $
//
// Library: OSP/Web
// Package: Web
// Module:  WebRequestHandlerFactory
//
// Definition of the WebRequestHandlerFactory class.
//
// Copyright (c) 2007, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef OSP_Web_WebRequestHandlerFactory_INCLUDED
#define OSP_Web_WebRequestHandlerFactory_INCLUDED


#include "Poco/OSP/Web/Web.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/OSP/BundleContext.h"


namespace Poco {
namespace OSP {
namespace Web {


class OSPWeb_API WebRequestHandlerFactory: public Poco::Net::HTTPRequestHandlerFactory
	/// WebRequestHandlerFactory is a HTTPRequestHandlerFactory that was extended
	/// to allow RequestHandlers easy access to the SessionManager and the owner's BundleContext.
{
public:
	WebRequestHandlerFactory();
		/// Creates the unintialized WebRequestHandlerFactory. The default constructor is called
		/// by the classloader (which requires a default constructor) followed by a call to init.

	~WebRequestHandlerFactory();
		/// Destroys the WebRequestHandlerFactory.

	void init(BundleContext::Ptr pContext);
		/// Initializes the object with the given BundleContext.

protected:
	BundleContext::Ptr context() const;
		/// Returns the context. The pointer is guaranteed to be valid.

	virtual void initImpl();
		/// Add extra initialization code by overriding this method in your subclass.

private:
	BundleContext::Ptr _pContext;
};


//
// inlines
//
inline BundleContext::Ptr WebRequestHandlerFactory::context() const
{
	return _pContext;
}


} } } // namespace Poco::OSP::Web


#endif // OSP_Web_WebRequestHandlerFactory_INCLUDED

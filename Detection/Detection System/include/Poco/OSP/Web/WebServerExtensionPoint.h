//
// WebServerExtensionPoint.h
//
// $Id: //poco/1.4/OSP/Web/include/Poco/OSP/Web/WebServerExtensionPoint.h#1 $
//
// Library: OSP/Web
// Package: Web
// Module:  WebServerExtensionPoint
//
// Definition of the WebServerExtensionPoint class.
//
// Copyright (c) 2007, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef OSP_Web_WebServerExtensionPoint_INCLUDED
#define OSP_Web_WebServerExtensionPoint_INCLUDED


#include "Poco/OSP/Web/Web.h"
#include "Poco/OSP/Web/WebServerDispatcher.h"
#include "Poco/OSP/Web/WebRequestHandlerFactory.h"
#include "Poco/OSP/ExtensionPoint.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/ClassLoader.h"
#include "Poco/Mutex.h"
#include "Poco/SharedPtr.h"
#include <map>


namespace Poco {
namespace OSP {
namespace Web {


class OSPWeb_API WebServerExtensionPoint: public ExtensionPoint
	/// WebServerExtension handles two extensions points.
	/// To register a directory in the Webserver:
	///     <extension point="osp.web.server.directory" 
	///                path="URI" 
	///                resource="dir inside bundle" 
	///                allowSpecialization="none|owner|all"
	///                index="index.html"/>
	///
	/// To register a RequestHandlerFactory for a given server uri/set of uris:
	///     <extension point="osp.web.server.requesthandler" 
	///                path="URI"
	///                class="MyRequestHandlerFactory" 
	///                library="MyLib"/>
	///
	/// Note that the extension points are automatically removed if a bundle is stopped.
	///
	/// The following attributes can be specified for both extension points:
	///    * path: the URI on the server to which the resource or handler is mapped
	///    * description: user-readable description of resource or handler
	///    * secure: if "true", require a secure (HTTPS) connection to access the resource
	///    * realm: specify authentication realm (together with permission)
	///    * permission: specify the necessary access permission for this resource.
	///                  HTTP Basic Authentication is used to obtain the user's
	///                  user name and password, which are then checked against
	///                  the specified permission using the authorization service.
	///    * hidden: if "true", path is not included by WebServerDispatcher::listVirtualPaths()
	///
	/// The following attributes can be specified for "osp.web.server.directory":
	///    * resource: specify a directory within the bundle where the HTML, image
	///                and other files are located.
	///    * index:    specify the name of the default document (defaults to "index.html").
	///
	/// The following attributes can be specified for "osp.web.server.requesthandler":
	///    * class: the class name of the request handler factory.
	///    * library: the name of the shared library containing the request handler factory. 
{
public:
	WebServerExtensionPoint(BundleContext::Ptr pContext, WebServerDispatcher* pDispatcher);
		/// Creates the WebServerExtension. Expects a not null pointer to the Web which must be valid during the whole
		/// life-time of the extension object

	~WebServerExtensionPoint();
		/// Destroys the WebServerExtension.

	// ExtensionPoint
	void handleExtension(Bundle::ConstPtr pBundle, Poco::XML::Element* pExtensionElem);

	static const std::string EXTPOINT_DIRECTORY;
	static const std::string EXTPOINT_HANDLER;

protected:
	void handleDirectory(Bundle::ConstPtr pBundle, Poco::XML::Element* pExtensionElem);
	void handleRequestHandler(Bundle::ConstPtr pBundle, Poco::XML::Element* pExtensionElem);
	void handleCommon(Bundle::ConstPtr pBundle, Poco::XML::Element* pExtensionElem, WebServerDispatcher::VirtualPath& vPath);

	void onBundleStopped(const void* pSender, BundleEvent& ev);
		/// When a bundle is stopped, all of its request handlers and mappings are automatically disabled.

	static const std::string ATTR_PATH;
	static const std::string ATTR_DESCRIPTION;
	static const std::string ATTR_SECURE;
	static const std::string ATTR_REALM;
	static const std::string ATTR_PERMISSION;
	static const std::string ATTR_RESOURCE;
	static const std::string ATTR_CLASS;
	static const std::string ATTR_LIBRARY;
	static const std::string ATTR_ALLOWSPECIALIZATION;
	static const std::string ATTR_INDEX;
	static const std::string ATTR_HIDDEN;
	static const std::string MANIFEST_NAME;

private:
	WebServerExtensionPoint();
	
	typedef Poco::SharedPtr<WebRequestHandlerFactory> FactoryPtr;
	typedef Poco::ClassLoader<WebRequestHandlerFactory> Loader;
	typedef std::map<std::string, Bundle::Ptr> LibBundleMap;
	
	BundleContext::Ptr   _pContext;
	WebServerDispatcher* _pDispatcher;
	Loader               _loader;
	LibBundleMap         _libBundleMap;
	Poco::FastMutex      _mutex;
};


} } } // namespace Poco::OSP::Web


#endif // OSP_Web_WebServerExtensionPoint_INCLUDED

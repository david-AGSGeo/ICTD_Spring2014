//
// Session.h
//
// $Id: //poco/1.4/OSP/Shell/include/Poco/OSP/Shell/Session.h#1 $
//
// Library: OSP/Shell
// Package: Shell
// Module:  Session
//
// Definition of the Session class.
//
// Copyright (c) 2009, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef OSP_Shell_Session_INCLUDED
#define OSP_Shell_Session_INCLUDED


#include "Poco/OSP/Shell/Shell.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/Auth/AuthService.h"


namespace Poco {
namespace OSP {
namespace Shell {


class OSPShell_API Session
	/// The Session class provides user authentication and
	/// authorization for the CommandProcessor.
	///
	/// It is also passed as the first argument to
	/// the execute() member function of Command, so
	/// that command implementations can perform
	/// custom authorization.
{
public:
	Session(Poco::OSP::BundleContext::Ptr pContext, const std::string& authServiceName);
		/// Creates the Session, using the given bundle context and
		/// the given service name of the authentication service.
		///
		/// An empty service name disables authentication and authorization.

	~Session();
		/// Destroys the Session.

	bool login(const std::string& userName, const std::string& credentials);
		/// Attempts to authenticate the user by checking the
		/// given userName and credentials with the authentication service.
		///
		/// Returns true if the user was successfully authenticated, false otherwise.
	
	bool authorize(const std::string& permission) const;
		/// Returns true if the user is authenticated and has the
		/// given permission, false otherwise.
	
	bool authenticated() const;
		/// Returns true if the user is authenticated.
	
	const std::string& user() const;
		/// Returns the name of the current user, or an empty string
		/// if no user is logged in.

protected:
	Poco::OSP::Auth::AuthService::Ptr authService() const;

private:
	Session();
	Session(const Session&);
	Session& operator = (const Session&);
	
	Poco::OSP::BundleContext::Ptr _pContext;
	std::string _authServiceName;
	mutable Poco::OSP::Auth::AuthService::Ptr _pAuthService;
	std::string _userName;
	bool _authenticated;
};


//
// inlines
//
inline bool Session::authenticated() const
{
	return _authenticated;
}


inline const std::string& Session::user() const
{
	return _userName;
}


} } } // namespace Poco::OSP::Web


#endif // OSP_Shell_Session_INCLUDED

//
// RemotingException.h
//
// $Id: //poco/1.4/RemotingNG/include/Poco/RemotingNG/RemotingException.h#2 $
//
// Library: RemotingNG
// Package: RemotingNG
// Module:  RemotingException
//
// Definition of the RemotingException class.
//
// Copyright (c) 2006-2011, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef RemotingNG_RemotingException_INCLUDED
#define RemotingNG_RemotingException_INCLUDED


#include "Poco/RemotingNG/RemotingNG.h"
#include "Poco/Exception.h"


namespace Poco {
namespace RemotingNG {


POCO_DECLARE_EXCEPTION(RemotingNG_API, RemotingException, Poco::LogicException)
POCO_DECLARE_EXCEPTION(RemotingNG_API, TransportException, RemotingException)
POCO_DECLARE_EXCEPTION(RemotingNG_API, ProtocolException, RemotingException)
POCO_DECLARE_EXCEPTION(RemotingNG_API, RemoteException, RemotingException)
POCO_DECLARE_EXCEPTION(RemotingNG_API, SerializerException, RemotingException)
POCO_DECLARE_EXCEPTION(RemotingNG_API, DeserializerException, RemotingException)
POCO_DECLARE_EXCEPTION(RemotingNG_API, UnknownTransportException, RemotingException)
POCO_DECLARE_EXCEPTION(RemotingNG_API, UnknownTypeException, RemotingException)
POCO_DECLARE_EXCEPTION(RemotingNG_API, UnknownObjectException, RemotingException)
POCO_DECLARE_EXCEPTION(RemotingNG_API, ORBDisabledException, RemotingException)
POCO_DECLARE_EXCEPTION(RemotingNG_API, MissingParamException, DeserializerException)
POCO_DECLARE_EXCEPTION(RemotingNG_API, WrongReplyException, DeserializerException)
POCO_DECLARE_EXCEPTION(RemotingNG_API, UnexpectedMessageException, DeserializerException)
POCO_DECLARE_EXCEPTION(RemotingNG_API, MethodNotFoundException, DeserializerException)


} } // namespace Poco::RemotingNG


#endif // RemotingNG_RemotingException_INCLUDED

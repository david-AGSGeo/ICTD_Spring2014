//
// XSDException.h
//
// $Id: //poco/1.4/XSD/Types/include/Poco/XSD/Types/XSDException.h#1 $
//
// Library: XSD/Types
// Package: XSDTypes
// Module:  XSDException
//
// Definition of the XSDException class.
//
// Copyright (c) 2008-2012, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef XSDTypes_XSDException_INCLUDED
#define XSDTypes_XSDException_INCLUDED


#include "Poco/XSD/Types/XSDTypes.h"
#include "Poco/Exception.h"


namespace Poco {
namespace XSD {
namespace Types {


POCO_DECLARE_EXCEPTION(XSDTypes_API, XSDException, Exception)
POCO_DECLARE_EXCEPTION(XSDTypes_API, TypeException, XSDException)
POCO_DECLARE_EXCEPTION(XSDTypes_API, SchemaException, XSDException)
POCO_DECLARE_EXCEPTION(XSDTypes_API, IllegalOrderException, SchemaException)
POCO_DECLARE_EXCEPTION(XSDTypes_API, ElementException, XSDException)
POCO_DECLARE_EXCEPTION(XSDTypes_API, NullTypeException, TypeException)
POCO_DECLARE_EXCEPTION(XSDTypes_API, InvalidTypeException, TypeException)
POCO_DECLARE_EXCEPTION(XSDTypes_API, TypeAlreadyDefinedException, TypeException)
POCO_DECLARE_EXCEPTION(XSDTypes_API, NullElementException, ElementException)
POCO_DECLARE_EXCEPTION(XSDTypes_API, InvalidElementException, ElementException)
POCO_DECLARE_EXCEPTION(XSDTypes_API, ElementAlreadyDefinedException, ElementException)


} } } // namespace Poco::XSD::Types


#endif // XSDTypes_XSDException_INCLUDED

//
// XSDParser.h
//
// $Id: //poco/1.4/XSD/Parser/include/Poco/XSD/Parser/XSDParser.h#4 $
//
// Library: XSD/Parser
// Package: XSDParser
// Module:  XSDParser
//
// Basic definitions for the Poco XSDParser library.
// This file must be the first file included by every other XSDParser
// header file.
//
// Copyright (c) 2008-2012, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef XSDParser_XSDParser_INCLUDED
#define XSDParser_XSDParser_INCLUDED


#include "Poco/Foundation.h"
#include <map>


//
// The following block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the XSDParser_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// XSDParser_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
//
#if defined(_WIN32) && defined(POCO_DLL)
	#if defined(XSDParser_EXPORTS)
		#define XSDParser_API __declspec(dllexport)
	#else
		#define XSDParser_API __declspec(dllimport)
	#endif
#endif


#if !defined(XSDParser_API)
	#define XSDParser_API
#endif


//
// Automatically link XSDParser library.
//
#if defined(_MSC_VER)
	#if !defined(POCO_NO_AUTOMATIC_LIBS) && !defined(XSDParser_EXPORTS)
		#pragma comment(lib, "PocoXSDParser" POCO_LIB_SUFFIX)
	#endif
#endif


namespace Poco {
namespace XSD {
namespace Parser {


typedef std::map<std::string, const std::string> CompactAttributes; // maps attrname to value


} } } // namespace Poco::XSD::Parser


#endif // XSDParser_XSDParser_INCLUDED

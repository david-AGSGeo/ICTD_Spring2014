//
// ServiceDesc.h
//
// $Id: //poco/1.4/UPnP/ServiceDesc/include/Poco/UPnP/ServiceDesc/ServiceDesc.h#1 $
//
// Library: UPnP/ServiceDesc
// Package: ServiceDesc
// Module:  ServiceDesc
//
// Basic definitions for the Poco UPnP ServiceDesc library.
// This file must be the first file included by every other UPnP ServiceDesc
// header file.
//
// Copyright (c) 2011-2013, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef UPnP_ServiceDesc_ServiceDesc_INCLUDED
#define UPnP_ServiceDesc_ServiceDesc_INCLUDED


#include "Poco/UPnP/UPnP.h"


//
// The following block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the UPnP_ServiceDesc_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// UPnP_ServiceDesc_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
//
#if defined(_WIN32) && defined(POCO_DLL)
	#if defined(UPnP_ServiceDesc_EXPORTS)
		#define UPnP_ServiceDesc_API __declspec(dllexport)
	#else
		#define UPnP_ServiceDesc_API __declspec(dllimport)
	#endif
#endif


#if !defined(UPnP_ServiceDesc_API)
	#define UPnP_ServiceDesc_API
#endif


//
// Automatically link UPnPServiceDesc library.
//
#if defined(_MSC_VER)
	#pragma warning(disable:4503) // decorated name length exceeded

	#if !defined(POCO_NO_AUTOMATIC_LIBS) && !defined(UPnP_ServiceDesc_EXPORTS)
		#pragma comment(lib, "PocoUPnPServiceDesc" POCO_LIB_SUFFIX)
	#endif
#endif


#endif // UPnP_ServiceDesc_ServiceDesc_INCLUDED

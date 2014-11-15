//
// SSDP.h
//
// $Id: //poco/1.4/UPnP/SSDP/include/Poco/UPnP/SSDP/SSDP.h#2 $
//
// Library: UPnP/SSDP
// Package: SSDP
// Module:  SSDP
//
// Basic definitions for the Poco UPnP SSDP library.
// This file must be the first file included by every other UPnP SSDP
// header file.
//
// Copyright (c) 2008-2010, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef UPnP_SSDP_SSDP_INCLUDED
#define UPnP_SSDP_SSDP_INCLUDED


#include "Poco/UPnP/UPnP.h"


//
// The following block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the UPnP_SSDP_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// UPnP_SSDP_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
//
#if defined(_WIN32) && defined(POCO_DLL)
	#if defined(UPnP_SSDP_EXPORTS)
		#define UPnP_SSDP_API __declspec(dllexport)
	#else
		#define UPnP_SSDP_API __declspec(dllimport)
	#endif
#endif


#if !defined(UPnP_SSDP_API)
	#define UPnP_SSDP_API
#endif


//
// Automatically link UPnPSSDP library.
//
#if defined(_MSC_VER)
	#pragma warning(disable:4503) // decorated name length exceeded

	#if !defined(POCO_NO_AUTOMATIC_LIBS) && !defined(UPnP_SSDP_EXPORTS)
		#pragma comment(lib, "PocoUPnPSSDP" POCO_LIB_SUFFIX)
	#endif
#endif


#endif // UPnP_SSDP_SSDP_INCLUDED

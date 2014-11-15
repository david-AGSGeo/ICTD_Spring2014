//
// GENA.h
//
// $Id: //poco/1.4/UPnP/GENA/include/Poco/UPnP/GENA/GENA.h#1 $
//
// Library: UPnP/GENA
// Package: GENA
// Module:  GENA
//
// Basic definitions for the UPnP GENA library.
// This file must be the first file included by every other GENA
// header file.
//
// Copyright (c) 2008-2011, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef UPnP_GENA_GENA_INCLUDED
#define UPnP_GENA_GENA_INCLUDED


#include "Poco/Foundation.h"


//
// The following block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the GENA_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// GENA_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
//
#if defined(_WIN32) && defined(POCO_DLL)
	#if defined(UPnPGENA_EXPORTS)
		#define UPnPGENA_API __declspec(dllexport)
	#else
		#define UPnPGENA_API __declspec(dllimport)
	#endif
#endif


#if !defined(UPnPGENA_API)
	#define UPnPGENA_API
#endif


//
// Automatically link UPnPGENA library.
//
#if defined(_MSC_VER)
	#if !defined(POCO_NO_AUTOMATIC_LIBS) && !defined(UPnPGENA_EXPORTS)
		#pragma comment(lib, "PocoUPnPGENA" POCO_LIB_SUFFIX)
	#endif
#endif


#endif // UPnP_GENA_GENA_INCLUDED

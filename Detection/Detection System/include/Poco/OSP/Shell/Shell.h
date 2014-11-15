//
// Shell.h
//
// $Id: //poco/1.4/OSP/Shell/include/Poco/OSP/Shell/Shell.h#1 $
//
// Library: OSP/Shell
// Package: Shell
// Module:  Shell
//
// Basic definitions for the Poco OSP Shell library.
// This file must be the first file included by every other OSP Shell
// header file.
//
// Copyright (c) 2009, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef OSP_Shell_Shell_INCLUDED
#define OSP_Shell_Shell_INCLUDED


#include "Poco/OSP/OSP.h"


//
// The following block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the OSPShell_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// OSPShell_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
//
#if defined(_WIN32) && defined(POCO_DLL)
	#if defined(OSPShell_EXPORTS)
		#define OSPShell_API __declspec(dllexport)
	#else
		#define OSPShell_API __declspec(dllimport)
	#endif
#endif


#if !defined(OSPShell_API)
	#define OSPShell_API
#endif


//
// Automatically link OSP Shell library.
//
#if defined(_MSC_VER)
	#if !defined(POCO_NO_AUTOMATIC_LIBS) && !defined(OSPShell_EXPORTS)
		#if defined(POCO_DLL)
			#if defined(_DEBUG)
				#pragma comment(lib, "PocoOSPShelld.lib")
			#else
				#pragma comment(lib, "PocoOSPShell.lib")
			#endif
		#endif
	#endif
#endif


// Turn off some annoying warnings
#if defined(_MSC_VER)
	#pragma warning(disable:4503) // decorated name length exceeded, name was truncated
#endif


#endif // OSP_Shell_Shell_INCLUDED

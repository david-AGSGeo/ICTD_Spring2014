//
// FastInfoset.h
//
// $Id: //poco/1.4/FastInfoset/include/Poco/FastInfoset/FastInfoset.h#2 $
//
// Library: FastInfoset
// Package: FastInfoset
// Module:  FastInfoset
//
// Basic definitions for the Poco FastInfoset library.
// This file must be the first file included by every other FastInfoset
// header file.
//
// Copyright (c) 2006-2010, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics
// Software Engineering GmbH.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part, without
// prior written permission from Applied Informatics.
//


#ifndef FastInfoset_FastInfoset_INCLUDED
#define FastInfoset_FastInfoset_INCLUDED


#include "Poco/Foundation.h"


//
// The following block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the FastInfoset_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// FastInfoset_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
//
#if (defined(_WIN32) || defined(__CYGWIN__)) && defined(POCO_DLL)
	#if defined(FastInfoset_EXPORTS)
		#define FastInfoset_API __declspec(dllexport)
	#else
		#define FastInfoset_API __declspec(dllimport)
	#endif
#endif


#if !defined(FastInfoset_API)
	#define FastInfoset_API
#endif


//
// Automatically link Fast Infoset library.
//
#if defined(_MSC_VER)
	#if !defined(POCO_NO_AUTOMATIC_LIBS) && !defined(FastInfoset_EXPORTS)
		#pragma comment(lib, "PocoFastInfoset" POCO_LIB_SUFFIX)
	#endif
#endif


#endif // FastInfoset_FastInfoset_INCLUDED

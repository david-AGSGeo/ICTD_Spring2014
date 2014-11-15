//
// Exception.h
//
// $Id: //poco/1.4/FastInfoset/include/Poco/FastInfoset/FISException.h#1 $
//
// Library: FastInfoset
// Package: FastInfoset
// Module:  Exception
//
// Definition of the XMLException class.
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


#ifndef FastInfoset_FISException_INCLUDED
#define FastInfoset_FISException_INCLUDED


#include "Poco/FastInfoset/FastInfoset.h"
#include "Poco/Exception.h"


namespace Poco {
namespace FastInfoset {


POCO_DECLARE_EXCEPTION(FastInfoset_API, FISException, Poco::RuntimeException)
POCO_DECLARE_EXCEPTION(FastInfoset_API, FISParseException, FISException)
POCO_DECLARE_EXCEPTION(FastInfoset_API, FISEncodingException, FISException)


} } // namespace Poco::FastInfoset


#endif 

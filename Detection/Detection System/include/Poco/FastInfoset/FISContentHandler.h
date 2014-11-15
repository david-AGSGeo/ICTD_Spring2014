//
// FISContentHandler.h
//
// $Id: //poco/1.4/FastInfoset/include/Poco/FastInfoset/FISContentHandler.h#1 $
//
// Library: FastInfoset
// Package: SAX
// Module:  FISContentHandler
//
// Definition of the FISContentHandler class.
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


#ifndef FastInfoset_FISContentHandler_INCLUDED
#define FastInfoset_FISContentHandler_INCLUDED


#include "Poco/FastInfoset/FastInfoset.h"
#include "Poco/SAX/ContentHandler.h"
#include "Poco/UUID.h"
#include <cstdlib>


namespace Poco {
namespace FastInfoset {


class FastInfoset_API FISContentHandler: public Poco::XML::ContentHandler
	/// FISContentHandler extends the XML ContentHandler with type specific character chunks.
	///
	/// Using a FISContentHandler registered with a FastInfosetParser, 
	/// an application can read data from a Fast Infoset document in binary encoded form.
	///
	/// Using the FISContentHandler interface of a FastInfosetWriter, an application
	/// can directly write encoded or binary data.
{
public:
	virtual void binaryData(const char* buffer, std::size_t size) = 0;
		/// Handle binary data.
		
	virtual void encodedData(Poco::Int16 value) = 0;
		/// Handle a 16-bit signed integer value.
				
	virtual void encodedData(Poco::Int32 value) = 0;
		/// Handle a 32-bit signed integer value.

	virtual void encodedData(Poco::Int64 value) = 0;
		/// Handle a 64-bit signed integer value.

	virtual void encodedData(bool value) = 0;
		/// Handle a boolean value.
		
	virtual void encodedData(float value) = 0;
		/// Handle a single-precision floating point value.
		
	virtual void encodedData(double value) = 0;
		/// Handle a double-precision floating point value.
		
	virtual void encodedData(const Poco::UUID& uuid) = 0;
		/// Handle a UUID.

protected:
	~FISContentHandler();
};


} } // namespace Poco::FastInfoset


#endif // FastInfoset_FISContentHandler_INCLUDED

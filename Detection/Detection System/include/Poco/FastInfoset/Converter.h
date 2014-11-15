//
// Converter.h
//
// $Id: //poco/1.4/FastInfoset/include/Poco/FastInfoset/Converter.h#2 $
//
// Library: FastInfoset
// Package: FastInfoset
// Module:  Converter
//
// Definition of the Converter class.
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


#ifndef FastInfoset_Converter_INCLUDED
#define FastInfoset_Converter_INCLUDED


#include "Poco/FastInfoset/FastInfoset.h"


namespace Poco {
namespace FastInfoset {


class FastInfoset_API Converter
	/// The Converter class provides convenience methods
	/// for converting from Fast Infoset to XML and vice 
	/// versa.
{
public:
	enum ConversionOptions
	{
		CONV_WRITE_XML_DECLARATION       = 0x01,
			/// Write an XML declaration at the beginning
			/// of the resulting XML document.

		CONV_PRETTY_PRINT_XML            = 0x02,
			/// Pretty-print (indent) the resulting
			/// XML document.
			
		CONV_REMOVE_IGNORABLE_WHITESPACE = 0x81
			/// Remove all whitespace-only character content
			/// between elements.			
	};

	static void convertToFIS(std::istream& xmlInput, std::ostream& fisOutput, int maxIndexedStringLength = 16, int options = 0);
		/// Converts an XML input stream into a FIS output stream, throws an exception if
		/// an error occurs while parsing the XML or writing the FIS document.
		///
		/// maxIndexedStringLength specifies the maximum length of strings entered into the vocabulary.
		/// Specifying a higher value results in potentially smaller FIS documents at the
		/// expense of higher memory usage during conversion.
		///
		/// The CONV_REMOVE_IGNORABLE_WHITESPACE option can be specified to remove all
		/// whitespace-only character content between elements.

	static void convertToXML(std::istream& fisInput, std::ostream& xmlOutput, int options = 0);
		/// Converts an FIS input stream into a XML output stream, throws an exception if
		/// an error occurs while parsing the FIS or writing the XML document.
		///
		/// The CONV_PRETTY_PRINT_XML option can be specified to pretty-print
		/// the resulting XML document. The CONV_WRITE_XML_DECLARATION can be
		/// specified to write an XML declaration at the beginning of the 
		/// resulting XML document.
};


} } // namespace Poco::FastInfoset


#endif // FastInfoset_Converter_INCLUDED

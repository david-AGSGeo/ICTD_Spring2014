//
// Encoding.h
//
// $Id: //poco/1.4/FastInfoset/include/Poco/FastInfoset/Encoding.h#1 $
//
// Library: FastInfoset
// Package: CodingAlgorithm
// Module:  Encoding
//
// Definition of the Encoding class.
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


#ifndef FastInfoset_Encoding_INCLUDED
#define FastInfoset_Encoding_INCLUDED


#include "Poco/FastInfoset/FastInfoset.h"
#include "Poco/SAX/ContentHandler.h"
#include "Poco/AutoPtr.h"
#include "Poco/RefCountedObject.h"
#include <cstdlib>


namespace Poco {
namespace FastInfoset {


class BitStreamReader;
class BitStreamWriter;
class FISContentHandler;


class FastInfoset_API Encoding: public Poco::RefCountedObject
	/// The base class for all encoding algorithms.
	///
	/// An encoding algorithm is responsible for writing
	/// data in encoded form to a FIS document, and for
	/// reading encoded data from a FIS document.
	///
	/// It also provides facilities for converting
	/// encoded data into text and vice versa.
{
public:
	typedef Poco::AutoPtr<Encoding> Ptr;

	typedef Poco::Int32 (*CheckMethod)(const std::string&);
		/// Test if the encoding can encode the given string.
		/// If yes, returns the size of the encoded data, otherwise
		/// a value < 0.
		
	typedef void (*EncodeMethod)(BitStreamWriter&, const std::string&);
		/// Encode the given in the string and write the encoded data
		/// using the writer.

	typedef Encoding::Ptr (*DecodeMethod)(BitStreamReader& reader);
		/// Decodes data from the reader into the returned Encoding object
		/// for which it is guaranteed that createContent was called.

	Encoding();
		/// Creates the Encoding.

	explicit Encoding(const std::string& content);
		/// Creates the Encoding using the given content.
		
	Encoding(const char* data, std::size_t length);
		/// Creates the Encoding using the given content.

	virtual ~Encoding();
		/// Destroys the Encoding.

	virtual Poco::UInt32 type() const = 0;
		/// Returns the encoding type.

	virtual bool merge(const Encoding& enc) = 0;
		/// Merges the given encoding into the current one iff 
		/// the two encoding types are identical.

	virtual void write(BitStreamWriter& writer) const = 0;
		/// Writes the internally stored data to the writer.

	virtual DecodeMethod decodeMethod() const = 0;
		/// Returns the decode method.

	virtual CheckMethod checkMethod() const = 0;
		/// Returns the check method.

	virtual EncodeMethod encodeMethod() const = 0;
		/// Returns the encode method.

	virtual void handle(Poco::XML::ContentHandler* pHandler) const;
		/// Pass the decoded data to the given ContentHandler.

	virtual void handle(FISContentHandler* pHandler) const = 0;
		/// Pass the decoded data to the given FISContentHandler.

	virtual const std::string& content() const;
		/// Returns the content as string.

	virtual std::string& content();
		/// Returns the content as string.

	virtual void createContent() = 0;
		/// Creates the string content from the encoded
		/// data. Must be called before calling content().

protected:
	std::string _content;
};


//
// inlines
//
inline const std::string& Encoding::content() const
{
	return _content;
}


inline std::string& Encoding::content()
{
	return _content;
}


inline void Encoding::handle(Poco::XML::ContentHandler* pHandler) const
{
	if (pHandler)
		pHandler->characters(_content.data(), 0, static_cast<int>(_content.length()));
}


} } // namespace Poco::FastInfoset


#endif // FastInfoset_Encoding_INCLUDED

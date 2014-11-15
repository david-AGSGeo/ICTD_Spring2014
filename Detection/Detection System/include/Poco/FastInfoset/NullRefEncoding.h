//
// NullRefEncoding.h
//
// $Id: //poco/1.4/FastInfoset/include/Poco/FastInfoset/NullRefEncoding.h#1 $
//
// Library: FastInfoset
// Package: CodingAlgorithm
// Module:  NullRefEncoding
//
// Definition of the NullRefEncoding class.
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


#ifndef FastInfoset_NullRefEncoding_INCLUDED
#define FastInfoset_NullRefEncoding_INCLUDED


#include "Poco/FastInfoset/FastInfoset.h"
#include "Poco/FastInfoset/NullEncoding.h"
#include "Poco/FastInfoset/EncodingAlgorithm.h"


namespace Poco {
namespace FastInfoset {


class FastInfoset_API NullRefEncoding: public NullEncoding
	/// An optimized version of NullEncoding that stores only a reference to the string.
{
public:
	explicit NullRefEncoding(const std::string& data);
		/// Creates the NullRefEncoding using the given data.
		///
		/// Only a reference to the data is stored.

	~NullRefEncoding();
		/// Destroys the NullRefEncoding.

	// Encoding
	bool merge(const Encoding& enc);
	void handle(Poco::XML::ContentHandler* pHandler) const;
	void handle(FISContentHandler* pHandler) const;
	const std::string& content() const;
	std::string& content();
	void write(BitStreamWriter& writer) const;
	
	// Implementation	
	void reset(const std::string& data);

private:
	const std::string* _data;
};


//
// inlines
//
inline const std::string& NullRefEncoding::content() const
{
	poco_check_ptr (_data);

	return *_data;
}


inline std::string& NullRefEncoding::content()
{
	throw Poco::InvalidAccessException("NullRefEncoding is immutable");
}


inline void NullRefEncoding::reset(const std::string& data)
{
	_data = &data;
}


} } // namespace Poco::FastInfoset


#endif // FastInfoset_NullRefEncoding_INCLUDED

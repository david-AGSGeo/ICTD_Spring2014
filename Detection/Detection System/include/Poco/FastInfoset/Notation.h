//
// Notation.h
//
// $Id: //poco/1.4/FastInfoset/include/Poco/FastInfoset/Notation.h#1 $
//
// Library: FastInfoset
// Package: FastInfoset
// Module:  Notation
//
// Definition of the Notation class.
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


#ifndef FastInfoset_Notation_INCLUDED
#define FastInfoset_Notation_INCLUDED


#include "Poco/FastInfoset/FastInfoset.h"


namespace Poco {
namespace FastInfoset {


class FastInfoset_API Notation
	/// Stores data for a Notation event.
{
public:
	Notation();
		/// Creates the Notation.

	Notation(const std::string& name, const std::string& publicId, const std::string& systemId);
		/// Creates the Notation.

	~Notation();
		/// Destroys the Notation.

	const std::string& getName() const;
		/// Returns the name of the notation

	const std::string& getPublicId() const;
		/// Returns the publicId

	const std::string& getSystemId() const;
		/// Returns the systemId

	void setName(const std::string& val);
		/// Sets the notation name

	void setPublicId(const std::string& val);
		/// Sets the publicId

	void setSystemId(const std::string& val);
		/// Sets the systemId

private:
	std::string _name;
	std::string _publicId;
	std::string _systemId;
};


//
// inlines
//
inline const std::string& Notation::getName() const
{
	return _name;
}


inline const std::string& Notation::getPublicId() const
{
	return _publicId;
}


inline const std::string& Notation::getSystemId() const
{
	return _systemId;
}


inline void Notation::setName(const std::string& val)
{
	_name = val;
}


inline void Notation::setPublicId(const std::string& val)
{
	_publicId = val;
}


inline void Notation::setSystemId(const std::string& val)
{
	_systemId = val;
}


} } // namespace Poco::FastInfoset


#endif // FastInfoset_Notation_INCLUDED

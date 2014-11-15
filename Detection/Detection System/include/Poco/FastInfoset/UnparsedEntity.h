//
// UnparsedEntity.h
//
// $Id: //poco/1.4/FastInfoset/include/Poco/FastInfoset/UnparsedEntity.h#1 $
//
// Library: FastInfoset
// Package: FastInfoset
// Module:  UnparsedEntity
//
// Definition of the UnparsedEntity class.
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


#ifndef FastInfoset_UnparsedEntity_INCLUDED
#define FastInfoset_UnparsedEntity_INCLUDED


#include "Poco/FastInfoset/FastInfoset.h"


namespace Poco {
namespace FastInfoset {


class FastInfoset_API UnparsedEntity
	/// Stores data fro an UnparsedEntity event
{
public:
	UnparsedEntity();
		/// Creates an uninitialized UnparsedEntity.

	UnparsedEntity(const std::string& name, const std::string& publicId, const std::string& systemId, const std::string& notationName);
		/// Creates the UnparsedEntity.

	~UnparsedEntity();
		/// Destroys the UnparsedEntity.

	const std::string& getName() const;
		/// Returns the name of the UnparsedEntity

	const std::string& getPublicId() const;
		/// Returns the publicId

	const std::string& getSystemId() const;
		/// Returns the systemId

	const std::string& getNotationName() const;
		/// Returns the notation name

	void setName(const std::string& val);
		/// Sets the UnparsedEntity name

	void setPublicId(const std::string& val);
		/// Sets the publicId

	void setSystemId(const std::string& val);
		/// Sets the systemId

	void setNotationName(const std::string& val);
		/// Sets the notation name

private:
	std::string _name;
	std::string _publicId;
	std::string _systemId;
	std::string _notationName;
};


//
// inlines
//
inline const std::string& UnparsedEntity::getName() const
{
	return _name;
}


inline const std::string& UnparsedEntity::getPublicId() const
{
	return _publicId;
}


inline const std::string& UnparsedEntity::getSystemId() const
{
	return _systemId;
}


inline const std::string& UnparsedEntity::getNotationName() const
{
	return _notationName;
}


inline void UnparsedEntity::setName(const std::string& val)
{
	_name = val;
}


inline void UnparsedEntity::setPublicId(const std::string& val)
{
	_publicId = val;
}


inline void UnparsedEntity::setSystemId(const std::string& val)
{
	_systemId = val;
}


inline void UnparsedEntity::setNotationName(const std::string& val)
{
	_notationName = val;
}


} } // namespace Poco::FastInfoset


#endif // FastInfoset_UnparsedEntity_INCLUDED

//
// QName.h
//
// $Id: //poco/1.4/XSD/Types/include/Poco/XSD/Types/QName.h#2 $
//
// Library: XSD/Types
// Package: XSDTypes
// Module:  QName
//
// Definition of the QName class.
//
// Copyright (c) 2008-2012, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef XSDTypes_QName_INCLUDED
#define XSDTypes_QName_INCLUDED


#include "Poco/XSD/Types/XSDTypes.h"
#include "Poco/XSD/Types/NamespaceManager.h"


namespace Poco {
namespace XSD {
namespace Types {


class XSDTypes_API QName
	/// A Qualified Name.
{
public:
	static const QName INVALID;

	QName();
	 /// Creates an invalid QName

	QName(const std::string& name, const std::string& ns);
		/// Creates the QName.

	QName(const QName& qname);

	QName& operator = (const QName& other);

	bool operator == (const QName& other) const;

	bool operator != (const QName& other) const;

	~QName();
		/// Destroys the QName.

	const std::string& name() const;

	const std::string& getNamespace() const;

	NamespaceManager::NamespaceId getNamespaceId() const;

	const NamespaceManager::NamespaceMap::const_iterator& getIterator() const;

private:
	std::string _name;
		/// The name of the QName

	NamespaceManager::NamespaceMap::const_iterator _it;
		/// The iterator to the namespace entry
};


//
// inlines
//
inline bool QName::operator == (const QName& other) const
{
	return other.name() == name() && other.getIterator() == getIterator();
}


inline bool QName::operator != (const QName& other) const
{
	return !this->operator ==(other);
}


inline const std::string& QName::name() const
{
	return _name;
}


inline const std::string& QName::getNamespace() const
{
	return _it->first;
}


inline NamespaceManager::NamespaceId QName::getNamespaceId() const
{
	return _it->second;
}


inline const NamespaceManager::NamespaceMap::const_iterator& QName::getIterator() const
{
	return _it;
}


} } } // namespace Poco::XSD::Types


#endif // XSDTypes_QName_INCLUDED

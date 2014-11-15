//
// ListRestriction.h
//
// $Id: //poco/1.4/UPnP/ServiceDesc/include/Poco/UPnP/ServiceDesc/ListRestriction.h#1 $
//
// Library: UPnP/ServiceDesc
// Package: ServiceDesc
// Module:  ListRestriction
//
// Definition of the ListRestriction class.
//
// Copyright (c) 2011-2013, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef UPnP_ServiceDesc_ListRestriction_INCLUDED
#define UPnP_ServiceDesc_ListRestriction_INCLUDED


#include "Poco/UPnP/ServiceDesc/ServiceDesc.h"
#include "Poco/UPnP/ServiceDesc/Restriction.h"
#include <set>


namespace Poco {
namespace UPnP {
namespace ServiceDesc {


class UPnP_ServiceDesc_API ListRestriction: public Restriction
	/// The ListRestriction restricts values to a given list of strings.
{
public:
	typedef std::set<std::string> Values;
	typedef Poco::AutoPtr<ListRestriction> Ptr;

	ListRestriction();
		/// Creates the ListRestriction.

	~ListRestriction();
		/// Destroys the ListRestriction.

	const Values& values() const;
		/// Returns a std::set containing the allowed values.

	// Restriction
	bool valid(const std::string& val) const;
	std::string toString() const;

protected:
	Values& values();
		/// Returns a std::set containing the allowed values.
	
private:
	Values _values;
	
	friend class ServiceContentHandler;
};


//
// inlines
//
inline const ListRestriction::Values& ListRestriction::values() const
{
	return _values;
}


inline ListRestriction::Values& ListRestriction::values()
{
	return _values;
}


} } } // Poco::UPnP::ServiceDesc


#endif // UPnP_ServiceDesc_ListRestriction_INCLUDED

//
// Documentation.h
//
// $Id: //poco/1.4/XSD/Types/include/Poco/XSD/Types/Documentation.h#2 $
//
// Library: XSD/Types
// Package: XSDTypes
// Module:  Documentation
//
// Definition of the Documentation class.
//
// Copyright (c) 2008-2012, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef XSDTypes_Documentation_INCLUDED
#define XSDTypes_Documentation_INCLUDED


#include "Poco/XSD/Types/XSDTypes.h"
#include "Poco/XSD/Types/AnnotationContent.h"


namespace Poco {
namespace XSD {
namespace Types {


class XSDTypes_API Documentation: public AnnotationContent
	/// This class represents a documentation in an XML Schema.
{
public:
	Documentation(const std::string& sourceUri, const std::string& lang);
		/// Creates the Documentation.

	virtual ~Documentation();
		/// Destroys the Documentation.

	const std::string& language() const;
		/// The language of the documentation entry. Can be empty.

	void accept(Visitor& v) const;

private:
	std::string _language;
};


//
// inlines
//
inline const std::string& Documentation::language() const
{
	return _language;
}


} } } // namespace Poco::XSD::Types


#endif // XSDTypes_Documentation_INCLUDED

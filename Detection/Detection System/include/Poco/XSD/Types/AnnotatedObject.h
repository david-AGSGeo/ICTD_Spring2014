//
// AnnotatedObject.h
//
// $Id: //poco/1.4/XSD/Types/include/Poco/XSD/Types/AnnotatedObject.h#2 $
//
// Library: XSD/Types
// Package: XSDTypes
// Module:  AnnotatedObject
//
// Definition of the AnnotatedObject class.
//
// Copyright (c) 2008-2012, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef XSDTypes_AnnotatedObject_INCLUDED
#define XSDTypes_AnnotatedObject_INCLUDED


#include "Poco/XSD/Types/XSDTypes.h"
#include "Poco/XSD/Types/Visitable.h"
#include "Poco/XSD/Types/Annotation.h"
#include "Poco/AutoPtr.h"
#include <vector>


namespace Poco {
namespace XSD {
namespace Types {


class XSDTypes_API AnnotatedObject: public Visitable
	/// AnnotatedObject is the abstract super class for all objects that
	/// can store an annotation internally.
{
public:
	typedef Poco::AutoPtr<AnnotatedObject> Ptr;
	typedef std::vector<Annotation> Annotations;

	AnnotatedObject();
		/// Creates the AnnotatedObject.

	AnnotatedObject(const std::string& id);
		/// Creates the AnnotatedObject.

	AnnotatedObject(const std::string& id, const Annotation& ann);
		/// Creates the AnnotatedObject.

	virtual ~AnnotatedObject();
		/// Destroys the AnnotatedObject.

	void addAnnotation(const Annotation& ann);
		/// Adds the annotation at the object.

	const Annotations& getAnnotations() const;
		/// Returns the annotation from the object.

private:
	Annotations _annotation;
};


//
// inlines
//
inline void AnnotatedObject::addAnnotation(const Annotation& ann)
{
	_annotation.push_back(ann);
}


inline const AnnotatedObject::Annotations& AnnotatedObject::getAnnotations() const
{
	return _annotation;
}


} } } // namespace Poco::XSD::Types


#endif // XSDTypes_AnnotatedObject_INCLUDED

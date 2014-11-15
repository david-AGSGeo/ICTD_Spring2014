//
// ElementTypeRef.h
//
// $Id: //poco/1.4/XSD/Types/include/Poco/XSD/Types/ElementTypeRef.h#2 $
//
// Library: XSD/Types
// Package: XSDElements
// Module:  ElementTypeRef
//
// Definition of the ElementTypeRef class.
//
// Copyright (c) 2008-2012, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef XSDTypes_ElementTypeRef_INCLUDED
#define XSDTypes_ElementTypeRef_INCLUDED


#include "Poco/XSD/Types/XSDTypes.h"
#include "Poco/XSD/Types/AbstractElementImpl.h"


namespace Poco {
namespace XSD {
namespace Types {


class XSDTypes_API ElementTypeRef: public AbstractElementImpl
	/// ElementTypeRef handles the Element definition case with a given external type.
{
public:
	ElementTypeRef();
		/// Creates the ElementTypeRef.

	ElementTypeRef(
		const std::string& id, 
		Poco::UInt32 minOcc, 
		Poco::UInt32 maxOcc,
		bool isAbstract,
		bool blockRestriction,
		bool blockExtension,
		bool blockSubstitution,
		const std::string& defaultValue,
		bool finalRestriction,
		bool finalExtension,
		const std::string& fixedValue,
		bool qualified,
		const std::string& name,
		const std::string& nameSpace,
		bool nillable,
		const QName& substitutionGroup,
		const QName& typeRef);
		/// Creates an initialized ElementTypeRef

	virtual ~ElementTypeRef();
		/// Destroys the ElementTypeRef.

	void fixup();

	const Type& type() const;

	void accept(Visitor& v) const;

private:
	const Type* _pType;
	QName _typeRef;
};


//
// inlines
//
inline const Type& ElementTypeRef::type() const
{
	poco_check_ptr (_pType);
	return *_pType;
}


} } } // namespace Poco::XSD::Types


#endif // XSDTypes_ElementTypeRef_INCLUDED

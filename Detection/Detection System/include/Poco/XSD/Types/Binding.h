//
// Binding.h
//
// $Id: //poco/1.4/XSD/Types/include/Poco/XSD/Types/Binding.h#2 $
//
// Library: XSD/Types
// Package: WSDL
// Module:  Binding
//
// Definition of the Binding class.
//
// Copyright (c) 2012, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef XSDTypes_Binding_INCLUDED
#define XSDTypes_Binding_INCLUDED


#include "Poco/XSD/Types/XSDTypes.h"
#include "Poco/XSD/Types/AnnotatedObject.h"
#include "Poco/XSD/Types/PortType.h"
#include "Poco/XML/Name.h"
#include <vector>


namespace Poco {
namespace XSD {
namespace Types {


class XSDTypes_API Binding: public AnnotatedObject
	/// This class represents a WSDL Binding.
{
public:
	typedef Poco::AutoPtr<Binding> Ptr;

	Binding();
		/// Creates the Binding.

	Binding(const std::string& name);
		/// Creates the Binding.

	~Binding();
		/// Destroys the Binding.

	void setName(const std::string& name);
		/// Sets the name.

	const std::string& name() const;
		/// Returns the name.
	
	void setPortType(PortType::Ptr pPortType);
		/// Associates a PortType with the Binding.
		
	PortType::Ptr getPortType() const;
		/// Returns the associated PortType.

	const BindingProperties& bindingProperties() const;
		/// Returns the binding properties for the entire binding (e.g., "soap.binding.stye", "soap.binding.transport").
		
	BindingProperties& bindingProperties();
		/// Returns the binding properties for the entire binding (e.g., "soap.binding.stye", "soap.binding.transport").
	
	void accept(Visitor& v) const;

private:
	std::string _name;
	PortType::Ptr _pPortType;
	BindingProperties _bindingProperties;
};


//
// inlines
//
inline void Binding::setName(const std::string& name)
{
	_name = name;
}


inline const std::string& Binding::name() const
{
	return _name;
}


inline void Binding::setPortType(PortType::Ptr pPortType)
{
	_pPortType = pPortType;
}

	
inline PortType::Ptr Binding::getPortType() const
{
	return _pPortType;
}


inline const BindingProperties& Binding::bindingProperties() const
{
	return _bindingProperties;
}

	
inline BindingProperties& Binding::bindingProperties()
{
	return _bindingProperties;
}


} } } // namespace Poco::XSD::Types


#endif // XSDTypes_Binding_INCLUDED

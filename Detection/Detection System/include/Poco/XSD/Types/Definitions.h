//
// Definitions.h
//
// $Id: //poco/1.4/XSD/Types/include/Poco/XSD/Types/Definitions.h#2 $
//
// Library: XSD/Types
// Package: XSDTypes
// Module:  Definitions
//
// Definition of the Definitions class.
//
// Copyright (c) 2012, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef XSDTypes_Definitions_INCLUDED
#define XSDTypes_Definitions_INCLUDED


#include "Poco/XSD/Types/XSDTypes.h"
#include "Poco/XSD/Types/Message.h"
#include "Poco/XSD/Types/Operation.h"
#include "Poco/XSD/Types/PortType.h"
#include "Poco/XSD/Types/Binding.h"
#include "Poco/XSD/Types/Service.h"
#include <map>


namespace Poco {
namespace XSD {
namespace Types {


class XSDTypes_API Definitions: public AnnotatedObject
	/// This class represents an entire WSDL definition.
{
public:
	typedef Poco::AutoPtr<Definitions> Ptr;
	typedef std::map<std::string, Message::Ptr> Messages;
	typedef std::map<std::string, PortType::Ptr> PortTypes;
	typedef std::map<std::string, Binding::Ptr> Bindings;
	typedef std::map<std::string, Service::Ptr> Services;

	Definitions(const std::string& targetNS);
		/// Creates the Definitions.

	~Definitions();
		/// Destroys the Definitions.

	const std::string& targetNamespace() const;
		/// The target namespace of the WSDL.

	void addMessage(Message::Ptr pMessage);
		/// Adds a WSDL Message.
		
	void addOperation(Operation::Ptr pOperation);
		/// Adds a WSDL Operation.
		
	void addPortType(PortType::Ptr pPortType);
		/// Adds a WSDL port type.

	void addBinding(Binding::Ptr pPortType);
		/// Adds a WSDL binding.
		
	void addService(Service::Ptr pService);
		/// Adds a WSDL service.

	const Definitions::Messages& messages() const;
		/// Returns all WSDL messages.
		
	const Definitions::PortTypes& portTypes() const;
		/// Returns all WSDL port types.
		
	const Definitions::Bindings& bindings() const;
		/// Returns all WSDL bindings.
		
	const Definitions::Services& services() const;
		/// Returns all WSDL services.

	void accept(Visitor& v) const;

private:
	std::string _targetNamespace;
	Messages       _messages;
	PortTypes      _portTypes;
	Bindings       _bindings;
	Services       _services;
};


//
// inlines
//
inline const std::string& Definitions::targetNamespace() const
{
	return _targetNamespace;
}


inline const Definitions::Messages& Definitions::messages() const
{
	return _messages;
}


inline const Definitions::PortTypes& Definitions::portTypes() const
{
	return _portTypes;
}


inline const Definitions::Bindings& Definitions::bindings() const
{
	return _bindings;
}


inline const Definitions::Services& Definitions::services() const
{
	return _services;
}


} } } // namespace Poco::XSD::Types


#endif // XSDTypes_Definitions_INCLUDED

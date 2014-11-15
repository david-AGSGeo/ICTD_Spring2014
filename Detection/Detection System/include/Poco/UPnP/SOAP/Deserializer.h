//
// Deserializer.h
//
// $Id: //poco/1.4/UPnP/SOAP/include/Poco/UPnP/SOAP/Deserializer.h#1 $
//
// Library: UPnP/SOAP
// Package: SOAP
// Module:  Deserializer
//
// Definition of the Deserializer class.
//
// Copyright (c) 2008-2011, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef UPnP_SOAP_Deserializer_INCLUDED
#define UPnP_SOAP_Deserializer_INCLUDED


#include "Poco/UPnP/SOAP/SOAP.h"
#include "Poco/RemotingNG/Deserializer.h"
#include "Poco/DOM/Document.h"
#include "Poco/DOM/Element.h"
#include "Poco/AutoPtr.h"


namespace Poco {
namespace UPnP {
namespace SOAP {


class UPnPSOAP_API Deserializer: public Poco::RemotingNG::Deserializer
	/// The Deserializer for the UPnP SOAP Transport.
	///
	/// This class can deserialize SOAP requests and responses,
	/// as well as XML schema based complex types.
	///
	/// Internally, the Deserializer builds a DOM document from the
	/// XML read from the stream. While this is not the most performant
	/// way to parse XML, it allows for handling messages that do not
	/// fully conform to their specification (such as containing additional
	/// elements, or elements arriving in wrong order). This is a frequent case 
	/// in UPnP networks.
	///
	/// For maximum interoperability with misbehaving UPnP SOAP implementations,
	/// the Deserializer ignores the XML namespace of all elements it processes.
{
public:
	Deserializer();
		/// Creates a Deserializer.

	~Deserializer();
		/// Destroys the Deserializer.

	// Poco::RemotingNG::Deserializer
	Poco::RemotingNG::SerializerBase::MessageType findMessage(std::string& name);
	void deserializeMessageBegin(const std::string& name, Poco::RemotingNG::SerializerBase::MessageType type);
	void deserializeMessageEnd(const std::string& name, Poco::RemotingNG::SerializerBase::MessageType type);
	bool deserializeStructBegin(const std::string& name, bool isMandatory);
	void deserializeStructEnd(const std::string& name);
	bool deserializeSequenceBegin(const std::string& name, bool isMandatory, Poco::UInt32& sizeHint);
	void deserializeSequenceEnd(const std::string& name);
	bool deserializeNullableBegin(const std::string& name, bool isMandatory, bool& isNull);
	void deserializeNullableEnd(const std::string& name);
	bool deserialize(const std::string& name, bool isMandatory, Poco::Int8& value);
	bool deserialize(const std::string& name, bool isMandatory, Poco::UInt8& value);
	bool deserialize(const std::string& name, bool isMandatory, Poco::Int16& value);
	bool deserialize(const std::string& name, bool isMandatory, Poco::UInt16& value);
	bool deserialize(const std::string& name, bool isMandatory, Poco::Int32& value);
	bool deserialize(const std::string& name, bool isMandatory, Poco::UInt32& value);
	bool deserialize(const std::string& name, bool isMandatory, long& value);
	bool deserialize(const std::string& name, bool isMandatory, unsigned long& value);
#ifndef POCO_LONG_IS_64_BIT
	bool deserialize(const std::string& name, bool isMandatory, Poco::Int64& value);
	bool deserialize(const std::string& name, bool isMandatory, Poco::UInt64& value);
#endif
	bool deserialize(const std::string& name, bool isMandatory, float& value);
	bool deserialize(const std::string& name, bool isMandatory, double& value);
	bool deserialize(const std::string& name, bool isMandatory, bool& value);
	bool deserialize(const std::string& name, bool isMandatory, char& value);
	bool deserialize(const std::string& name, bool isMandatory, std::string& value);
	bool deserialize(const std::string& name, bool isMandatory, std::vector<char>& value);

protected:
	void resetImpl();
	void setupImpl(std::istream& istr);

private:
	Deserializer(const Deserializer&);
	Deserializer& operator = (const Deserializer&);

	Poco::XML::Element* findBody() const;
	Poco::XML::Element* findMessage() const;
	Poco::XML::Element* findElement(Poco::XML::Element* pParent, const std::string& localName) const;
	Poco::XML::Element* findNextElement(Poco::XML::Element* pElem, const std::string& localName) const;
	bool isElement(Poco::XML::Node* pNode, const std::string& localName) const;
	void handleConditionalError(const std::string& name, bool isMandatory);
	std::string deserializeElement(const std::string& name, bool isMandatory, bool& found);
	void deserializeFault();

private:
	static const std::string RESPONSE;

	Poco::AutoPtr<Poco::XML::Document> _pDocument;
	Poco::XML::Element* _pMessage;
	Poco::XML::Element* _pElement;
	std::string _lastElement;
};


} } } // namespace Poco::UPnP::SOAP


#endif // UPnP_SOAP_Deserializer_INCLUDED

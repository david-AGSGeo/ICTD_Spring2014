//
// Serializer.h
//
// $Id: //poco/1.4/UPnP/SOAP/include/Poco/UPnP/SOAP/Serializer.h#2 $
//
// Library: UPnP/SOAP
// Package: SOAP
// Module:  Serializer
//
// Definition of the Serializer class.
//
// Copyright (c) 2008-2011, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef UPnP_SOAP_Serializer_INCLUDED
#define UPnP_SOAP_Serializer_INCLUDED


#include "Poco/UPnP/SOAP/SOAP.h"
#include "Poco/XML/XMLWriter.h"
#include "Poco/SAX/AttributesImpl.h"
#include "Poco/RemotingNG/Serializer.h"
#include <memory>


namespace Poco {
namespace UPnP {
namespace SOAP {


class UPnPSOAP_API Serializer: public Poco::RemotingNG::Serializer
	/// The Serializer for the UPnP SOAP Transport.
	///
	/// This class can serialize SOAP requests and responses,
	/// as well as XML schema based complex types.
	///
	/// Internally, the Serializer uses a Poco::XML::XMLWriter
	/// to immediately write XML to the stream, without first
	/// building an internal representation of the XML (such as
	/// a DOM document).
{
public:
	static const XML::XMLString SOAP_NAMESPACE;
	static const XML::XMLString SOAP_ENCODING;
	static const XML::XMLString SOAP_ENVELOPE_PREFIX;
	static const XML::XMLString SOAP_ACTION_PREFIX;
	static const XML::XMLString SOAP_ENVELOPE;
	static const XML::XMLString SOAP_ENCODING_STYLE;
	static const XML::XMLString SOAP_BODY;
	static const XML::XMLString SOAP_FAULT;
	static const XML::XMLString SOAP_FAULTCODE;
	static const XML::XMLString SOAP_FAULTCODE_CLIENT;
	static const XML::XMLString SOAP_FAULTSTRING;
	static const XML::XMLString SOAP_FAULTDETAIL;
	static const XML::XMLString SOAP_TRUE;
	static const XML::XMLString SOAP_FALSE;
	static const XML::XMLString UPNP_ERROR;
	static const XML::XMLString UPNP_ERROR_NAMESPACE;
	static const XML::XMLString UPNP_ERROR_CODE;
	static const XML::XMLString UPNP_ERROR_DESCRIPTION;
	static const XML::AttributesImpl EMPTY_ATTRIBUTES;
	static const XML::XMLString EMPTY_STRING;

	Serializer();
		/// Creates the Serializer.

	~Serializer();
		/// Destroys the Serializer.

	// Poco::RemotingNG::Serializer
	void serializeMessageBegin(const std::string& name, Poco::RemotingNG::SerializerBase::MessageType type);
	void serializeMessageEnd(const std::string& name, Poco::RemotingNG::SerializerBase::MessageType type);
	void serializeFaultMessage(const std::string& name, Poco::Exception& exc);
	void serializeStructBegin(const std::string& name);
	void serializeStructEnd(const std::string& name);
	void serializeSequenceBegin(const std::string& name, Poco::UInt32 numElems);
	void serializeSequenceEnd(const std::string& name);
	void serializeNullableBegin(const std::string& name, bool isNull);
	void serializeNullableEnd(const std::string& name);
	void serialize(const std::string& name, Poco::Int8 value);
	void serialize(const std::string& name, Poco::UInt8 value);
	void serialize(const std::string& name, Poco::Int16 value);
	void serialize(const std::string& name, Poco::UInt16 value);
	void serialize(const std::string& name, Poco::Int32 value);
	void serialize(const std::string& name, Poco::UInt32 value);
	void serialize(const std::string& name, long value);
	void serialize(const std::string& name, unsigned long value);
#ifndef POCO_LONG_IS_64_BIT
	void serialize(const std::string& name, Poco::Int64 value);
	void serialize(const std::string& name, Poco::UInt64 value);
#endif
	void serialize(const std::string& name, float value);
	void serialize(const std::string& name, double value);
	void serialize(const std::string& name, bool value);
	void serialize(const std::string& name, char value);
	void serialize(const std::string& name, const std::string& value);
	void serialize(const std::string& name, const std::vector<char>& value);

protected:
	void resetImpl();
	void setupImpl(std::ostream& ostr);
	void serializeData(const std::string& name, const std::string& value);

private:
	std::auto_ptr<XML::XMLWriter> _pWriter;
	std::ostream*                 _pStream;
	int                           _inDocument;
};


} } } // namespace Poco::UPnP::SOAP


#endif // UPnP_SOAP_Serializer_INCLUDED

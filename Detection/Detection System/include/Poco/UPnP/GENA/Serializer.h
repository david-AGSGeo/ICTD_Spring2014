//
// Serializer.h
//
// $Id: //poco/1.4/UPnP/GENA/include/Poco/UPnP/GENA/Serializer.h#1 $
//
// Library: UPnP/GENA
// Package: GENA
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


#ifndef UPnP_GENA_Serializer_INCLUDED
#define UPnP_GENA_Serializer_INCLUDED


#include "Poco/UPnP/GENA/GENA.h"
#include "Poco/XML/XMLWriter.h"
#include "Poco/SAX/AttributesImpl.h"
#include "Poco/RemotingNG/Serializer.h"
#include "Poco/SharedPtr.h"
#include <memory>


namespace Poco {
namespace UPnP {
namespace GENA {


class UPnPGENA_API Serializer: public Poco::RemotingNG::Serializer
	/// The Serializer for the UPnP GENA Transport.
	///
	/// This class can serialize GENA event messages (XML property sets).
	///
	/// Internally, the Serializer uses a Poco::XML::XMLWriter
	/// to immediately write XML to the stream, without first
	/// building an internal representation of the XML (such as
	/// a DOM document).
{
public:
	static const XML::XMLString UPNP_EVENT_NAMESPACE;
	static const XML::XMLString UPNP_PROPERTYSET;
	static const XML::XMLString UPNP_PROPERTY;
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
	std::ostream* _pStream;
	std::string _variable;
};


} } } // namespace Poco::UPnP::GENA


#endif // UPnP_GENA_Serializer_INCLUDED

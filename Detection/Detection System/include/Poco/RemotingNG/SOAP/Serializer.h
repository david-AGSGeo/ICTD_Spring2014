//
// Serializer.h
//
// $Id: //poco/1.4/RemotingNG/SOAP/include/Poco/RemotingNG/SOAP/Serializer.h#8 $
//
// Library: RemotingNG/SOAP
// Package: SOAP
// Module:  Serializer
//
// Definition of the Serializer class.
//
// Copyright (c) 2006-2012, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef RemotingNG_SOAP_Serializer_INCLUDED
#define RemotingNG_SOAP_Serializer_INCLUDED


#include "Poco/RemotingNG/SOAP/SOAP.h"
#include "Poco/RemotingNG/Serializer.h"
#include "Poco/XML/XMLWriter.h"
#include "Poco/SAX/AttributesImpl.h"
#include "Poco/Net/MultipartWriter.h"
#include "Poco/NumberFormatter.h"
#include "Poco/SharedPtr.h"
#include <memory>
#include <map>


namespace Poco {
namespace RemotingNG {
namespace SOAP {


class RemotingNGSOAP_API Serializer: public Poco::RemotingNG::Serializer
	/// The Serializer implementation for the SOAP
	/// Transport.
	///
	/// The serializer creates an XML stream according
	/// to SOAP 1.1/1.2 Document/Literal message format.
	///
	/// The serializer can also be used to serialize plain
	/// XML. To do so, instead of serializeMessageBegin() and
	/// serializeMessageEnd(), call serializeStructBegin()
	/// and serializeStructEnd(), respectively, at the root level,
	/// after calling setup().
{
public:
	static const std::string SOAPPREFIX;
	static const std::string SOAP11NAMESPACE;
	static const std::string SOAP12NAMESPACE;
	static const std::string XSIPREFIX;
	static const std::string XSINAMESPACE;
	static const std::string XSINIL;
	static const std::string XOPNAMESPACE;
	static const std::string XOPINCLUDE;
	static const std::string XOPHREF;
	static const std::string EMPTYSTRING;
	static const XML::AttributesImpl EMPTYATTRIBUTES;
	static const std::string VAL_TRUE;
	static const std::string VAL_FALSE;
	static const std::string ENVELOPE;
	static const std::string FAULT;
	static const std::string ENCODINGSTYLE;
	static const std::string FAULTCODE;
	static const std::string FAULTCODESERVER;
	static const std::string FAULTSTRING;
	static const std::string CODE;
	static const std::string CODE_VALUE;
	static const std::string REASON;
	static const std::string REASON_TEXT;
	static const std::string LANG;
	static const std::string CODEVALUERECEIVER;
	static const std::string SOAPBODY;
	static const std::string SOAPHEADER;
	static const std::string SOAPENCODINGNAMESPACE;
	static const std::string REPLY;
	
	enum SOAPVersion
	{
		SOAP_1_1 = 11,
		SOAP_1_2 = 12
	};
	
	enum
	{
		MIN_MTOM_SIZE = 64
	};

	Serializer(bool prettyPrint = false);
		/// Creates the Serializer for SOAP 1.1. 
		///
		/// If prettyPrint is true, XML messages will be pretty-printed.

	Serializer(SOAPVersion soapVersion, bool prettyPrint = false);
		/// Creates the Serializer for the given SOAP version. 
		///
		/// If prettyPrint is true, XML messages will be pretty-printed.

	~Serializer();
		/// Destroys the Serializer.

	void setSOAPVersion(SOAPVersion version);
		/// Sets the SOAP version used for serialization.
		///
		/// Note that this method must not be called after
		/// serialization has started.
		
	SOAPVersion getSOAPVersion() const;
		/// Returns the SOAP version used for serialization.
		
	void enableMTOM(bool enable);
		/// Enables or disables MTOM.

	bool isMTOMEnabled() const;
		/// Returns true iff MTOM is enabled.
		
	std::string createMTOMContentType(const std::string& action = EMPTYSTRING);
		/// Creates the Content-Type value for an MTOM message
		/// containing the MIME boundary and start content ID.

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
	void serializeOptionalBegin(const std::string& name, bool isOptional);
	void serializeOptionalEnd(const std::string& name);
	void serialize(const std::string& name, Poco::Int8 val);
	void serialize(const std::string& name, Poco::UInt8 val);
	void serialize(const std::string& name, Poco::Int16 val);
	void serialize(const std::string& name, Poco::UInt16 val);
	void serialize(const std::string& name, Poco::Int32 val);
	void serialize(const std::string& name, Poco::UInt32 val);
	void serialize(const std::string& name, long val);
	void serialize(const std::string& name, unsigned long val);

#ifndef POCO_LONG_IS_64_BIT
	void serialize(const std::string& name, Poco::Int64 val);
	void serialize(const std::string& name, Poco::UInt64 val);
#endif

	void serialize(const std::string& name, float val);
	void serialize(const std::string& name, double val);
	void serialize(const std::string& name, bool val);
	void serialize(const std::string& name, char val);
	void serialize(const std::string& name, const char* pVal);
	void serialize(const std::string& name, const std::string& val);
	void serialize(const std::string& name, const std::vector<char>& val);
	
	void pushAttribute(const std::string& ns, const std::string& attrName);
	void registerNamespace(const std::string& ns);

protected:
	void resetImpl();
	void setupImpl(std::ostream& out);

private:
	Serializer(const Serializer&);
	Serializer& operator=(const Serializer&);

	void serializeMethodStart(const std::string& methodName);
	void serializeMethodEnd(const std::string& methodName);
	void serializeData(const std::string& name, const std::string& val);
	void handleStartElementImpl(const std::string& name, const std::string& value);
	void handleStartElementXml(const std::string& name, const std::string& value);
	void handleStartElementComplexImpl(const std::string& name);
	void handleEndElementComplexImpl(const std::string& name);
	void handleStartElementComplexXml(const std::string& name);
	void handleEndElementComplexXml(const std::string& name);
	void handleStartElementNilImpl(const std::string& name);
	void handleStartElementNilXml(const std::string& name);
	void handleStartElementIncludeImpl(const std::string& name, const std::string& cid);
	void handleStartElementIncludeXml(const std::string& name, const std::string& cid);
	void checkHeadersEnd(const std::string& name);
	bool checkHeadersStart(const std::string& name);
	void writeRoot();
	void createEnvelope();
	std::string createContentID();
	void writeParts();

private:
	typedef void (Serializer::*StartElementFunct)(const std::string&, const std::string&);
	typedef void (Serializer::*StartElementComplexFunct)(const std::string&);
	typedef void (Serializer::*EndElementComplexFunct)(const std::string&);
	typedef void (Serializer::*StartElementNilFunct)(const std::string&);
	typedef void (Serializer::*StartElementIncludeFunct)(const std::string&, const std::string&);

	struct DelayedElement
	{
		std::string name;
		std::string nameSpace;
		std::string value;
		bool simpleElem;
		XML::AttributesImpl attr;
		std::map<std::string, std::string> openAttr; /// Attrs still missing for this element
		std::vector<DelayedElement> children;
		int curChild;

		DelayedElement();
		DelayedElement(const std::string& val);
		DelayedElement(const std::string& n, const std::string& ns);
		DelayedElement(const std::string& n, const std::string& ns, const std::string& val, bool simpleElem);
		DelayedElement(const std::string& n, const std::string& ns, const std::string& val, bool simpleElem, const std::map<std::string, std::string>& openAttr);
		bool valid() const;
		void clear();
	};

	void write(const Serializer::DelayedElement& elem, bool closeXMLTags);
	void closeXML();

	SOAPVersion _soapVersion;
	bool _mtom;
	bool _prettyPrint;
	const std::string* _pSOAPNamespace;
	std::auto_ptr<XML::XMLWriter> _pXMLWriter;
	std::map<std::string, std::string> _attr; /// Collects attr info for elements, maps attr names to namespaces.
	std::set<std::string> _headerElements;
	Poco::SharedPtr<DelayedElement> _pRoot;
	std::stack<DelayedElement*> _curParent;
	int _depth;
	Poco::SharedPtr<DelayedElement> _pDelayed;
	StartElementFunct handleStartElement;
	StartElementComplexFunct handleStartElementComplex;
	EndElementComplexFunct handleEndElementComplex;
	StartElementNilFunct handleStartElementNil;
	StartElementIncludeFunct handleStartElementInclude;
	bool _documentStarted;
	std::ostream* _pStream;
	Poco::Net::MultipartWriter* _pMultipartWriter;
	std::string _boundary;
	std::string _startContentID;
	std::map<std::string, const std::vector<char>*> _parts; 
};


//
// inlines
//
inline Serializer::SOAPVersion Serializer::getSOAPVersion() const
{
	return _soapVersion;
}


} } } // namespace Poco::RemotingNG::SOAP


#endif // RemotingNG_SOAP_Serializer_INCLUDED

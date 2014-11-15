//
// FastInfosetWriter.h
//
// $Id: //poco/1.4/FastInfoset/include/Poco/FastInfoset/FastInfosetWriter.h#1 $
//
// Library: FastInfoset
// Package: Writer
// Module:  FastInfosetWriter
//
// Definition of the FastInfosetWriter class.
//
// Copyright (c) 2006-2010, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics
// Software Engineering GmbH.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part, without
// prior written permission from Applied Informatics.
//


#ifndef FastInfoset_FastInfosetWriter_INCLUDED
#define FastInfoset_FastInfosetWriter_INCLUDED


#include "Poco/FastInfoset/FastInfoset.h"
#include "Poco/FastInfoset/BitStreamWriter.h"
#include "Poco/FastInfoset/DocumentVocabulary.h"
#include "Poco/FastInfoset/FISDocumentHandler.h"
#include "Poco/FastInfoset/FISContentHandler.h"
#include "Poco/FastInfoset/Notation.h"
#include "Poco/FastInfoset/Encoding.h"
#include "Poco/FastInfoset/UnparsedEntity.h"
#include "Poco/XML/Name.h"
#include "Poco/SAX/NamespaceSupport.h"
#include "Poco/SAX/ContentHandler.h"
#include "Poco/SAX/LexicalHandler.h"
#include "Poco/SAX/DTDHandler.h"
#include "Poco/SAX/Attributes.h"
#include "Poco/SharedPtr.h"
#include <vector>


namespace Poco {
namespace XML {


class Locator;
class Attributes;


} // namespace XML


namespace FastInfoset {


class FastInfoset_API FastInfosetWriter: public FISContentHandler, public Poco::XML::LexicalHandler, public Poco::XML::DTDHandler, public FISDocumentHandler
	/// This class serializes SAX2 ContentHandler, LexicalHandler and
	/// DTDHandler events into a Fast Infoset stream.
	/// 
	/// Various consistency checks are performed on the written data
	/// (i.e. there must be exactly one root element and every startElement() 
	/// must have a matching endElement()).
	///
	/// The writer contains extensive support for XML Namespaces, so that a client  
	/// application does not have to keep track of prefixes and supply xmlns attributes.
	///
	/// If the client does not provide namespace prefixes (either by specifying them
	/// as part of the qualified name given to startElement(), or by calling
	/// startPrefixMapping()), the XMLWriter automatically generates namespace
	/// prefixes in the form ns1, ns2, etc.
	///
	/// The writer supports automatic indexing of character data element content.
	/// Only character data with a given maximum length (default is 7)
	/// will be indexed. The length can be set with setMaxIndexedStringLength().
{
public:
	FastInfosetWriter(std::ostream& str, bool writeXMLDeclaration, const DocumentVocabulary& initialVocabulary);
		/// Creates the FastInfosetWriter using the given initial document vocabulary.
		/// Passing an initial, populated document vocabulary can speed up the 
		/// generation of the Fast Infoset stream.
		///
		/// If writeXMLDeclaration is true, an XML declaration is included
		/// in the resulting Fast Infoset document.
		
	FastInfosetWriter(std::ostream& str, bool writeXMLDeclaration, DocumentVocabulary::VocabularyImpl vocImpl = DocumentVocabulary::VOC_HASH);
		/// Creates the FastInfosetWriter.
		///
		/// If writeXMLDeclaration is true, an XML declaration is included
		/// in the resulting Fast Infoset document.
		///
		/// Specify DocumentVocabulary::VOC_HASH or DocumentVocabulary::VOC_MAP for 
		/// vocImpl (DocumentVocabulary::VOC_VECTOR cannot be used with the writer). 
		/// VOC_MAP has the advantage that it does not
		/// impose any restrictions to the size of a vocabulary (except for available
		/// physical memory). For very large documents, the hash tables of a hash 
		/// vocabulary may overflow.
		/// In contrast, the size of a map vocabulary is only restricted by
		/// available memory. Parsing performance may be slightly better
		/// with a hash vocabulary, though.

	FastInfosetWriter(std::ostream& str);
		/// Creates the FastInfosetWriter. 
		///
		/// No XML declaration is included in the generated
		/// Fast Infoset document.
		
	~FastInfosetWriter();
		/// Destroys the FastInfosetWriter.

	void setMaxIndexedStringLength(int length);
		/// Sets the maximum length for indexed character data.
		///
		/// Character data element content which is shorter than
		/// the given length will be indexed in the resulting
		/// Fast Infoset document.

	int getMaxIndexedStringLength() const;
		/// Returns the maximum length for indexed character data.
		///
		/// Character data element content which is shorter than
		/// the given length will be indexed in the resulting
		/// Fast Infoset document.

	void setDocumentLocator(const Poco::XML::Locator* loc);
		/// Unused for Fast Infoset documents.

	void startDocument();
		/// Writes a generic XML declaration to the stream.
		/// If a document type has been set (see SetDocumentType),
		/// a DOCTYPE declaration is also written.

	void endDocument();
		/// Checks that all elements are closed and prints a final newline.

	void startFragment();
		/// Document fragments are not supported by Fast Infoset. Will throw an exception.

	void endFragment();
		/// Document fragments are not supported by FIS. Will throw an exception.

	void startElement(const std::string& namespaceURI, const std::string& localName, const std::string& qname, const Poco::XML::Attributes& attributes);
		/// Writes an XML start element tag.
		///
		/// Namespaces are handled as follows.
		///   1. If a qname, but no namespaceURI and localName are given, the qname is taken as element name.
		///   2. If a namespaceURI and a localName, but no qname is given, and the given namespaceURI has been
		///      declared earlier, the namespace prefix for the given namespaceURI together with the localName
		///      is taken as element name. If the namespace has not been declared, a prefix in the form
		///      "ns1", "ns2", etc. is generated and the namespace is declared with the generated prefix.
		///   3. If all three are given, and the namespace given in namespaceURI has not been declared, it is declared now.
		///      Otherwise, see 2.

	void startElement(const std::string& namespaceURI, const std::string& localName, const std::string& qname);
		/// Writes an XML start element tag with no attributes.
		/// See the other startElement() method for more information.
		
	void endElement(const std::string& namespaceURI, const std::string& localName, const std::string& qname);
		/// Writes an XML end element tag.
		///
		/// Throws an exception if the name of doesn't match the
		/// one of the most recent startElement().

	void emptyElement(const std::string& namespaceURI, const std::string& localName, const std::string& qname);
		/// Writes an empty XML element tag (<elem/>).

	void emptyElement(const std::string& namespaceURI, const std::string& localName, const std::string& qname, const Poco::XML::Attributes& attributes);
		/// Writes an empty XML element tag with the given attributes (<elem attr1="value1"... />).

	void characters(const char ch[], int start, int length);
		/// Writes XML character data.
		///
		/// The characters must be encoded in UTF-8.

	void characters(const std::string& str);
		/// Writes XML character data.
		///
		/// The characters must be encoded in UTF-8.

	void ignorableWhitespace(const char ch[], int start, int length);
		/// Writes whitespace characters by simply passing them to
		/// characters().

	void processingInstruction(const std::string& target, const std::string& data);
		/// Writes a processing instruction.

	void startPrefixMapping(const std::string& prefix, const std::string& namespaceURI);
		/// Begin the scope of a prefix-URI Namespace mapping.
		/// A namespace declaration is written with the next element.

	void endPrefixMapping(const std::string& prefix);
		/// End the scope of a prefix-URI mapping.

	void skippedEntity(const std::string& name);
		/// Does nothing.

	void dataElement(const std::string& namespaceURI, const std::string& localName, const std::string& qname, const std::string& data, 
	                 const std::string& attr1 = std::string(), const std::string& value1 = std::string(),
	                 const std::string& attr2 = std::string(), const std::string& value2 = std::string(),
	                 const std::string& attr3 = std::string(), const std::string& value3 = std::string());
		/// Writes a data element in the form <name attr1="value1"...>data</name>.

	// LexicalHandler
	void startCDATA();
		/// Writes the <![CDATA[ string that begins a CDATA section.
		/// Use characters() to write the actual character data.

	void endCDATA();
		/// Writes the ]]> string that ends a CDATA section.

	void comment(const char ch[], int start, int length);
		/// Writes a comment.

	void startDTD(const std::string& name, const std::string& publicId, const std::string& systemId);
		/// Writes a DTD declaration.

	void endDTD();
		/// Writes the closing characters of a DTD declaration.

	void startEntity(const std::string& name);
		/// Does nothing.

	void endEntity(const std::string& name);
		/// Does nothing.
	
	// DTDHandler
	void notationDecl(const std::string& name, const std::string* publicId, const std::string* systemId);
		/// Writes a notation to the header. startDocument must not have been called yet!

	void unparsedEntityDecl(const std::string& name, const std::string* publicId, const std::string& systemId, const std::string& notationName);
		/// Writes a unparsed entity to the header. startDocument must not have been called yet!

	// FISVocabularyHandler
	void setDocumentVocabulary(const DocumentVocabulary& voc);
		/// Sets the documentVocabulary. Only accepts default vocabularies.

	DocumentVocabulary& getDocumentVocabulary();
		/// Returns the documentVocabulary

	const DocumentVocabulary& getDocumentVocabulary() const;
		/// Returns the documentVocabulary as a const object

	void setWriteXMLDeclaration(bool val);
		/// Set to true if an XML declaration should be written.

	void setExternalVocabulary(const std::string& uri, const DocumentVocabulary& voc);
		/// Sets the location of the external dictionary and its content. The content is required
		/// so we can create a diff to the finally set initial vocabulary and encode only the difference!

	// FISContentHandler
	void binaryData(const char* buffer, std::size_t size);
	void encodedData(Poco::Int16 value);
	void encodedData(Poco::Int32 value);
	void encodedData(Poco::Int64 value);
	void encodedData(bool value);
	void encodedData(float value);
	void encodedData(double value);
	void encodedData(const Poco::UUID& uuid);

	// Helpers
	template <typename T> 
	void encodedData(const std::vector<T>& vec)
	{
		typename std::vector<T>::const_iterator it = vec.begin();
		typename std::vector<T>::const_iterator itEnd = vec.end();
		for (; it != itEnd; ++it)
			encodedData(*it);
	}

	template <typename T> 
	void encodedData(const std::set<T>& val)
	{
		typename std::set<T>::const_iterator it = val.begin();
		typename std::set<T>::const_iterator itEnd = val.end();
		for (; it != itEnd; ++it)
			encodedData(*it);
	}

protected:
	enum State
	{
		UNINITIALIZED,
		INDOCUMENT,
		INELEMENT,
		INCDATA,
		INDTD
	};
	typedef std::vector<State> States;

	typedef std::map<std::string, std::string> AttributeMap;
		/// Maps an attribute namespace prefix to a URI.
	
	struct AttributeValue
	{
		std::string prefix;
		std::string value;
		std::string namespaceURI;
		std::string localName;
	};

	typedef std::vector<AttributeValue> AttributeValues; 

	std::string newPrefix();
		/// Creates a new prefix.

	const std::string& nameToString(const std::string& localName, const std::string& qname) const;
		/// Returns either the localname of the qname.

	void declareAttributeNamespaces(const Poco::XML::Attributes& attributes);
		/// Declares the namespaces.

	void addNamespaceAttributes(AttributeMap& attributeMap);
		/// Checks which namespaces are new in the current state and returns them in the AttributeMap.

	void addAttributes(AttributeValues& attributeVals, const Poco::XML::Attributes& attributes, const std::string& elementNamespaceURI);
		/// Extracts all non-namespace attributes from parameter attributes and adds them to attributeVals,

	void handleEncodedData();
		/// Serializes any encoded character data, if present.

	void handleNamespaces(const Poco::XML::Attributes& attributes, const std::string& elementNamespaceURI, AttributeMap& nsAttributeMap, AttributeValues& attributeVal);
		/// Handles namespaces.

private:
	void writeHeader();

	void writeInitialVocabulary(const DocumentVocabulary& diff);
	
	void writeExternalVocabulary(const std::string& uri);

	void writeRestrictedAlphabet(const DocumentRestrictedAlphabet &al);

	void writeVocabulary(const DocumentVocabulary::XMLStringVocabulary& voc);

	void writeEncodedVocabulary(const DocumentVocabulary::XMLStringVocabulary& voc);

	void writeNameSurrogates(const QualifiedNameVocabulary& voc, bool inElement);

	void writeNotations(const std::vector<Notation>& notations);

	void writeUnparsedEntities(const std::vector<UnparsedEntity>& unparsedEntities);

	Poco::UInt32 writeIdentifyingStringOrIndex(const std::string& str, DocumentVocabulary::ID id);
		/// Returns the idx assigned to the string

	void writeIdentifyingString(const std::string& str, DocumentVocabulary::ID id);
		/// Serializes an identifying string.

	void writeIdentifyingStringIndex(Poco::UInt32 strIdx);
		/// Serializes an identifying string or an index presenting it.

	Poco::UInt32 writeQualifiedName(const std::string& prefix, const std::string& ns, const std::string& localName, bool inElement);
		/// Returns the index assigned to the tuple.

	Poco::UInt32 insertQualifiedName(const QualifiedNameEntry& qne, bool inElement);

	Poco::UInt32 writeQualifiedName(const QualifiedNameEntry& qne, bool inElement);

	void writeEncodedCharacterString(const std::string& str, Poco::UInt32 enc);
		/// Serializes an encoded character string.

	void writeEncodedCharacterString(Encoding::Ptr& str);
		/// Serializes an encoded character string.

	Poco::UInt32 writeNonIdentifyingStringOrIndex(const std::string& str, DocumentVocabulary::ID voc);
		/// Returns the idx assigned to the string

	Poco::UInt32 writeNonIdentifyingStringOrIndex(Encoding::Ptr& str, DocumentVocabulary::ID voc);
		/// Returns the idx assigned to the string

	Poco::UInt32 writeQualifiedNameOrIndex(const std::string& prefix, const std::string& ns, const std::string& localName, bool inElement);
		/// The last parameter specifies if we encode a qname of an element or of an attribute, returns the index assigned to the tuple.

	QualifiedNameVocabulary& getQNameVocabulary(bool inElement);
		/// Returns either the QualifiedNameVocabulary for attributes or elements depending on parameter inElement.

	void writeNamespaceAttribute(const std::string& prefix, const std::string& ns);
		/// Writes a namespace attribute.

	void writeNotation(const std::string& name, const std::string* pPublicId, const std::string* pSystemId);
		/// Writes a notation.

	void writeUnparsedEntity(const std::string& name, const std::string* pPublicId, const std::string& systemId, const std::string& notationName);
		/// Writes an unparsed entity.

	void writeProcessingInstruction(const std::string& target, const std::string& content);
		/// Writes a processing instruction.

	void writeDocumentTypeDeclaration(const std::string& publicId, const std::string& systemId);
		/// Writes a document type declaration.

	void writeComment(const std::string& comment);
		/// Writes a comment.

	void writeCharacterChunk(const std::string& characterChunk);
		/// Writes a character chunk.

	void writeUnexpandedEntityReference(const std::string& name, const std::string* pPublicId, const std::string* pSystemId);
		/// Writes an unexpanded entitiy reference.

	void writeAttribute(const std::string& prefix, const std::string& ns, const std::string& localName, const std::string& normalizedValue);
		/// Writes an attribute.

	void writeElement(const std::string& prefix, const std::string& ns, const std::string& localName, const AttributeValues& attributes, const AttributeMap& nsAttributes);
		/// Writes an element.

	void insertEncoding(const Encoding::Ptr& ptr);

private:
	enum
	{
		DEFAULT_MAX_INDEXED_STRING_LENGTH = 16
	};

	BitStreamWriter    _writer;
	bool               _writeXmlDeclaration;
	DocumentVocabulary _docVocabulary;
	States             _states;
	int                _prefix;
	Poco::XML::NamespaceSupport _namespaces;
	
	std::vector<Encoding::Ptr>    _encodedData;
	std::vector<Notation>       _notations;
	std::vector<UnparsedEntity> _unparsedEntities;
	DocumentVocabulary _externalVocabulary;
	std::string        _externalURI;
	EncodingAlgorithm  _encoding;
	int _maxIndexedStringLength;
};


//
// inlines
//
inline void FastInfosetWriter::setMaxIndexedStringLength(int length)
{
	_maxIndexedStringLength = length;
}


inline int FastInfosetWriter::getMaxIndexedStringLength() const
{
	return _maxIndexedStringLength;
}


inline void FastInfosetWriter::setDocumentVocabulary(const DocumentVocabulary& voc)
{
	if (voc.impl() == DocumentVocabulary::VOC_VECTOR)
		throw Poco::InvalidArgumentException("A DocumentVocabulary with VOC_VECTOR implementation cannot be used by FastInfosetWriter");
	_docVocabulary = voc;
}


inline DocumentVocabulary& FastInfosetWriter::getDocumentVocabulary()
{
	return _docVocabulary;
}


inline const DocumentVocabulary& FastInfosetWriter::getDocumentVocabulary() const
{
	return _docVocabulary;
}


inline void FastInfosetWriter::setWriteXMLDeclaration(bool val)
{
	_writeXmlDeclaration = val;
}


inline QualifiedNameVocabulary& FastInfosetWriter::getQNameVocabulary(bool inElement)
{
	if (inElement)
		return _docVocabulary.elementVocabulary();
	return _docVocabulary.attributeVocabulary();
}


inline void FastInfosetWriter::setExternalVocabulary(const std::string& uri, const DocumentVocabulary& voc)
{
	_externalVocabulary = voc;
	_externalURI = uri;
}


} } // namespace Poco::FastInfoset


#endif // FastInfoset_FastInfosetWriter_INCLUDED

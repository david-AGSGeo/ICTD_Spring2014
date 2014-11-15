//
// FastInfosetParser.h
//
// $Id: //poco/1.4/FastInfoset/include/Poco/FastInfoset/FastInfosetParser.h#1 $
//
// Library: FastInfoset
// Package: SAX
// Module:  FastInfosetParser
//
// Definition of the FastInfosetParser class.
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


#ifndef FastInfoset_FastInfosetParser_INCLUDED
#define FastInfoset_FastInfosetParser_INCLUDED


#include "Poco/FastInfoset/FastInfoset.h"
#include "Poco/FastInfoset/DocumentVocabulary.h"
#include "Poco/FastInfoset/BitStreamReader.h"
#include "Poco/FastInfoset/Decoder.h"
#include "Poco/FastInfoset/Encoding.h"
#include "Poco/FastInfoset/FISException.h"
#include "Poco/SAX/XMLReader.h"
#include "Poco/SAX/AttributesImpl.h"


namespace Poco {
namespace XML {


class DeclHandler;
class LexicalHandler;
class XMLWriter;


} // namespace XML


namespace FastInfoset {


class FISDocumentHandler;
class IdentifyingStringOrIndex;
class QualifiedName;
class QualifiedNameOrIndex;
class NonIdentifyingStringOrIndex;
class FastInfosetWriter;
class FISContentHandler;
class FISDocumentHandler;


class FastInfoset_API FastInfosetParser: public Poco::XML::XMLReader
	/// This class provides a SAX2 (Simple API for XML) interface
	/// for parsing a Fast Infoset document.
	///
	/// For more information, please refer to the Poco::XML::XMLReader
	/// class.
	///
	/// The following SAX2 features and properties are supported:
	///   * http://xml.org/sax/features/namespaces
	///   * http://xml.org/sax/features/namespace-prefixes
	///   * http://xml.org/sax/properties/lexical-handler
	///   * http://xml.org/sax/properties/declaration-handler
	///
	/// Note that namespace support is always enabled and cannot be
	/// turned off.
	///
	/// The parser supports external vocabularies but it does not 
	/// support user defined encodings.
{
public:
	explicit FastInfosetParser(DocumentVocabulary::VocabularyImpl vocImpl = DocumentVocabulary::VOC_VECTOR);
		/// Creates the FastInfosetParser, using the given vocabulary implementation.
		///
		/// Using DocumentVocabulary::VOC_VECTOR will result in fastest parsing performance, 
		/// however the document vocabulary produced by the parser cannot be used by a
		/// FastInfosetWriter.
		///
		/// For more information, see the DocumentVocabulary class.

	explicit FastInfosetParser(const DocumentVocabulary& voc);
		/// Creates the FastInfosetParser, using the given external vocabulary.
		///
		/// For more information, see the DocumentVocabulary class.

	~FastInfosetParser();
		/// Destroys the FastInfosetParser.

	void initialize(FastInfosetWriter* pWriter);
		/// Initializes the handlers with the given FastInfosetWriter 
		/// (including ContentHandler, LexicalHandler, DTDHandler, FISDocumentHandler).
		///
		/// This is mostly useful for testing purposes.

	void initialize(Poco::XML::XMLWriter* pWriter);
		/// Initializes the handlers with the given XMLWriter 
		/// (including ContentHandler, LexicalHandler, DTDHandler, FISDocumentHandler).
		///
		/// This is useful for converting a Fast Infoset document
		/// into an equivalent XML document.

	void setEntityResolver(Poco::XML::EntityResolver* pResolver);
		/// Allow an application to register an entity resolver.
		///
		/// If the application does not register an entity resolver, the 
		/// XMLReader will perform its own default resolution.
		/// 
		/// Applications may register a new or different resolver in the middle of a 
		/// parse, and the SAX parser must begin using the new resolver immediately.

	Poco::XML::EntityResolver* getEntityResolver() const;
		/// Return the current entity resolver.

	void setDTDHandler(Poco::XML::DTDHandler* pDTDHandler);
		/// Allow an application to register a DTD event handler.
		///
		/// If the application does not register a DTD handler, all DTD events reported by 
		/// the SAX parser will be silently ignored.
		/// 
		/// Applications may register a new or different handler in the middle of a parse, 
		/// and the SAX parser must begin using the new handler immediately.

	Poco::XML::DTDHandler* getDTDHandler() const;
		/// Return the current DTD handler.
		
	void setDocumentHandler(FISDocumentHandler* pDocumentHandler);
		/// Allow an application to register a Fast Infoset document handler.
		///
		/// The Fast Infoset document handler is used to 
		/// access the vocabulary of a Fast Infoset document.
		
	FISDocumentHandler* getDocumentHandler() const;
		/// Return the current Fast Infoset document handler.

	void setContentHandler(Poco::XML::ContentHandler* pContentHandler);
		/// Allow an application to register a content event handler.
		/// 
		/// If the application does not register a content handler, all content events 
		/// reported by the SAX parser will be silently ignored.
		/// 
		/// Applications may register a new or different handler in the middle of a parse, 
		/// and the SAX parser must begin using the new handler immediately.
		///
		/// Instead of a Poco::XML::ContentHandler, an application can also
		/// register an instance of FISContentHandler to read encoded data (such as
		/// integers or floating point values) in their binary representation.

	Poco::XML::ContentHandler* getContentHandler() const;
		/// Return the current content handler.

	void setErrorHandler(Poco::XML::ErrorHandler* pErrorHandler);
		/// Allow an application to register an error event handler.
		///
		/// If the application does not register an error handler, all error events reported by 
		/// the SAX parser will be silently ignored; however, normal processing may not continue. 
		/// It is highly recommended that all SAX applications implement an error handler to avoid 
		/// unexpected bugs.
		/// 
		/// Applications may register a new or different handler in the middle of a parse, and the 
		/// SAX parser must begin using the new handler immediately.

	Poco::XML::ErrorHandler* getErrorHandler() const;
		/// Return the current error handler.
	
	void setFeature(const std::string& featureId, bool state);
		/// Set the state of a feature.
		///
		/// The feature name is any fully-qualified URI. It is possible for an XMLReader to 
		/// expose a feature value but to be unable to change the current value. Some feature 
		/// values may be immutable or mutable only in specific contexts, such as before, during, 
		/// or after a parse.
		/// 
		/// All XMLReaders are required to support setting http://xml.org/sax/features/namespaces 
		/// to true and http://xml.org/sax/features/namespace-prefixes to false.

	bool getFeature(const std::string& featureId) const;
		/// Look up the value of a feature.
		///
		/// The feature name is any fully-qualified URI. It is possible for an XMLReader 
		/// to recognize a feature name but temporarily be unable to return its value. 
		/// Some feature values may be available only in specific contexts, such as before, 
		/// during, or after a parse. Also, some feature values may not be programmatically 
		/// accessible. (In the case of an adapter for SAX1 Parser, there is no 
		/// implementation-independent way to expose whether the underlying parser is performing 
		/// validation, expanding external entities, and so forth.)
		/// 
		/// All XMLReaders are required to recognize the 
		/// http://xml.org/sax/features/namespaces and the 
		/// http://xml.org/sax/features/namespace-prefixes feature names.
		/// Implementors are free (and encouraged) to invent their own features, 
		/// using names built on their own URIs.
		
	void setProperty(const std::string& propertyId, const std::string& value);
		/// Set the value of a property.
		/// 
		/// The property name is any fully-qualified URI. It is possible for an XMLReader 
		/// to recognize a property name but to be unable to change the current value. 
		/// Some property values may be immutable or mutable only in specific contexts, 
		/// such as before, during, or after a parse.
		/// 
		/// XMLReaders are not required to recognize setting any specific property names, though a 
		/// core set is defined by SAX2.
		/// 
		/// This method is also the standard mechanism for setting extended handlers.

	void setProperty(const std::string& propertyId, void* value);
		/// Set the value of a property.
		/// See also setProperty(const std::string&, const std::string&).

	void* getProperty(const std::string& propertyId) const;
		/// Look up the value of a property.
		/// String values are returned as char*
		/// The property name is any fully-qualified URI. It is possible for an XMLReader to 
		/// recognize a property name but temporarily be unable to return its value. Some property 
		/// values may be available only in specific contexts, such as before, during, or after a parse.
		///
		/// XMLReaders are not required to recognize any specific property names, though an initial 
		/// core set is documented for SAX2.
		/// 
		/// Implementors are free (and encouraged) to invent their own properties, using names 
		/// built on their own URIs.

	void parse(Poco::XML::InputSource* pSource);
		/// Parse a Fast Infoset document.
		/// 
		/// The application can use this method to instruct the XML reader to begin parsing an 
		/// Fast Infoset document from any valid input source (a character stream, a byte stream, or a URI).
		/// 
		/// Applications may not invoke this method while a parse is in progress (they should create 
		/// a new XMLReader instead for each nested XML document). Once a parse is complete, an 
		/// application may reuse the same XMLReader object, possibly with a different input source. 
		/// Configuration of the XMLReader object (such as handler bindings and values established for 
		/// feature flags and properties) is unchanged by completion of a parse, unless the definition of that 
		/// aspect of the configuration explicitly specifies other behavior. (For example, feature flags or 
		/// properties exposing characteristics of the document being parsed.)
		/// 
		/// During the parse, the XMLReader will provide information about the XML document through the registered 
		/// event handlers.
		///
		/// This method is synchronous: it will not return until parsing has ended. If a client application 
		/// wants to terminate parsing early, it should throw an exception.

	void parse(const std::string& systemId);
		/// Parse a Fast Infoset document from a system identifier.
		///
		/// See also parse(InputSource*).

	void parseMemoryNP(const char* xml, std::size_t size);
		/// Parse a Fast Infoset document from a memory buffer.
		/// This is generally the fastest method for parsing a 
		/// Fast Infoset document.
		///
		/// See also parse(InputSource*).

	const DocumentVocabulary& vocabulary() const;
		/// Returns the vocabulary built up by the parser.

private:
	struct ResolvedQualName
		/// Internal data struct presenting a qualifiedName, introduced to avoid string copying where possible, reduces memory overhead.
	{
		const std::string* pPrefix;
		const std::string* pUri;
		const std::string* pLocalName;
		ResolvedQualName();
	};

	void parseDocument(BitStreamReader& aReader);
		/// Parses the document and all of its children.

	void parseDocumentChildren(BitStreamReader& aReader, const Decoder::OpenHeaderParts& parts);
		/// Parses all document children.

	void parseElement(BitStreamReader& aReader);
		/// Parses a single element with all children.

	void parseElementChildren(BitStreamReader& aReader);
		/// Parses all element children.

	bool parseElementChild(BitStreamReader& aReader);
		/// Parses one single element child.

	Encoding::Ptr parseEncodedCharacterString(BitStreamReader& aReader);
		/// Reads an encodedCharacterString and returns the decoded version.

	const std::string& parseEncodedCharacterStringXML(BitStreamReader& aReader, Poco::UInt32& type);
		/// Reads an encodedCharacterString and returns the decoded version. Always returns a reference to
		/// _encodedCharacterString for performance reasons! Make sure to copy the returned value if subsequent
		/// calls tothis method occur.

	const std::string& parseIdentifyingStringOrIndex(BitStreamReader& aReader, DocumentVocabulary::ID id);
		/// Reads an IdentifyingStringOrIndex, always returns the string value of that type.

	const std::string& parseIdentifyingStringOrIndex(BitStreamReader& aReader, DocumentVocabulary::ID id, Poco::UInt32& index);
		/// Reads an IdentifyingStringOrIndex, always returns the string value of that type.

	const std::string& parseCondIdentifyingStringOrIndex(BitStreamReader& aReader, bool retData, DocumentVocabulary::ID id);
		/// Same as above but conditional, returns an empty string if retData is false. Useful for optional string entries.

	Encoding::Ptr parseNonIdentifyingStringOrIndex(BitStreamReader& aReader, DocumentVocabulary::ID id);
		/// Reads an NonIdentifyingStringOrIndex, always returns the string value of that type

	const std::string& parseNonIdentifyingStringOrIndexXML(BitStreamReader& aReader, DocumentVocabulary::ID id, Poco::UInt32& type);
		/// Reads an NonIdentifyingStringOrIndex, always returns the string value of that type

	void parseQualifiedNameOrIndex(BitStreamReader& aReader, ResolvedQualName& qualName, bool isElement);
		/// Parses a QualifiedNameOrIndex attribute, always returns the resolved qualified name (ie strings instead of indices)

	void parseNamespaceAttribute(BitStreamReader& aReader, Poco::XML::AttributesImpl& attrs);
		/// Reads a nameSpaceAttribute, and declares it.

	const QualifiedNameEntry& getQualifiedNameEntry(Poco::UInt32 idx, bool isElement);
		/// Looksup for the given idx the assigned QualifiedNameEntry.

	QualifiedNameVocabulary& getQNameVocabulary(bool inElement);
		/// Returns either the QualifiedNameVocabulary for attributes or elements depending on parameter inElement.

	void parseNotation(BitStreamReader& aReader);
		/// Parses over a notation.

	void parseUnparsedEntity(BitStreamReader& aReader);
		/// Parses an unparsed entity.

	void parseDocumentTypeDeclaration(BitStreamReader& aReader);
		/// Parses a document type declaration.

	void parseProcessingInstruction(BitStreamReader& aReader);
		/// Parses a processing instruction.

	void parseComment(BitStreamReader& aReader);
		/// Parses a comment.

	void parseCharacterChunk(BitStreamReader& aReader);
		/// Parses a character chunk.

	void parseUnexpandedEntityReference(BitStreamReader& aReader);
		/// Parses a unexpanded entity reference.

	void parseAttribute(BitStreamReader& aReader, Poco::XML::AttributesImpl& attrs);
		/// Parses an attribute.

private:
	Poco::XML::EntityResolver* _pEntityResolver;
	Poco::XML::DTDHandler*     _pDTDHandler;
	Poco::XML::ContentHandler* _pContentHandler;
	Poco::XML::ErrorHandler*   _pErrorHandler;
	Poco::XML::DeclHandler*    _pDeclHandler;
	Poco::XML::LexicalHandler* _pLexicalHandler;
	FISDocumentHandler*  _pDocumentHandler;
	FISContentHandler*   _pFISHandler;
	bool _namespacePrefixes;
	DocumentVocabulary   _voc;
	Poco::XML::AttributesImpl _attr;
	Poco::XML::AttributesImpl _nsAttr;

	bool                 _inCDATA;
	std::string          _encodedCharacterString;
	std::string          _decodedCharacterString;
	std::string          _tempString;
	std::string          _qname;
	Encoding::Ptr        _pNullEncoding;
	Encoding::Ptr        _pNullRefEncoding;

	static const std::string EMPTY_STRING;
	static const std::string XMLNS;

	friend class FastInfosetWriter;
};


//
// inlines
//
inline void FastInfosetParser::parseElementChildren(BitStreamReader& aReader)
{
	bool ok = true;
	Poco::UInt8 ns;
	aReader.peek(ns, 4);
	while (ok && ns != 15)
	{
		ok = parseElementChild(aReader);
		aReader.peek(ns, 4);
	}
	if (!ok) throw FISParseException("Unexpected end of stream while parsing element children");
}


inline const QualifiedNameEntry& FastInfosetParser::getQualifiedNameEntry(Poco::UInt32 idx, bool isElement)
{
	if (isElement)
	{
		return _voc.elementVocabulary().value(idx);
	}
	else
	{
		return _voc.attributeVocabulary().value(idx);
	}
}


inline const std::string& FastInfosetParser::parseCondIdentifyingStringOrIndex(BitStreamReader& aReader, bool retData, DocumentVocabulary::ID id)
{
	if (!retData)
		return EMPTY_STRING;
	return parseIdentifyingStringOrIndex(aReader, id);
}


inline QualifiedNameVocabulary& FastInfosetParser::getQNameVocabulary(bool inElement)
{
	if (inElement)
		return _voc.elementVocabulary();
	return _voc.attributeVocabulary();
}


inline const DocumentVocabulary& FastInfosetParser::vocabulary() const
{
	return _voc;
}


} } // namespace Poco::FastInfoset


#endif // FastInfoset_FastInfosetParser_INCLUDED

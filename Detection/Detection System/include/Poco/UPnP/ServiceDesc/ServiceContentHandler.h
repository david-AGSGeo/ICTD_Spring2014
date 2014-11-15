//
// ServiceContentHandler.h
//
// $Id: //poco/1.4/UPnP/ServiceDesc/include/Poco/UPnP/ServiceDesc/ServiceContentHandler.h#1 $
//
// Library: UPnP/ServiceDesc
// Package: ServiceDescParser
// Module:  ServiceContentHandler
//
// Definition of the ServiceContentHandler class.
//
// Copyright (c) 2011-2013, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef UPnP_ServiceDesc_ServiceContentHandler_INCLUDED
#define UPnP_ServiceDesc_ServiceContentHandler_INCLUDED


#include "Poco/UPnP/ServiceDesc/ServiceDesc.h"
#include "Poco/UPnP/ServiceDesc/ServiceStateMachine.h"
#include "Poco/UPnP/ServiceDesc/ListRestriction.h"
#include "Poco/UPnP/ServiceDesc/RangeRestriction.h"
#include "Poco/UPnP/ServiceDesc/Service.h"
#include "Poco/SAX/ContentHandler.h"
#include "Poco/SAX/AttributesImpl.h"
#include "Poco/Mutex.h"
#include <stack>
#include <vector>


namespace Poco {
namespace UPnP {
namespace ServiceDesc {


class UPnP_ServiceDesc_API ServiceContentHandler: public XML::ContentHandler
	/// The ServiceContentHandler is used to parse a UPnP
	/// Service Description XML document.
{
public:
	static const XML::XMLString VAL_NO;

	ServiceContentHandler();
		/// Creates the ServiceContentHandler.

	~ServiceContentHandler();
		/// Destroys the ServiceContentHandler.

	Service::Ptr service() const;
		/// Returns the loaded service.
	
	//  Poco::XML::ContentHandler
	void setDocumentLocator(const XML::Locator* loc);
	void startDocument();
	void endDocument();
	void startElement(const XML::XMLString& uri, const XML::XMLString& localName, const XML::XMLString& qname, const XML::Attributes& attrList);
	void endElement(const XML::XMLString& uri, const XML::XMLString& localName, const XML::XMLString& qname);
	void characters(const XML::XMLChar ch[], int start, int length);
	void ignorableWhitespace(const XML::XMLChar ch[], int start, int length);
	void processingInstruction(const XML::XMLString& target, const XML::XMLString& data);
	void startPrefixMapping(const XML::XMLString& prefix, const XML::XMLString& uri);
	void endPrefixMapping(const XML::XMLString& prefix);
	void skippedEntity(const XML::XMLString& name);

private:
	void stateUninitializedStart(const XML::XMLString& uri, const XML::XMLString& localName, const XML::XMLString& qname, const XML::Attributes& attrList);
	void stateUninitializedEnd(const XML::XMLString& uri, const XML::XMLString& localName, const XML::XMLString& qname);
	void stateScpdStart(const XML::XMLString& uri, const XML::XMLString& localName, const XML::XMLString& qname, const XML::Attributes& attrList);
	void stateSpecVersionStart(const XML::XMLString& uri, const XML::XMLString& localName, const XML::XMLString& qname, const XML::Attributes& attrList);
	void stateMajorStart(const XML::XMLString& uri, const XML::XMLString& localName, const XML::XMLString& qname, const XML::Attributes& attrList);
	void stateMinorStart(const XML::XMLString& uri, const XML::XMLString& localName, const XML::XMLString& qname, const XML::Attributes& attrList);
	void stateActionListStart(const XML::XMLString& uri, const XML::XMLString& localName, const XML::XMLString& qname, const XML::Attributes& attrList);
	void stateActionStart(const XML::XMLString& uri, const XML::XMLString& localName, const XML::XMLString& qname, const XML::Attributes& attrList);
	void stateActionNameStart(const XML::XMLString& uri, const XML::XMLString& localName, const XML::XMLString& qname, const XML::Attributes& attrList);
	void stateActionOptionalStart(const XML::XMLString& uri, const XML::XMLString& localName, const XML::XMLString& qname, const XML::Attributes& attrList);
	void stateArgumentListStart(const XML::XMLString& uri, const XML::XMLString& localName, const XML::XMLString& qname, const XML::Attributes& attrList);
	void stateArgumentStart(const XML::XMLString& uri, const XML::XMLString& localName, const XML::XMLString& qname, const XML::Attributes& attrList);
	void stateArgumentNameStart(const XML::XMLString& uri, const XML::XMLString& localName, const XML::XMLString& qname, const XML::Attributes& attrList);
	void stateArgumentDirectionStart(const XML::XMLString& uri, const XML::XMLString& localName, const XML::XMLString& qname, const XML::Attributes& attrList);
	void stateArgumentRetValStart(const XML::XMLString& uri, const XML::XMLString& localName, const XML::XMLString& qname, const XML::Attributes& attrList);
	void stateArgumentRelatedStateVariableStart(const XML::XMLString& uri, const XML::XMLString& localName, const XML::XMLString& qname, const XML::Attributes& attrList);
	void stateServiceStateTableStart(const XML::XMLString& uri, const XML::XMLString& localName, const XML::XMLString& qname, const XML::Attributes& attrList);
	void stateStateVariableStart(const XML::XMLString& uri, const XML::XMLString& localName, const XML::XMLString& qname, const XML::Attributes& attrList);
	void stateStateVariableNameStart(const XML::XMLString& uri, const XML::XMLString& localName, const XML::XMLString& qname, const XML::Attributes& attrList);
	void stateStateVariableDatatypeStart(const XML::XMLString& uri, const XML::XMLString& localName, const XML::XMLString& qname, const XML::Attributes& attrList);
	void stateStateVariableDefaultValueStart(const XML::XMLString& uri, const XML::XMLString& localName, const XML::XMLString& qname, const XML::Attributes& attrList);
	void stateStateVariableAllowedValueStart(const XML::XMLString& uri, const XML::XMLString& localName, const XML::XMLString& qname, const XML::Attributes& attrList);
	void stateStateVariableAllowedValuelistStart(const XML::XMLString& uri, const XML::XMLString& localName, const XML::XMLString& qname, const XML::Attributes& attrList);
	void stateStateVariableAllowedValueRangeStart(const XML::XMLString& uri, const XML::XMLString& localName, const XML::XMLString& qname, const XML::Attributes& attrList);
	void stateStateVariableAllowedValueRangeMinStart(const XML::XMLString& uri, const XML::XMLString& localName, const XML::XMLString& qname, const XML::Attributes& attrList);
	void stateStateVariableAllowedValueRangeMaxStart(const XML::XMLString& uri, const XML::XMLString& localName, const XML::XMLString& qname, const XML::Attributes& attrList);
	void stateStateVariableAllowedValueRangeStepStart(const XML::XMLString& uri, const XML::XMLString& localName, const XML::XMLString& qname, const XML::Attributes& attrList);
	void stateSendEventsAttributeStart(const XML::XMLString& uri, const XML::XMLString& localName, const XML::XMLString& qname, const XML::Attributes& attrList);
	void stateStateVariableOptionalStart(const XML::XMLString& uri, const XML::XMLString& localName, const XML::XMLString& qname, const XML::Attributes& attrList);
	void stateScpdEnd(const XML::XMLString& uri, const XML::XMLString& localName, const XML::XMLString& qname);
	void stateSpecVersionEnd(const XML::XMLString& uri, const XML::XMLString& localName, const XML::XMLString& qname);
	void stateMajorEnd(const XML::XMLString& uri, const XML::XMLString& localName, const XML::XMLString& qname);
	void stateMinorEnd(const XML::XMLString& uri, const XML::XMLString& localName, const XML::XMLString& qname);
	void stateActionListEnd(const XML::XMLString& uri, const XML::XMLString& localName, const XML::XMLString& qname);
	void stateActionEnd(const XML::XMLString& uri, const XML::XMLString& localName, const XML::XMLString& qname);
	void stateActionNameEnd(const XML::XMLString& uri, const XML::XMLString& localName, const XML::XMLString& qname);
	void stateActionOptionalEnd(const XML::XMLString& uri, const XML::XMLString& localName, const XML::XMLString& qname);
	void stateArgumentListEnd(const XML::XMLString& uri, const XML::XMLString& localName, const XML::XMLString& qname);
	void stateArgumentEnd(const XML::XMLString& uri, const XML::XMLString& localName, const XML::XMLString& qname);
	void stateArgumentNameEnd(const XML::XMLString& uri, const XML::XMLString& localName, const XML::XMLString& qname);
	void stateArgumentDirectionEnd(const XML::XMLString& uri, const XML::XMLString& localName, const XML::XMLString& qname);
	void stateArgumentRetValEnd(const XML::XMLString& uri, const XML::XMLString& localName, const XML::XMLString& qname);
	void stateArgumentRelatedStateVariableEnd(const XML::XMLString& uri, const XML::XMLString& localName, const XML::XMLString& qname);
	void stateServiceStateTableEnd(const XML::XMLString& uri, const XML::XMLString& localName, const XML::XMLString& qname);
	void stateStateVariableEnd(const XML::XMLString& uri, const XML::XMLString& localName, const XML::XMLString& qname);
	void stateStateVariableNameEnd(const XML::XMLString& uri, const XML::XMLString& localName, const XML::XMLString& qname);
	void stateStateVariableDatatypeEnd(const XML::XMLString& uri, const XML::XMLString& localName, const XML::XMLString& qname);
	void stateStateVariableDefaultValueEnd(const XML::XMLString& uri, const XML::XMLString& localName, const XML::XMLString& qname);
	void stateStateVariableAllowedValueEnd(const XML::XMLString& uri, const XML::XMLString& localName, const XML::XMLString& qname);
	void stateStateVariableAllowedValuelistEnd(const XML::XMLString& uri, const XML::XMLString& localName, const XML::XMLString& qname);
	void stateStateVariableAllowedValueRangeEnd(const XML::XMLString& uri, const XML::XMLString& localName, const XML::XMLString& qname);
	void stateStateVariableAllowedValueRangeMinEnd(const XML::XMLString& uri, const XML::XMLString& localName, const XML::XMLString& qname);
	void stateStateVariableAllowedValueRangeMaxEnd(const XML::XMLString& uri, const XML::XMLString& localName, const XML::XMLString& qname);
	void stateStateVariableAllowedValueRangeStepEnd(const XML::XMLString& uri, const XML::XMLString& localName, const XML::XMLString& qname);
	void stateSendEventsAttributeEnd(const XML::XMLString& uri, const XML::XMLString& localName, const XML::XMLString& qname);
	void stateStateVariableOptionalEnd(const XML::XMLString& uri, const XML::XMLString& localName, const XML::XMLString& qname);
	int getCharactersAsInt() const;
	int getCharactersAsInt(int def) const;
	static const std::string& serviceToCppType(const std::string& serviceType);
	static void initTypeMappings();

private:
	ServiceStateMachine _stateMachine;
	std::stack<ServiceStateMachine::State> _states;
	XML::XMLString _characters;
	Service::Ptr _pService;
	Argument _arg;
	ListRestriction::Ptr _pListRestriction;
	RangeRestriction::Ptr _pRangeRestriction;
	
	static std::map<std::string, std::string> _typeMappings;
	static Poco::FastMutex _mutex;

	friend class ServiceStateMachine;
	friend struct ServiceStateMachine::StateInfo;
};


//
// inlines
//
inline Service::Ptr ServiceContentHandler::service() const
{
	return _pService;
}


} } } // namespace Poco::UPnP::ServiceDesc


#endif // UPnP_ServiceDesc_ServiceContentHandler_INCLUDED

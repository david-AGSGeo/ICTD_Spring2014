//
// ServiceStateMachine.h
//
// $Id: //poco/1.4/UPnP/ServiceDesc/include/Poco/UPnP/ServiceDesc/ServiceStateMachine.h#1 $
//
// Library: UPnP/ServiceDesc
// Package: ServiceDescParser
// Module:  ServiceStateMachine
//
// Definition of the ServiceStateMachine class.
//
// Copyright (c) 2011-2013, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef UPnP_ServiceDesc_ServiceStateMachine_INCLUDED
#define UPnP_ServiceDesc_ServiceStateMachine_INCLUDED


#include "Poco/UPnP/ServiceDesc/ServiceDesc.h"
#include "Poco/XML/XMLString.h"
#include "Poco/SAX/Attributes.h"
#include <set>
#include <vector>
#include <map>


namespace Poco {
namespace UPnP {
namespace ServiceDesc {


class ServiceContentHandler;


class UPnP_ServiceDesc_API ServiceStateMachine
	/// A state machine for parsing a UPnP XML service description.
{
public:
	static const XML::XMLString EL_SCPD;
	static const XML::XMLString EL_SPECVERSION;
	static const XML::XMLString EL_MAJOR;
	static const XML::XMLString EL_MINOR;
	static const XML::XMLString EL_ACTIONLIST;
	static const XML::XMLString EL_ACTION;
	static const XML::XMLString EL_ACTION_NAME;
	static const XML::XMLString EL_ACTION_OPTIONAL;
	static const XML::XMLString EL_ARGUMENTLIST;
	static const XML::XMLString EL_ARGUMENT;
	static const XML::XMLString EL_ARGUMENT_NAME;
	static const XML::XMLString EL_ARGUMENT_DIRECTION;
	static const XML::XMLString EL_ARGUMENT_RETVAL;
	static const XML::XMLString EL_ARGUMENT_RELATEDSTATEVARIABLE;
	static const XML::XMLString EL_SERVICESTATETABLE;
	static const XML::XMLString EL_STATEVARIABLE;
	static const XML::XMLString EL_STATEVARIABLE_NAME;
	static const XML::XMLString EL_STATEVARIABLE_DATATYPE;
	static const XML::XMLString EL_STATEVARIABLE_DEFAULTVALUE;
	static const XML::XMLString EL_STATEVARIABLE_ALLOWEDVALUE;
	static const XML::XMLString EL_STATEVARIABLE_ALLOWEDVALUELIST;
	static const XML::XMLString EL_STATEVARIABLE_ALLOWEDVALUERANGE;
	static const XML::XMLString EL_STATEVARIABLE_ALLOWEDVALUERANGE_MIN;
	static const XML::XMLString EL_STATEVARIABLE_ALLOWEDVALUERANGE_MAX;
	static const XML::XMLString EL_STATEVARIABLE_ALLOWEDVALUERANGE_STEP;
	static const XML::XMLString EL_STATEVARIABLE_OPTIONAL;
	static const XML::XMLString EL_SENDEVENTSATTRIBUTE;
	static const XML::XMLString ATTR_SENDEVENTS;
	
	enum State
	{
		ST_UNINITIALIZED = 0,
		ST_INITIALIZED,
		ST_SCPD,
		ST_SPECVERSION,
		ST_MAJOR,
		ST_MINOR,
		ST_ACTIONLIST,
		ST_ACTION,
		ST_ACTION_NAME,
		ST_ACTION_OPTIONAL, // non-standard extension needed for some profiles!
		ST_ARGUMENTLIST,
		ST_ARGUMENT,
		ST_ARGUMENT_NAME,
		ST_ARGUMENT_DIRECTION,
		ST_ARGUMENT_RETVAL,
		ST_ARGUMENT_RELATEDSTATEVARIABLE,
		ST_SERVICESTATETABLE,
		ST_STATEVARIABLE,
		ST_STATEVARIABLE_NAME,
		ST_STATEVARIABLE_DATATYPE,
		ST_STATEVARIABLE_DEFAULTVALUE,
		ST_STATEVARIABLE_ALLOWEDVALUE,
		ST_STATEVARIABLE_ALLOWEDVALUELIST,
		ST_STATEVARIABLE_ALLOWEDVALUERANGE,
		ST_STATEVARIABLE_ALLOWEDVALUERANGE_MIN,
		ST_STATEVARIABLE_ALLOWEDVALUERANGE_MAX,
		ST_STATEVARIABLE_ALLOWEDVALUERANGE_STEP,
		ST_STATEVARIABLE_OPTIONAL, // non-standard extension needed for some profiles!
		ST_SENDEVENTSATTRIBUTE, // non-standard extension needed for some profiles!
		ST_FINISHED
	};

	typedef void (ServiceContentHandler::*StartMethod)(const XML::XMLString&, const XML::XMLString&, const XML::XMLString&, const XML::Attributes&);
	typedef void (ServiceContentHandler::*EndMethod)(const XML::XMLString&, const XML::XMLString&, const XML::XMLString&);
	typedef std::map<XML::XMLString, State> Successors;

	struct StateInfo
	{
		State       _state;
		StartMethod _start;
		EndMethod   _end;
		Successors    _successors;
		
		StateInfo();
		StateInfo(State _state, StartMethod start, EndMethod end, const Successors& successors);
		bool isValidSuccessor(const XML::XMLString& localName) const;
		State successorState(const XML::XMLString& localName) const;
	};

	typedef std::vector<StateInfo> StateInfos;
		/// the position of the vector equals the int value of the enum State

	typedef std::map<XML::XMLString, ServiceStateMachine::State> StateMap;
		/// Maps an element name to the assigned State
		/// Due to performance reasons we define the localname of the xsd element
		/// as the key. The correct behavior would be to use the localname AND the url.

	ServiceStateMachine();
		/// Creates the ServiceStateMachine.

	virtual ~ServiceStateMachine();
		/// Destroys the ServiceStateMachine.

	const ServiceStateMachine::StateInfo& stateInfo(ServiceStateMachine::State aState) const;
	ServiceStateMachine::State state(const XML::XMLString& elementName, ServiceStateMachine::State parent) const;

private:
	void initialize();
	void defineStateInitialized();
	void defineStateScpd();
	void defineStateSpecVersion();
	void defineStateMajor();
	void defineStateMinor();
	void defineStateActionList();
	void defineStateAction();
	void defineStateActionName();
	void defineStateActionOptional();
	void defineStateArgumentList();
	void defineStateArgument();
	void defineStateArgumentName();
	void defineStateArgumentDirection();
	void defineStateArgumentRetVal();
	void defineStateArgumentRelatedStateVariable();
	void defineStateServiceStateTable();
	void defineStateStateVariable();
	void defineStateStateVariableName();
	void defineStateStateVariableDatatype();
	void defineStateStateVariableDefaultValue();
	void defineStateStateVariableAllowedValue();
	void defineStateStateVariableAllowedValuelist();
	void defineStateStateVariableAllowedValueRange();
	void defineStateStateVariableAllowedValueRangeMin();
	void defineStateStateVariableAllowedValueRangeMax();
	void defineStateStateVariableAllowedValueRangeStep();
	void defineStateSendEventsAttribute();
	void defineStateStateVariableOptional();

private:
	StateInfos _stateInfos;
};


//
// inlines
//
inline ServiceStateMachine::State ServiceStateMachine::state(const XML::XMLString& elementName, ServiceStateMachine::State parent) const
{
	return stateInfo(parent).successorState(elementName);
}


inline const ServiceStateMachine::StateInfo& ServiceStateMachine::stateInfo(ServiceStateMachine::State aState) const
{
	return _stateInfos[aState];
}


inline bool ServiceStateMachine::StateInfo::isValidSuccessor(const XML::XMLString& localName) const
{
	return (_successors.find(localName) != _successors.end());
}


} } } // Poco::UPnP::ServiceDesc


#endif // UPnP_ServiceDesc_ServiceStateMachine_INCLUDED

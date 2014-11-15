//
// StateVariable.h
//
// $Id: //poco/1.4/UPnP/ServiceDesc/include/Poco/UPnP/ServiceDesc/StateVariable.h#1 $
//
// Library: UPnP/ServiceDesc
// Package: ServiceDesc
// Module:  StateVariable
//
// Definition of the StateVariable class.
//
// Copyright (c) 2011-2013, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef UPnP_ServiceDesc_StateVariable_INCLUDED
#define UPnP_ServiceDesc_StateVariable_INCLUDED


#include "Poco/UPnP/ServiceDesc/ServiceDesc.h"
#include "Poco/UPnP/ServiceDesc/Restriction.h"
#include "Poco/AutoPtr.h"
#include "Poco/RefCountedObject.h"


namespace Poco {
namespace UPnP {
namespace ServiceDesc {


class UPnP_ServiceDesc_API StateVariable: public Poco::RefCountedObject
	/// This class represents a state variable
	/// in a UPnP service description.
{
public:
	typedef Poco::AutoPtr<StateVariable> Ptr;

	StateVariable();
		/// Creates the StateVariable.

	~StateVariable();
		/// Destroys the StateVariable.

	bool sendEvents() const;
		/// Returns true if eventing is enabled for this state variable.

	const std::string& name() const;
		/// Returns the name of this variable, UTF-8 encoded.

	const std::string& type() const;
		/// Returns the UPnP type of this variable.
		///
		/// The following types are defined in the UPnP Device Architecture document:
		///   - ui1: Unsigned 1 Byte int. Same format as int without leading sign.
		///   - ui2: Unsigned 2 Byte int. Same format as int without leading sign.
		///   - ui4: Unsigned 4 Byte int. Same format as int without leading sign. 
		///   - i1: 1 Byte int. Same format as int. 
		///   - i2: 2 Byte int. Same format as int. 
		///   - i4: 4 Byte int. Same format as int. Must be between -2147483648 and 2147483647. 
		///   - int: Fixed point, integer number. May have leading sign. May have leading zeros. 
		///     No currency symbol. No grouping of digits to the left of the decimal, e.g., no commas.
		///   - r4: 4 Byte float. Same format as float. Must be between 3.40282347E+38 to 1.17549435E-38.
		///   - r8: 8 Byte float. Same format as float. Must be between -1.79769313486232E308 and 
		///     -4.94065645841247E-324 for negative values, and between 4.94065645841247E-324 and 
		///     1.79769313486232E308 for positive values, i.e., IEEE 64-bit (8-Byte) double. 
		///   - number: Same as r8. 
		///   - fixed.14.4: Same as r8 but no more than 14 digits to the left of the decimal point and no
		///     more than 4 to the right. 
		///   - float: Floating point number. Mantissa (left of the decimal) and/or exponent may have a 
		///     leading sign. Mantissa and/or exponent may have leading zeros. Decimal character in 
		///     mantissa is a period, i.e., whole digits in mantissa separated from fractional digits 
		///     by period. Mantissa separated from exponent by E. No currency symbol. 
		///     No grouping of digits in the mantissa, e.g., no commas.
		///   - char: Unicode string. One character long.
		///   - string: Unicode string. No limit on length.
		///   - date: Date in a subset of ISO 8601 format without time data.
		///   - dateTime: Date in ISO 8601 format with optional time but no time zone.
		///   - dateTime.tz: Date in ISO 8601 format with optional time and optional time zone.
		///   - time: Time in a subset of ISO 8601 format with no date and no time zone.
		///   - time.tz: Time in a subset of ISO 8601 format with optional time zone but no date.
		///   - boolean: “0” for false or “1” for true. The values “true”, “yes”, “false”, or “no” 
		///     may also be used but are not recommended.
		///   - bin.base64: MIME-style Base64 encoded binary BLOB. Takes 3 Bytes, splits them into 
		///     4 parts, and maps each 6 bit piece to an octet. No limit on size.
		///   - bin.hex: Hexadecimal digits representing octets. Treats each nibble as a hex digit 
		///     and encodes as a separate Byte. No limit on size.
		///   - uri: Universal Resource Identifier.
		///   - uuid: Universally Unique ID. Hexadecimal digits representing octets. Optional
		///     embedded hyphens are ignored.

	const std::string& cppType() const;
		/// Returns the C++ type of this variable.

	const std::string& defaultValue() const;
		/// Returns the default value of this variable, or
		/// an empty string if no default value is defined.
		
	const Restriction& valueRestriction() const;
		/// Returns the restriction for this variable.
		
	bool optional() const;
		/// Returns true if the variable is optional, or false otherwise.
		
protected:
	void setName(const std::string& name);
		/// Sets the name of the variable.

	void setType(const std::string& type);
		/// Sets the data type of this variable.

	void setCppType(const std::string& type);
		/// Sets the C++ type of this variable.

	void setDefaultValue(const std::string& value);
		/// Sets the default value for this variable.

	void setValueRestriction(Restriction::Ptr pRestriction);
		/// Sets a restriction for this variable.

	void setOptional(bool optional);
		/// Sets the optional flag of this variable.

	void enableEvents(bool enable);
		/// Enable or disable eventing for this variable.

private:
	bool _sendEvents;
	bool _optional;
	std::string _name;
	std::string _type;
	std::string _cppType;
	std::string _defaultValue;
	Restriction::Ptr _pValueRestriction; 
	
	friend class ServiceContentHandler;
};


//
// inlines
//
inline bool StateVariable::sendEvents() const
{
	return _sendEvents;
}


inline const std::string& StateVariable::name() const
{
	return _name;
}


inline const std::string& StateVariable::type() const
{
	return _type;
}


inline const std::string& StateVariable::cppType() const
{
	return _cppType;
}


inline const std::string& StateVariable::defaultValue() const
{
	return _defaultValue;
}


inline const Restriction& StateVariable::valueRestriction() const
{
	return *_pValueRestriction;
}


inline bool StateVariable::optional() const
{
	return _optional;
}


inline void StateVariable::enableEvents(bool enable)
{
	_sendEvents = enable;
}


inline void StateVariable::setName(const std::string& name)
{
	_name = name;
}


inline void StateVariable::setType(const std::string& type)
{
	_type = type;
}


inline void StateVariable::setCppType(const std::string& cppType)
{
	_cppType = cppType;
}


inline void StateVariable::setDefaultValue(const std::string& value)
{
	_defaultValue = value;
}


inline void StateVariable::setValueRestriction(Restriction::Ptr pRestriction)
{
	poco_check_ptr (pRestriction);
	_pValueRestriction = pRestriction;
}


inline void StateVariable::setOptional(bool optional)
{
	_optional = optional;
}


} } } // namespace Poco::UPnP::ServiceDesc


#endif // UPnP_ServiceDesc_StateVariable_INCLUDED

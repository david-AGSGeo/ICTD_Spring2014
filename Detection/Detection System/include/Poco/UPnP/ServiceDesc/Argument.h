//
// Argument.h
//
// $Id: //poco/1.4/UPnP/ServiceDesc/include/Poco/UPnP/ServiceDesc/Argument.h#1 $
//
// Library: UPnP/ServiceDesc
// Package: ServiceDesc
// Module:  Argument
//
// Definition of the Argument class.
//
// Copyright (c) 2011-2013, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef UPnP_ServiceDesc_Argument_INCLUDED
#define UPnP_ServiceDesc_Argument_INCLUDED


#include "Poco/UPnP/ServiceDesc/ServiceDesc.h"


namespace Poco {
namespace UPnP {
namespace ServiceDesc {


class UPnP_ServiceDesc_API Argument
	/// This class represents an argument to an Action in a UPnP service description.
{
public:
	enum Direction
	{
		DIR_IN = 0,  /// input parameter
		DIR_OUT,     /// output parameter
		DIR_RETURN   /// return value
	};

	Argument();
		/// Creates the Argument.

	Argument(const Argument& arg);
		/// Creates the Argument by copying another one.

	~Argument();
		/// Destroys the Argument.

	Argument& operator = (const Argument&);
		/// Assignment operator.

	const std::string& name() const;
		/// Returns the name of the argument.

	std::string parameterName() const;
		/// Returns a transformation of the parameter name to a valid
		/// C++ identifier.

	Direction direction() const;
		/// Returns the kind of parameter (input, output or return value).

	const std::string& stateVariable() const;
		/// Returns the name of the related state variable in the service's state variable table.

protected:
	void setName(const std::string& name);
		/// Sets the name of the argument.

	void setDirection(Direction dir);
		/// Sets the direction of the argument.

	void setStateVariable(const std::string& name);
		/// Sets the name of the related state variable.
		
private:	
	std::string _name;
	std::string _stateVariable;
	Direction   _direction;
	
	friend class ServiceContentHandler;
	friend class Action;
};


//
// inlines
//
inline const std::string& Argument::name() const
{
	return _name;
}


inline Argument::Direction Argument::direction() const
{
	return _direction;
}


inline const std::string& Argument::stateVariable() const
{
	return _stateVariable;
}


inline void Argument::setName(const std::string& name)
{
	_name = name;
}


inline void Argument::setDirection(Argument::Direction dir)
{
	_direction = dir;
}


inline void Argument::setStateVariable(const std::string& name)
{
	_stateVariable = name;
}


} } } // namespace Poco::UPnP::ServiceDesc


#endif // UPnP_ServiceDesc_Argument_INCLUDED

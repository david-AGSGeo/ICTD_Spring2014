//
// Action.h
//
// $Id: //poco/1.4/UPnP/ServiceDesc/include/Poco/UPnP/ServiceDesc/Action.h#2 $
//
// Library: UPnP/ServiceDesc
// Package: ServiceDesc
// Module:  Action
//
// Definition of the Action class.
//
// Copyright (c) 2011-2013, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef UPnP_ServiceDesc_Action_INCLUDED
#define UPnP_ServiceDesc_Action_INCLUDED


#include "Poco/UPnP/ServiceDesc/ServiceDesc.h"
#include "Poco/UPnP/ServiceDesc/Argument.h"
#include "Poco/SharedPtr.h"
#include "Poco/AutoPtr.h"
#include "Poco/RefCountedObject.h"
#include "Poco/Exception.h"
#include <vector>


namespace Poco {
namespace UPnP {
namespace ServiceDesc {


class UPnP_ServiceDesc_API Action: public Poco::RefCountedObject
	/// This class represents an action in a UPnP service description.
{
public:
	typedef Poco::AutoPtr<Action> Ptr;
	typedef std::vector<Argument> Arguments;

	Action();
		/// Creates the Action.

	~Action();
		/// Destroys the Action.

	const std::string& name() const;
		/// Returns the action's name, UTF-8 encoded.
	
	std::string methodName() const;
		/// Returns a transformation of the action name to a valid
		/// C++ identifier.

	bool hasReturnArgument() const;
		/// Returns true if a return argument exists

	const Argument& returnArgument() const;
		/// Returns the return argument.
		///
		/// Will throw a Poco::NotFoundException if no return argument
		/// has been set.

	const Arguments& arguments() const;
		/// Returns the in and out arguments, not including the return parameter.

	Arguments& arguments();
		/// Returns the in and out arguments, not including the return parameter.

	bool optional() const;
		/// Returns true whether the action is optional, or false otherwise.

protected:
	void setName(const std::string& name);
		/// Sets the action's name.
		
	void setReturnArgument(const Argument& arg);
		/// Sets a argument as return argument.

	void setOptional(bool optional);
		/// Specifies whether the action is optional.

private:
	bool _optional;
	std::string _name;
	Poco::SharedPtr<Argument> _pRet;
	Arguments _args;
	
	friend class ServiceContentHandler;
};


//
// inlines
//
inline const std::string& Action::name() const
{
	return _name;
}


inline bool Action::hasReturnArgument() const
{
	return !_pRet.isNull();
}


inline const Argument& Action::returnArgument() const
{
	if (_pRet)
		return *_pRet;
	else
		throw Poco::NotFoundException("return");
}


inline Action::Arguments& Action::arguments()
{
	return _args;
}


inline const Action::Arguments& Action::arguments() const
{
	return _args;
}


inline bool Action::optional() const
{
	return _optional;
}


inline void Action::setName(const std::string& name)
{
	_name = name;
}


inline void Action::setReturnArgument(const Argument& arg)
{
	poco_assert (arg.direction() == Argument::DIR_RETURN);

	_pRet = new Argument(arg);
}


inline void Action::setOptional(bool optional)
{
	_optional = optional;
}


} } } // namespace Poco::UPnP::ServiceDesc


#endif // UPnP_ServiceDesc_Action_INCLUDED

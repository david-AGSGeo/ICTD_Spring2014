//
// Message.h
//
// $Id: //poco/1.4/XSD/Types/include/Poco/XSD/Types/Message.h#2 $
//
// Library: XSD/Types
// Package: WSDL
// Module:  Message
//
// Definition of the Message class.
//
// Copyright (c) 2012, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef XSDTypes_Message_INCLUDED
#define XSDTypes_Message_INCLUDED


#include "Poco/XSD/Types/XSDTypes.h"
#include "Poco/XSD/Types/AnnotatedObject.h"
#include "Poco/XML/Name.h"
#include <vector>


namespace Poco {
namespace XSD {
namespace Types {


class XSDTypes_API Message: public AnnotatedObject
	/// This class represents a WSDL message.
{
public:
	typedef Poco::AutoPtr<Message> Ptr;

	struct Part
	{
		std::string name;
		XML::Name elementName;
	};
	typedef std::vector<Part> Parts;

	Message();
		/// Creates the Message.

	Message(const std::string& name);
		/// Creates the Message.

	~Message();
		/// Destroys the Message.

	void setName(const std::string& name);
		/// Sets the name.

	const std::string& name() const;
		/// Returns the name.
		
	void addPart(const std::string& name, const Poco::XML::Name& elementName);
		/// Adds a new part to the message.
		
	const Parts& parts() const;
		/// Returns the message parts.
	
	void accept(Visitor& v) const;

private:
	std::string _name;
	Parts _parts;
};


//
// inlines
//
inline void Message::setName(const std::string& name)
{
	_name = name;
}


inline const std::string& Message::name() const
{
	return _name;
}


inline const Message::Parts& Message::parts() const
{
	return _parts;
}


} } } // namespace Poco::XSD::Types


#endif // XSDTypes_Message_INCLUDED

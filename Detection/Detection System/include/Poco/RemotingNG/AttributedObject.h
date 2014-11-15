//
// AttributedObject.h
//
// $Id: //poco/1.4/RemotingNG/include/Poco/RemotingNG/AttributedObject.h#1 $
//
// Library: RemotingNG
// Package: ORB
// Module:  AttributedObject
//
// Definition of the AttributedObject class.
//
// Copyright (c) 2006-2011, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef RemotingNG_AttributedObject_INCLUDED
#define RemotingNG_AttributedObject_INCLUDED


#include "Poco/RemotingNG/RemotingNG.h"
#include "Poco/RefCountedObject.h"
#include "Poco/AutoPtr.h"
#include "Poco/Mutex.h"
#include <map>


namespace Poco {
namespace RemotingNG {


class RemotingNG_API AttributedObject: public Poco::RefCountedObject
	/// A AttributedObject can hold any number of attributes in 
	/// the form of name-value pairs.
{
public:
	typedef Poco::AutoPtr<AttributedObject> Ptr;
	typedef std::map<std::string,std::string> NameValueMap;

	AttributedObject();
		/// Creates a AttributedObject.

	virtual ~AttributedObject();
		/// Destroys the AttributedObject.
		
	void setAttribute(const std::string& name, const std::string& value);
		/// Adds or modifies the attribute with the given name.
		
	const std::string& getAttribute(const std::string& name) const;
		/// Returns the value of the attribute with the given name.
		/// Throws a Poco::NotFoundException if no such attribute
		/// exists.
		
	const std::string& getAttribute(const std::string& name, const std::string& deflt) const;
		/// Returns the value of the attribute with the given name,
		/// or the given default value if no such attribute
		/// exists.
	
	bool hasAttribute(const std::string& name) const;
		/// Returns true iff an attribute with the given name exists.
		
private:
	AttributedObject(const AttributedObject&);
	AttributedObject& operator = (const AttributedObject&);

	NameValueMap _attributes;
	mutable Poco::FastMutex _mutex;
};


} } // namespace Poco::RemotingNG


#endif // RemotingNG_AttributedObject_INCLUDED

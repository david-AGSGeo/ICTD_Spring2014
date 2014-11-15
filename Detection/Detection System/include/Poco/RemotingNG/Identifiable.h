//
// Identifiable.h
//
// $Id: //poco/1.4/RemotingNG/include/Poco/RemotingNG/Identifiable.h#1 $
//
// Library: RemotingNG
// Package: ORB
// Module:  Identifiable
//
// Definition of the Identifiable class.
//
// Copyright (c) 2006-2011, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef RemotingNG_Identifiable_INCLUDED
#define RemotingNG_Identifiable_INCLUDED


#include "Poco/RemotingNG/RemotingNG.h"
#include "Poco/RefCountedObject.h"
#include "Poco/AutoPtr.h"
#include "Poco/URI.h"


namespace Poco {
namespace RemotingNG {


class RemotingNG_API Identifiable: public virtual Poco::RefCountedObject
	/// An Identifiable object stores a TypeId, ObjectId and URI for an object.
	///
	/// The remoting__ prefix for the Identifiable member functions and variables 
	/// is used to avoid name clashes with methods from subclasses.
{
public:
	typedef Poco::AutoPtr<Identifiable> Ptr;
	typedef std::string ObjectId;
	typedef std::string TypeId;

	Identifiable(const Identifiable::ObjectId& oid);
		/// Creates the Identifiable using the given ObjectId.

	virtual ~Identifiable();
		/// Destroys the Identifiable.

	const Identifiable::ObjectId& remoting__objectId() const;
		/// Returns the object's ObjectId.

	void remoting__setURI(const Poco::URI& uri);
		/// Sets the URI for the object.

	const Poco::URI& remoting__getURI() const;
		/// Returns the object's URI.

	virtual const Identifiable::TypeId& remoting__typeId() const = 0;
		/// Returns the object's TypeId.
		///
		/// The TypeId is defined by a subclass and cannot be changed.

private:
	Identifiable::ObjectId _remoting__oid;
	Poco::URI              _remoting__uri;
};


//
// inlines
//
inline const Identifiable::ObjectId& Identifiable::remoting__objectId() const
{
	return _remoting__oid;
}


inline const Poco::URI& Identifiable::remoting__getURI() const
{
	return _remoting__uri;
}


} } // namespace Poco::RemotingNG


#endif // RemotingNG_Identifiable_INCLUDED

//
// Deserializer.h
//
// $Id: //poco/1.4/UPnP/GENA/include/Poco/UPnP/GENA/Deserializer.h#1 $
//
// Library: UPnP/GENA
// Package: GENA
// Module:  Deserializer
//
// Definition of the Deserializer class.
//
// Copyright (c) 2008-2011, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef UPnP_GENA_Deserializer_INCLUDED
#define UPnP_GENA_Deserializer_INCLUDED


#include "Poco/UPnP/GENA/GENA.h"
#include "Poco/RemotingNG/Deserializer.h"


namespace Poco {
namespace UPnP {
namespace GENA {


class UPnPGENA_API Deserializer: public Poco::RemotingNG::Deserializer
	/// The Deserializer for the UPnP GENA Transport.
	///
	/// This class can deserialize GENA event messages (XML property sets).
	/// A special optimization allows for reuse of the Deserializer
	/// to deserialize multiple properties where each one is treated
	/// as a separate message (as required by the RemotingNG architecture).
{
public:
	typedef std::pair<std::string, std::string> KeyValuePair;
	typedef std::vector<KeyValuePair> KeyValueVec;

	Deserializer();
		/// Creates a Deserializer.

	~Deserializer();
		/// Destroys the Deserializer.
		
	bool hasMoreProperties() const;
		/// Returns true if there is at least one more property to deserialize.
		
	void popProperty();
		/// Removes the last property from the vector.

	// Poco::RemotingNG::Deserializer
	Poco::RemotingNG::SerializerBase::MessageType findMessage(std::string& name);
	void deserializeMessageBegin(const std::string& name, Poco::RemotingNG::SerializerBase::MessageType type);
	void deserializeMessageEnd(const std::string& name, Poco::RemotingNG::SerializerBase::MessageType type);
	bool deserializeStructBegin(const std::string& name, bool isMandatory);
	void deserializeStructEnd(const std::string& name);
	bool deserializeSequenceBegin(const std::string& name, bool isMandatory, Poco::UInt32& sizeHint);
	void deserializeSequenceEnd(const std::string& name);
	bool deserializeNullableBegin(const std::string& name, bool isMandatory, bool& isNull);
	void deserializeNullableEnd(const std::string& name);
	bool deserialize(const std::string& name, bool isMandatory, Poco::Int8& value);
	bool deserialize(const std::string& name, bool isMandatory, Poco::UInt8& value);
	bool deserialize(const std::string& name, bool isMandatory, Poco::Int16& value);
	bool deserialize(const std::string& name, bool isMandatory, Poco::UInt16& value);
	bool deserialize(const std::string& name, bool isMandatory, Poco::Int32& value);
	bool deserialize(const std::string& name, bool isMandatory, Poco::UInt32& value);
	bool deserialize(const std::string& name, bool isMandatory, long& value);
	bool deserialize(const std::string& name, bool isMandatory, unsigned long& value);
#ifndef POCO_LONG_IS_64_BIT
	bool deserialize(const std::string& name, bool isMandatory, Poco::Int64& value);
	bool deserialize(const std::string& name, bool isMandatory, Poco::UInt64& value);
#endif
	bool deserialize(const std::string& name, bool isMandatory, float& value);
	bool deserialize(const std::string& name, bool isMandatory, double& value);
	bool deserialize(const std::string& name, bool isMandatory, bool& value);
	bool deserialize(const std::string& name, bool isMandatory, char& value);
	bool deserialize(const std::string& name, bool isMandatory, std::string& value);
	bool deserialize(const std::string& name, bool isMandatory, std::vector<char>& value);

protected:
	void resetImpl();
	void setupImpl(std::istream& istr);
	const std::string& deserializeOne();

private:
	Deserializer(const Deserializer&);
	Deserializer& operator = (const Deserializer&);

private:	
	std::istream* _pStream;
	KeyValueVec _properties;
};


//
// inlines
//
inline bool Deserializer::hasMoreProperties() const
{
	return !_properties.empty();
}


} } } // namespace Poco::UPnP::GENA


#endif // UPnP_GENA_Deserializer_INCLUDED

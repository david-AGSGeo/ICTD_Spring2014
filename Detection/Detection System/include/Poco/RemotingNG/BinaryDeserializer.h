//
// BinaryDeserializer.h
//
// $Id: //poco/1.4/RemotingNG/include/Poco/RemotingNG/BinaryDeserializer.h#2 $
//
// Library: RemotingNG
// Package: Serialization
// Module:  BinaryDeserializer
//
// Definition of the Deserializer class.
//
// Copyright (c) 2006-2011, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef RemotingNG_BinaryDeserializer_INCLUDED
#define RemotingNG_BinaryDeserializer_INCLUDED


#include "Poco/RemotingNG/Deserializer.h"
#include "Poco/RemotingNG/RemotingException.h"
#include "Poco/BinaryReader.h"
#include <stack>
#include <memory>


namespace Poco {
namespace RemotingNG {


class RemotingNG_API BinaryDeserializer: public Deserializer
	/// A generic Deserializer using a proprietary binary
	/// serialization format based on the Poco::BinaryReader
	/// class. The BinaryDeserializer is used in conjunction
	/// with the BinarySerializer class.
	///
	/// Please see the BinarySerializer class for more information.
{
public:
	BinaryDeserializer();
		/// Creates a BinaryDeserializer.

	~BinaryDeserializer();
		/// Destroys the BinaryDeserializer.

	void deserializeEndPoint(std::string& oid, std::string& tid);
		/// Serializes the object and type ID of the service object.

	// Deserializer
	SerializerBase::MessageType findMessage(std::string& name);
	void deserializeMessageBegin(const std::string& name, SerializerBase::MessageType type);
	void deserializeMessageEnd(const std::string& name, SerializerBase::MessageType type);
	bool deserializeStructBegin(const std::string& name, bool isMandatory);
	void deserializeStructEnd(const std::string& name);
	bool deserializeSequenceBegin(const std::string& name, bool isMandatory, Poco::UInt32& lengthHint);
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

private:
	bool handleVector();
	bool checkStream();
	void findMessageImpl();

	typedef std::auto_ptr<Poco::BinaryReader> BinaryReaderPtr;
	typedef std::pair<int, int> LengthLevelPair;
	typedef std::stack<LengthLevelPair> LevelLengthVec;

	BinaryReaderPtr _pReader;
	std::string _messageName;
	SerializerBase::MessageType _messageType;
	LevelLengthVec _sequenceLengths;
	int _curLevel;
};


//
// inlines
//
inline bool BinaryDeserializer::checkStream()
{
	if (_pReader->good())
		return true;
	else
		throw DeserializerException("unexpected end of, or bad stream");
}


} } // namespace Poco::RemotingNG


#endif // RemotingNG_BinaryDeserializer_INCLUDED

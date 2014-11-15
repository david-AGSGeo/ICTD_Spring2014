//
// UPnPException.h
//
// $Id: //poco/1.4/UPnP/include/Poco/UPnP/UPnPException.h#3 $
//
// Library: UPnP
// Package: Core
// Module:  UPnPException
//
// Definition of the UPnPException class.
//
// Copyright (c) 2008-2010, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef UPnP_UPnPException_INCLUDED
#define UPnP_UPnPException_INCLUDED


#include "Poco/UPnP/UPnP.h"
#include "Poco/Exception.h"
#include <map>


namespace Poco {
namespace UPnP {


class UPnP_API UPnPException: public Poco::Exception
	/// This exception class is used for UPnP specific errors.
	///
	/// It should be used for reporting errors for which
	/// a service specification defines a specific UPnP error
	/// code.
{
public:
	enum PredefinedErrorCode
	{
		CODE_INVALID_ACTION = 401,
		CODE_INVALID_ARGS = 402,
		CODE_ACTION_FAILED = 501,
		CODE_ARGUMENT_VALUE_INVALID = 600,
		CODE_ARGUMENT_VALUE_OUT_OF_RANGE = 601,
		CODE_OPTIONAL_ACTION_NOT_IMPLEMENTED = 602,
		CODE_OUT_OF_MEMORY = 603,
		CODE_HUMAN_INTERVENTION_REQUIRED = 604,
		CODE_STRING_ARGUMENT_TOO_LONG = 605,
		CODE_ACTION_NOT_AUTHORIZED = 606,
		CODE_SIGNATURE_FAILURE = 607,
		CODE_SIGNATURE_MISSING = 608,
		CODE_NOT_ENCRYPTED = 609,
		CODE_INVALID_SEQUENCE = 610,
		CODE_INVALID_CONTROL_URL = 611,
		CODE_NO_SUCH_SESSION = 612
	};
	
	enum CodeRanges
	{
		RANGE_COMMON_ERROR_START = 600,
		RANGE_COMMON_ERROR_END = 699,
		RANGE_ACTION_SPECIFIC_ERROR_START = 700,
		RANGE_ACTION_SPECIFIC_ERROR_END = 799,
		RANGE_VENDOR_SPECIFIC_START = 800,
		RANGE_VENDOR_SPECIFIC_END = 899
	};

	UPnPException(int code);
	UPnPException(const std::string& msg, int code);
	UPnPException(const std::string& msg, const std::string& arg, int code);
	UPnPException(const std::string& msg, const Poco::Exception& exc, int code);
	UPnPException(const UPnPException& exc);
	~UPnPException() throw();

	UPnPException& operator = (const UPnPException& exc);

	const char* name() const throw();
	const char* className() const throw();
	Poco::Exception* clone() const;
	void rethrow() const;							

	static bool codeIsValid(int code);
		/// Checks if an error code is valid, ie. it has beed registered.
		/// Returns true if the code has been registered, false otherwise.

	static const std::string& description(int code);
		/// Returns a description for the given error code.
		///
		/// If no description for the error code has been registered,
		/// returns an empty string.

	static void registerCode(int code, const std::string& desc);
		/// Registers a new error code. The code must be in a  valid int range defined by the UPnP standard.
		/// Only values in the range 613-899 can be registered. All other values are either forbidden
		/// or assigned a static text.

private:
	typedef std::map<int, std::string> CodeStrings;

	static CodeStrings& codeStrings();
	static CodeStrings initCodeStrings();
	static void registerPrivateCode(CodeStrings& data, int code, const std::string& desc);
};


} } // namespace Poco::UPnP


#endif // UPnP_UPnPException_INCLUDED

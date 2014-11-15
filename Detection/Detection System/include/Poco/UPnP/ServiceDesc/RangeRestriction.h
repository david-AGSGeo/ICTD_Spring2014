//
// RangeRestriction.h
//
// $Id: //poco/1.4/UPnP/ServiceDesc/include/Poco/UPnP/ServiceDesc/RangeRestriction.h#2 $
//
// Library: UPnP/ServiceDesc
// Package: ServiceDesc
// Module:  RangeRestriction
//
// Definition of the RangeRestriction class.
//
// Copyright (c) 2011-2013, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef UPnP_ServiceDesc_RangeRestriction_INCLUDED
#define UPnP_ServiceDesc_RangeRestriction_INCLUDED


#include "Poco/UPnP/ServiceDesc/ServiceDesc.h"
#include "Poco/UPnP/ServiceDesc/Restriction.h"


namespace Poco {
namespace UPnP {
namespace ServiceDesc {


class UPnP_ServiceDesc_API RangeRestriction: public Restriction
	/// The RangeRestriction restricts values to a given numerical range.
{
public:
	typedef Poco::AutoPtr<RangeRestriction> Ptr;

	RangeRestriction();
		/// Creates the RangeRestriction.

	~RangeRestriction();
		/// Destroys the RangeRestriction.

	Poco::Int64 minimum() const;
		/// Returns the minimum value allowed.

	Poco::Int64 maximum() const;
		/// Returns the maximum value allowed.

	Poco::Int64 step() const;
		/// Returns the interval between two values.

	// Restriction
	bool valid(const std::string& val) const;
	std::string toString() const;

protected:
	void setMinimum(Poco::Int64 val);
		/// Sets the minimum value allowed.
		
	void setMaximum(Poco::Int64 val);
		/// Sets the maximum value allowed.
		
	void setStep(Poco::Int64 val);
		/// Sets the interval between two values.

private:
	RangeRestriction(const RangeRestriction&);
	RangeRestriction& operator = (const RangeRestriction&);

	Poco::Int64 _minimum;
	Poco::Int64 _maximum;
	Poco::Int64 _step;
	
	friend class ServiceContentHandler;
};


//
// inlines
//
inline Poco::Int64 RangeRestriction::minimum() const
{
	return _minimum;
}


inline Poco::Int64 RangeRestriction::maximum() const
{
	return _maximum;
}


inline Poco::Int64 RangeRestriction::step() const
{
	return _step;
}


inline void RangeRestriction::setMinimum(Poco::Int64 val)
{
	_minimum = val;
}


inline void RangeRestriction::setMaximum(Poco::Int64 val)
{
	_maximum = val;
}


inline void RangeRestriction::setStep(Poco::Int64 val)
{
	poco_assert (_step > 0);
	_step = val;
}


} } } // namespace Poco::UPnP::ServiceDesc


#endif // UPnP_ServiceDesc_RangeRestriction_INCLUDED

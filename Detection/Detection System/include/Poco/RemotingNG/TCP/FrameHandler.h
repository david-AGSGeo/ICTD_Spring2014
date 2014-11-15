//
// FrameHandler.h
//
// $Id: //poco/1.4/RemotingNG/TCP/include/Poco/RemotingNG/TCP/FrameHandler.h#2 $
//
// Library: RemotingNG/TCP
// Package: TCP
// Module:  FrameHandler
//
// Definition of the FrameHandler class.
//
// Copyright (c) 2006-2012, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef RemotingNG_TCP_FrameHandler_INCLUDED
#define RemotingNG_TCP_FrameHandler_INCLUDED


#include "Poco/RemotingNG/TCP/TCP.h"
#include "Poco/RemotingNG/TCP/Frame.h"
#include "Poco/RemotingNG/TCP/Connection.h"
#include "Poco/RefCountedObject.h"
#include "Poco/AutoPtr.h"


namespace Poco {
namespace RemotingNG {
namespace TCP {


class RemotingNGTCP_API FrameHandler: public Poco::RefCountedObject
	/// A frame handler handles frames on behalf
	/// of a Connection. 
{
public:
	typedef Poco::AutoPtr<FrameHandler> Ptr;

	virtual bool handleFrame(Connection::Ptr pConnection, Frame::Ptr pFrame) = 0;
		/// Handle the given frame.
		///
		/// If the handler accepts the frame, it should return true.
		/// In this case, the FrameHandler is responsible for returning
		/// the Frame to the Connection's Frame pool when it's no longer
		/// needed.
		///
		/// If the handler does not accept the frame, it should return
		/// false.
};


} } } // namespace Poco::RemotingNG::TCP


#endif // RemotingNG_TCP_FrameHandler_INCLUDED

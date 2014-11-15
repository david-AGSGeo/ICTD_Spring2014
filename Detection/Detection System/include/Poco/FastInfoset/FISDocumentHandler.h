//
// FISDocumentHandler.h
//
// $Id: //poco/1.4/FastInfoset/include/Poco/FastInfoset/FISDocumentHandler.h#1 $
//
// Library: FastInfoset
// Package: Writer
// Module:  FISDocumentHandler
//
// Definition of the FISDocumentHandler class.
//
// Copyright (c) 2006-2010, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics
// Software Engineering GmbH.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part, without
// prior written permission from Applied Informatics.
//


#ifndef FastInfoset_FISDocumentHandler_INCLUDED
#define FastInfoset_FISDocumentHandler_INCLUDED


#include "Poco/FastInfoset/FastInfoset.h"


namespace Poco {
namespace FastInfoset {


class DocumentVocabulary;


class FastInfoset_API FISDocumentHandler
	/// The FISDocumentHandler interface allows for setting and querying
	/// the vocabulatory used for a document.
{
public:
	virtual void setDocumentVocabulary(const DocumentVocabulary& voc) = 0;
		/// Sets the documentVocabulary.

	virtual DocumentVocabulary& getDocumentVocabulary() = 0;
		/// Returns the documentVocabulary.

	virtual const DocumentVocabulary& getDocumentVocabulary() const = 0;
		/// Returns the documentVocabulary as a const object.

	virtual void setWriteXMLDeclaration(bool val) = 0;
		/// Sets a boolean which defines if the xml declaration header should be written.

	virtual void setExternalVocabulary(const std::string& uri, const DocumentVocabulary& voc) = 0;
		/// Sets the location of the external dictionary and its content. The content is required
		/// so that the writer can create a diff to the finally set initial vocabulary and encode 
		/// only the difference.

protected:
	virtual ~FISDocumentHandler();
		/// Destroys the FISDocumentHandler.
};


} } // namespace Poco::FastInfoset


#endif // FastInfoset_FISDocumentHandler_INCLUDED

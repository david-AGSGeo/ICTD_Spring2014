//
// SQLiteStatementImpl.h
//
// $Id: //poco/1.4/Data/SQLite/include/Poco/Data/SQLite/SQLiteStatementImpl.h#1 $
//
// Library: Data/SQLite
// Package: SQLite
// Module:  SQLiteStatementImpl
//
// Definition of the SQLiteStatementImpl class.
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#ifndef DataConnectors_SQLite_SQLiteStatementImpl_INCLUDED
#define DataConnectors_SQLite_SQLiteStatementImpl_INCLUDED


#include "Poco/Data/SQLite/SQLite.h"
#include "Poco/Data/SQLite/Binder.h"
#include "Poco/Data/SQLite/Extractor.h"
#include "Poco/Data/StatementImpl.h"
#include "Poco/Data/MetaColumn.h"
#include "Poco/SharedPtr.h"
#include "Poco/Random.h"


struct sqlite3;
struct sqlite3_stmt;


namespace Poco {
namespace Data {
namespace SQLite {


class SQLite_API SQLiteStatementImpl: public Poco::Data::StatementImpl
	/// Implements statement functionality needed for SQLite
{
public:
	SQLiteStatementImpl(sqlite3* pDB, int maxRetryAttempts, int minRetrySleep, int maxRetrySleep);
		/// Creates the SQLiteStatementImpl.

	~SQLiteStatementImpl();
		/// Destroys the SQLiteStatementImpl.

protected:
	Poco::UInt32 columnsReturned() const;
		/// Returns number of columns returned by query.

	const MetaColumn& metaColumn(Poco::UInt32 pos) const;
		/// Returns column meta data.

	bool hasNext();
		/// Returns true if a call to next() will return data.

	void next();
		/// Retrieves the next row from the resultset.
		/// Will throw, if the resultset is empty.

	bool canBind() const;
		/// Returns true if a valid statement is set and we can bind.

	void compileImpl();
		/// Compiles the statement, doesn't bind yet, retries if
		/// the database is locked.

	void compileImplImpl();
		/// Compiles the statement, doesn't bind yet

	void bindImpl();
		/// Binds parameters

	AbstractExtractor& extractor();
		/// Returns the concrete extractor used by the statement.

	AbstractBinder& binder();
		/// Returns the concrete binder used by the statement.

private:
	void clear();
		/// Removes the _pStmt
		
	void sleep();
		/// Sleep for a random time (between retry attempts).

	typedef Poco::Data::AbstractBindingVec Bindings;
	typedef Poco::Data::AbstractExtractionVec Extractions;

	sqlite3*      _pDB;
	sqlite3_stmt* _pStmt;
	int           _maxRetryAttempts;
	int           _minRetrySleep;
	int           _maxRetrySleep;
	bool          _stepCalled;
	int           _nextResponse;
	Poco::SharedPtr<Binder>    _pBinder;
	Poco::SharedPtr<Extractor> _pExtractor;
	std::vector<Poco::Data::MetaColumn> _columns;
	Poco::Random _rnd;
};


//
// inlines
//
inline AbstractExtractor& SQLiteStatementImpl::extractor()
{
	return *_pExtractor;
}


inline AbstractBinder& SQLiteStatementImpl::binder()
{
	return *_pBinder;
}


} } } // namespace Poco::Data::SQLite


#endif // DataConnectors_SQLite_SQLiteStatementImpl_INCLUDED

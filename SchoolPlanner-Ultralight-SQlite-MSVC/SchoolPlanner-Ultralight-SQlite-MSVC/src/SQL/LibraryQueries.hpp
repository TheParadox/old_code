#pragma once

namespace DB {

	bool createLibraryTable(sqlite3* _db, json _request);

	bool createLibrary(sqlite3* _db, json _request);

	bool updateLibrary(sqlite3* _db, json _request);

	json selectSingleLibrary(sqlite3* _db, json _request);

	json selectAllLibraries(sqlite3* _db, json _request);
};
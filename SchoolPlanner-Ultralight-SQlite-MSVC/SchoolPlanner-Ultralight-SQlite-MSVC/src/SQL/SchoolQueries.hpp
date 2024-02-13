#pragma once


namespace DB {

	bool createSchoolTable(sqlite3* _db);

	bool createSchool(sqlite3* _db, json _request);

	bool updateSchool(sqlite3* _db, json _request);

	json selectSingleSchool(sqlite3* _db, json _request);

	json selectAllSchools(sqlite3* _db, json _request);
};
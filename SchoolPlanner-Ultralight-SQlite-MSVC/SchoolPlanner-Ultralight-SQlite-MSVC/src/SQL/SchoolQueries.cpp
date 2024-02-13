#include "sc_pch.hpp"
#include "SchoolQueries.hpp"

namespace DB {
	enum SchoolColumns {
		ID = 0,
		Name
	};


	bool createSchoolTable(sqlite3* _db) {
		int rc;
		bool success = false;
		sqlite3_stmt* stmt;
		std::string query = "CREATE TABLE school("
			"ID INTEGER PRIMARY KEY NOT NULL," 
			"name TEXT NOT NULL);";

		int nBytes = query.size();
		rc = sqlite3_prepare_v2(_db, query.c_str(), nBytes, &stmt, nullptr);

		if (DBH::checkStatusCode(rc)) {
			rc = sqlite3_step(stmt);

			if (DBH::checkStatusCode(rc)) {
				SC_TRACE("Successfully CREATED the School Table");
				success = true;
			} else {
				SC_ERROR("Step - failed to CREATED the School Table - code: {0}", rc);
			}
		} else {
			SC_ERROR("Prepare - failed to CREATED the School Table - code: {0}", rc);
		}

		sqlite3_finalize(stmt);
		return success;
	};

	bool createSchool(sqlite3* _db, json _request) {
		int rc;
		bool success = false;
		sqlite3_stmt* stmt;

		std::string schoolName = JH::getStdString(_request, "schoolName");

		std::string query = "INSERT INTO school(name )"
			"VALUES(?)";

		int nBytes = query.size();
		rc = sqlite3_prepare_v2(_db, query.c_str(), nBytes, &stmt, nullptr);
		//sqlite3_bind_null(stmt, 1);
		SC_TRACE("CREATE TEXT: {0}", JH::getStdString(_request, "schoolName"));
		sqlite3_bind_text(stmt, 1, JH::getStdString(_request, "schoolName").c_str(), -1, SQLITE_TRANSIENT);

		if (DBH::checkStatusCode(rc)) {
			rc = sqlite3_step(stmt);

			if (DBH::checkStatusCode(rc)) {
				SC_TRACE("Successfully CREATED the School");
				success = true;
			} else {
				SC_ERROR("Step - failed to CREATED the School");
			}
		} else {
			SC_ERROR("Prepare - failed to CREATED the School");
		}


		sqlite3_finalize(stmt);
		return success;
	};

	bool updateSchool(sqlite3* _db, json _request) {
		int rc;
		bool success = false;
		sqlite3_stmt* stmt;
		const char* query = "";

		int nBytes = (int)strlen(query);
		rc = sqlite3_prepare_v2(_db, query, nBytes, &stmt, nullptr);


		if (DBH::checkStatusCode(rc)) {
			rc = sqlite3_step(stmt);

			if (DBH::checkStatusCode(rc)) {
				SC_TRACE("Successfully UPDATED the School");
				success = true;
			} else {
				SC_ERROR("Step - failed to UPDATED the School");
			}
		} else {
			SC_ERROR("Prepare - failed to UPDATED the School");
		}


		sqlite3_finalize(stmt);
		return success;
	};

	json selectSingleSchool(sqlite3* _db, json _request) {
		int rc;
		sqlite3_stmt* stmt;
		std::string query = "SELECT * FROM school";

		int nBytes = query.size();
		json response = json();
		response["success"] = false;
		rc = sqlite3_prepare_v2(_db, query.c_str(), nBytes, &stmt, nullptr);

		if (DBH::checkStatusCode(rc)) {
			rc = sqlite3_step(stmt);

			if (DBH::checkStatusCode(rc)) {
				SC_TRACE("Successfully SELECT the School");
				response["success"] = true;

				response["school"]["id"] = sqlite3_column_int(stmt, SchoolColumns::ID);
				response["school"]["name"] = DBH::getStringColumn(stmt, SchoolColumns::Name);

				SC_TRACE("ID: {0}", response["school"]["id"]);
				SC_TRACE("Name: {0}", response["school"]["name"]);

			} else {
				SC_ERROR("Step - failed to SELECT the School");
			}
		} else {
			SC_ERROR("Prepare - failed to SELECT the School");
		}


		sqlite3_finalize(stmt);
		return response;
	};

	json selectAllSchools(sqlite3* _db, json _request) {
		int rc;
		sqlite3_stmt* stmt;
		const char* query = "";

		int nBytes = (int)strlen(query);
		json response = json();
		response["success"] = false;
		rc = sqlite3_prepare_v2(_db, query, nBytes, &stmt, nullptr);

		if (DBH::checkStatusCode(rc)) {

			do {
				rc = sqlite3_step(stmt);

				if (rc != SQLITE_OK) {
					SC_ERROR("Step - failed to SELECT the School");
				} else {
					response["success"] = true;
				}

			} while (DBH::checkStatusCode(rc));

		} else {
			SC_ERROR("Prepare - failed to SELECT the School");
		}

		sqlite3_finalize(stmt);
		return response;
	};

};
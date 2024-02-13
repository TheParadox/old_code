#include "sc_pch.hpp"
#include "LibraryQueries.hpp"

namespace DB {


	bool createLibraryTable(sqlite3* _db, json _request) {
		int rc;
		bool success = false;
		sqlite3_stmt* stmt;
		const char* query = "";

		int nBytes = (int)strlen(query);
		rc = sqlite3_prepare_v2(_db, query, nBytes, &stmt, nullptr);

		if (rc == SQLITE_OK) {
			rc = sqlite3_step(stmt);

			if (rc == SQLITE_OK) {
				SC_TRACE("Successfully CREATED the Library Table");
				success = true;
			} else {
				SC_ERROR("Step - failed to CREATED the Library Table");
			}
		} else {
			SC_ERROR("Prepare - failed to CREATED the Library Table");
		}

		sqlite3_finalize(stmt);
		return success;
	};

	bool createLibrary(sqlite3* _db, json _request) {
		int rc;
		bool success = false;
		sqlite3_stmt* stmt;
		const char* query = "";

		int nBytes = (int)strlen(query);
		rc = sqlite3_prepare_v2(_db, query, nBytes, &stmt, nullptr);

		if (rc == SQLITE_OK) {
			rc = sqlite3_step(stmt);

			if (rc == SQLITE_OK) {
				SC_TRACE("Successfully CREATED the Library");
				success = true;
			} else {
				SC_ERROR("Step - failed to CREATED the Library");
			}
		} else {
			SC_ERROR("Prepare - failed to CREATED the Library");
		}


		sqlite3_finalize(stmt);
		return success;
	};

	bool updateLibrary(sqlite3* _db, json _request) {
		int rc;
		bool success = false;
		sqlite3_stmt* stmt;
		const char* query = "";

		int nBytes = (int)strlen(query);
		rc = sqlite3_prepare_v2(_db, query, nBytes, &stmt, nullptr);


		if (rc == SQLITE_OK) {
			rc = sqlite3_step(stmt);

			if (rc == SQLITE_OK) {
				SC_TRACE("Successfully UPDATED the Library");
				success = true;
			} else {
				SC_ERROR("Step - failed to UPDATED the Library");
			}
		} else {
			SC_ERROR("Prepare - failed to UPDATED the Library");
		}


		sqlite3_finalize(stmt);
		return success;
	};

	json selectSingleLibrary(sqlite3* _db, json _request) {
		int rc;
		sqlite3_stmt* stmt;
		const char* query = "";

		int nBytes = (int)strlen(query);
		json response = json();
		response["success"] = false;
		rc = sqlite3_prepare_v2(_db, query, nBytes, &stmt, nullptr);

		if (rc == SQLITE_OK) {
			rc = sqlite3_step(stmt);

			if (rc == SQLITE_OK) {
				SC_TRACE("Successfully SELECT the Library");
				response["success"] = true;
			} else {
				SC_ERROR("Step - failed to SELECT the Library");
			}
		} else {
			SC_ERROR("Prepare - failed to SELECT the Library");
		}


		sqlite3_finalize(stmt);
		return response;
	};

	json selectAllLibraries(sqlite3* _db, json _request) {
		int rc;
		sqlite3_stmt* stmt;
		const char* query = "";

		int nBytes = (int)strlen(query);
		json response = json();
		response["success"] = false;
		rc = sqlite3_prepare_v2(_db, query, nBytes, &stmt, nullptr);

		if (rc == SQLITE_OK) {

			do {
				rc = sqlite3_step(stmt);
				response["success"] = true;


				if (rc != SQLITE_OK) {
					SC_ERROR("Step - failed to SELECT the Library");
				}
			} while (rc == SQLITE_OK);

		} else {
			SC_ERROR("Prepare - failed to SELECT the Library");
		}

		sqlite3_finalize(stmt);
		return response;
	};

};
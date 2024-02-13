#include "sc_pch.hpp"
#include "Database.hpp"


//std::function<void(json)> Database::s_replyToUI = nullptr;

Database::Database() {
	m_db = nullptr;
}

Database::~Database() {
	shutdown();
}

json Database::createDB(std::string _dbName) {
	loadDB(_dbName);

	if (m_db == nullptr) {
		SC_CRITICAL("m_db is STILL nullptr");
	}
	DB::createSchoolTable(m_db);

	return json();
}

json Database::loadDB(std::string _dbName) {
	int rc;
	json response = json();

	rc = sqlite3_open(_dbName.c_str(), &m_db);

	if (rc == SQLITE_OK) {
		SC_INFO("Successfully opened, the database");
		response["success"] = true;
	} else {
		SC_ERROR("Unable to open database: {0}", sqlite3_errmsg(m_db));
		response["success"] = false;
	}

	return response;
}

json Database::queryDB(json _request) {
	json response = json();

	DBTable table;
	DBMethod method;

	if (!m_db) {
		response["success"] = false;
		response["school"] = "";
		response["dbLoaded"] = false;
	} else {
		table = JH::getStdString(_request, "table");

		method = JH::getStdString(_request, "method");
	}


	switch (table) {
		case TablesEnum::School:

			switch (method) {
				case MethodsEnum::Create:
					DB::createSchool(m_db, _request);
					break;
				case MethodsEnum::Update:
					DB::updateSchool(m_db, _request);
					break;
				case MethodsEnum::SelectOne:
					response = DB::selectSingleSchool(m_db, _request);
					break;
				case MethodsEnum::SelectAll:
					break;
				default:
					break;
			}

			break;
		case TablesEnum::Library:

			switch (method) {
				case MethodsEnum::Create:
					DB::createLibrary(m_db, _request);
					break;
				case MethodsEnum::Update:
					DB::updateLibrary(m_db, _request);
					break;
				case MethodsEnum::SelectOne:
					DB::selectSingleLibrary(m_db, _request);
					break;
				case MethodsEnum::SelectAll:
					DB::selectAllLibraries(m_db, _request);
					break;
				default:
					break;
			}

			break;
		default:
			break;
	}

	return response;
}

void Database::shutdown() {
	sqlite3_close(m_db);
}

/*void Database::setUIReply(std::function<void(json)> _f) {
	s_replyToUI = _f;
}*/
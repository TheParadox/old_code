#pragma once

#include "Structs/DBTable.hpp"
#include "Structs/DBMethod.hpp"

#include "SchoolQueries.hpp"
#include "LibraryQueries.hpp"


class Database {
public:
	Database();
	~Database();

	json createDB(std::string _dbName);
	json loadDB(std::string _dbName);
	json queryDB(json _request);
	void shutdown();

	//static void setUIReply(std::function<void(json)> f); -- Not needed?

private:
	sqlite3* m_db;

	//static std::function<void(json)> s_replyToUI; -- Not needed?
};
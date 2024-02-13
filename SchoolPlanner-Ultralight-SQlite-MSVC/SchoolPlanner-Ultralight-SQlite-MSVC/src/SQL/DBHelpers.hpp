#pragma once

namespace DBH {

	bool checkStatusCode(int _code);

	std::string getStringColumn(sqlite3_stmt* _stmt, int _col);

};
#include "sc_pch.hpp"
#include "DBHelpers.hpp"

namespace DBH {
	bool checkStatusCode(int _code) {
		switch (_code) {
			case SQLITE_OK:
			case SQLITE_DONE:
			case SQLITE_ROW:
				return true;
				break;

			default:
				SC_WARN("Unknown SQL Error Code: {0}", _code);
				break;
		}

		return false;
	};


	std::string getStringColumn(sqlite3_stmt* _stmt, int _col) {
		const unsigned char* text = sqlite3_column_text(_stmt, _col);
		int size = sqlite3_column_bytes(_stmt, _col);

		return std::string(text, text + size);
	};

};
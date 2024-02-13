#ifndef STRUCTS_HPP
#define STRUCTS_HPP

#include <string>
#include <vector>
#include <set>
#include <iostream>

struct InvData {
public:
	inline void addRow(int _column, std::string _data) {
		if(_column >= m_numColumns){
			addColumn();
		}

		if(_data.length() == 11){
			m_data[_column].insert(_data);
		}
	};

	inline void print() {
		uint32_t sizeOfIndex = m_data[0].size();
		for(uint32_t r = 0; r < sizeOfIndex; r++){
			
			std::string currentIndex = *std::next(m_data[0].begin(), r);

			std::cout << r << ": " << currentIndex << " - ";
			for(uint32_t c = 1; c < m_numColumns; c++) {
				if(m_data[c].contains(currentIndex)){
					std::cout << currentIndex << " - ";
				} else {
					std::cout << "___________" << " - ";
				}
			}

			std::cout << "::\n";
		}

	};

	inline std::string toExport() {
		std::string output = "";
		uint32_t sizeOfIndex = m_data[0].size();
		for(uint32_t r = 0; r < sizeOfIndex; r++){
			
			std::string currentIndex = *std::next(m_data[0].begin(), r);

			output += currentIndex + ",";
			for(uint32_t c = 1; c < m_numColumns; c++) {
				if(m_data[c].contains(currentIndex)){
					output += currentIndex + ",";
				} else {
					output += ",";
				}
			}

			output += "\n";
		}

		return output;
	};

private:
	inline void addColumn() {
		m_data.push_back(std::set<std::string>());
		m_numColumns++;
	};

private:

	uint32_t m_numColumns = 0;
	std::vector<std::set<std::string>> m_data;
};

#endif
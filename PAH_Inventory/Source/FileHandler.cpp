#include "FileHandler.hpp"

#include <sstream>

uint32_t loadDataFile(std::string _filename, InvData* _sortedData) {
	std::ifstream file;

	file.open(_filename);
	if(file) {
		std::string row;
		std::string cell;

		while(std::getline(file, row, '\n')) {
			std::stringstream rowStream(row);
			uint32_t colID = 0;
			while(std::getline(rowStream, cell, ',')){
				_sortedData->addRow(colID, cell);
				colID++;
			}
		}
	} else {
		std::cout << "Failed to load the data file" << std::endl;
		return 1;
	}
	file.close();

	return 0;
}
uint32_t exportToFile(InvData* _sortedData) {

	std::ofstream file;

	file.open("FilteredData.csv", std::ios::trunc);
	file << _sortedData->toExport();
	file.close();

	return 0;
};

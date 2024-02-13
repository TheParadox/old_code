#include <iostream>
#include <string>

#include "structs.hpp"
#include "FileHandler.hpp"

int main(int argc, char** argv) {

	std::cout << "PAH Inventory Assitance" << std::endl;

	std::string filename;
	if(argc > 0) {
		filename = argv[1];
	} else {
		return 0;
	}

	InvData inventory;
	std::string fileData;

	loadDataFile(filename, &inventory);
	exportToFile(&inventory);

	inventory.print();

	return 0;
}
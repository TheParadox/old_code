#ifndef FILE_HANDLER_HPP
#define FILE_HANDLER_HPP

#include <iostream>
#include <fstream>
#include <string>

#include "structs.hpp"

uint32_t loadDataFile(std::string _filename, InvData* _sortedData);
uint32_t exportToFile(InvData* _sortedData);

#endif
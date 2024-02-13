#ifndef FILE_WRITER_HPP
#define FILE_WRITER_HPP

#include <string>
#include <fstream>

class FileWriter {
public:
	FileWriter();
	~FileWriter();

	void newFile(std::string fileName);
	void writeDataToFile(std::string data, std::string item, bool isFirst, bool isLast);
	void earlyBreak();
	void finishedWriting();

private:
	std::ofstream file_;
	std::string fileName_;
};

#endif //FILE_WRITER_HPP
#include "FileWriter.hpp"

FileWriter::FileWriter()
{

}


FileWriter::~FileWriter()
{
	if(file_.is_open())
	{
		file_.close();
	}
}


void FileWriter::newFile(std::string fileName)
{
	fileName_ = fileName + ".json";
	file_.open(fileName_, std::ios::out);

	file_ << "{";
}

void FileWriter::writeDataToFile(std::string data, std::string item, bool isFirst, bool isLast)
{
	if(isFirst)
	{
		if(item == "planet")
		{
			file_ << ",";
		}
		file_ << "\"" << item << "\":[";
	}

	if(!isFirst)
	{
		file_ << ",";
	}

	file_ << data;

	if(isLast)
	{
		file_ << "]";
	}
}

void FileWriter::earlyBreak()
{
	file_ << "]";
}

void FileWriter::finishedWriting()
{
	file_ << "}";
	file_.close();
}
#include "File.h"

std::fstream * File::file(nullptr);

std::vector<std::string> File::getLines(std::string path)
{
	try
	{
		open(path);
	}
	catch (std::string error)
	{
		std::cerr << error << std::endl;
		return std::vector<std::string>();
	}

	std::vector<std::string> lines;
	std::string line = "";

	while (file->good() && std::getline(*file, line))
	{
		lines.push_back(line);
	}

	close();
	return lines;
}

void File::open(std::string path)
{
	file = new std::fstream(path.c_str(), std::ios::in);
	if (!file->is_open()) throw ("Cant open file: " + path);
	if (file->fail()) throw ("File is failing" + path);
}

void File::close()
{
	file->close();
	delete file;
}


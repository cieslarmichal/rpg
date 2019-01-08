#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class File
{
public:
	File() = delete;
	static std::vector<std::string> getLines(std::string path);
private:
	static void open(std::string path);
	static void close();
	static std::fstream * file;
};

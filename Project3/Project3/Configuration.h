#pragma once

// Configuration class used to read config file properties like title, width, height

#include <string>
#include <fstream>
#include <map>

using std::wstring;
using std::string;
using std::map;
using std::ifstream;


class Configuration {
private:
	wstring title;	
	int width;
	int height;	

	void parseConfigFile(string filename, map<string, string> &fileMap);

public:
	Configuration(string filename);
	wstring getTitle() { return title; }	
	int getWidth() { return width; }
	int getHeight() { return height; }	
};

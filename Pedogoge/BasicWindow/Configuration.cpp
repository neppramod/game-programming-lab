#include "Configuration.h"
#include <iostream>

#include <fstream>

using std::cout;
using std::endl;

#include "stringformat.h"

bool debug = true;

Configuration::Configuration(string filename)
{
	//title = "Hello, Title!";
	//startX = 0;
	//startY = 0;
	//width = 500;
	//height = 500;
	//colorRed = 0.4f;
	//colorGreen = 0.6f;
	//colorBlue = 0.9f;

	map<string, string> someMap;	// dummy
	map<string, string> &fileMap = someMap;

	// Read the config file and setup fileMap
	parseConfigFile(filename, fileMap);

	title = fileMap["title"];
	startX = std::stoi(fileMap["startX"]);
	startY = std::stoi(fileMap["startY"]);
	width = std::stoi(fileMap["width"]);
	height = std::stoi(fileMap["height"]);
	colorRed = std::stof(fileMap["colorRed"]);
	colorGreen = std::stof(fileMap["colorGreen"]);
	colorBlue = std::stof(fileMap["colorBlue"]);
}

void Configuration::parseConfigFile(string filename, map<string, string> &fileMap)
{
	ifstream fin;
	fin.open(filename);

	if (fin.fail()) {
		cout << "\nThere was error opening the file." << endl;
		exit(1);
	}

	string line;
	string key;
	string value;

	// Debug
	std::ofstream log;
	log.open("log.txt");

	while (!fin.eof()) {
		getline(fin, line);
		int colonPosition = line.find(":");
		key = trim_copy(line.substr(0, colonPosition));
		//value = line.substr(colonPosition + 1);
		value = trim_copy(line.substr(colonPosition + 1));
		fileMap[key] = value;
	}

	fin.close();

	// Debug
	if (debug) {
		for (map<string, string>::const_iterator it = fileMap.begin(); it != fileMap.end(); ++it) {
			log << it->first << ":" << it->second << endl;
		}
	}


	log.close();
}



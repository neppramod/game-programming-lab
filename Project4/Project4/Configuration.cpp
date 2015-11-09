#include "Configuration.h"
#include <iostream>

#include <fstream>

using std::cout;
using std::endl;

#include "Stringformat.h"

bool debug = true;

Configuration::Configuration(string filename)
{
	map<string, string> someMap;	// dummy
	map<string, string> &fileMap = someMap;

	// Read the config file and setup fileMap
	parseConfigFile(filename, fileMap);

	std::string tmp = fileMap["title"];
	title.assign(tmp.begin(), tmp.end());

	width = std::stoi(fileMap["width"]);
	height = std::stoi(fileMap["height"]);
	}

// Reads external configuration file values into fileMap
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
		value = trim_copy(line.substr(colonPosition + 1));
		fileMap[key] = value;
	}

	fin.close();

	// Debug. For Debug purpose, we also write the values to external log
	if (debug) {
		for (map<string, string>::const_iterator it = fileMap.begin(); it != fileMap.end(); ++it) {
			log << it->first << ":" << it->second << endl;
		}
	}


	log.close();
}



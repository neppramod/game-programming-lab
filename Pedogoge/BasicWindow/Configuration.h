#pragma once

#include <string>
#include <fstream>
#include <map>

using std::string;
using std::map;
using std::ifstream;


class Configuration {
private:
	string title;
	int startX;
	int startY;
	int width;
	int height;
	float colorRed;
	float colorGreen;
	float colorBlue;

	void parseConfigFile(string filename, map<string, string> &fileMap);

public:
	Configuration(string filename);
	string getTitle() { return title; }
	int getStartX() { return startX; }
	int getStartY() { return startY; }
	int getWidth() { return width; }
	int getHeight() { return height; }
	float getColorRed() { return colorRed; }
	float getColorGreen() { return colorGreen; }
	float getColorBlue() { return colorBlue; }
};

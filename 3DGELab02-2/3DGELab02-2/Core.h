#pragma once

#ifndef CORE_H
#define CORE_H

#include <gl/glew.h>
#include <vector>

using namespace std;

class Core
{
public:
	struct Vertex {
		GLfloat x, y, z;
		GLfloat red, green, blue;
	};

	// Reads data from a configuration file. This file should have been in a utility class
	void ReadGraphicsFile(string filename, vector<Vertex> & vertices);
	
};

#endif

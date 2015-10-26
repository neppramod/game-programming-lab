#include "Core.h"

#include <fstream>
#include <iostream>

void Core::ReadGraphicsFile(string filename, vector<Vertex> & vertices)
{
	ifstream fin;
	fin.open(filename);
	if (fin.fail()) {
		cout << "\nThere was error opening the file." << endl;
		exit(1);
	}

	while (!fin.eof()) {
		Vertex vertex;
		fin >> vertex.x >> vertex.y >> vertex.z >> vertex.red >> vertex.green >> vertex.blue;

		if (fin.fail()) {
			break;
		}

		vertices.push_back(vertex);
	}
}
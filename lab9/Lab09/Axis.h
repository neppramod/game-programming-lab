#pragma once
#ifndef AXIS
#define AXIS

#include "OGL3DObject.h"

#include <string>
using std::string;


class Axis :
	public OGL3DObject
{
protected:
	float length;
public:
	Axis(const string& name, float length=1.0f);
	virtual ~Axis();
protected:
	void generate();
};

#endif
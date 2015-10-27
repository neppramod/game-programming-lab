#pragma once
#ifndef MATH_UTIL
#define MATH_UTIL

const float PI_CONST = 3.142159f;

#define DegToRad(degrees) ((degrees) * PI_CONST / 180.0f)

struct VertexData {
	float x, y, z, w;
};

#endif

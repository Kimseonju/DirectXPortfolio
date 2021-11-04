#pragma once

#include <DirectXMath.h>
#include <DirectXPackedVector.h>

using namespace DirectX;

#include "Flag.h"
#include <math.h>
#include <random>

#define PI	3.14159f

static float DegreeToRadian(float Angle)
{
	return Angle / 180.f * PI;

}
static float RadianToDegree(float Angle)
{
	return Angle * 180.f / PI;
}

static int GetRandom(int Min, int Max)
{
	std::random_device rd;
	std::mt19937_64 rng1(rd());
	std::uniform_int_distribution<int> dist(Min, Max);


	return dist(rng1);
}
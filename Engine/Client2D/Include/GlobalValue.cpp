#include "GlobalValue.h"

CPlayer* CGlobalValue::MainPlayer;
CBasicMouse* CGlobalValue::MainMouse;

int CGlobalValue::GetRandom(int Random)
{
	std::random_device rd;
	std::mt19937_64 rng1(rd());
	std::uniform_int_distribution<int> dist(0, Random);


	return dist(rng1);
}

float CGlobalValue::Lerp2DMax(float _Start, float _End, float _Ratio)
{
    if (0 >= _Ratio)
    {
        _Ratio = 0.0f;
    }

    if (1.0f <= _Ratio)
    {
        _Ratio = 1.0f;
    }

    return Lerp2D(_Start, _End, _Ratio);
}

float CGlobalValue::Lerp2D(float _Start, float _End, float _Ratio)
{
    float ReturnValue;
    ReturnValue = (1 - _Ratio) * _Start + _Ratio * _End;

    return ReturnValue;
}

#pragma once
#include "Vector3d.h"

class Directional_Light
{
public: 

	Directional_Light();
	~Directional_Light();
	Directional_Light(int redLightIntensity, int greenLightIntensity, int blueLightIntensity, Vector3D directionToLightSource);

	//Accessors
	int GetredLightIntensity();
	void SetredLightIntensity(int input);
	int GetgreenLightIntensity();
	void SetgreenLightIntensity(int input);
	int GetblueLightIntensity();
	void SetblueLightIntensity(int input);
	Vector3D GetdirectionToLightSource();
	void SetdirectionToLightSource(float firstValue, float secondValue, float thirdValue);

private:
	int _redLightIntensity;
	int _greenLightIntensity;
	int _blueLightIntensity;
	Vector3D _directionToLightSource;
};


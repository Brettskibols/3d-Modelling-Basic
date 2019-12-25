#include "Directional_Light.h"

Directional_Light::Directional_Light()
{
	_redLightIntensity = 0;
	_greenLightIntensity = 0;
	_blueLightIntensity = 0;
	_directionToLightSource = Vector3D(0, 0, 0);
}

Directional_Light::~Directional_Light()
{
	//Empty Deconstructor that will be called when 'Rasteriser app' has finished to DESTROY muwhahahahaha!!!!!
}

Directional_Light::Directional_Light(int redLightIntensity, int greenLightIntensity, int blueLightIntensity, Vector3D directionToLightSource)
{
	_redLightIntensity = redLightIntensity;
	_greenLightIntensity = greenLightIntensity;
	_blueLightIntensity = blueLightIntensity;
	_directionToLightSource = directionToLightSource;
}

int Directional_Light::GetredLightIntensity() 
{
	return _redLightIntensity;
}

void Directional_Light::SetredLightIntensity(int input)
{
	_redLightIntensity = input;
}

int Directional_Light::GetgreenLightIntensity() 
{
	return _greenLightIntensity;
}

void Directional_Light::SetgreenLightIntensity(int input)
{
	_greenLightIntensity = input;
}

int Directional_Light::GetblueLightIntensity() 
{
	return _blueLightIntensity;
}

void Directional_Light::SetblueLightIntensity(int input)
{
	_blueLightIntensity = input;
}

Vector3D Directional_Light::GetdirectionToLightSource() 
{
	return Vector3D(_directionToLightSource);
}

void Directional_Light::SetdirectionToLightSource(float firstValue, float secondValue, float thirdValue)
{
	_directionToLightSource = Vector3D(firstValue, secondValue, thirdValue);   //Must specify type of object before values otherwise weird cast errors for types.
}


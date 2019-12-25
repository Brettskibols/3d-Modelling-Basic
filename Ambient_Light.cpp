#include "Ambient_Light.h"

Ambient_Light::Ambient_Light()
{
	_redLightIntensity = 0;
	_greenLightIntensity = 0;
	_blueLightIntensity = 0;
}

Ambient_Light::~Ambient_Light()
{
	//Empty Deconstructor that will be called when 'Rasteriser app' has finished to DESTROY muwhahahahaha!!!!!
}

Ambient_Light::Ambient_Light(int redLightIntensity, int greenLightIntensity, int blueLightIntensity)
{
	_redLightIntensity = redLightIntensity;
	_greenLightIntensity = greenLightIntensity;
	_blueLightIntensity = blueLightIntensity;
}


int Ambient_Light::GetredLightIntensity()
{
	return _redLightIntensity;
}

void Ambient_Light::SetredLightIntensity(int input)
{
	_redLightIntensity = input;
}

int Ambient_Light::GetgreenLightIntensity()
{
	return _greenLightIntensity;
}

void Ambient_Light::SetgreenLightIntensity(int input)
{
	_greenLightIntensity = input;
}

int Ambient_Light::GetblueLightIntensity()
{
	return _blueLightIntensity;
}

void Ambient_Light::SetblueLightIntensity(int input)
{
	_blueLightIntensity = input;
}


/*Ambient_Light::Ambient_Light& operator= (Ambient_Light& rhs)
{

}
*/

//Vertex::operator==(const Vertex& rhs) const

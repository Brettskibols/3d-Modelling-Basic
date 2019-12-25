#pragma once
class Ambient_Light
{
public:

	Ambient_Light();
	~Ambient_Light();
	Ambient_Light(int redLightIntensity, int greenLightIntensity, int blueLightIntensity);

	//Accessors
	int GetredLightIntensity();
	void SetredLightIntensity(int input);
	int GetgreenLightIntensity();
	void SetgreenLightIntensity(int input);
	int GetblueLightIntensity();
	void SetblueLightIntensity(int input);

	Ambient_Light& operator= (Ambient_Light& rhs);

private:
	int _redLightIntensity;
	int _greenLightIntensity;
	int _blueLightIntensity;
};
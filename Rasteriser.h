#pragma once
#include <vector>
#include "Framework.h"
#include "Vertex.h"
#include "Matrix.h"
#include "Model.h"
#include "MD2Loader.h"
#include "Camera.h"
#include "Directional_Light.h"

using namespace std;

class Rasteriser : public Framework
{
public:
	bool Initialise();
	void Render(const Bitmap& bitmap);
	void Update(const Bitmap& bitmap);
	void GeneratePerspectiveMatrix(float d, float aspectRatio);     //Generates Perspective Matrix
	void GenerateViewMatrix(float d, int width, int height);       //Generates Screen (Viewing) Matrix
	void DrawWireFrame(const HDC& deviceContext);
	void DrawSolidFlat(const HDC& deviceContext);
	void DrawSolidFlatDemoColors(const HDC& deviceContext);

	//Accessors
	vector<Directional_Light>& GetDirectionalLights();
	Ambient_Light GetAmbientLight();
	void DrawString(const Bitmap& bitmap, LPCTSTR text);

private:
	Model _inputModel;
	Matrix _transformationMatrix;
	Camera _camera;
	Matrix _perspectiveMatrix;
	Matrix _viewMatrix;
	Ambient_Light _myAmbientLight{ 0, 255, 255 };  //Hard coded because only 1 global at any 1 time and wanted to keep it as this
	vector<Directional_Light> _directionalLights;  //Collection of directional lights
	vector<Ambient_Light> _ambientLights;
	float angle{ 0 };
	int demoState = 0;
	float translationXCounter = 0;
	float translationYCounter = 0;
	float translationZCounter = 0;
	float scalingXCounter = 0;
	float scalingYCounter = 0;
	float scalingZCounter = 0;
	float scalingTotalCounter = 0;
	float totalTranslationCounter = 0;
};
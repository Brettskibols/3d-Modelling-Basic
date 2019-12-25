#include "Rasteriser.h"
#include "MD2Loader.h"
#include "Model.h"
#include "Camera.h"
#include "Bitmap.h"
#include "Polygon3D.h"
#include <vector>

Rasteriser app;

bool Rasteriser::Initialise() 
{
	MD2Loader::LoadModel("marvin.md2", _inputModel, &Model::AddPolygon, &Model::AddVertex);                        //Inserts model polys and verts into object MODEL = _inputModel
	angle = 0;
	_camera = Camera();
	demoState = 0;
	scalingXCounter = 1;
	scalingYCounter = 1;
	scalingZCounter = 1;
	scalingTotalCounter = 1;
	totalTranslationCounter = 1;
	Directional_Light myDirectionalLight(0, 255, 255, Vector3D(1, 0, 1));   //Used for Directional light initialisation
	_directionalLights.push_back(myDirectionalLight);     // pushes back onto dirctional lighting list
	return true;
}

void Rasteriser::Render(const Bitmap& bitmap) //draws the specified Model to the bitmap
{
	if (demoState == 0)
	{
		// Add code to either here or the Matrix Class to do the Radians math so this 'orrible mess with pie goes away
		bitmap.Clear(RGB(255, 255, 255));
		_inputModel.ApplyTransformToLocalVertices(Matrix::RotateMatrixY((float)(angle * 3.14 / 180)));
		_inputModel.ApplyTransformToTransformedVertices(Matrix::Scale(scalingXCounter, scalingXCounter, scalingZCounter));
		_inputModel.ApplyTransformToTransformedVertices(_camera.GetCameraTransformation());
		_inputModel.ApplyTransformToTransformedVertices(_perspectiveMatrix);
		_inputModel.Dehomogenize();
		_inputModel.ApplyTransformToTransformedVertices(_viewMatrix);
		DrawString(bitmap, L"WireFrame Model Only + Rotation");
		_inputModel.Draw(bitmap.GetDC());    
	}

	else if (demoState == 1)
	{
		bitmap.Clear(RGB(255, 255, 255));
		_inputModel.ApplyTransformToLocalVertices(Matrix::RotateMatrixY((float)(angle * 3.14 / 180)));
		_inputModel.ApplyTransformToTransformedVertices(Matrix::Scale(scalingXCounter, scalingXCounter, scalingZCounter));
		_inputModel.ApplyTransformToTransformedVertices(_camera.GetCameraTransformation());
		_inputModel.ApplyTransformToTransformedVertices(_perspectiveMatrix);
		_inputModel.Dehomogenize();
		_inputModel.ApplyTransformToTransformedVertices(_viewMatrix);
		DrawString(bitmap, L"WireFrame Model Only + Scaling");
		_inputModel.Draw(bitmap.GetDC());
	}

	else if (demoState == 2)
	{
		bitmap.Clear(RGB(255, 255, 255));
		_inputModel.ApplyTransformToLocalVertices(Matrix::RotateMatrixY((float)(angle * 3.14 / 180)));
		_inputModel.ApplyTransformToTransformedVertices(Matrix::Scale(scalingXCounter, scalingXCounter, scalingZCounter));
		_inputModel.ApplyTransformToTransformedVertices(_camera.GetCameraTransformation());
		_inputModel.ApplyTransformToTransformedVertices(_perspectiveMatrix);
		_inputModel.Dehomogenize();
		_inputModel.ApplyTransformToTransformedVertices(_viewMatrix);
		DrawString(bitmap, L"WireFrame Model Only + Rotation + Scaling");
		_inputModel.Draw(bitmap.GetDC());
	}

	else if (demoState == 3)
	{
		bitmap.Clear(RGB(255, 255, 255));
		_inputModel.ApplyTransformToLocalVertices(Matrix::RotateMatrixY((float)(angle * 3.14 / 180)));
		_inputModel.ApplyTransformToTransformedVertices(Matrix::Translation(translationXCounter, translationYCounter, translationZCounter));
		_inputModel.ApplyTransformToTransformedVertices(_camera.GetCameraTransformation());
		_inputModel.ApplyTransformToTransformedVertices(_perspectiveMatrix);
		_inputModel.Dehomogenize();
		_inputModel.ApplyTransformToTransformedVertices(_viewMatrix);
		DrawString(bitmap, L"WireFrame Model Only + Rotation + Translation");
		_inputModel.Draw(bitmap.GetDC());
	}
	else if (demoState == 4)
	{
		bitmap.Clear(RGB(255, 255, 255));
		_inputModel.ApplyTransformToLocalVertices(Matrix::RotateMatrixY((float)(angle * 3.14 / 180)));
		_inputModel.ApplyTransformToTransformedVertices(Matrix::Translation(translationXCounter, translationYCounter, translationZCounter));
		_inputModel.ApplyTransformToTransformedVertices(_camera.GetCameraTransformation());
		_inputModel.ApplyTransformToTransformedVertices(_perspectiveMatrix);
		_inputModel.Dehomogenize();
		_inputModel.ApplyTransformToTransformedVertices(_viewMatrix);
		DrawString(bitmap, L"WireFrame Model Only + Rotation + Translation");
		_inputModel.Draw(bitmap.GetDC());
	}

	else if (demoState == 5)
	{
		bitmap.Clear(RGB(255, 255, 255));
		_inputModel.ApplyTransformToLocalVertices(Matrix::RotateMatrixY((float)(angle * 3.14 / 180)));
		_inputModel.CalculateBackFaces(_camera);
		_inputModel.ApplyTransformToTransformedVertices(_camera.GetCameraTransformation());
		_inputModel.Sort();
		_inputModel.ApplyTransformToTransformedVertices(_perspectiveMatrix);
		_inputModel.Dehomogenize();
		_inputModel.ApplyTransformToTransformedVertices(_viewMatrix);
		DrawString(bitmap, L"WireFrame Model + Backface Culling");
		Rasteriser::DrawWireFrame(bitmap.GetDC());
	}

	else if (demoState == 6)
	{
		bitmap.Clear(RGB(255, 255, 255));
		_inputModel.ApplyTransformToLocalVertices(Matrix::RotateMatrixY((float)(angle * 3.14 / 180)));
		_inputModel.CalculateBackFaces(_camera);
		_inputModel.ApplyTransformToTransformedVertices(_camera.GetCameraTransformation());
		_inputModel.Sort();
		_inputModel.ApplyTransformToTransformedVertices(_perspectiveMatrix);
		_inputModel.Dehomogenize();
		_inputModel.ApplyTransformToTransformedVertices(_viewMatrix);
		DrawString(bitmap, L"Polygon Drawing + Flat Shading");
		Rasteriser::DrawSolidFlatDemoColors(bitmap.GetDC());
	}

	else if (demoState == 7)
	{
		bitmap.Clear(RGB(0, 0, 0));
		_inputModel.ApplyTransformToLocalVertices(Matrix::RotateMatrixY((float)(angle * 3.14 / 180)));
		_inputModel.CalculateBackFaces(_camera);
		_inputModel.ApplyTransformToTransformedVertices(_camera.GetCameraTransformation());
		_inputModel.Sort();
		_inputModel.SetKd_red(0.5f);
		_inputModel.SetKd_green(0.5f);          //Setting reflection coefficients of model to 1.0 (Fully reflects all light for demo purposes)
		_inputModel.SetKd_blue(0.5f);
		_inputModel.CalculateAmbientLight(_myAmbientLight);
		_inputModel.ApplyTransformToTransformedVertices(_perspectiveMatrix);
		_inputModel.Dehomogenize();
		_inputModel.ApplyTransformToTransformedVertices(_viewMatrix);
		DrawString(bitmap, L"Polygon Drawing + Ambient Lighting");
		Rasteriser::DrawSolidFlat(bitmap.GetDC());
	}

	else if (demoState == 8)
	{
	bitmap.Clear(RGB(0, 0, 0));
	_inputModel.ApplyTransformToLocalVertices(Matrix::RotateMatrixY((float)(angle * 3.14 / 180)));
	_inputModel.CalculateBackFaces(_camera);
	_inputModel.ApplyTransformToTransformedVertices(_camera.GetCameraTransformation());
	_inputModel.Sort();
	_inputModel.SetKd_red(0.5f);
	_inputModel.SetKd_green(0.5f);          //demo values
	_inputModel.SetKd_blue(0.5f);
	_inputModel.CalculateAmbientLight(_myAmbientLight);
	_inputModel.CalculateLightingDirectional(_directionalLights);
	_inputModel.ApplyTransformToTransformedVertices(_perspectiveMatrix);
	_inputModel.Dehomogenize();
	_inputModel.ApplyTransformToTransformedVertices(_viewMatrix);
	DrawString(bitmap, L"Ambient Lighting + Directional Lighting + Polygon Sorting");
	Rasteriser::DrawSolidFlat(bitmap.GetDC());
	}
}

void Rasteriser::Update(const Bitmap& bitmap)
{
	float width = (float)bitmap.GetWidth();
	float height = (float)bitmap.GetHeight();
	float aspectRatio = (float)(width / height);
	float d = 1;
	GeneratePerspectiveMatrix(d, aspectRatio);
	GenerateViewMatrix(d, (int)width, (int)height);
	
	//Demostate setting machine
	if (angle < 270)
	{
		demoState = 0;
		angle++;
	}

	else if (angle >= 270 && angle < 500)
	{
		demoState = 1;
		angle++;
	}

	else if (angle >= 500 && angle < 650)
	{
		demoState = 2;
		angle++;
	}

	else if (angle >= 650 && angle < 850)
	{
		demoState = 3;
		angle++;
	}

	else if (angle >= 850 && angle < 1100)
	{
		demoState = 4;
		angle++;
	}

	else if (angle >= 1100 && angle < 1300)
	{
		demoState = 5;
		angle++;
	}

	else if (angle >= 1300 && angle < 1500)
	{
		demoState = 6;
		angle++;
	}

	else if (angle >= 1500 && angle < 1750)
	{
		demoState = 7;
		angle++;
	}
	else if (angle >= 1750 && angle < 2200)
	{
		demoState = 8;
		angle++;
	}
	else if(angle == 2200)
	{
		angle = 0;
	}

	//Scaling and Translation machines to get Marvin to the desired spot and back again
	if (demoState == 1)
	{
		if (scalingTotalCounter < 1.5)
		{
			scalingXCounter = static_cast <float> (scalingXCounter + 0.005);
			scalingYCounter = static_cast <float> (scalingYCounter + 0.005);
			scalingZCounter = static_cast <float> (scalingZCounter + 0.005);
			scalingTotalCounter = static_cast <float> (scalingTotalCounter + 0.005);
		}
	}
	else if (demoState == 2)
	{
		if (scalingTotalCounter > 1)
		{
			scalingXCounter = static_cast <float> (scalingXCounter - 0.005);
			scalingYCounter = static_cast <float> (scalingYCounter - 0.005);
			scalingZCounter = static_cast <float> (scalingZCounter - 0.005);
			scalingTotalCounter = static_cast <float> (scalingTotalCounter - 0.005);
		}
	}

	else if (demoState == 3)
	{
		if (totalTranslationCounter < 100)
		{
			translationXCounter = static_cast <float> (translationXCounter + 1);
			translationYCounter = static_cast <float> (translationYCounter + 1);
			translationZCounter = static_cast <float> (translationZCounter + 1);
			totalTranslationCounter = static_cast <float> (totalTranslationCounter + 1);
		}
	}

	else if (demoState == 4)
	{
		if (totalTranslationCounter > 1)
		{
			translationXCounter = static_cast <float> (translationXCounter - 1);
			translationYCounter = static_cast <float> (translationYCounter - 1);
			translationZCounter = static_cast <float> (translationZCounter - 1);
			totalTranslationCounter = static_cast <float> (totalTranslationCounter - 1);
		}
	}
}

void Rasteriser::GeneratePerspectiveMatrix(float d, float aspectRatio)   
{
	_perspectiveMatrix = { d/aspectRatio,    0,    0,    0,
	                       0,                d,    0,    0,
		                   0,                0,    d,    0,
		                   0,                0,    1,    0 };
}

void Rasteriser::GenerateViewMatrix(float d, int width, int height)      
{
	float halfWidth = (float)(width / 2); 
	float halfHeight = (float)(height / 2);
	float halfD = (float)(d / 2); 

	_viewMatrix =     { halfWidth,           0,          0,        halfWidth,
	                    0,       -(halfHeight),     0,        halfHeight,
		                0,              0,          halfD,     halfD,
		                0,              0,          0,           1 };
}

void Rasteriser::DrawWireFrame(const HDC& deviceContext)    
{
	const HPEN& pen = (HPEN)CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	const HPEN& old = (HPEN)SelectObject(deviceContext, pen);

	for (Polygon3D& polygon : _inputModel.GetPolygons())  
	{
		bool culling = polygon.GetcullPolygonFlag();
		if (culling == false)
		{
			int v0 = polygon.GetIndex(0);
			int v1 = polygon.GetIndex(1);
			int v2 = polygon.GetIndex(2);

			Vertex& vertexA = _inputModel.GetTransformedVertices()[v0]; //points
			Vertex& vertexB = _inputModel.GetTransformedVertices()[v1];                                                                  
			Vertex& vertexC = _inputModel.GetTransformedVertices()[v2];                                                                  

			MoveToEx(deviceContext, vertexA.GetIntX(), vertexA.GetIntY(), NULL); //Polygon
			LineTo(deviceContext, vertexB.GetIntX(), vertexB.GetIntY());
			LineTo(deviceContext, vertexC.GetIntX(), vertexC.GetIntY());
			LineTo(deviceContext, vertexA.GetIntX(), vertexA.GetIntY());
		}
	}
	SelectObject(deviceContext, old);
	DeleteObject(pen);
}

void Rasteriser::DrawSolidFlat(const HDC& deviceContext)
{
	POINT logicalCoordinates[3] { 0,0,0 };

	for (Polygon3D& polygon : _inputModel.GetPolygons())
	{

	int v0 = polygon.GetIndex(0);
	int v1 = polygon.GetIndex(1);
	int v2 = polygon.GetIndex(2);

	Vertex& vertexA = _inputModel.GetTransformedVertices()[v0]; //points
	Vertex& vertexB = _inputModel.GetTransformedVertices()[v1];                                                                  
	Vertex& vertexC = _inputModel.GetTransformedVertices()[v2];

	logicalCoordinates[0] = {static_cast<long>(vertexA.GetIntX()), static_cast<long>(vertexA.GetIntY())}; //points
	logicalCoordinates[1] = {static_cast<long>(vertexB.GetIntX()), static_cast<long>(vertexB.GetIntY())};                           
	logicalCoordinates[2] = { static_cast<long>(vertexC.GetIntX()), static_cast<long>(vertexC.GetIntY())};

	const HPEN& pen = (HPEN)CreatePen(PS_SOLID, 1, polygon.GetResultingColor());
	const HPEN& oldpen = (HPEN)SelectObject(deviceContext, pen);
	const HBRUSH& brush = (HBRUSH)CreateSolidBrush(polygon.GetResultingColor());
	const HBRUSH& oldbrush = (HBRUSH)SelectObject(deviceContext, brush);

	Polygon(deviceContext, logicalCoordinates, 3);   //Draws using Polygon() passed HDC, my list of points and the no of indexed points

	SelectObject(deviceContext, oldpen);
	DeleteObject(pen);
	SelectObject(deviceContext, oldbrush);
	DeleteObject(brush);
	}
}

void Rasteriser::DrawSolidFlatDemoColors(const HDC& deviceContext)
{
	POINT logicalCoordinates[3]{ 0,0,0 };

	for (Polygon3D& polygon : _inputModel.GetPolygons())
	{

		int v0 = polygon.GetIndex(0);
		int v1 = polygon.GetIndex(1);
		int v2 = polygon.GetIndex(2);

		Vertex& vertexA = _inputModel.GetTransformedVertices()[v0]; //points
		Vertex& vertexB = _inputModel.GetTransformedVertices()[v1];                                                                
		Vertex& vertexC = _inputModel.GetTransformedVertices()[v2];

		logicalCoordinates[0] = { static_cast<long>(vertexA.GetIntX()), static_cast<long>(vertexA.GetIntY()) }; 
		logicalCoordinates[1] = { static_cast<long>(vertexB.GetIntX()), static_cast<long>(vertexB.GetIntY()) };                           
		logicalCoordinates[2] = { static_cast<long>(vertexC.GetIntX()), static_cast<long>(vertexC.GetIntY()) };

		polygon.SetResultingColor(RGB(0,255,255));   //Sets flat colors for the demo shading using Polygon()

		const HPEN& pen = (HPEN)CreatePen(PS_SOLID, 1, polygon.GetResultingColor());
		const HPEN& oldpen = (HPEN)SelectObject(deviceContext, pen);
		const HBRUSH& brush = (HBRUSH)CreateSolidBrush(polygon.GetResultingColor());
		const HBRUSH& oldbrush = (HBRUSH)SelectObject(deviceContext, brush);

		Polygon(deviceContext, logicalCoordinates, 3); // Own drawing function that handles the array of points and draws between them, 
		                                               // solidbrush handing the polygon color and pen used for the lines between vertices

		SelectObject(deviceContext, oldpen);
		DeleteObject(pen);
		SelectObject(deviceContext, oldbrush);
		DeleteObject(brush);
	}
}

vector<Directional_Light>& Rasteriser::GetDirectionalLights()
{
	return _directionalLights;
}

/*Ambient_Light Rasteriser::GetAmbientLight()
{
	return _ambientLights;                     //Decided against using this as only 1 ambient light needed and hardcoded.
}
*/

void Rasteriser::DrawString(const Bitmap& bitmap, LPCTSTR text)
{
	HDC hdc = bitmap.GetDC();
	HFONT hFont, hOldFont;

	// Retrieve a handle to the variable stock font.  
	hFont = hFont = CreateFont(30, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Myfont"));

	// Select the variable stock font into the specified device context. 
	if (hOldFont = (HFONT)SelectObject(hdc, hFont))
	{
		SetTextColor(hdc, RGB(255, 255, 255));
		SetBkColor(hdc, RGB(0, 0, 0));

		// Display the text string.  
		TextOut(hdc, 10, 10, text, lstrlen(text));

		// Restore the original font.        
		SelectObject(hdc, hOldFont);
	}
	DeleteObject(hFont);
}



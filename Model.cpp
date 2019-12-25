#include "Model.h"
#include "Camera.h"
#include "Vertex.h"
#include <vector>
#include <algorithm>
#include "Rasteriser.h"
#include <cmath>
using namespace std;

Model::Model()
{
	//initialize 
	_ka_red = 0.2f;
	_ka_green = 0.2f;
	_ka_blue = 0.2f;

	_kd_red = 0.0f;
	_kd_green = 0.0f;
	_kd_blue = 0.0f;
}

Model::~Model()
{
	//Empty Deconstructor that will be called when 'Rasteriser app' has finished to DESTROY muwhahahahaha!!!!!
}

void Model::Dehomogenize()
{
	for (Vertex& vertex : _transformedVertices)
	{
		vertex.Dehomogenize();
	}
}

vector<Polygon3D>& Model::GetPolygons()   //Do I need const at the start? MAYBE REMOVE from 'const vector<Polygon3D>& GetPolygons();' in Model.h.
//const vector<Polygon3D>& GetPolygons();
{
	return _polygons; //Returns list of Polgons.
}

vector<Vertex>& Model::GetTransformedVertices()
{
	return _transformedVertices;
}

size_t Model::GetPolygonCount() const
{
	return _polygons.size(); //Returns Polygon number.
}

const vector<Vertex>& Model::GetVertices()
{
	return _vertices; //Returns list of verticles.
}

size_t Model::GetVertexCount() const
{
	return _vertices.size(); //Returns Vertices number.
}

void Model::Draw(const HDC& deviceContext)    // MOVE to Rasteriser class, rename 'DrawWireFrame()' and change so only draws polygons if NOT marked for culling
{
	const HPEN& pen = (HPEN)CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	const HPEN& old = (HPEN)SelectObject(deviceContext, pen);
	
	for (Polygon3D& polygon : _polygons)
	{
		int v0 = polygon.GetIndex(0);
		int v1 = polygon.GetIndex(1);
		int v2 = polygon.GetIndex(2);

		/*
		Vertex& vertexA = _displyVertices[v0];
		Vertex& vertexB = _displyVertices[v1];
		Vertex& vertexC = _displyVertices[v2];
		*/

		Vertex& vertexA = _transformedVertices[v0];
		Vertex& vertexB = _transformedVertices[v1];
		Vertex& vertexC = _transformedVertices[v2];

		

		MoveToEx(deviceContext, vertexA.GetIntX(), vertexA.GetIntY(), NULL);

		LineTo(deviceContext, vertexB.GetIntX(), vertexB.GetIntY());
		LineTo(deviceContext, vertexC.GetIntX(), vertexC.GetIntY());
		LineTo(deviceContext, vertexA.GetIntX(), vertexA.GetIntY());
	}
	SelectObject(deviceContext, old);
	DeleteObject(pen);
}

void Model::CalculateBackFaces(Camera _camera)
{
	for (Polygon3D& polygon : _polygons)
	{
		int index0 = polygon.GetIndex(0);
		int index1 = polygon.GetIndex(1);
		int index2 = polygon.GetIndex(2);

		Vertex& vertex0 = _transformedVertices[index0];
		Vertex& vertex1 = _transformedVertices[index1];
		Vertex& vertex2 = _transformedVertices[index2];

		Vector3D a = Vertex::VertexToVector3D(vertex0, vertex1);
		Vector3D b = Vertex::VertexToVector3D(vertex0, vertex2);

		Vector3D normal = Vector3D::CrossProduct(b, a);                                         
		Vector3D eyeVector = Vertex::VertexToVector3D(vertex0, _camera.getLocation());           
		                                                                                         
		float dotProductOfNormalVectorAndEyeVector = Vector3D::DotProduct(normal, eyeVector);    
		if (dotProductOfNormalVectorAndEyeVector < 0)
		{
			polygon.SetcullPolygonFlag(true);
		}
		else if (dotProductOfNormalVectorAndEyeVector > 0)   
		{
			polygon.SetcullPolygonFlag(false);
		}
	}
}

void Model::Sort()
{
	for (Polygon3D& polygon : _polygons)
	{
		int v0 = polygon.GetIndex(0);
		int v1 = polygon.GetIndex(1);
		int v2 = polygon.GetIndex(2);

		Vertex& vertexA = GetTransformedVertices()[v0];
		Vertex& vertexB = GetTransformedVertices()[v1];                                                                 
		Vertex& vertexC = GetTransformedVertices()[v2];

		float ThisPolygonAverageZValue = (vertexA.GetZ() + vertexB.GetZ() + vertexC.GetZ()) / 3;
		polygon.SetaverageZValue(ThisPolygonAverageZValue);
	}
	sort(_polygons.begin(), _polygons.end(), [](Polygon3D& a, Polygon3D& b)
	{
		return a.GetaverageZValue() > b.GetaverageZValue();    
	});
}

void Model::AddVertex(float x, float y, float z)
{
	_vertices.push_back(Vertex(x, y, z));
		//Adds Vertex.....Hopefully - New Vertex body created that accepts x,y and x, default value of 1 given to UNUSED w. 
}

void Model::AddPolygon(int i0, int i1, int i2)
{
	_polygons.push_back(Polygon3D(i0, i1, i2));
}

void Model::ApplyTransformToLocalVertices(const Matrix& transform) //Applies transformation Matrix to each Vertex in the original _vertices collection
{
	_transformedVertices.clear();

	for (Vertex i : _vertices) 
	{
		_transformedVertices.push_back(transform * i);
	}
}

size_t Model::GetTransformedVertexCount() const
{
	int count = 0;
	for (Vertex i : _transformedVertices)
	{
		count++;
	}
	return count;
}

void Model::ApplyTransformToTransformedVertices(const Matrix& transform) //Applies transformation Matrix to each Vertex in the _transformedVertices collection
{
	for (int i = 0; i < GetTransformedVertexCount(); i++)
	{

		_transformedVertices[i] = transform * _transformedVertices[i];
	}
}

float Model::GetKd_red()
{
	return _kd_red;
}

void Model::SetKd_red(float value)
{
	_kd_red = value;
}

float Model::GetKd_green()
{
	return _kd_green;
}

void Model::SetKd_green(float value)
{
	_kd_green = value;
}

float Model::GetKd_blue()
{
	return _kd_blue;
}

void Model::SetKd_blue(float value)
{
	_kd_blue = value;
}

void Model::CalculateAmbientLight(Ambient_Light& _ambientLight)
{
	for (Polygon3D& polygon : _polygons)
	{
		float totalRed = 0;
		float totalGreen = 0;
		float totalBlue = 0;

		float tempRed = 0;
		float tempGreen = 0;
		float tempBlue = 0;

		tempRed = static_cast<float>(_ambientLight.GetredLightIntensity());
		tempGreen = static_cast<float>(_ambientLight.GetgreenLightIntensity());
		tempBlue = static_cast<float>(_ambientLight.GetblueLightIntensity());

		tempRed = tempRed * _ka_red;
		tempGreen = tempGreen * _ka_green;
		tempBlue = tempBlue * _ka_blue;

		totalRed = totalRed + tempRed;
		totalGreen = totalGreen + tempGreen;
		totalBlue = totalBlue + tempBlue;

		if (totalRed > 255)
		{
			totalRed = 255;
		}
		else if (totalRed < 0)
		{
			totalRed = 0;
		}

		if (totalGreen > 255)
		{
			totalGreen = 255;
		}
		else if (totalGreen < 0)
		{
			totalGreen = 0;
		}

		if (totalBlue > 255)
		{
			totalBlue = 255;
		}
		else if (totalBlue < 0)
		{
			totalBlue = 0;
		}

		polygon.SetResultingColor(RGB(totalRed, totalGreen, totalBlue));
	}
}



void Model::CalculateLightingDirectional(vector<Directional_Light>& _directionalLights)
{
	for (Polygon3D& polygon : _polygons)
	{
		float totalRed = GetRValue(polygon.GetResultingColor());
		float totalGreen = GetGValue(polygon.GetResultingColor());
		float totalBlue = GetBValue(polygon.GetResultingColor());
		
		if (polygon.GetcullPolygonFlag() == false)
		{
			for (Directional_Light& lightSource : _directionalLights)
			{
				float tempRed = 0;
				float tempGreen = 0;
				float tempBlue = 0;

				tempRed = static_cast<float>(lightSource.GetredLightIntensity());
				tempGreen = static_cast<float>(lightSource.GetgreenLightIntensity());
				tempBlue = static_cast<float>(lightSource.GetblueLightIntensity());

				tempRed = tempRed * _kd_red;
				tempGreen = tempGreen * _kd_green;
				tempBlue = tempBlue * _kd_blue;

				int index0 = polygon.GetIndex(0);
				int index1 = polygon.GetIndex(1);
				int index2 = polygon.GetIndex(2);

				Vertex& vertex0 = _transformedVertices[index0];
				Vertex& vertex1 = _transformedVertices[index1];
				Vertex& vertex2 = _transformedVertices[index2];

				Vector3D a = Vertex::VertexToVector3D(vertex0, vertex1);
				Vector3D b = Vertex::VertexToVector3D(vertex0, vertex2);
				Vector3D polygonNormal = Vector3D::CrossProduct(b, a);

				Vector3D directionToLightSource = lightSource.GetdirectionToLightSource();
				float polygonNormalLength = polygonNormal.GetLength();
				float lightSourceLength = directionToLightSource.GetLength();
				Vector3D polygonNormalisedNormal((polygonNormal.GetXv()) / polygonNormalLength, (polygonNormal.GetYv()) / polygonNormalLength, (polygonNormal.GetZv()) / polygonNormalLength);
				Vector3D lightNormalised((directionToLightSource.GetXv()) / lightSourceLength, (directionToLightSource.GetYv()) / lightSourceLength, (directionToLightSource.GetZv()) / lightSourceLength);
				
				float dotProductNormalNormalLightSourceNormal = Vector3D::DotProduct(polygonNormalisedNormal, lightNormalised);

				if (dotProductNormalNormalLightSourceNormal < 0)
				{
					dotProductNormalNormalLightSourceNormal = 0;
				}

				tempRed = tempRed * dotProductNormalNormalLightSourceNormal;
				tempGreen = tempGreen * dotProductNormalNormalLightSourceNormal;
				tempBlue = tempBlue * dotProductNormalNormalLightSourceNormal;

				totalRed = totalRed + tempRed;
				totalGreen = totalGreen + tempGreen;
				totalBlue = totalBlue + tempBlue;

				if (totalRed > 255)
				{
					totalRed = 255;
				}
				else if (totalRed < 0)
				{
					totalRed = 0;
				}

				if (totalGreen > 255)
				{
					totalGreen = 255;
				}
				else if (totalGreen < 0)
				{
					totalGreen = 0;
				}

				if (totalBlue > 255)
				{
					totalBlue = 255;
				}
				else if (totalBlue < 0)
				{
					totalBlue = 0;
				}
			}
		}
		polygon.SetResultingColor(RGB(totalRed, totalGreen, totalBlue));
	}
}
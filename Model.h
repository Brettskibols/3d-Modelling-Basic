#pragma once
#include "Polygon3D.h"
#include <vector>
#include "Vertex.h"
#include "Matrix.h"
#include <windows.h>
#include "Polygon3d.h"
#include "Camera.h"
#include "Directional_Light.h"
#include "Ambient_Light.h"

using namespace std;

class Model
{
public:
	Model();
	~Model();

	//Accessors
	vector<Polygon3D>& GetPolygons();    //vector<Directional_Light>& GetDirectionalLights();>
	vector<Vertex>& GetTransformedVertices();
	const vector<Vertex>& GetVertices();     

	void Dehomogenize();
	size_t GetPolygonCount() const;
	size_t GetVertexCount() const;           
	size_t GetTransformedVertexCount() const;

	void Draw(const HDC& deviceContext);
	void CalculateBackFaces(Camera _camera);
	//void Sort(Model _inputModel);
	void Sort();

	//Adding to Vertex's and Polygons
	void AddVertex(float x, float y, float z);
	void AddPolygon(int i0, int i1, int i2);
	//void AddPolygon(int i0, int i1, int i2);

	//Transformation methods
	void ApplyTransformToLocalVertices(const Matrix &transform);                            //Applies transformation Matrix to each Vertex in the original _vertices collection
	void ApplyTransformToTransformedVertices(const Matrix &transform);                      //Applies transformation Matrix to each Vertex in the _transformedVertices collection

	//Accessors for Model reflectance coefficients
	float GetKd_red();
	void SetKd_red(float value);
	float GetKd_green();
	void SetKd_green(float value);
	float GetKd_blue();
	void SetKd_blue(float value);

	//Lighting related methods
	void CalculateLightingDirectional(vector<Directional_Light>& _directionalLights);
	void CalculateAmbientLight(Ambient_Light& _ambientLight);

private:
	vector<Polygon3D> _polygons;
	vector<Vertex> _vertices;
	vector<Vertex> _transformedVertices;
	vector<Vertex> _temp;

	float _ka_red;
	float _ka_green;
	float _ka_blue;

	float _kd_red;
	float _kd_green;
	float _kd_blue;
};


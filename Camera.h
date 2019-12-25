#pragma once
#include "Matrix.h"

class Camera
{
public:

	Camera();
	~Camera();
	Camera(const Vertex location, float _xRotation, float _yRotation, float _zRotation);

	//Accessors:
	void AssembleCameraMatrix();
	float GetxRotation() const;
	void SetxRotation(float rhs);
	float GetyRotation() const;
	void SetyRotation(float rhs);
	float GetzRotation() const;
	void SetzRotation(float rhs);
	float GetxFocalPoint() const;
	void SetxFocalPoint(const float xFocalPoint);
	float GetyFocalPoint() const;
	void SetyFocalPoint(const float yFocalPoint);
	float GetzFocalPoint() const;
	void SetzFocalPoint(const float zFocalPoint);
	void SetLocation(Vertex rhs);
	Vertex getLocation() const;

	void accessValues(Vertex _location, float xRotation, float yRotation, float zRotation);
	Matrix GetCameraTransformation();
	Matrix _cameraTransformation;
	Matrix transform;

private:
	float _xRotation;
	float _yRotation;
	float _zRotation;
	float _xFocalPoint;
	float _yFocalPoint;
	float _zFocalPoint;
	Vertex _location;
};


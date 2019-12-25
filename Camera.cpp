#include "Camera.h"
#include <cmath>
#include "bitmap.h"

/*
Class to handle viewing camera transformation
*/

Camera::Camera()
{
	accessValues(Vertex(0, 0, -50, 1), 0, 0, 0);
}

Camera::Camera(const Vertex location, float xRotation, float yRotation, float zRotation)
{
	accessValues(location, xRotation, yRotation, zRotation);
}

Camera::~Camera()
{
	//Empty Deconstructor that will be called when 'Rasteriser app' has finished to DESTROY muwhahahahaha!!!!!
}

Vertex Camera::getLocation() const
{
	return _location;
}

void Camera::SetLocation(Vertex rhs)
{
	_location = rhs;
}

float Camera::GetxRotation() const
{
	return (float)(_xRotation * (3.14 / 180));
}

void Camera::SetxRotation(float rhs)
{
	_xRotation = rhs;
}

float Camera::GetyRotation() const
{
	return (float)(_yRotation * (3.14 / 180));
}

void Camera::SetyRotation(float rhs)
{
	_yRotation = rhs;
}

float Camera::GetzRotation() const
{
	return (float)(_zRotation * (3.14 / 180));
}

void Camera::SetzRotation(float rhs)
{
	_zRotation = rhs;
}

float Camera::GetxFocalPoint() const
{
	return _xFocalPoint;
}

void Camera::SetxFocalPoint(const float xFocalPoint)
{
	_xFocalPoint = xFocalPoint;
}

float Camera::GetyFocalPoint() const
{
	return _yFocalPoint;
}

void Camera::SetyFocalPoint(const float yFocalPoint)
{
	_yFocalPoint = yFocalPoint;
}

float Camera::GetzFocalPoint() const
{
	return _zFocalPoint;
}

void Camera::SetzFocalPoint(const float zFocalPoint)
{
	_zFocalPoint = zFocalPoint;
}

void Camera::accessValues(Vertex location, float xRotation, float yRotation, float zRotation)
{
	_location = location;
	_xRotation = xRotation;
	_yRotation = yRotation;
	_zRotation = zRotation;
	AssembleCameraMatrix();
}

void Camera::AssembleCameraMatrix()
{
	Matrix xRotationMatrix = {       1,                0,                        0,                 0,
									 0,       cos(GetxRotation()),      sin(GetxRotation()),        0,
									 0,      -sin(GetxRotation()),      cos(GetxRotation()),        0,
									 0,                0,                        0,                 1 };

	Matrix yRotationMatrix = { cos(GetyRotation()),    0,               -sin(GetyRotation()),       0,
									 0,                1,                        0,                 0,
							   sin(GetyRotation()),    0,                cos(GetyRotation()),       0,
									 0,                0,                          0,               1 };

	Matrix zRotationMatrix = { cos(GetzRotation()), sin(GetzRotation()),               0,           0,
							  -sin(GetzRotation()), cos(GetzRotation()),               0,           0,
									 0,                0,                              1,           0,
									 0,                0,                              0,           1 };

	Matrix positionMatrix = {        1,                0,                  0,                 -(_location.GetX()),
									 0,                1,                  0,                 -(_location.GetY()),
									 0,                0,                  1,                 -(_location.GetZ()),
									 0,                0,                  0,                       1 };

	 _cameraTransformation = xRotationMatrix * yRotationMatrix * zRotationMatrix * positionMatrix;
}

Matrix Camera::GetCameraTransformation()
{
	return _cameraTransformation;
}
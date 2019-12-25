#pragma once
#include "windows.h"
class Polygon3D
{
public:
	Polygon3D();
	Polygon3D(const int& index0, const int& index1, const int& index2);
	~Polygon3D();
	Polygon3D(const Polygon3D& p);

	// Remember to RESET the culling flags when the Polygon doesn't need to be culled, otherwise the model will dissappear after 1 rotation
	// Add collection to Polygon 3D to store the normals of the polygons as will need it for future excercises
	// Update copy constructors and '=' operator to handle additional fields (such as the new BOOL for culling)

	//Accessors
	int GetIndex(const int& i) const;
	bool GetcullPolygonFlag() const;
	void SetcullPolygonFlag(bool input);
	float GetaverageZValue() const;
	void SetaverageZValue(float input);
	COLORREF GetResultingColor();
	void SetResultingColor(COLORREF inputColor);

	//Assignment Operators
	Polygon3D& operator= (const Polygon3D& rhs);

private:
	int _indices[3];
	bool _cullPolygonFlag;
	float _averageZValue;
	COLORREF _resultingColor;
};


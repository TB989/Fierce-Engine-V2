#pragma once

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/

/* SystemIncludes*/

/* Forward declarations: 
*  -Pointers:  Pointer* myPointer;
*              Reference& myReference;
*  -Functions: Object MyFunction(Object myObject);
*              Pointer* MyFunction(Pointer* myPointer);
*              Reference& MyFunction(Reference& myReference);
*/

class Mat2 {
public:
	Mat2();
private:
	float m00, m10;
	float m01, m11;
};

class Mat3 {
public:
	Mat3();
private:
	float m00, m10, m20;
	float m01, m11, m21;
	float m02, m12, m22;
};

class Mat4 {
public:
	Mat4();

	static void getOrthographicProjectionMatrix(Mat4* mat, float width, float height, float nn, float ff);
public:
	float m00, m10, m20, m30;
	float m01, m11, m21, m31;
	float m02, m12, m22, m32;
	float m03, m13, m23, m33;
};
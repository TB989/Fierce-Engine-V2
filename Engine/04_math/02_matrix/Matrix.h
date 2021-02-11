#pragma once

#define M00 m[0]
#define M10 m[1]
#define M20 m[2]
#define M30 m[3]

#define M01 m[4]
#define M11 m[5]
#define M21 m[6]
#define M31 m[7]

#define M02 m[8]
#define M12 m[9]
#define M22 m[10]
#define M32 m[11]

#define M03 m[12]
#define M13 m[13]
#define M23 m[14]
#define M33 m[15]

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/
#include "99_utils/FierceStrings.h"

/* SystemIncludes*/

/* Forward declarations: 
*  -Pointers:  Pointer* myPointer;
*              Reference& myReference;
*  -Functions: Object MyFunction(Object myObject);
*              Pointer* MyFunction(Pointer* myPointer);
*              Reference& MyFunction(Reference& myReference);
*/

class Vector4f;
class Transform2D;
class Transform3D;

class Mat4 {
public:
	Mat4();
	Mat4(float* matrix);
	Mat4(const Mat4& matrix);
	~Mat4();

public:
	float* get();
	void print(std::string name);

	void setToIdentity();
	void setToNull();
	void setToTranslation(float x,float y,float z);
	void setToXRotation(float angle);
	void setToYRotation(float angle);
	void setToZRotation(float angle);
	void setToScale(float scaleX,float scaleY,float scaleZ);
	void setToOrthographicProjection(float width, float height,float n,float f);
	void setToPerspectiveProjection(float aspect, float FOV, float n, float f);
	void setToTransform(Transform2D* transform);
	void setToTransform(Transform3D* transform);
	void setToView(Transform3D* transform);

	Mat4* translate(float x,float y,float z);
	Mat4* rotateX(float angle);
	Mat4* rotateY(float angle);
	Mat4* rotateZ(float angle);
	Mat4* scale(float scaleX, float scaleY, float scaleZ);
	Mat4* transform(Transform2D* transform);
	Mat4* transform(Transform3D* transform);

public:
	Mat4& operator=(const Mat4 matrix);
	bool operator==(const Mat4& matrix);
	bool operator!=(const Mat4& matrix);

	Mat4& operator+=(const Mat4& matrix);
	Mat4& operator-=(const Mat4& matrix);
	Mat4& operator*=(const Mat4& matrix);
	Mat4& operator*=(float factor);
	Mat4& operator/=(float factor);

private:
	float* m;
};

Mat4 operator+(const Mat4& m1, const Mat4& m2);
Mat4 operator-(const Mat4& m1, const Mat4& m2);
Mat4 operator*(const Mat4& m1, const Mat4& m2);

Mat4 operator*(const Mat4& matrix, float factor);
Mat4 operator*(float factor, const Mat4& matrix);
Mat4 operator/(const Mat4& matrix, float factor);
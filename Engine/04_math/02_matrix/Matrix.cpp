#include "Matrix.h"

Mat2::Mat2() {
	m00 = 1;
	m10 = 0;

	m01 = 0;
	m11 = 1;
}

Mat3::Mat3() {
	m00 = 1;
	m10 = 0;
	m20 = 0;

	m01 = 0;
	m11 = 1;
	m21 = 0;

	m02 = 0;
	m12 = 0;
	m22 = 1;
}


Mat4::Mat4() {
	m00 = 1;
	m10 = 0;
	m20 = 0;
	m30 = 0;

	m01 = 0;
	m11 = 1;
	m21 = 0;
	m31 = 0;

	m02 = 0;
	m12 = 0;
	m22 = 1;
	m32 = 0;

	m03 = 0;
	m13 = 0;
	m23 = 0;
	m33 = 1;
}

void Mat4::getOrthographicProjectionMatrix(Mat4* mat, float width, float height, float nn, float ff) {
	mat->m00 = 1.0f / width;
	mat->m10 = 0;
	mat->m20 = 0;
	mat->m30 = 0;

	mat->m01 = 0;
	mat->m11 = 1.0f / height;
	mat->m21 = 0;
	mat->m31 = 0;

	mat->m02 = 0;
	mat->m12 = 0;
	mat->m22 = -2.0f / (ff - nn);
	mat->m32 = -(ff + nn) / (ff - nn);

	mat->m03 = 0;
	mat->m13 = 0;
	mat->m23 = 0;
	mat->m33 = 1;
}
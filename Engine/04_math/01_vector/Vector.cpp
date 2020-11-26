#include "Vector.h"

#include "02_system/01_logging/Logger.h"

Vector2f::Vector2f() {
	m_x = 0.0f;
	m_y = 0.0f;
}

Vector2f::Vector2f(float value) {
	m_x = value;
	m_y = value;
}

Vector2f::Vector2f(float x, float y) {
	m_x = x;
	m_y = y;
}

Vector2f::Vector2f(const Vector2f& vector){
	m_x = vector.m_x;
	m_y = vector.m_y;
}

float Vector2f::length() {
	return std::sqrtf(m_x * m_x + m_y * m_y);
}

float Vector2f::lengthSquared(){
	return m_x * m_x + m_y * m_y;
}

float Vector2f::distance(const Vector2f& vector){
	return std::sqrtf((m_x - vector.m_x)*(m_x - vector.m_x) + (m_y - vector.m_y)*(m_y - vector.m_y));
}

float Vector2f::distanceSquared(const Vector2f& vector){
	return (m_x - vector.m_x) * (m_x - vector.m_x) + (m_y - vector.m_y) * (m_y - vector.m_y);
}

void Vector2f::normalize() {
	float l = length();
	m_x = m_x / l;
	m_y = m_y / l;
}

void Vector2f::print(){
	Loggers::MATH->info("(%1.3f/%1.3f)",m_x,m_y);
}

Vector2f operator+(const Vector2f& v1, const Vector2f& v2) {
	return Vector2f(v1.m_x + v2.m_x, v1.m_y + v2.m_y);
}

Vector2f operator-(const Vector2f& v1, const Vector2f& v2) {
	return Vector2f(v1.m_x - v2.m_x, v1.m_y - v2.m_y);
}

Vector2f operator*(const Vector2f& v1, const float factor) {
	return Vector2f(v1.m_x * factor, v1.m_y * factor);
}

Vector2f operator/(const Vector2f& v1, const float factor) {
	return Vector2f(v1.m_x / factor, v1.m_y / factor);
}

float operator*(const Vector2f& v1, const Vector2f& v2) {
	return v1.m_x * v2.m_x + v1.m_y * v2.m_y;
}

bool operator==(const Vector2f& v1, const Vector2f& v2) {
	return v1.m_x == v2.m_x && v1.m_y == v2.m_y;
}

bool operator!=(const Vector2f& v1, const Vector2f& v2) {
	return !(v1 == v2);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Vector3f::Vector3f() {
	m_x = 0.0f;
	m_y = 0.0f;
	m_z = 0.0f;
}

Vector3f::Vector3f(float value) {
	m_x = value;
	m_y = value;
	m_z = value;
}

Vector3f::Vector3f(float x, float y, float z) {
	m_x = x;
	m_y = y;
	m_z = z;
}

Vector3f::Vector3f(const Vector3f& vector){
	m_x = vector.m_x;
	m_y = vector.m_y;
	m_z = vector.m_z;
}

float Vector3f::length() {
	return std::sqrtf(m_x * m_x + m_y * m_y + m_z * m_z);
}

float Vector3f::lengthSquared(){
	return m_x * m_x + m_y * m_y + m_z * m_z;
}

float Vector3f::distance(const Vector3f& vector){
	return std::sqrtf((m_x - vector.m_x) * (m_x - vector.m_x) + (m_y - vector.m_y) * (m_y - vector.m_y)+ (m_z - vector.m_z) * (m_z - vector.m_z));
}

float Vector3f::distanceSquared(const Vector3f& vector){
	return (m_x - vector.m_x) * (m_x - vector.m_x) + (m_y - vector.m_y) * (m_y - vector.m_y) + (m_z - vector.m_z) * (m_z - vector.m_z);
}

void Vector3f::normalize() {
	float l = length();
	m_x = m_x / l;
	m_y = m_y / l;
	m_z = m_z / l;
}

void Vector3f::print(){
	Loggers::MATH->info("(%1.3f/%1.3f/%1.3f)", m_x, m_y,m_z);
}

Vector3f Vector3f::cross(const Vector3f& v1, const Vector3f& v2){
	return Vector3f(
		v1.m_y * v2.m_z - v1.m_z * v2.m_y,
		v1.m_z * v2.m_x - v1.m_x * v2.m_z,
		v1.m_x * v2.m_y - v1.m_y * v2.m_x
		);
}

Vector3f operator+(const Vector3f& v1, const Vector3f& v2) {
	return Vector3f(v1.m_x + v2.m_x, v1.m_y + v2.m_y, v1.m_z + v2.m_z);
}

Vector3f operator-(const Vector3f& v1, const Vector3f& v2) {
	return Vector3f(v1.m_x - v2.m_x, v1.m_y - v2.m_y, v1.m_z - v2.m_z);
}

Vector3f operator*(const Vector3f& v1, const float factor) {
	return Vector3f(v1.m_x * factor, v1.m_y * factor, v1.m_z * factor);
}

Vector3f operator/(const Vector3f& v1, const float factor) {
	return Vector3f(v1.m_x / factor, v1.m_y / factor, v1.m_z / factor);
}

float operator*(const Vector3f& v1, const Vector3f& v2) {
	return v1.m_x * v2.m_x + v1.m_y * v2.m_y + v1.m_z * v2.m_z;
}

bool operator==(const Vector3f& v1, const Vector3f& v2) {
	return v1.m_x == v2.m_x && v1.m_y == v2.m_y && v1.m_z == v2.m_z;
}

bool operator!=(const Vector3f& v1, const Vector3f& v2) {
	return !(v1 == v2);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Vector4f::Vector4f() {
	m_x = 0.0f;
	m_y = 0.0f;
	m_z = 0.0f;
	m_w = 0.0f;
}

Vector4f::Vector4f(float value) {
	m_x = value;
	m_y = value;
	m_z = value;
	m_w = value;
}

Vector4f::Vector4f(float x, float y, float z, float w) {
	m_x = x;
	m_y = y;
	m_z = z;
	m_w = w;
}

Vector4f::Vector4f(const Vector4f& vector){
	m_x = vector.m_x;
	m_y = vector.m_y;
	m_z = vector.m_z;
	m_w = vector.m_w;
}

float Vector4f::length() {
	return std::sqrtf(m_x * m_x + m_y * m_y + m_z * m_z + m_w * m_w);
}

float Vector4f::lengthSquared(){
	return m_x * m_x + m_y * m_y + m_z * m_z + m_w * m_w;
}

float Vector4f::distance(const Vector4f& vector){
	return std::sqrtf((m_x - vector.m_x) * (m_x - vector.m_x) + (m_y - vector.m_y) * (m_y - vector.m_y) + (m_z - vector.m_z) * (m_z - vector.m_z) + (m_w - vector.m_w) * (m_w - vector.m_w));
}

float Vector4f::distanceSquared(const Vector4f& vector){
	return (m_x - vector.m_x) * (m_x - vector.m_x) + (m_y - vector.m_y) * (m_y - vector.m_y) + (m_z - vector.m_z) * (m_z - vector.m_z) + (m_w - vector.m_w) * (m_w - vector.m_w);
}

void Vector4f::normalize() {
	float l = length();
	m_x = m_x / l;
	m_y = m_y / l;
	m_z = m_z / l;
	m_w = m_w / l;
}

void Vector4f::print(){
	Loggers::MATH->info("(%1.3f/%1.3f/%1.3f/%1.3f)", m_x, m_y, m_z,m_w);
}

Vector4f operator+(const Vector4f& v1, const Vector4f& v2) {
	return Vector4f(v1.m_x + v2.m_x, v1.m_y + v2.m_y, v1.m_z + v2.m_z, v1.m_w + v2.m_w);
}

Vector4f operator-(const Vector4f& v1, const Vector4f& v2) {
	return Vector4f(v1.m_x - v2.m_x, v1.m_y - v2.m_y, v1.m_z - v2.m_z, v1.m_w - v2.m_w);
}

Vector4f operator*(const Vector4f& v1, const float factor) {
	return Vector4f(v1.m_x * factor, v1.m_y * factor, v1.m_z * factor, v1.m_w * factor);
}

Vector4f operator/(const Vector4f& v1, const float factor) {
	return Vector4f(v1.m_x / factor, v1.m_y / factor, v1.m_z / factor, v1.m_w / factor);
}

float operator*(const Vector4f& v1, const Vector4f& v2) {
	return v1.m_x * v2.m_x + v1.m_y * v2.m_y + v1.m_z * v2.m_z + v1.m_w * v2.m_w;
}

bool operator==(const Vector4f& v1, const Vector4f& v2) {
	return v1.m_x == v2.m_x && v1.m_y == v2.m_y && v1.m_z == v2.m_z && v1.m_w == v2.m_w;
}

bool operator!=(const Vector4f& v1, const Vector4f& v2) {
	return !(v1 == v2);
}
#include <stdexcept>
#include <iostream>
#include <cmath>

#include "Vector4.h"


/*==============================*
*         Constructors         *
*==============================*/

Vector4::Vector4() {
	this->vector[0] = 0;
	this->vector[1] = 0;
	this->vector[2] = 0;
	this->vector[3] = 0;
}

Vector4::Vector4(double x, double y, double z) {
	this->vector[0] = x;
	this->vector[1] = y;
	this->vector[2] = z;
	this->vector[3] = 0;
}

Vector4::Vector4(double x, double y, double z, double w) {
	this->vector[0] = x;
	this->vector[1] = y;
	this->vector[2] = z;
	this->vector[3] = w;
}

Vector4::Vector4(const Vector4& v) {
	this->vector[0] = v[0];
	this->vector[1] = v[1];
	this->vector[2] = v[2];
	this->vector[3] = v[3];
}

/*==============================*
*      Setters and Getters     *
*==============================*/

void Vector4::set(double x, double y, double z, double w) {
	this->vector[0] = x;
	this->vector[1] = y;
	this->vector[2] = z;
	this->vector[3] = w;
}

void Vector4::set(double x, double y, double z) {
	this->vector[0] = x;
	this->vector[1] = y;
	this->vector[2] = z;
}

void Vector4::set(int index, double value) {
	if (index < 0 || index >= SIZE) throw std::out_of_range(VECTOR4_RANGE_ERR);
	else this->vector[index] = value;
}

double Vector4::get(int index) const{
	if (index < 0 || index >= SIZE) throw std::out_of_range(VECTOR4_RANGE_ERR);
	else return this->vector[index];
}

double& Vector4::operator [](const int index) {
	if (index < 0 || index >= SIZE) throw std::out_of_range(VECTOR4_RANGE_ERR);
	else return this->vector[index];
}

double Vector4::operator [](const int index) const {
	return this->get(index);
}



/*==============================*
*          Arithmetic          *
*==============================*/

// Add

Vector4& Vector4::operator+=(const Vector4& v) {
	this->vector[0] += v[0];
	this->vector[1] += v[1];
	this->vector[2] += v[2];
	this->vector[3] += v[3];

	return *this;
}

void Vector4::add(const Vector4& v) {
	(*this) += v;
}

// Subtract

Vector4& Vector4::operator-=(const Vector4& v) {
	this->vector[0] -= v[0];
	this->vector[1] -= v[1];
	this->vector[2] -= v[2];
	this->vector[3] -= v[3];

	return *this;
}

void Vector4::subtract(const Vector4& v) {
	(*this) -= v;
}

// Multiply

Vector4& Vector4::operator*=(const float f) {
    this->vector[0] *= f;
    this->vector[1] *= f;
    this->vector[2] *= f;
    
    return *this;
}

void Vector4::negate() {
    *this *= -1.0f;
}

// Cross Product

void Vector4::cross(const Vector4& v) {
	//calculate cross product
	double s1 = this->vector[1] * v[2] - this->vector[2] * v[1];
	double s2 = this->vector[2] * v[0] - this->vector[0] * v[2];
	double s3 = this->vector[0] * v[1] - this->vector[1] * v[0];

	//clobber
	this->vector[0] = s1;
	this->vector[1] = s2;
	this->vector[2] = s3;
}

Vector4 Vector4::cross(Vector4 u, const Vector4& v) {
	u.cross(v);
	return u;
}

double Vector4::dot(const Vector4& u, const Vector4& v) {
	return u.dot(v);
}

double Vector4::dot(const Vector4& u) const {
	return this->vector[0] * u.vector[0] + this->vector[1] * u.vector[1] + this->vector[2] * u.vector[2];
}

double Vector4::angle(const Vector4& u, const Vector4& v) {
	return u.angle(v);
}

double Vector4::angle(const Vector4& u) const {
	return acos(this->dot(u) / (this->length() * u.length()));
}

void Vector4::dehomogenize() {
	double factor = this->vector[3];
	this->vector[0] /= factor;
	this->vector[1] /= factor;
	this->vector[2] /= factor;
	this->vector[3] /= factor;
}

Vector4 Vector4::dehomogenize(Vector4 v) {
	v.dehomogenize();
	return v;
}

void Vector4::normalize() {
	double mag = this->length();
    if(mag != 0) {
        this->vector[0] /= mag;
        this->vector[1] /= mag;
        this->vector[2] /= mag;
    }

}

Vector4 Vector4::normalize(Vector4 v) {
	v.normalize();
	return v;
}

double Vector4::length() const {
	return sqrt(this->lengthSquared());
}

double Vector4::lengthSquared() const {
	return this->dot(*this);
}

void Vector4::print() const {
	std::cout << "<" <<
		this->vector[0] << ", " <<
		this->vector[1] << ", " <<
		this->vector[2] << ", " <<
		this->vector[3] << ">" << std::endl;
}

Vector4 Vector4::lerp(float f, const Vector4& u, const Vector4& v) {
	return u + (v - u)*f;
}
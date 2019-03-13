#ifndef MATRIX_H_
#define MATRIX_H_

#include <string>
#include "stddef.h"
#include "initializer_list"
#include "math.h"

template <typename T, size_t row, size_t column> class Matrix {

	using M = Matrix<T, row, column>;

private:
	T elements[row*column];

	void Set(std::initializer_list<T>& list) {
		size_t i = 0;
		for (auto iter = list.begin(); iter != list.end(); iter++) {
			(*this)(i) = *iter;
			i++;
		}
	}

public:
	T& operator () (size_t i, size_t j) {
		return elements[i*column + j];
	}
	T& operator () (size_t i) {
		return elements[i];
	}

	const T& operator () (size_t i, size_t j) const {
		return elements[i*column + j];
	}
	const T& operator () (size_t i) const {
		return elements[i];
	}

	Matrix() {
		for (size_t i = 0; i < row*column; i++) {
			(*this)(i) = 0;
		}
	}
	Matrix(std::initializer_list<T> list) {
		Set(list);
	}

	M& operator = (const M& a) {
		for (size_t i = 0; i < row*column; i++) {
			(*this)(i) = a(i);
		}
		return *this;
	}
	M& operator = (std::initializer_list<T> list) {
		Set(list);
		return *this;
	}

	M operator +() const{
		return *this;
	}

	M operator + (const M& a) const{
		M r;
		for (size_t i = 0; i < row*column; i++) {
			r(i) = (*this)(i) + a(i);
		}
		return r;
	}

	M operator * (const T scalar) const{
		M r;
		for (size_t i = 0; i < row*column; i++) {
			r(i) = (*this)(i)*scalar;
		}
		return r;
	}
	M operator / (const T scalar) const{
		M r;
		for (size_t i = 0; i < row*column; i++) {
			r(i) = (*this)(i) /scalar;
		}
		return r;
	}

	M operator - () const{
		return *(this) * (-1);
	}
	M operator - (const M& a) const{
		return *(this) + (-a);
	}

	M& operator += (const M& a) {
		(*this) = (*this) + a;
		return *this;
	}
	M& operator -= (const M& a) {
		(*this) = (*this) - a;
		return *this;
	}
	M& operator *= (const M& a) {
		(*this) = (*this) * a;
		return *this;
	}
	M& operator *= (const T scalar) {
		(*this) = (*this) * scalar;
		return *this;
	}
	M& operator /= (const T scalar) {
		(*this) = (*this) / scalar;
		return *this;
	}

	template<size_t n>
	Matrix<T, row, n> operator * (const Matrix<T, column, n>& a) const{
		Matrix<T, row, n> r;
		for (size_t i = 0; i < row; i++) {
			for (size_t j = 0; j < n; j++) {
				for (size_t k = 0; k < column; k++) {
					r(i, j) += (*this)(i, k) * a(k, j);
				}
			}
		}
		return r;
	}

	T Norm() const{
		T r = 0;
		for (size_t i = 0; i < row*column; i++) {
			r += (*this)(i)* (*this)(i);
		}
		return sqrtf(r);
	}

	M Normalized() const{
		return (*this) / Norm();
	}

	Matrix<T, column, row> Transpose() const{
		Matrix<T, column, row> r;
		for (size_t i = 0; i < row; i++) {
			for (size_t j = 0; j < column; j++) {
					r(j, i) = (*this)(i, j);
			}
		}
		return r;
	}

	std::string ToString() const{
		std::string str = "";
		for (size_t i = 0; i < row; i++) {
			for (size_t j = 0; j < column; j++) {
				str += std::to_string(GetElement(i,j));
				if (j < column - 1) str += ", ";
			}
			str += "\n";
		}
		str += "\n";
		return str;
	}
};

template <size_t row, size_t column>
using Matrixf = Matrix<float, row, column>;

using Vector2f = Matrixf<2, 1>;
using Vector3f = Matrixf<3, 1>;
using Matrix2f = Matrixf<2, 2>;
using Matrix3f = Matrixf<3, 3>;

#endif // !MATRIX_H_

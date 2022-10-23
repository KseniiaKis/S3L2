#pragma once

#include <iostream>
#include"vector.h"
#include"Matrix.cpp"
using namespace std;

template<typename T>
class TDynamicMatrix : public TDynamicVector<TDynamicVector<T>>
{
public:
	TDynamicMatrix();
	TDynamicMatrix(const int size = 1);
	TDynamicMatrix& operator=(const TDynamicMatrix& tmp);
	TDynamicMatrix operator+ (const TDynamicMatrix& mt);
	TDynamicMatrix  operator- (const TDynamicMatrix& mt);
	TDynamicMatrix  operator* (const TDynamicMatrix<T>& _SM);
	TDynamicVector<T> operator*(TDynamicVector<T>& v);


	friend istream& operator>>(istream& in, TMatrix& mt)
	{
		for (int i = 0; i < mt.size; i++)
			in >> mt.pMem[i];
		return in;
	}

	friend ostream& operator<<(ostream& out, const TMatrix& mt)
	{
		for (int i = 0; i < mt.size; i++)
			out << mt.pMem[i];
		return out;
	}


	template<typename T>
	inline TDynamicMatrix<T>::TDynamicMatrix()
	{
		this->size = NULL;
		this->pMem = nullptr;
	}

	template<typename T>
	inline TDynamicMatrix<T>::TDynamicMatrix(const int size = 1)
	{
		this->pMem = new TVector[size];
		for (int i = 0; i < size; i++)
			this->pMem[i] = TVector(i + 1);
		this->size = size;
	}

	template<typename T>
	inline TDynamicMatrix<T>& TDynamicMatrix<T>::operator=(const TDynamicMatrix& tmp)
	{
		if (this != &tmp) {
			if (this->size != tmp.size) {
				this->size = tmp.size;
				delete[] this->pMem;
				this->pMem = new TVector<T>[this->size];
			}
			this->start = tmp.start;
			for (int i = 0; i < this->size; ++i)
				this->pMem[i] = tmp.pMem[i];
		}
		return *this;
	}

	template<typename T>
	inline TDynamicMatrix<T> TDynamicMatrix<T>::operator+(const TDynamicMatrix& mt)
	{
		TDynamicMatrix<T> result(*this);
		for (int i = 0; i < this->size; i++)
			result.pMem[i] = this->pMem[i] + mt.pMem[i];
		return result;
	}

	template<typename T>
	inline TDynamicMatrix<T> TDynamicMatrix<T>::operator-(const TDynamicMatrix& mt)
	{
		TMatrix<T> result(*this);
		for (int i = 0; i < this->size; i++)
			result.pMem[i] = this->pMem[i] - mt.pMem[i];
		return result;
	}



	template<typename T>
	inline TDynamicMatrix<T> TDynamicMatrix<T>::operator*(const TDynamicMatrix<T>& _SM)
	{
		if (this->size != _SM.size) throw"operator*len != _SM.size";
		TDynamicMatrix<T> result(this->size);
		for (int i = 0; i < this->size; i++) {
			for (int j = 0; j < i; j++) {
				result[i][j] = 0;
				for (int k = 0; k < i; k++) {
					if (!(j <= i) && (k <= i))
						result[i][j] += (*this)[i][k] * _SM[k][j];
				}
			}
		}
		return result;
	}

	template<typename T>
	inline TDynamicVector<T> TDynamicMatrix<T>::operator*(TDynamicVector<T>& v)
	{
		if (size != v.size()) throw length_error("cant multiply matrix and vector with not equal size");
		TDynamicVector<T> res(size);
		for (int i = 0; i < size; i++)
			res[i] = pMem[i] * v;
		return res;
	}

};
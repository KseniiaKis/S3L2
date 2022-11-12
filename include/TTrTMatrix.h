#pragma once
#ifndef __TTrTMatrix_H__
#define __TTrTMatrix_H__

#include <iostream>
#include "TVector.h"
#include "TSqMatrix.h"

template <class T>
class TTrTMatrix :protected TVector<TVector<T>>
{
  using TVector<TVector<T>>::pMemory;
  using TVector<TVector<T>>::length;
public:
  TTrTMatrix();
  TTrTMatrix(int _length);
  ~TTrTMatrix();

  const int GetLength();

  using TVector<TVector<T>>::operator[];
  bool operator==(const TTrTMatrix& matrix);
  bool operator!=(const TTrTMatrix& matrix);
  TTrTMatrix operator+(const TTrTMatrix& matrix);
  TTrTMatrix& operator=(const TTrTMatrix& matrix);
  TTrTMatrix operator-(const TTrTMatrix& matrix);
  TTrTMatrix operator*(const TTrTMatrix& matrix);
  TSqMatrix<T> operator*(const TSqMatrix<T>& matrix);
  TVector<T> operator*(TVector<T>& vector);
  TTrTMatrix operator*(const T input);

  friend std::istream& operator>>(std::istream& istr, TTrTMatrix& matrix);
  friend std::ostream& operator<<(std::ostream& ostr, const TTrTMatrix& matrix);

};
template <class T>
TTrTMatrix<T>::TTrTMatrix()
{
  length = NULL;
  pMemory = nullptr;
}
template<class T>
TTrTMatrix<T>::TTrTMatrix(int _length)
{
  if (_length > 0)
  {
    length = _length;
    pMemory = new TVector<T>[length];
    for (int i = 0; i < length; i++)
    {
      pMemory[i] = TVector<T>(length - i);
    }
  }
  else
  {
    throw std::range_error("TTrTMatrix init error");
  }
}
template <class T>
TTrTMatrix<T>::~TTrTMatrix()
{
  if (pMemory != nullptr)
  {
    delete[] pMemory;
  }
  length = NULL;
  pMemory = nullptr;
}
template <class T>
const int TTrTMatrix<T>::GetLength()
{
  return length;
}
template<class T>
bool TTrTMatrix<T>::operator==(const TTrTMatrix& matrix)
{
  if (length != matrix.length)
  {
    return false;
  }
  if (pMemory == nullptr || matrix.pMemory == nullptr)
  {
    throw std::range_error("TTrTMatrix operation == error");
  }
  else
  {
    for (int i = 0; i < length; i++)
    {
      if (pMemory[i] != matrix.pMemory[i])
      {
        return false;
      }
    }
    return true;
  }
}
template<class T>
bool TTrTMatrix<T>::operator!=(const TTrTMatrix& matrix)
{
  if (length != matrix.length)
  {
    return true;
  }
  if (pMemory == nullptr || matrix.pMemory == nullptr)
  {
    throw std::range_error("TTrTMatrix operation == error");
  }
  else
  {
    for (int i = 0; i < length; i++)
    {
      if (pMemory[i] != matrix.pMemory[i])
      {
        return true;
      }
    }
    return false;
  }
}
template <class T>
TTrTMatrix<T> TTrTMatrix<T>::operator+(const TTrTMatrix<T>& matrix)
{
  if (length != matrix.length || length == 0 || pMemory == nullptr)
  {
    throw std::range_error("TTrTMatrix operator + error");
  }
  TTrTMatrix<T> Result = TTrTMatrix<T>(length);
  for (int i = 0; i < length; i++)
  {
    for (int j = 0; j < length - i; j++)
    {
      Result.pMemory[i][j] = pMemory[i][j] + matrix.pMemory[i][j];
    }
  }
  return Result;
}
template <class T>
TTrTMatrix<T>& TTrTMatrix<T>::operator=(const TTrTMatrix<T>& matrix)
{
  if (length != matrix.length || length == 0 || pMemory == nullptr)
  {
    throw std::range_error("TTrTMatrix operator = error");
  }
  for (int i = 0; i < length; i++)
  {
    for (int j = 0; j < length; j++)
    {
      pMemory[i][j] = matrix.pMemory[i][j];
    }
  }
  return *this;
}
template <class T>
TTrTMatrix<T> TTrTMatrix<T>::operator-(const TTrTMatrix<T>& matrix)
{
  if (length != matrix.length || length == 0 || pMemory == nullptr)
  {
    throw std::range_error("TTrTMatrix operator + error");
  }
  TTrTMatrix<T> Result = TTrTMatrix<T>(length);
  for (int i = 0; i < length; i++)
  {
    for (int j = 0; j < length - i; j++)
    {
      Result.pMemory[i][j] = pMemory[i][j] - matrix.pMemory[i][j];
    }
  }
  return Result;
}

template<class T>
TTrTMatrix<T> TTrTMatrix<T>::operator*(const TTrTMatrix& matrix)
{
  if (length != matrix.length || length == 0 || pMemory == nullptr)
  {
    throw std::range_error("TTrTMatrix operator * error");
  }
  TTrTMatrix<T> Result = TTrTMatrix<T>(length);
  for (int i = 0; i < length; i++)
  {
    for (int j = 0; j <= i; j++)
    {
      Result[i][j] = 0;
      for (int k = j; k <= i; k++)
      {
        Result[i - j][j] += matrix.pMemory[i - j][j - k] * pMemory[i - k][k];
      }
    }
  }
  return Result;
}
template <class T>
TSqMatrix<T> TTrTMatrix<T>::operator*(const TSqMatrix<T>& matrix)
{
  if (length != matrix.length || length == 0 || pMemory == nullptr)
  {
    throw std::range_error("TTrTMatrix operator * error");
  }
  TTrTMatrix<T> Result = TTrTMatrix<T>(length);
  for (int i = 0; i < length; i++)
  {
    for (int j = 0; j <= i; j++)
    {
      Result[i][j] = 0;
      for (int k = j; k <= i; k++)
      {
        Result[i][j] += matrix.pMemory[i][k] * pMemory[k][j];
      }
    }
  }
  return Result;
}
template<class T>
TVector<T> TTrTMatrix<T>::operator*(TVector<T>& vector)
{
  if (length != vector.GetLength() || length == 0 || pMemory == nullptr)
  {
    throw std::range_error("TTrTMatrix operator+ error");
  }
  TVector<T> Result = TVector<T>(length);
  for (int i = 0; i < length; i++)
  {
    Result[i] = 0;
    for (int j = 0; j <= i; j++)
    {
      Result[j] += pMemory[i][j] * vector[i];
    }
  }
  return Result;
}
template<class T>
TTrTMatrix<T> TTrTMatrix<T>::operator*(const T input)
{
  if (length == 0 || pMemory == nullptr)
  {
    throw std::range_error("TTrTMatrix operator * error");
  }
  TTrTMatrix<T> Result = TTrTMatrix<T>(length);
  for (int i = 0; i < length; i++)
  {
    Result.pMemory[i] = pMemory[i] * input;
  }
  return Result;
}
template<class T>
std::istream& operator>>(std::istream& istr, TTrTMatrix<T>& matrix)
{
  for (int i = 0; i < matrix.length; i++)
  {
    for (int j = 0; j < i + 1; j++)
    {
      istr >> matrix.pMemory[i][j];
    }
  }
  return istr;
}
template<class T>
std::ostream& operator<<(std::ostream& ostr, const TTrTMatrix<T>& matrix)
{
  for (int i = 0; i < matrix.length; i++)
  {
    for (int j = 0; j < i + 1; j++)
    {
      ostr << matrix.pMemory[i][j] << ' ';
    }
    ostr << '\n';
  }
  return ostr;
}
#endif
#pragma once
#ifndef __TTrBMatrix_H__
#define __TTrBMatrix_H__

#include <iostream>
#include "TVector.h"
#include "TSqMatrix.h"

template <class T>
class TTrBMatrix :protected TVector<TVector<T>>
{
  using TVector<TVector<T>>::pMemory;
  using TVector<TVector<T>>::length;
public:
  TTrBMatrix();
  TTrBMatrix(int _length);
  ~TTrBMatrix();

  const int GetLength();

  using TVector<TVector<T>>::operator[];
  bool operator==(const TTrBMatrix& matrix);
  bool operator!=(const TTrBMatrix& matrix);
  TTrBMatrix operator+(const TTrBMatrix& matrix);
  TTrBMatrix& operator=(const TTrBMatrix& matrix);
  TTrBMatrix operator-(const TTrBMatrix& matrix);
  TTrBMatrix operator*(const TTrBMatrix& matrix);
  TSqMatrix<T> operator*(const TSqMatrix<T>& matrix);
  TVector<T> operator*(TVector<T>& vector);
  TTrBMatrix operator*(const T input);

  friend std::istream& operator>>(std::istream& istr, TTrBMatrix& matrix);
  friend std::ostream& operator<<(std::ostream& ostr, const TTrBMatrix& matrix);

};
template <class T>
TTrBMatrix<T>::TTrBMatrix()
{
  length = NULL;
  pMemory = nullptr;
}
template<class T>
TTrBMatrix<T>::TTrBMatrix(int _length)
{
  if (_length > 0)
  {
    length = _length;
    pMemory = new TVector<T>[length];
    for (int i = 0; i < length; i++)
    {
      pMemory[i] = TVector<T>(i + 1);
    }
  }
  else
  {
    throw std::range_error("TTrBMatrix init error");
  }
}
template <class T>
TTrBMatrix<T>::~TTrBMatrix()
{
  if (pMemory != nullptr)
  {
    delete[] pMemory;
  }
  length = NULL;
  pMemory = nullptr;
}
template <class T>
const int TTrBMatrix<T>::GetLength()
{
  return length;
}
template<class T>
bool TTrBMatrix<T>::operator==(const TTrBMatrix& matrix)
{
  if (length != matrix.length)
  {
    return false;
  }
  if (pMemory == nullptr || matrix.pMemory == nullptr)
  {
    throw std::range_error("TTrBMatrix operation == error");
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
bool TTrBMatrix<T>::operator!=(const TTrBMatrix& matrix)
{
  if (length != matrix.length)
  {
    return true;
  }
  if (pMemory == nullptr || matrix.pMemory == nullptr)
  {
    throw std::range_error("TTrBMatrix operation == error");
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
TTrBMatrix<T> TTrBMatrix<T>::operator+(const TTrBMatrix<T>& matrix)
{
  if (length != matrix.length || length == 0 || pMemory == nullptr)
  {
    throw std::range_error("TTrBMatrix operator + error");
  }
  TTrBMatrix<T> Result = TTrBMatrix<T>(length);
  for (int i = 0; i < length; i++)
  {
    for (int j = 0; j < i + 1; j++)
    {
      Result.pMemory[i][j] = pMemory[i][j] + matrix.pMemory[i][j];
    }
  }
  return Result;
}
template <class T>
TTrBMatrix<T>& TTrBMatrix<T>::operator=(const TTrBMatrix<T>& matrix)
{
  if (length != matrix.length || length == 0 || pMemory == nullptr)
  {
    throw std::range_error("TTrBMatrix operator = error");
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
TTrBMatrix<T> TTrBMatrix<T>::operator-(const TTrBMatrix<T>& matrix)
{
  if (length != matrix.length || length == 0 || pMemory == nullptr)
  {
    throw std::range_error("TTrBMatrix operator - error");
  }
  TTrBMatrix<T> Result = TTrBMatrix<T>(length);
  for (int i = 0; i < length; i++)
  {
    for (int j = 0; j < i + 1; j++)
    {
      Result.pMemory[i][j] = pMemory[i][j] - matrix.pMemory[i][j];
    }
  }
  return Result;
}

template<class T>
TTrBMatrix<T> TTrBMatrix<T>::operator*(const TTrBMatrix& matrix)
{
  if (length != matrix.length || length == 0 || pMemory == nullptr)
  {
    throw std::range_error("TTrBMatrix operator * error");
  }
  TTrBMatrix<T> Result = TTrBMatrix<T>(length);
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
template <class T>
TSqMatrix<T> TTrBMatrix<T>::operator*(const TSqMatrix<T>& matrix)
{
  if (length != matrix.length || length == 0 || pMemory == nullptr)
  {
    throw std::range_error("TTrBMatrix operator * error");
  }
  TTrBMatrix<T> Result = TTrBMatrix<T>(length);
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
TVector<T> TTrBMatrix<T>::operator*(TVector<T>& vector)
{
  if (length != vector.GetLength() || length == 0 || pMemory == nullptr)
  {
    throw std::range_error("TTrBMatrix operator+ error");
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
TTrBMatrix<T> TTrBMatrix<T>::operator*(const T input)
{
  if (length == 0 || pMemory == nullptr)
  {
    throw std::range_error("TTrBMatrix operator * error");
  }
  TTrBMatrix<T> Result = TTrBMatrix<T>(length);
  for (int i = 0; i < length; i++)
  {
    Result.pMemory[i] = pMemory[i] * input;
  }
  return Result;
}
template<class T>
std::istream& operator>>(std::istream& istr, TTrBMatrix<T>& matrix)
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
std::ostream& operator<<(std::ostream& ostr, const TTrBMatrix<T>& matrix)
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
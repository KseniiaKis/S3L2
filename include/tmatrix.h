#ifndef __TMATRIX_H__
#define __TMATRIX_H__
#include <iostream>
using namespace std;

template<class T>
class TDynamicVector
{
protected:
  int len;
  T* mas;
public:
  TDynamicVector();
  TDynamicVector(int n);
  TDynamicVector(T* arr, int s);
  TDynamicVector(const TDynamicVector<T>& v);
  TDynamicVector(TDynamicVector<T>&& v) noexcept;
  ~TDynamicVector();
  int size();
  void Resize(int nlen);
  T& operator[](int i);
  const T& operator[](int i) const;
  bool operator==(const TDynamicVector<T>& v);
  bool operator!=(const TDynamicVector<T>& v);
  TDynamicVector<T> operator+(T n);
  TDynamicVector<T> operator-(double n);
  TDynamicVector<T> operator*(double n);
  TDynamicVector<T> operator+(const TDynamicVector<T>& v);
  TDynamicVector<T> operator-(const TDynamicVector<T>& v);
  TDynamicVector<T> operator*(const TDynamicVector<T>& v);
  TDynamicVector<T>& operator=(const TDynamicVector<T>& v);
  TDynamicVector<T>& operator=(TDynamicVector<T>&& v) noexcept;
  friend istream& operator>>(istream& istr, const TDynamicVector<T>& v);
  friend ostream& operator<<(ostream& ostr, const TDynamicVector<T>& v);
};

#endif

template<class T>
TDynamicVector<T>::TDynamicVector()
{
  len = NULL;
  mas = nullptr;
}

template<class T>
inline TDynamicVector<T>::TDynamicVector(int n)
{
  if (n <= 0) throw "error";
  len = n;
  mas = new T[len];
  for (int i = 0; i < len; i++)
    mas[i] = 1;
}

template<class T>
inline TDynamicVector<T>::TDynamicVector(T* arr, int s)
{
  len = s;
  mas = new T[len];
  for (int i = 0; i < len; i++)
    mas[i] = arr[i];
}

template<class T>
inline TDynamicVector<T>::TDynamicVector(const TDynamicVector<T>& v)
{
  len = v.len;
  if (v.len == 0)
    mas = nullptr;
  else
    mas = new T[len];
  for (int i = 0; i < len; i++)
    mas[i] = v.mas[i];
}

template<class T>
inline TDynamicVector<T>::TDynamicVector(TDynamicVector<T>&& v) noexcept
{
  mas = v.mas;
  len = v.len;
  v.mas = nullptr;
  v.len = 0;
}

template<class T>
inline TDynamicVector<T>::~TDynamicVector()
{
  if (mas != nullptr)
  {
    delete[] mas;
    mas = nullptr;
  }
  len = NULL;
}

template<class T>
inline int TDynamicVector<T>::size()
{
  return len;
}

template<class T>
inline void TDynamicVector<T>::Resize(int _len)
{
  if (_len < 0) throw "error";
  TDynamicVector<T> res(*this);
  delete[] mas;
  mas = new T[_len];
  for (int i = 0; i < min(_len, res.len); i++)
  {
    mas[i] = res.mas[i];
  }
  if (_len > res.len)
    for (int j = res.len; j < _len; j++)
      mas[j] = 0;
  len = _len;
}

template<class T>
inline T& TDynamicVector<T>::operator[](int i)
{
  if (len == 0) throw "error";
  if ((i < 0) || (i > len)) throw "not found";
  return mas[i];
}

template<class T>
inline const T& TDynamicVector<T>::operator[](int i) const
{
  if (len == 0) throw "error";
  if ((i < 0) || (i > len)) throw "not found";
  return mas[i];
}

template<class T>
inline bool TDynamicVector<T>::operator==(const TDynamicVector<T>& v)
{
  if (len != v.len) return false;
  else
  {
    for (int i = 0; i < len; i++)
      if (mas[i] != v.mas[i])
        return false;
  }
  return true;
}

template<class T>
inline bool TDynamicVector<T>::operator!=(const TDynamicVector<T>& v)
{
  if (len != v.len) return true;
  else
  {
    for (int i = 0; i < len; i++)
      if (mas[i] != v.mas[i])
        return true;
  }
  return false;
}

template<class T>
inline TDynamicVector<T> TDynamicVector<T>::operator+(T n)
{
  if (n == 0) return *this;
  TDynamicVector<T> res(*this);
  {
    for (int i = 0; i < len; i++)
      res.mas[i] = res.mas[i] + n;
  }
  return res;
}

template<class T>
inline TDynamicVector<T> TDynamicVector<T>::operator-(double n)
{
  if (n == 0) return *this;
  TDynamicVector<T> res(*this);
  {
    for (int i = 0; i < len; i++)
      res.mas[i] = res.mas[i] - n;
  }
  return res;
}

template<class T>
inline TDynamicVector<T> TDynamicVector<T>::operator*(double n)
{
  if (n == 0) mas = nullptr;
  TDynamicVector<T> res(*this);
  {
    for (int i = 0; i < len; i++)
      res.mas[i] = res.mas[i] * n;
  }
  return res;
}

template<class T>
inline TDynamicVector<T> TDynamicVector<T>::operator+(const TDynamicVector<T>& v)
{
  TDynamicVector<T> res(*this);
  if ((len == v.len) && (v.mas != 0) && (mas != 0))
  {
    for (int i = 0; i < len; i++)
      res.mas[i] = res.mas[i] + v.mas[i];
  }
  else
    throw "error";
  return res;
}

template<class T>
inline TDynamicVector<T> TDynamicVector<T>::operator-(const TDynamicVector<T>& v)
{
  TDynamicVector<T> res(*this);
  if ((len == v.len) && (v.pMem != 0) && (mas != 0))
  {
    for (int i = 0; i < len; i++)
      res.mas[i] = res.mas[i] - v.mas[i];
  }
  else
    throw "error";
  return res;
}

template<class T>
inline TDynamicVector<T> TDynamicVector<T>::operator*(const TDynamicVector<T>& v)
{
  TDynamicVector<T> res(*this);
  if ((len == v.len) && (v.mas != 0) && (mas != 0))
  {
    for (int i = 0; i < len; i++)
      res.mas[i] = res.mas[i] * v.mas[i];
  }
  else
    throw "error";
  return res;
}

template<class T>
inline TDynamicVector<T>& TDynamicVector<T>::operator=(const TDynamicVector<T>& v)
{
  if (this == &v) return *this;
  if (v.mas == 0)
  {
    delete[] mas;
    mas = 0;
    len = 0;
    return *this;
  }
  if (mas != 0)
    delete[] mas;
  len = v.len;
  mas = new T[len];
  for (int i = 0; i < len; i++)
    mas[i] = v.mas[i];
  return *this;
}

template<class T>
inline TDynamicVector<T>& TDynamicVector<T>::operator=(TDynamicVector<T>&& v) noexcept
{
  if (this != &v)
  {
    delete[] mas;
    mas = v.mas;
    len = v.len;
    v.mas = nullptr;
    v.len = 0;
  }
  return *this;
}

template <class T>
ostream& operator<<(std::ostream& ostr, TDynamicVector<T>& v)
{
  for (int i = 0; i < v.size(); i++)
    ostr << v[i] << ' ';
  return ostr;
}

template <class T>
istream& operator>>(std::istream& istr, TDynamicVector<T>& v)
{
  T a = 0;
  std::cout << "Enter your vector = " << std::endl;
  for (int i = 0; i < v.size(); i++)
  {
    istr >> a;
    v[i] = a;
  }
  return istr;
}

template<class T>
class TDynamicMatrix : protected TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::mas;
  using TDynamicVector<TDynamicVector<T>>::len;
public:
  using TDynamicVector<TDynamicVector<T>>::operator[];
  using TDynamicVector<TDynamicVector<T>>::size;
  TDynamicMatrix();
  TDynamicMatrix(int n);
  TDynamicMatrix(const TDynamicMatrix<T>& m);
  bool operator==(const TDynamicMatrix<T>& m);
  bool operator!=(const TDynamicMatrix<T>& m);
  TDynamicMatrix<T> operator*(const T& v);
  TDynamicVector<T> operator*(TDynamicVector<T>& v);
  TDynamicMatrix<T> operator+(const TDynamicMatrix<T>& m);
  TDynamicMatrix<T> operator-(const TDynamicMatrix<T>& m);
  TDynamicMatrix<T> operator*(const TDynamicMatrix<T>& m);
  TDynamicMatrix<T> operator=(const TDynamicMatrix<T>& m);
  friend istream& operator>>(istream& istr, const TDynamicMatrix<T>& m);
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix<T>& m);
};

template<class T>
inline TDynamicMatrix<T>::TDynamicMatrix()
{
  this->len = NULL;
  this->mas = nullptr;
}

template<class T>
inline TDynamicMatrix<T>::TDynamicMatrix(int n)
{
  if (n <= 0) throw "error";
  this->len = n;
  if (this->mas != nullptr)
    delete[] this->mas;
  this->mas = new TDynamicVector<T>[this->len];
  for (int i = 0; i < this->len; i++)
    this->mas[i] = TDynamicVector<T>(i + 1);
}

template<class T>
inline TDynamicMatrix<T>::TDynamicMatrix(const TDynamicMatrix<T>& m)
{
  if (m.len == 0)
    this->mas = 0;
  if (m.len > 0)
    this->len = m.len;
  this->mas = new TDynamicVector<T>[len];
  for (int i = 0; i < len; i++)
    this->mas[i] = m.mas[i];
}

template<class T>
inline bool TDynamicMatrix<T>::operator==(const TDynamicMatrix<T>& m)
{
  return TDynamicVector < TDynamicVector<T>> :: operator==(m);
}

template<class T>
inline bool TDynamicMatrix<T>::operator!=(const TDynamicMatrix<T>& m)
{
  return TDynamicVector < TDynamicVector<T>> :: operator!=(m);
}

template<class T>
inline TDynamicMatrix<T> TDynamicMatrix<T>::operator*(const T& v)
{
  TDynamicMatrix<T> res(*this);
  for (int i = 0; i < len; i++)
    res.mas[i] = mas[i] * v;
  return res;
}

template<class T>
inline TDynamicVector<T> TDynamicMatrix<T>::operator*(TDynamicVector<T>& v)
{
  if (this->len != v.size()) throw "error";
  TDynamicVector<T> res(this->len);
  for (int i = 0; i < len; i++)
  {
    res[i] = 0;
    for (int j = 0; j <= i; j++)
      res[j] += this->mas[i][j] * v[i];
  }
  return res;
}

template<class T>
inline TDynamicMatrix<T> TDynamicMatrix<T>::operator+(const TDynamicMatrix<T>& m)
{
  if (m.len != len) throw "error";
  TDynamicMatrix<T> res(*this);
  for (int i = 0; i < len; i++)
    res.mas[i] = mas[i] + m.mas[i];
  return res;
}

template<class T>
inline TDynamicMatrix<T> TDynamicMatrix<T>::operator-(const TDynamicMatrix<T>& m)
{
  if (m.len != len) throw "error";
  TDynamicMatrix<T> res(*this);
  for (int i = 0; i < len; i++)
    res.mas[i] = mas[i] - m.mas[i];
  return res;
}

template<class T>
inline TDynamicMatrix<T> TDynamicMatrix<T>::operator*(const TDynamicMatrix<T>& m)
{
  if (m.len != len) throw "error";
  TDynamicMatrix<T> res(*this);
  for (int i = 0; i < len; i++)
    for (int j = 0; j <= i; j++)
    {
      res[i][j] = 0;
      for (int k = j; k <= i; k++)
        res.mas[i][j] += m.mas[i][k] * mas[k][j];
    }
  return res;
}

template<class T>
inline TDynamicMatrix<T> TDynamicMatrix<T>::operator=(const TDynamicMatrix<T>& m)
{
  TDynamicVector<TDynamicVector<T>>::operator=(m);
  return *this;
}

template<class T>
std::istream& operator>>(std::istream& istr, TDynamicMatrix<T>& m)
{
  std::cout << "Enter your matrix = " << std::endl;
  for (int i = 0; i < m.size(); i++)
  {
    for (int j = 0; j < i + 1; j++)
    {
      istr >> m[i][j];
    }
  }
  return istr;
}

template<class T>
std::ostream& operator<<(std::ostream& ostr, TDynamicMatrix<T>& m)
{
  for (int i = 0; i < m.size(); i++)
  {
    for (int j = 0; j < i + 1; j++)
    {
      ostr << m[i][j] << ' ';
    }
    std::cout << std::endl;
  }
  return ostr;
}
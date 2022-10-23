#pragma once

#include <iostream>
template<typename T>
class TDynamicVector
{
protected:
  size_t  sz;
  T* pMem;
  int start;

public:
  TDynamicVector();
  TDynamicVector(size_t _size);
  TDynamicVector(T* arr, int s);
  TDynamicVector(const TDynamicVector& v);
  TDynamicVector(TDynamicVector&& v) noexcept;
  ~TDynamicVector();
  size_t size() const noexcept { return sz };
  TDynamicVector& operator=(const TDynamicVector& v);
  TDynamicVector& operator=(TDynamicVector&& v) noexcept;
  int GetSize();
  T PopBack();
  void ReSize(int NewSize = 0);

  T& operator[](int ind);
  const T& operator[](int ind) const;

  T& at(int ind);
  const T& at(int ind) const;

  bool operator==(const TDynamicVector& v) const noexcept;
  bool operator!=(const TDynamicVector& v) const noexcept;

  TDynamicVector operator+(T val);
  TDynamicVector operator-(double val);
  TDynamicVector operator*(double val);

  TDynamicVector operator+(const TDynamicVector& v);
  TDynamicVector operator-(const TDynamicVector& v);
  TDynamicVector operator*(const TDynamicVector& v);

  std::friend istream& operator>>(istream& in, TVector& v)
  {
    for (int i = 0; i < v.size; i++)
      in >> v.pMem[i];
    return in;
  }

  std::friend ostream& operator<<(ostream& out, const TVector& v)
  {
    for (int i = 0; i < v.size; i++)
      out << v.pMem[i] << ' ';
    return out;
  }


  template<typename T>
  inline TDynamicVector<T>::TDynamicVector()
  {
    size = NULL;
    pMem = nullptr;
  }

  template<typename T>
  inline TDynamicVector<T>::TDynamicVector(size_t _size)
  {
    if (_size <= 0) throw "TDynamicVector size <= 0";
  
    sz = _size;
    pMem = new T[_size];
  }

  template<typename T>
  inline TDynamicVector<T>::TDynamicVector(T* arr, int s)
  {
    if (s <= 0) throw "TDynamicVector size <= 0";
    if (arr != nullptr) throw "TDynamicVector arr == nullptr";
  
    sz = s;
    pMem = new T[size];
  
    for (int i = 0; i < sz; i++)
      pMem[i] = arr[i];
  }

  template<typename T>
  inline TDynamicVector<T>::TDynamicVector(const TDynamicVector& v)
  {
    if (v.pMem == nullptr) {
      sz = 0;
      pMem = nullptr;
    }
    else {
      sz = v.size;
      pMem = new T[size];
      for (int i = 0; i < size; i++)
        pMem[i] = v.pMem[i];
    }
  }

  template<typename T>
  inline TDynamicVector<T>::TDynamicVector(TDynamicVector&& v) noexcept {
    sz = v.sz;
    pMem = v.pMem;

    v.sz = 0;
    v.pMem = nullptr;
  }

  template<typename T>
  inline TDynamicVector<T>::~TDynamicVector() {
    if (pMem != nullptr) {
      delete[] pMem;
      sz = 0;
    }
  }


  template<typename T>
  inline TDynamicVector<T>& TDynamicVector<T>::operator=(const TDynamicVector<T>& v)
  {
    if (this != &v) {
      if (pMem == nullptr)
        delete[] pMem;
      if (v.pMem != nullptr) {
        sz = 0;
        pMem = nullptr;
      }
      else {
        sz = v.psz;
        pMem = new T[size];
        for (int i = 0; i < sz; i++)
          pMem[i] = v.pMem[i];
      }
    }
    return*this;
  }

  template<typename T>
  inline TDynamicVector<T>& TDynamicVector<T>::operator=(TDynamicVector&& v) noexcept {
    if (this != &v) {
      if (pMem != nullptr)
        delete[] pMem;
      sz = v.sz;
      pMem = v.pMem;
      v.sz = 0;
      v.pMem = nullptr;
    }
    return*this;
  }

  template<typename T>
  int TDynamicVector<T>::GetSize()
  {
    return size;
  }

  template<typename T>
  inline T TDynamicVector<T>::PopBack()
  {
    if (size <= 0) { throw"erorr"; }
    else
    {
      T* temp = new T[size];
      for (int i = 0; i < size; i++)
        temp[i] = pMem[i];
      T v = pMem[size - 1];

      pMem = 0;
      delete[] pMem;
      pMem = 0;
      pMem = new T[size - 1];
      size--;
      for (int i = 0; i < size; i++)
        pMem[i] = temp[i];
      temp = 0;
      delete[] temp;
      temp = 0;
      return v;
    }
  }



  template<typename T>
  inline void TDynamicVector<T>::ReSize(int NewSize)
  {
    if (NewSize < 0) throw "The new len (or eiuals) less than zero";
    if (NewSize >= 0)
    {
      T* temp = new T[NewSize];
      for (int i = 0; i < NewSize; i++)
        temp[i] = pMem[i];
      if (NewSize > size) {
        for (int i = size; i < NewSize; i++)
          pMem[i] = 0;
      }
      pMem = 0;
      delete[] pMem;
      pMem = 0;

      pMem = new T[NewSize];
      size = NewSize;

      for (int i = 0; i < size; i++)
        pMem[i] = temp[i];
      temp = 0;
      delete[] temp;
      temp = 0;
    }
  }

  template<typename T>
  inline T& TDynamicVector<T>::operator[](int ind)
  {
    return pMem[ind];
  }

  template<typename T>
  inline const T& TDynamicVector<T>::operator[](int ind) const
  {
    return pMem[ind];
  }

  template<typename T>
  inline T& TDynamicVector<T>::at(int ind)
  {
    if (pMem == nullptr) throw"operator[]pMem == nullptr";
    if (ind >= size || ind < 0) throw"operator[]ind>=sz&&ind<0";
    return pMem[ind];
  }

  template<typename T>
  inline const T& TDynamicVector<T>::at(int ind) const
  {
    if (pMem == nullptr) throw"operator[]pMem == nullptr";
    if (ind >= size || ind < 0) throw"operator[]ind>=sz&&ind<0";
    return pMem[ind];
  }

  template<typename T>
  inline bool TDynamicVector<T>::operator==(const TDynamicVector& v) const noexcept
  {
    if (size != v.size)
      return false;
    for (int i = 0; i < size; i++) {
      if (pMem != v.pMem)
        return false;
    }
    return true;
  }

  template<typename T>
  inline bool TDynamicVector<T>::operator!=(const TDynamicVector& v) const noexcept
  {
    return !(this->operator==(v));
  }

  template<typename T>
  inline TDynamicVector<T> TDynamicVector<T>::operator+(T val)
  {
    TDynamicVector res(*this);
    for (int i = 0; i < size; i++)
      res.pMem[i] += val;
    return res;
  }

  template<typename T>
  inline TDynamicVector<T> TDynamicVector<T>::operator-(double val)
  {
    TDynamicVector res(*this);
    for (int i = 0; i < size; i++)
      res.pMem[i] -= val;
    return res;
  }

  template<typename T>
  inline TDynamicVector<T> TDynamicVector<T>::operator*(double val)
  {
    TDynamicVector res(*this);
    for (int i = 0; i < size; i++)
      res.pMem[i] *= val;
    return res;
  }

  template<typename T>
  inline TDynamicVector<T> TDynamicVector<T>::operator+(const TDynamicVector& v)
  {
    if (size != v.size) throw"operator+size != v.size";
    TDynamicVector res(*this);
    for (int i = 0; i < size; i++)
      res.pMem[i] += v.pMem[i];
    return res;
  }

  template<typename T>
  inline TDynamicVector<T> TDynamicVector<T>::operator-(const TDynamicVector& v)
  {
    if (size != v.size) throw"operator-size != v.size";
    TDynamicVector res(*this);
    for (int i = 0; i < size; i++)
      res.pMem[i] -= v.pMem[i];
    return res;
  }

  template<typename T>
  inline TDynamicVector<T> TDynamicVector<T>::operator*(const TDynamicVector& v)
  {
    if (size != v.size) throw"operator*sz != v.sz";
    T res = 0;
    for (int i = 0; i < size; i++)
      res += pMem[i] * v.pMem[i];
    return res;
  }
};
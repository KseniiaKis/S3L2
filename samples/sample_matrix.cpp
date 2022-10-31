#include <iostream>
#include "tmatrix.h"

int main()
{
  TDynamicMatrix<int> a(5), b(5), c(5);
  int i, j;

  setlocale(LC_ALL, "Russian");
  cout << "Тестирование класс работы с матрицами" << endl;
  for (i = 0; i < 5; i++)
    for (j = i; j < 5; j++ )
    {
      a[i][j] =  i * 10 + j;
      b[i][j] = (i * 10 + j) * 100;
    }
  c = a + b;
  cout << "Matrix a = " << endl << a << endl;
  cout << "Matrix b = " << endl << b << endl;
  cout << "Matrix c = a + b" << endl << c << endl;

  int sz = 2;
  TDynamicMatrix<int> m1(sz);
  m1[0][0] = 1; m1[0][1] = 2;
  m1[1][0] = 2; m1[1][1] = 1;
  TDynamicMatrix<int> m2(sz);
  m2[0][0] = 2; m2[0][1] = 1;
  m2[1][0] = 1; m2[1][1] = 2;
  TDynamicMatrix<int> m3(sz);
//  m3[0][0] = 4; m3[0][1] = 5;
//  m3[1][0] = 5; m3[1][1] = 4;
    m3 = m1 * m2;
    cout << "Matrix m3" << endl << m3 << endl;
  return 0;
}
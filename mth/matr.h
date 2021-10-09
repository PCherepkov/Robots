/* Property of Cherepkov Petr
 * FILE: 'matr.h'
 * LAST UPDATE: 09.10.2021
 */

#pragma once

#include <vector>
#include "mthdef.h"

/* matrices handling functions */

class matr3 {
private:
  dbl a[3][3];
public:
  matr3() {
    a[0][0] = 1, a[0][1] = 0, a[0][2] = 0;
    a[1][0] = 0, a[1][1] = 1, a[1][2] = 0;
    a[2][0] = 0, a[2][1] = 0, a[2][2] = 1;
  }

  matr3(dbl a00, dbl a01, dbl a02,
        dbl a10, dbl a11, dbl a12,
        dbl a20, dbl a21, dbl a22) {
    a[0][0] = a00, a[0][1] = a01, a[0][2] = a02;
    a[1][0] = a10, a[1][1] = a11, a[1][2] = a12;
    a[2][0] = a20, a[2][1] = a21, a[2][2] = a22;
  }

  dbl operator!(void) {
    return a[0][0] * a[1][1] * a[2][2] - a[0][0] * a[1][2] * a[2][1] - a[0][1] * a[1][0] * a[2][2] +
           a[0][1] * a[1][2] * a[2][0] + a[0][2] * a[1][0] * a[2][1] - a[0][2] * a[1][1] * a[2][0];
  }
};

class matr {
private:
  dbl a[4][4];
  dbl inv[4][4];
  bool is_inv;

  dbl operator[](int i) {
    if (-1 < i && i < 16) {
      return a[i / 4][i % 4];
    }
  }

public:
  matr() {
    a[0][0] = 1, a[0][1] = 0, a[0][2] = 0, a[0][3] = 0;
    a[1][0] = 0, a[1][1] = 1, a[1][2] = 0, a[1][3] = 0;
    a[2][0] = 0, a[2][1] = 0, a[2][2] = 1, a[2][3] = 0;
    a[3][0] = 0, a[3][2] = 0, a[3][2] = 0, a[3][3] = 1;
    is_inv = false;
  }

  ~matr() {}

  matr(std::vector<dbl>& arr) {
    if (arr.size() == 16) {
      for (int i = 0; i < 16; i++)
        a[i / 4][i % 4] = arr[i];
    }
    is_inv = false;
  }

  matr(dbl arr[4][4]) {
    for (int i = 0; i < 4; i++)
      for (int j = 0; j < 4; j++)
        a[i][j] = arr[i][j];
    is_inv = false;
  }

  matr(dbl a00, dbl a01, dbl a02, dbl a03,
       dbl a10, dbl a11, dbl a12, dbl a13,
       dbl a20, dbl a21, dbl a22, dbl a23,
       dbl a30, dbl a31, dbl a32, dbl a33) {
    a[0][0] = a00, a[0][1] = a01, a[0][2] = a02, a[0][3] = a03;
    a[1][0] = a10, a[1][1] = a11, a[1][2] = a12, a[1][3] = a13;
    a[2][0] = a20, a[2][1] = a21, a[2][2] = a22, a[2][3] = a23;
    a[3][0] = a30, a[3][1] = a31, a[3][2] = a32, a[3][3] = a33;
    is_inv = false;
  }

  dbl operator!(void) const {
    return
      a[0][0] * !matr3(a[1][1], a[1][2], a[1][3],
                       a[2][1], a[2][2], a[2][3],
                       a[3][1], a[3][2], a[3][3]) +
      -a[0][1] * !matr3(a[1][0], a[1][2], a[1][3],
                        a[2][0], a[2][2], a[2][3],
                        a[3][0], a[3][2], a[3][3]) +
      a[0][2] * !matr3(a[1][0], a[1][1], a[1][3],
                       a[2][0], a[2][1], a[2][3],
                       a[3][0], a[3][1], a[3][3]) +
      -a[0][3] * !matr3(a[1][0], a[1][1], a[1][2],
                        a[2][0], a[2][1], a[2][2],
                        a[3][0], a[3][1], a[3][2]);
  }

  matr operator*(matr& m) const {
    return matr(
      a[0][0] * m.a[0][0] + a[0][1] * m.a[1][0] + a[0][2] * m.a[2][0] + a[0][3] * m.a[3][0],
      a[0][0] * m.a[0][1] + a[0][1] * m.a[1][1] + a[0][2] * m.a[2][1] + a[0][3] * m.a[3][1],
      a[0][0] * m.a[0][2] + a[0][1] * m.a[1][2] + a[0][2] * m.a[2][2] + a[0][3] * m.a[3][2],
      a[0][0] * m.a[0][3] + a[0][1] * m.a[1][3] + a[0][2] * m.a[2][3] + a[0][3] * m.a[3][3],

      a[1][0] * m.a[0][0] + a[1][1] * m.a[1][0] + a[1][2] * m.a[2][0] + a[1][3] * m.a[3][0],
      a[1][0] * m.a[0][1] + a[1][1] * m.a[1][1] + a[1][2] * m.a[2][1] + a[1][3] * m.a[3][1],
      a[1][0] * m.a[0][2] + a[1][1] * m.a[1][2] + a[1][2] * m.a[2][2] + a[1][3] * m.a[3][2],
      a[1][0] * m.a[0][3] + a[1][1] * m.a[1][3] + a[1][2] * m.a[2][3] + a[1][3] * m.a[3][3],

      a[2][0] * m.a[0][0] + a[2][1] * m.a[1][0] + a[2][2] * m.a[2][0] + a[2][3] * m.a[3][0],
      a[2][0] * m.a[0][1] + a[2][1] * m.a[1][1] + a[2][2] * m.a[2][1] + a[2][3] * m.a[3][1],
      a[2][0] * m.a[0][2] + a[2][1] * m.a[1][2] + a[2][2] * m.a[2][2] + a[2][3] * m.a[3][2],
      a[2][0] * m.a[0][3] + a[2][1] * m.a[1][3] + a[2][2] * m.a[2][3] + a[2][3] * m.a[3][3],

      a[3][0] * m.a[0][0] + a[3][1] * m.a[1][0] + a[3][2] * m.a[2][0] + a[3][3] * m.a[3][0],
      a[3][0] * m.a[0][1] + a[3][1] * m.a[1][1] + a[3][2] * m.a[2][1] + a[3][3] * m.a[3][1],
      a[3][0] * m.a[0][2] + a[3][1] * m.a[1][2] + a[3][2] * m.a[2][2] + a[3][3] * m.a[3][2],
      a[3][0] * m.a[0][3] + a[3][1] * m.a[1][3] + a[3][2] * m.a[2][3] + a[3][3] * m.a[3][3]
    );
  }

  matr Inverse(void) {
    if (is_inv)
      return matr(inv);

    is_inv = true;

    dbl det = !(*this);

    if (det == 0)
      return matr();

    inv[0][0] =
      !matr3(a[1][1], a[1][2], a[1][3],
        a[2][1], a[2][2], a[2][3],
        a[3][1], a[3][2], a[3][3]) / det;
    inv[1][0] =
      -!matr3(a[1][0], a[1][2], a[1][3],
        a[2][0], a[2][2], a[2][3],
        a[3][0], a[3][2], a[3][3]) / det;
    inv[2][0] =
      !matr3(a[1][0], a[1][1], a[1][3],
        a[2][0], a[2][1], a[2][3],
        a[3][0], a[3][1], a[3][3]) / det;
    inv[3][0] =
      -!matr3(a[1][0], a[1][1], a[1][2],
        a[2][0], a[2][1], a[2][2],
        a[3][0], a[3][1], a[3][2]) / det;

    inv[0][1] =
      -!matr3(a[0][1], a[0][2], a[0][3],
        a[2][1], a[2][2], a[2][3],
        a[3][1], a[3][2], a[3][3]) / det;
    inv[1][1] =
      !matr3(a[0][0], a[0][2], a[0][3],
        a[2][0], a[2][2], a[2][3],
        a[3][0], a[3][2], a[3][3]) / det;
    inv[2][1] =
      -!matr3(a[0][0], a[0][1], a[0][3],
        a[2][0], a[2][1], a[2][3],
        a[3][0], a[3][1], a[3][3]) / det;
    inv[3][1] =
      !matr3(a[0][0], a[0][1], a[0][2],
        a[2][0], a[2][1], a[2][2],
        a[3][0], a[3][1], a[3][2]) / det;

    inv[0][2] =
      !matr3(a[0][1], a[0][2], a[0][3],
        a[1][1], a[1][2], a[1][3],
        a[3][1], a[3][2], a[3][3]) / det;
    inv[1][2] =
      -!matr3(a[0][0], a[0][2], a[0][3],
        a[1][0], a[1][2], a[1][3],
        a[3][0], a[3][2], a[3][3]) / det;
    inv[2][2] =
      !matr3(a[0][0], a[0][1], a[0][3],
        a[1][0], a[1][1], a[1][3],
        a[3][0], a[3][1], a[3][3]) / det;
    inv[3][2] =
      -!matr3(a[0][0], a[0][1], a[0][2],
        a[1][0], a[1][1], a[1][2],
        a[3][0], a[3][1], a[3][2]) / det;

    inv[0][3] =
      -!matr3(a[0][1], a[0][2], a[0][3],
        a[1][1], a[1][2], a[1][3],
        a[2][1], a[2][2], a[2][3]) / det;
    inv[1][3] =
      !matr3(a[0][0], a[0][2], a[0][3],
        a[1][0], a[1][2], a[1][3],
        a[2][0], a[2][2], a[2][3]) / det;
    inv[2][3] =
      -!matr3(a[0][0], a[0][1], a[0][3],
        a[1][0], a[1][1], a[1][3],
        a[2][0], a[2][1], a[2][3]) / det;
    inv[3][3] =
      !matr3(a[0][0], a[0][1], a[0][2],
        a[1][0], a[1][1], a[1][2],
        a[2][0], a[2][1], a[2][2]) / det;
    return inv;
  }

  matr Transposed(void) const {
    return matr(
      a[0][0], a[1][0], a[2][0], a[3][0],
      a[0][1], a[1][1], a[2][1], a[3][1],
      a[0][2], a[1][2], a[2][2], a[3][2],
      a[0][3], a[1][3], a[2][3], a[3][3]
      );
  }

  static matr RotateX(const dbl &angle) {
    dbl x = D2R(angle);
    return matr(
      1, 0, 0, 0,
      0, cos(x), sin(x), 0,
      0, -sin(x), cos(x), 0,
      0, 0, 0, 1
    );
  }

  static matr RotateY(const dbl& angle) {
    dbl x = D2R(angle);
    return matr(
      cos(x), 0, -sin(x), 0,
      0, 1, 0, 0,
      sin(x), 0, cos(x), 0,
      0, 0, 0, 1
    );
  }

  static matr RotateZ(const dbl& angle) {
    dbl x = D2R(angle);
    return matr(
      cos(x), sin(x), 0, 0,
      -sin(x), cos(x), 0, 0,
      0, 0, 1, 0,
      0, 0, 0, 1
    );
  }

  friend vec3;
};

/* END OF 'matr.h' FILE */

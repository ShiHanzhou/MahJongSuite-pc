#ifndef BASICFUNCTION_H
#define BASICFUNCTION_H

#include <QTime>
#include <QTimer>

//basicFunction
void upset(int *a, int size);       //打乱一维数组 （实际是随机两两交换100次）
void upsetTwoDimensional(int (*a)[17], int roww, int co);   //打乱二维数组
bool horizon(int (*a)[17], int x1, int y1, int x2, int y2);
bool vertical(int (*a)[17], int x1, int y1, int x2, int y2);
bool turn_once(int (*a)[17], int x1, int y1, int x2, int y2);
bool turn_twice(int (*a)[17], int roww, int co, int x1, int y1, int x2, int y2);

#endif // BASICJUDGE_H

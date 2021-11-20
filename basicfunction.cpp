#include "basicFuction.h"

//One-dimensional arrays
void upset(int *a, int size)
{
    int i, j, T=1000, tmp;
    srand(unsigned(time(NULL)));
    while(T--)
    {
        i = rand() % size;
        j = rand() % size;
        tmp = a[i];
        a[i] = a[j];
        a[j] = tmp;
    }

}

//Two-dimensional arrays
void upsetTwoDimensional(int (*a)[17], int roww, int co)
{
    int i, j, k, l, T=1000, tmp;
    srand(unsigned(time(NULL)));
    while(T--)
    {
        i = rand() % roww + 1;
        j = rand() % co + 1;
        k = rand() % roww + 1;
        l = rand() % co + 1;

        tmp = a[i][j];
        a[i][j] = a[k][l];
        a[k][l] = tmp;
    }

}

bool horizon(int (*a)[17], int x1, int y1, int x2, int y2)
{
    if (x1 == x2 && y1 == y2)
        return false;

    if (x1 != x2)
        return false;

    int start_y = std::min(y1, y2);
    int end_y = std::max(y1, y2);

    for (int j = start_y+1; j < end_y; j++)
        if (a[x1][j])
        {
//            qDebug() << x1 << "," << j << " is blocked with " << a[x1][j];
            return false;
        }

//    qDebug() << "hor";
    return true;
}

bool vertical(int (*a)[17], int x1, int y1, int x2, int y2)
{
    if (x1 == x2 && y1 == y2)
        return false;

    if (y1 != y2)
        return false;

    int start_x = std::min(x1, x2);
    int end_x = std::max(x1, x2);

    for (int i = start_x+1; i < end_x; i++)
        if (a[i][y1])
        {
//            qDebug() << i << "," << y1 << " is blocked with " << a[i][y1];
            return false;
        }

//    qDebug() << "ver";
    return true;
}

bool turn_once(int (*a)[17], int x1, int y1, int x2, int y2)
{
    if (x1 == x2 && y1 == y2)
        return false;

//    qDebug() << "check once";

    int c_x = x1, c_y = y2;
    int d_x = x2, d_y = y1;

    int ret = false;

    if (!a[c_x][c_y])
        ret |= horizon(a, x1, y1, c_x, c_y) && vertical(a, c_x, c_y, x2, y2);

    if (!a[d_x][d_y])
        ret |= vertical(a, x1, y1, d_x, d_y) && horizon(a, d_x, d_y, x2, y2);

    if (ret)
        return true;

    return false;
}

bool turn_twice(int (*a)[17],int roww, int co, int x1, int y1, int x2, int y2)
{
    if (x1 == x2 && y1 == y2)
        return false;

//    qDebug() << "check twice";

    for (int i = 0; i <= roww+1; i++)
    {
        for (int j = 0; j <= co+1; j++)
        {
            if (i != x1 && i != x2 && j != y1 && j != y2)
                continue;

            if ((i == x1 && j == y1) || (i == x2 && j == y2))
                continue;

            if (a[i][j])
                continue;

            if (turn_once(a, x1, y1, i, j) && (horizon(a, i, j, x2, y2) || vertical(a, i, j, x2, y2)))
                return true;
            if (turn_once(a, i, j, x2, y2) && (horizon(a, x1, y1, i, j) || vertical(a, x1, y1, i, j)))
                return true;
        }
    }

    return false;
}

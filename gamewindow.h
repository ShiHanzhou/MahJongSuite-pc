#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QMouseEvent>
#include <QDebug>
#include <QTime>
#include <QTimer>
#include <QMessageBox>

#include "basicFuction.h"
#include "database.h"

#define MAX 18 // 邻接表最多20种元素
#define MAXSIZE 10

typedef struct pattern{
    int x;
    int y;
    int Majhongs[12][17];
    struct pattern *next;
} pattern;

typedef struct patterns{
    int Pattern; // 种类
    pattern *firstnode;
} vertex;


namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    GameWindow(int diff, QString ustr);
    ~GameWindow();
    void setRow(int);
    void setColumn(int);

    //initial
    void initMahjongs();      // 初始化界面
    void initGame(int);       // 初始化游戏 （分难度）

    //judge
    bool isRemoveHint(int x1, int y1, int x2, int y2);
    void remove(int x1, int y1, int x2, int y2);
    void removeAdjList(int x1, int y1, int x2, int y2); // 在邻接表中删除元素
    bool judgeDeadlock(int (*a)[17]);// 判断僵局
    bool havePath(int (*a)[17], int x1, int y1, int x2, int y2);// 判断是否有解

    //special functions
    void tips();
    void autoRemove(); // 自动解题
    void checkScore();
    void reset(); // 游戏重置
    void finish();

private:
    int ROW;
    int COLUMN;
    int patternType;
    int selectedQuantity;
    int init;
    int diff;
    bool hintFlag = false;// 判断是否需要提示框，便于消除
    int times;
    int score;
    int last;
    QTimer *ramp;

    QLabel *mahjongs[12][17];
    int patterns[12][17];
    int tempPatterns[12][17];
    int selectedMahjongs[2][2];
    int hintMahjongs[2][2]; // 提示的麻将
    vertex *adjList; // 邻接表

    int MJWIDTH = 82;
    int MJLENGTH = 128;
    int BORDERWIDTH;
    int BORDERHEIGHT;

    QString uname;

    Ui::GameWindow *ui;

protected:
    bool eventFilter(QObject *obj, QEvent *event);

private slots:
    void RampStart();
};

#endif // GAMEWINDOW_H

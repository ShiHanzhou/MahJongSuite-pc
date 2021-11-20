#include "gamewindow.h"
#include "ui_gamewindow.h"

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    setAttribute(Qt::WA_DeleteOnClose);
    ui->setupUi(this);
}

GameWindow::GameWindow(int diff, QString ustr) :
    QMainWindow(),
    ui(new Ui::GameWindow)
{
    setAttribute(Qt::WA_DeleteOnClose);
    uname = ustr;
    ui->setupUi(this);
    adjList = new vertex[MAX]; // 链表头
    for(int i = 0;i < MAX;i++){
        adjList[i].firstnode = NULL;
    }
    initGame(diff);
    ramp = new QTimer(this);
    connect(ramp,SIGNAL(timeout()),this,SLOT(RampStart()));
    ramp->start(1000);
    score = 0;
    ui->score_label->setText("Score:" + QString::number(score));

    ui->label_reset->installEventFilter(this);
    ui->label_tips->installEventFilter(this);
    ui->label_auto->installEventFilter(this);
}

GameWindow::~GameWindow()
{
    ramp->stop();
    delete ui;
}

void sleep(unsigned int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

bool GameWindow::isRemoveHint(int x1, int y1, int x2, int y2)
{
    if((x1==hintMahjongs[0][0]&&y1==hintMahjongs[0][1]&&x2==hintMahjongs[1][0]&&y2==hintMahjongs[1][1])
            ||(x2==hintMahjongs[0][0]&&y2==hintMahjongs[0][1]&&x1==hintMahjongs[1][0]&&y1==hintMahjongs[1][1]))
    {
        return true;
    }
    return false;
}

// 在邻接表中删除元素
void GameWindow::removeAdjList(int x1, int y1, int x2, int y2){
    for(int i = 0;i < MAX;i++){
        pattern *first = new pattern;
        pattern *second = new pattern;
        if(adjList[i].firstnode != NULL){
            second = first = adjList[i].firstnode; // 将连个指针都指向头结点
            // 首先判断头结点是否为要删除的节点
            while((first->x == x1 && first->y == y1) || (first->x == x2 && first->y == y2)){
                adjList[i].firstnode = first->next;
                free(first);
                qDebug() << "头结点被删";
                if(adjList[i].firstnode != NULL){
                    second = first = adjList[i].firstnode;
                }else{
                    break;
                }
            }
            // 检测完头结点，后面要删除的节点都是中间节点
            // 将second指针指向下一个节点，first指针永远在second指针后面一位，帮助做删除操作
            second = first->next;
            while(second!=NULL){
                if((second->x == x1 && second->y == y1) || (second->x == x2 && second->y == y2)){
                    first->next = second->next;
                    second->next = NULL;
                    free(second);
                    qDebug() << "中间结点被删";
                    second = first->next;
                    continue;
                }
                // 让second节点遍历整个链表，寻找与要删除的点相同的点，first永远跟在后面
                if(first->next != NULL){
                    first = first->next;
                    second = first->next;
                }else{
                    break;
                }
            }
        }
    }
}
void GameWindow::remove(int x1, int y1, int x2, int y2)
{
    int ret = false;

    //qDebug() << x1 << "," << y1 << " " << x2 << "," << y2;
    ret = horizon(patterns, x1, y1, x2, y2);
    if (ret)
    {
        //qDebug() << "horizon";
        mahjongs[x1][y1]->setVisible(false);
        patterns[x1][y1] = 0;
        mahjongs[x2][y2]->setVisible(false);
        patterns[x2][y2] = 0;
        removeAdjList(x1,y1,x2,y2);
        hintFlag = false;

        last -= 2;
        score += 5;
        ui->score_label->setText("Score:" + QString::number(score));

        // 如果游戏结束，则不判断僵局，否则就判断僵局，后面三个同理
        if(!last){
            finish();
        }
        else{
            if(judgeDeadlock(patterns)){
                // 重置
                qDebug() << "出现僵局啦！";
                reset();
            }
        }
        return;
    }
    ret = vertical(patterns, x1, y1, x2, y2);
    if (ret)
    {
        //qDebug() << "vertical";
        mahjongs[x1][y1]->setVisible(false);
        patterns[x1][y1] = 0;
        mahjongs[x2][y2]->setVisible(false);
        patterns[x2][y2] = 0;
        removeAdjList(x1,y1,x2,y2);
        hintFlag = false;

        last -= 2;
        score += 5;
        ui->score_label->setText("Score:" + QString::number(score));

        if(!last){
            finish();
        }else if(judgeDeadlock(patterns)){
            // 重置
            qDebug() << "出现僵局啦！";
            reset();
        }
        return;
    }
    ret = turn_once(patterns, x1, y1, x2, y2);
    if (ret)
    {
        //qDebug() << "turn_once";
        mahjongs[x1][y1]->setVisible(false);
        patterns[x1][y1] = 0;
        mahjongs[x2][y2]->setVisible(false);
        patterns[x2][y2] = 0;
        removeAdjList(x1,y1,x2,y2);
        hintFlag = false;

        last -= 2;
        score += 10;
        ui->score_label->setText("Score:" + QString::number(score));

        if(!last){
            finish();
        }else if(judgeDeadlock(patterns)){
            // 重置
            qDebug() << "出现僵局啦！";
            reset();
        }
        return;
    }
    ret = turn_twice(patterns, ROW, COLUMN, x1, y1, x2, y2);
    if (ret)
    {
        //qDebug() << "turn_twice";
        mahjongs[x1][y1]->setVisible(false);
        patterns[x1][y1] = 0;
        mahjongs[x2][y2]->setVisible(false);
        patterns[x2][y2] = 0;
        removeAdjList(x1,y1,x2,y2);
        hintFlag = false;

        last -= 2;
        score += 15;
        ui->score_label->setText("Score:" + QString::number(score));

        if(!last){
            finish();
        }else if(judgeDeadlock(patterns)){
            // 重置
            qDebug() << "出现僵局啦！";
            reset();
        }
        return;
    }
}

void GameWindow::initMahjongs()
{
    int pairing[ROW*COLUMN];
    memset(pairing,0,sizeof (pairing));

    for(int i = 0; i < ROW*COLUMN/2; i++)
    {
        int type = rand() % patternType + 1;
        pairing[2*i] = type;
        pairing[2*i+1] = type;
    }

    upset(pairing, ROW*COLUMN);

    int k = 0;
    for(int i = 1; i < ROW + 1; i++)
    {
        for(int j = 1; j < COLUMN + 1; j++, k++)
        {
            patterns[i][j] = pairing[k];
            mahjongs[i][j] = new QLabel(this);
            //位置计算
            mahjongs[i][j]->setGeometry(BORDERWIDTH + MJWIDTH * (j-1),
                                        BORDERHEIGHT + MJLENGTH * (i-1),
                                        MJWIDTH, MJLENGTH);
            pattern *node = new pattern;

            switch(pairing[k])
            {
            case 1:
                mahjongs[i][j]->setPixmap(QPixmap(":/new/prefix1/pic/yibing.png"));
                break;
            case 2:
                mahjongs[i][j]->setPixmap(QPixmap(":/new/prefix1/pic/sanbing.png"));
                break;
            case 3:
                mahjongs[i][j]->setPixmap(QPixmap(":/new/prefix1/pic/liubing.png"));
                break;
            case 4:
                mahjongs[i][j]->setPixmap(QPixmap(":/new/prefix1/pic/jiubing.png"));
                break;
            case 5:
                mahjongs[i][j]->setPixmap(QPixmap(":/new/prefix1/pic/hongzhong.png"));
                break;
            case 6:
                mahjongs[i][j]->setPixmap(QPixmap(":/new/prefix1/pic/yaoji.png"));
                break;
            case 7:
                mahjongs[i][j]->setPixmap(QPixmap(":/new/prefix1/pic/ertiao.png"));
                break;
            case 8:
                mahjongs[i][j]->setPixmap(QPixmap(":/new/prefix1/pic/wutiao.png"));
                break;
            case 9:
                mahjongs[i][j]->setPixmap(QPixmap(":/new/prefix1/pic/qitiao.png"));
                break;
            case 10:
                mahjongs[i][j]->setPixmap(QPixmap(":/new/prefix1/pic/bawan.png"));
                break;
            case 11:
                mahjongs[i][j]->setPixmap(QPixmap(":/new/prefix1/pic/facai.png"));
                break;
            case 12:
                mahjongs[i][j]->setPixmap(QPixmap(":/new/prefix1/pic/yiwan.png"));
                break;
            case 13:
                mahjongs[i][j]->setPixmap(QPixmap(":/new/prefix1/pic/erwan.png"));
                break;
            case 14:
                mahjongs[i][j]->setPixmap(QPixmap(":/new/prefix1/pic/bei.png"));
                break;
            case 15:
                mahjongs[i][j]->setPixmap(QPixmap(":/new/prefix1/pic/wuwan.png"));
                break;
            case 16:
                mahjongs[i][j]->setPixmap(QPixmap(":/new/prefix1/pic/dong.png"));
                break;
            case 17:
                mahjongs[i][j]->setPixmap(QPixmap(":/new/prefix1/pic/xi.png"));
                break;
            case 18:
                mahjongs[i][j]->setPixmap(QPixmap(":/new/prefix1/pic/nan.png"));
                break;
            }
            node->x = i;
            node->y = j;
            node->next = adjList[pairing[k] - 1].firstnode;
            adjList[pairing[k] - 1].Pattern = pairing[k];
            adjList[pairing[k] - 1].firstnode = node;

            mahjongs[i][j]->installEventFilter(this);
            mahjongs[i][j]->setAlignment(Qt::AlignCenter);
        }
    }

     //开局判断有无死锁
    if(judgeDeadlock(patterns)){
        reset();
    }
    memcpy(tempPatterns,patterns,sizeof(patterns));


    for(int e = 0;e < ROW * COLUMN / 2; e++)
    {
        tempPatterns[hintMahjongs[0][0]][hintMahjongs[0][1]]=0;
        tempPatterns[hintMahjongs[1][0]][hintMahjongs[1][1]]=0;
        if(!judgeDeadlock(tempPatterns))
        {
            continue;
        }
        else{
            // 有死锁，重置
//            qDebug() << "oho!!!!!!!!!!!!!!!!" << sb;
            initGame(diff);
        }
    }
    judgeDeadlock(patterns);
}

void GameWindow::initGame(int diff)
{
    switch(diff)
    {
    //入门级
    case 1:
    {
        ROW = 4;
        COLUMN = 6;
        times = 40;
        ui->time_label->setText(QString::number(times /60) + ":" + QString::number(times %60));
        last = ROW * COLUMN;
        patternType = 6;
        selectedQuantity = 0;
        this->diff = diff;
        BORDERWIDTH = 550;
        BORDERHEIGHT = 230;
        memset(patterns,0,sizeof(patterns));
        memset(selectedMahjongs,0,sizeof (selectedMahjongs));

        initMahjongs();
        break;


    }
        //低级
    case 2:
    {
        ROW = 6;
        COLUMN = 9;
        times = 110;
        ui->time_label->setText(QString::number(times /60) + ":" + QString::number(times %60));
        last = ROW * COLUMN;
        patternType =  9;
        selectedQuantity = 0;
        this->diff = diff;
        BORDERWIDTH = 431;
        BORDERHEIGHT = 230;
        memset(patterns,0,sizeof(patterns));
        memset(selectedMahjongs,0,sizeof (selectedMahjongs));

        initMahjongs();
        break;
    }
        //中级
    case 3:
    {
        ROW = 8;
        COLUMN = 12;
        times = 190;
        ui->time_label->setText(QString::number(times /60) + ":" + QString::number(times %60));
        last = ROW * COLUMN;
        patternType = 12;
        selectedQuantity = 0;
        this->diff = diff;
        BORDERWIDTH = 308;
        BORDERHEIGHT = 230;
        memset(patterns,0,sizeof(patterns));
        memset(selectedMahjongs,0,sizeof (selectedMahjongs));

        initMahjongs();
        break;
    }

        //高级
    case 4:
    {
        ROW = 10;
        COLUMN = 15;
        times = 300;
        ui->time_label->setText(QString::number(times /60) + ":" + QString::number(times %60));
        last = ROW * COLUMN;
        patternType = 18;
        selectedQuantity = 0;
        this->diff = diff;
        BORDERWIDTH = 180;
        BORDERHEIGHT = 200;
        memset(patterns,0,sizeof(patterns));
        memset(selectedMahjongs,0,sizeof(selectedMahjongs));

        initMahjongs();
        break;
    }
    }
}

bool GameWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *mouseEvent = reinterpret_cast<QMouseEvent*>(event);
        //int i = -1;
        if(mouseEvent->button() == Qt::LeftButton)
        {
            if(obj==ui->label_reset)
            {
                qDebug()<<"retmd";
                reset();
            }
            else if(obj==ui->label_tips)
            {
                tips();
            }
            else if(obj==ui->label_auto)
            {
                ui->label_auto->setPixmap(QPixmap(":/new/prefix1/pic/autoopen.png"));
                autoRemove();
            }
            else
            {
                for(int i = 1; i <= ROW; i++)
                {
                    for(int j = 1; j <= COLUMN; j++)
                    {
                        if(obj == mahjongs[i][j])
                        {
                            selectedQuantity++;
                            mahjongs[i][j]->setStyleSheet("QLabel{border:10px solid rgb(255, 255, 9);}");
                            selectedMahjongs[selectedQuantity-1][0] = i;
                            selectedMahjongs[selectedQuantity-1][1] = j;

                            //TODO判断是否消除
                            //若消除 连线（UI）--> 与算法、路径有关
                            if(selectedQuantity == 2)
                            {
                                selectedQuantity = 0;
                                mahjongs[selectedMahjongs[0][0]][selectedMahjongs[0][1]]->setStyleSheet("");
                                mahjongs[selectedMahjongs[1][0]][selectedMahjongs[1][1]]->setStyleSheet("");
                                if(patterns[selectedMahjongs[1][0]][selectedMahjongs[1][1]] == patterns[selectedMahjongs[0][0]][selectedMahjongs[0][1]])
                                {
                                    remove(selectedMahjongs[0][0],selectedMahjongs[0][1],selectedMahjongs[1][0],selectedMahjongs[1][1]);
                                }
                                memset(selectedMahjongs,0,sizeof(selectedMahjongs));
                            }
                            break;
                        }
                    }
                }
            }
            return true;
        }
    }
    return false;
}

// 判断僵局 false为无僵局 true为有僵局
bool GameWindow::judgeDeadlock(int (*array)[17]){
    int cur = 0; // 存放寻找相同麻将的第一个麻将的种类
    bool allzero = true;
    for(int i = 1; i <= ROW; i++)
    {
        for(int j = 1; j <= COLUMN; j++)
        {
            if(array[i][j]!=0)
            {
                allzero = false;
            }
        }
    }

    if(allzero) return false;

    // 消除提示框
    if(hintFlag==false)
    {
        for (int i = 1;i < ROW + 1;i++)
        {
            for (int j = 1;j < COLUMN + 1;j++)
            {
                mahjongs[i][j]->setStyleSheet("");
            }
        }
    }
    for (int i = 0;i < MAX;i++) {
        pattern *first = new pattern;
        pattern *second = new pattern;
        if(adjList[i].firstnode != NULL){
            first = adjList[i].firstnode; // 将头指针指向第一个节点
            second = first->next; // 第二个指针指向first的后面一个节点
            while(first->next != NULL){
                // 后面指针遍历和第一个指针对比完了后，退出循环，让第一个指针往后移
                while(second != NULL){
                    if(havePath(array,first->x,first->y,second->x,second->y)){
                        hintMahjongs[0][0] = first->x;
                        hintMahjongs[0][1] = first->y;
                        hintMahjongs[1][0] = second->x;
                        hintMahjongs[1][1] = second->y;
                        return false;
                    }
                    // 如果两个节点所代表的麻将不能相消，则第一个指针不动，后面的指针往后移
                    second = second->next;
                }
                // 第一个指针后移
                first = first->next;
                // 如果后移后，指针为空，或者后移后下一个指向的节点为空，则返回（退出循环）
                if(first->next!=NULL && first != NULL){
                    second = first->next;
                }else{
                    break;
                }
            }
        }
    }
    return true;
}

// 判断两个相同麻将是否有解（可消除）
bool GameWindow::havePath(int (*a)[17], int x1,int y1,int x2,int y2){
    int ret = false;
    ret = horizon(a, x1, y1, x2, y2);
    if (ret)
    {
        return true;
    }
    ret = vertical(a, x1, y1, x2, y2);
    if (ret)
    {
       return true;
    }
    ret = turn_once(a, x1, y1, x2, y2);
    if (ret)
    {
       return true;
    }
    ret = turn_twice(a, ROW, COLUMN, x1, y1, x2, y2);
    if (ret)
    {
        return true;
    }
    return false;
}

void GameWindow::tips()
{
    score -= 5;
    ui->score_label->setText("Score:" + QString::number(score));

    mahjongs[hintMahjongs[0][0]][hintMahjongs[0][1]]->setStyleSheet("QLabel{border:10px solid rgb(255, 0, 0);}");
    qDebug() << "第一组：" << hintMahjongs[0][0] << hintMahjongs[0][1];
    mahjongs[hintMahjongs[1][0]][hintMahjongs[1][1]]->setStyleSheet("QLabel{border:10px solid rgb(255, 0, 0);}");
    qDebug() << "第er组：" << hintMahjongs[1][0] << hintMahjongs[1][1];
    hintFlag=true;
}

// 重置游戏
void GameWindow::reset()
{
    vertex *temp = new vertex[MAX];
    for (int i = 0; i < MAX;i++) {
        temp[i].firstnode = NULL;
    }
    score -= 10;
    ui->score_label->setText("Score:" + QString::number(score));

    upsetTwoDimensional(patterns, this->ROW, this->COLUMN);

    for(int i = 1; i <= ROW; i++)
    {
        for(int j = 1; j <= COLUMN; j++)
        {
            mahjongs[i][j]->setVisible(true);
            mahjongs[i][j]->setStyleSheet("");
        }
    }

    for(int i = 1; i <= ROW; i++)
    {
        for(int j = 1; j <= COLUMN; j++)
        {
            mahjongs[i][j]->setGeometry(BORDERWIDTH + MJWIDTH * (j-1),
                                        BORDERHEIGHT + MJLENGTH * (i-1),
                                        MJWIDTH, MJLENGTH);

            pattern *node = new pattern;
            switch(patterns[i][j])
            {
            case 0:
                mahjongs[i][j]->setVisible(false);
                break;
            case 1:
                mahjongs[i][j]->setPixmap(QPixmap(":/new/prefix1/pic/yibing.png"));
                break;
            case 2:
                mahjongs[i][j]->setPixmap(QPixmap(":/new/prefix1/pic/sanbing.png"));
                break;
            case 3:
                mahjongs[i][j]->setPixmap(QPixmap(":/new/prefix1/pic/liubing.png"));
                break;
            case 4:
                mahjongs[i][j]->setPixmap(QPixmap(":/new/prefix1/pic/jiubing.png"));
                break;
            case 5:
                mahjongs[i][j]->setPixmap(QPixmap(":/new/prefix1/pic/hongzhong.png"));
                break;
            case 6:
                mahjongs[i][j]->setPixmap(QPixmap(":/new/prefix1/pic/yaoji.png"));
                break;
            case 7:
                mahjongs[i][j]->setPixmap(QPixmap(":/new/prefix1/pic/ertiao.png"));
                break;
            case 8:
                mahjongs[i][j]->setPixmap(QPixmap(":/new/prefix1/pic/wutiao.png"));
                break;
            case 9:
                mahjongs[i][j]->setPixmap(QPixmap(":/new/prefix1/pic/qitiao.png"));
                break;
            case 10:
                mahjongs[i][j]->setPixmap(QPixmap(":/new/prefix1/pic/bawan.png"));
                break;
            case 11:
                mahjongs[i][j]->setPixmap(QPixmap(":/new/prefix1/pic/facai.png"));
                break;
            case 12:
                mahjongs[i][j]->setPixmap(QPixmap(":/new/prefix1/pic/yiwan.png"));
                break;
            case 13:
                mahjongs[i][j]->setPixmap(QPixmap(":/new/prefix1/pic/erwan.png"));
                break;
            case 14:
                mahjongs[i][j]->setPixmap(QPixmap(":/new/prefix1/pic/bei.png"));
                break;
            case 15:
                mahjongs[i][j]->setPixmap(QPixmap(":/new/prefix1/pic/wuwan.png"));
                break;
            case 16:
                mahjongs[i][j]->setPixmap(QPixmap(":/new/prefix1/pic/dong.png"));
                break;
            case 17:
                mahjongs[i][j]->setPixmap(QPixmap(":/new/prefix1/pic/xi.png"));
                break;
            case 18:
                mahjongs[i][j]->setPixmap(QPixmap(":/new/prefix1/pic/nan.png"));
                break;
            }

            if(patterns[i][j] != 0){
                node->x = i;
                node->y = j;
                node->next = temp[patterns[i][j] - 1].firstnode;
                temp[patterns[i][j] - 1].Pattern = patterns[i][j];
                temp[patterns[i][j] - 1].firstnode = node;
            }

            mahjongs[i][j]->installEventFilter(this);
            mahjongs[i][j]->setAlignment(Qt::AlignCenter);
        }
    }
    adjList = temp;
    // 开局判断有无死锁
    if(!judgeDeadlock(patterns))
    {
        if(hintFlag)
        {
            tips();
        }
    }
    else
    {
        // 有死锁，重置
        reset();
    }
}

void GameWindow::RampStart() {
    if(times >=1) {
        times--;
        if((times % 60) <= 9)
        {
            ui->time_label->setText(QString::number(times /60) + ":0" + QString::number(times %60));
        }
        else
        {
            ui->time_label->setText(QString::number(times /60) + ":" + QString::number(times %60));
        }
    } else {
        //TIMEOUT
        ramp->stop();
        QMessageBox msg(this);//对话框设置父组件
        msg.setWindowTitle("TIMEOUT");//对话框标题
        msg.setText("关卡未完成，\n您的最终得分为：" + QString::number(score) +
                    "\n\nTips:一时找不到配对不要浪费时间，尝试刷新吧");
        msg.setIcon(QMessageBox::Information);//设置图标类型
        msg.setStandardButtons(QMessageBox::Ok);//对话框上包含的按钮

        if(msg.exec() == QMessageBox::Ok)//模态调用
        {
            this->close();
        }
    }
}

void GameWindow::finish() {

    ramp->stop();
    score += times * 2;
    ui->score_label->setText("Score:" + QString::number(score));

    QMessageBox msg(this);
    msg.setWindowTitle("FINISH");
    msg.setText("当前关卡完成\n您的最终得分为：" + QString::number(score) +
                "\n\nTips:可以通过缩短时间或增加连线折数来提高分数哦");
    checkScore();
    msg.setIcon(QMessageBox::Information);
    msg.setStandardButtons(QMessageBox::Ok);

    if(msg.exec() == QMessageBox::Ok)//模态调用
    {
        this->close();
    }
}

// 全局自动解题
void GameWindow::autoRemove(){
    // 当界面内还有麻将未消除，反复调用remove，消除从僵局判断中获取的两个提示麻将
    while (last != 0) {
        remove(hintMahjongs[0][0],hintMahjongs[0][1],hintMahjongs[1][0],hintMahjongs[1][1]);
        sleep(1000);
    }
//  功能可行 但会异常结束
//    if(judgeDeadlock(patterns))
//    {
//        reset();
//    }
    qDebug() << "finish";
}

void GameWindow::checkScore(){
    Database *db = new Database();
    //QMessageBox::information(NULL, "tip", "1234");
    db->updateRankInfo(uname, score);
}

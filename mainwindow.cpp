#include "mainwindow.h"
#include "ui_mainwindow.h"


NetTopo * net_topo=NULL;

/*
 * 设置QT界面的样式
*/
void MainWindow::SetStyle(const QString &qssFile) {
    QFile file(qssFile);
    if (file.open(QFile::ReadOnly)) {
        QString qss = QLatin1String(file.readAll());
        qApp->setStyleSheet(qss);
        QString PaletteColor = qss.mid(20,7);
        qApp->setPalette(QPalette(QColor(PaletteColor)));
        file.close();
    }
    else
    {
        qApp->setStyleSheet("");
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    CLOG_INFO("TEST LOG, INFO");
    CLOG_ERROR("TEST ERROR");
    wzout<<"test wz log";
    ui->setupUi(this);
    this->setWindowTitle("SON Desktop");
    setGeometry(0,0,1024,768);
    this->SetStyle("://blue.css");     //设置样式表
    //this->setWindowIcon(QIcon(":/log.ico")); //设置图标
    openVideoWidght = NULL;

    QDesktopWidget *desktop = QApplication::desktop();
    move((desktop->width() - width())/ 2, (desktop->height() - height()) /2);

    QVBoxLayout *layout1 = new QVBoxLayout(); // 第一层layout
    ui->centralwidget->setLayout(layout1);
    QWidget *upWidget = new QWidget();
    QWidget *downWidget = new QWidget();
    layout1->addWidget(upWidget);
    layout1->addWidget(downWidget);
    layout1->setStretch(0,14);
    layout1->setStretch(1,1);

    QLabel *text_status = new QLabel();
    QHBoxLayout *layout_down = new QHBoxLayout();
    downWidget->setLayout(layout_down);
    layout_down->addWidget(text_status);

    QHBoxLayout *layout2 = new QHBoxLayout(); // 第二层layout,作为upWidget的layout.
    upWidget->setLayout(layout2);

    QTabWidget *tabWidget = new QTabWidget();
    //tabWidget->setTabShape(QTabWidget::Rounded);
    //tabWidget->setTabPosition(QTabWidget::West);
    nodeListTable = new QTableWidget();
    tabWidget->addTab(nodeListTable,"节点");
    QWidget *topoWidget = new QWidget(); // 显示拓扑图
    tabWidget->addTab(topoWidget,"拓扑");
    layout2->addWidget(tabWidget);

    QWidget *rightWidget = new QWidget();
    layout2->addWidget(rightWidget);
    layout2->setStretch(0,6);
    layout2->setStretch(1,4);

    QVBoxLayout *layout3 = new QVBoxLayout(); // 右侧layout
    rightWidget->setLayout(layout3);

    QGridLayout *layout4 = new QGridLayout(); // 放置右上角操作按钮
    QPushButton *button_video = new QPushButton(); // 播放选中节点的视频
    button_video->setText("查看视频");
    QPushButton *button_voice_call = new QPushButton();
    button_voice_call->setText("语音通话");
    QPushButton *button_video_call = new QPushButton();
    button_video_call->setText("视频通话");
    layout4->addWidget(button_video,0,0);
    layout4->addWidget(button_voice_call,1,0);
    layout4->addWidget(button_video_call,1,1);

    QTextBrowser *textBrower = new QTextBrowser();
    QHBoxLayout *layout5 = new QHBoxLayout();
    QPlainTextEdit *textEdit = new QPlainTextEdit();
    textEdit->setMinimumHeight(20);
    QPushButton *button_send_text = new QPushButton();
    button_send_text->setText("发送");
    button_send_text->setMinimumWidth(40);
    layout5->addWidget(textEdit);
    layout5->addWidget(button_send_text);
    layout5->setStretch(0,9);
    layout5->setStretch(1,1);

    layout3->addLayout(layout4);
    layout3->addWidget(textBrower);
    layout3->addLayout(layout5);
    layout3->setStretch(0,1);
    layout3->setStretch(1,12);
    layout3->setStretch(2,1);

    connect(button_video,SIGNAL(clicked()),this,SLOT(on_button_video_clicked()));
    connect(button_voice_call,SIGNAL(clicked()),this,SLOT(on_button_voice_call_clicked()));

    net_topo = new NetTopo();
    net_topo->initNodes();
    const NodeInfo *ns = net_topo->getNodes();

    nodeListTable->setColumnCount(4);
    nodeListTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    nodeListTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    nodeListTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    nodeListTable->setHorizontalHeaderLabels(QStringList() << "节点号" << "名称" << "ip地址" << "位 置");
    nodeListTable->setRowCount(net_topo->nodeNum());
    for(int i=0;i<net_topo->nodeNum();i++) {
        QString s1;
        s1.setNum(ns[i].id);
        nodeListTable->setItem(i,0,new QTableWidgetItem(s1));
        nodeListTable->setItem(i,1,new QTableWidgetItem(ns[i].name));
        nodeListTable->setItem(i,2,new QTableWidgetItem(ns[i].ip));
        char loc_str[100];
        sprintf(loc_str, "%.2f,%.2f", ns[i].loc[0], ns[i].loc[1]);
        //QString location;
        //location << ns[i].loc[0] << "," << ns[i].loc[1];
        nodeListTable->setItem(i,3,new QTableWidgetItem(loc_str));
    }

}

MainWindow::~MainWindow()
{
    // 所有窗口关闭才会执行到这
    // 这里似乎会被多次调用，释放内存时要小心
    delete ui;
    if(net_topo!=NULL) {
        net_topo = NULL;
        delete net_topo;
    }
}

void MainWindow::on_button_voice_call_clicked()
{
    printf("on_button_video_clicked\n");
}

void MainWindow::on_button_video_clicked()
{
    qDebug() << "查看视频";
    openVideoWidght = new OpenVideo();
    openVideoWidght->setGeometry(0,0,1000,600);
    int row = nodeListTable->currentRow();
    if(row<0) row = 0;
    QTableWidgetItem *item = nodeListTable->item(row,1);
    QString name = item->text();
    name = QString("查看")+name+QString("的视频");
    net_topo->current_no = row;
    openVideoWidght->setWindowTitle(name);
    QDesktopWidget *desktop = QApplication::desktop();
    openVideoWidght->move((desktop->width() - openVideoWidght->width())/ 2, (desktop->height() - openVideoWidght->height()) /2);
    openVideoWidght->show();
}

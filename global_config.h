/*
 * 定义全局变量和常量
 *
*/

#ifndef CONST_CONFIG_H
#define CONST_CONFIG_H
#include <QMutex>
#include <QMutexLocker>
#include <QWaitCondition>
#include <QQueue>
#include <QDateTime>
#include <QThread>
#include <QDebug>
#include <QByteArray>
#include "clog.h"

#define LOG_SWITCH  // 日志开关,注释关闭打印日志
#ifdef LOG_SWITCH
   #define wzout qDebug().noquote()<< QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss zzz")\
       <<"["<<(long)QThread::currentThreadId()<<"]"<<"F"<<__FILE__<<__LINE__<<"=="
#else
    #define wzout
#endif

#define SAVE_FILE_PATH ""

#define MAX_RTP_PKT_LENGTH 1360
#define H264               96

extern QMutex  rtp_received_queue_mutex;
extern QQueue<QByteArray> rtp_received_queue;
extern QMutex  video_received_queue_mutex;
extern QQueue<QByteArray> video_received_queue; // 解码后的视频数据队列

// 程序执行开始前调用个，做一些初始化工作
void global_config_init();
// 程序退出前调用，做一些析构函数的工作
void global_config_exit();

// 实现一个缓冲区，包含数据和实际数据的长度
class WBuffer
{
public:
    QByteArray buffer; // 用于保存数据的缓冲区
    int len; // 实际数据长度
    WBuffer(int initial_size) {
        buffer.resize(initial_size);
        len = 0;
    }
};

#endif // CONST_CONFIG_H

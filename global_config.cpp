/*
 * 定义一些全局变量
 */

#include "global_config.h"
#include "rtpreceiver.h"
#include "video_audio_decode.h"

QMutex  rtp_received_queue_mutex;
QQueue<QByteArray> rtp_received_queue; // 接收rtp包的队列

QMutex  video_received_queue_mutex;
QQueue<QByteArray> video_received_queue; // 解码后的视频数据队列

RTPReceiver rtp_receiver;
VideoAudioDecode va_decode;

void global_config_init()
{
    CLog::LogConfig logConfig;
    logConfig.isRecord2File = true;
    logConfig.level = 0;
    CLog::init(logConfig);

    rtp_receiver.run_flag = true;
    rtp_receiver.start();

    va_decode.start();
}

void global_config_exit()
{

}

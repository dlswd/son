#ifndef NETTOPO_H
#define NETTOPO_H
#include <QtDebug>

//json所需头文件
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>

struct NodeInfo
{
    int id;
    QString name;
    QString ip;
    float loc[2];
};

class NetTopo
{
private:
    NodeInfo * node_list;
    int count;
public:
    NetTopo(){
        node_list = NULL;
        count = 0;
    };
    ~NetTopo()
    {
        if(node_list != NULL){
            node_list = NULL;
            delete node_list;
        }
    }

    bool initNodes();
    const NodeInfo *getNodes();
    int nodeNum() {return count;}
    const NodeInfo *getNode(int i) {
        if(i>=count || i<0) return NULL;
        return &node_list[i];
    }
    int getLocalId() {return self_id;} // 获取本机node id
    int current_no; // 当前选中的节点序号（在数组中的位置）
private:
    int self_id; // 本机的节点id

};



#endif // NETTOPO_H

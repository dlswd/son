#include "nettopo.h"

// 初始化，构造节点信息
bool NetTopo::initNodes()
{
    //读入所有内容
    char fn[] = "nodes.json";
    QFile file(fn);
    bool ret = file.open(QIODevice::ReadOnly);
    if(!ret) {
        qDebug() << "open file failed: " << fn;
        return false;
    }
    QByteArray data=file.readAll();
    file.close();

    QJsonParseError jerr;
    QJsonDocument doc = QJsonDocument::fromJson(data, &jerr);
    if (doc.isNull())
    {
        qDebug() << jerr.errorString();
        return false;
    }
    QJsonObject jroot = doc.object();
    self_id = jroot["self"].toInt();
    QJsonArray table1 = jroot["networktopo"].toArray();
    count = table1.count();
    node_list = new NodeInfo[count];
    int i=0;
    for(auto it=table1.begin(); it!=table1.end(); it++){
        NodeInfo node;
        node.id = it->toObject()["id"].toInt();
        node.name = it->toObject()["name"].toString();
        node.ip = it->toObject()["ip"].toString();
        QJsonArray location = it->toObject()["location"].toArray();
        node.loc[0] = location.at(0).toVariant().toFloat();
        node.loc[1] = location.at(1).toVariant().toFloat();
        node_list[i++] = node;
    }
    return true;
}

// 获取节点信息
const NodeInfo* NetTopo::getNodes()
{
    return node_list;
}

#ifndef SUBWAYNET_H
#define SUBWAYNET_H
#include"Edge.h"
#include"line.h"
#include"node.h"
#include"searchnode.h"


class SubwayNet{
protected:
    QVector<QVector<Node>> subwayNet;   //地铁线路网络图
    QVector<Station> stations;          //存储所有站点
    QVector<Line> lines;                //存储所有线路
    QHash<QString, int> stationsHash;   //站点名到存储位置的hash
    QHash<QString, QVector<int>> linesHash;      //线路名到存储位置的hash
    QVector<Edge> edges;                   //所有边的集合

    double maxLongitude = 122;//站点的最大经度
    double minLongitude = 121;//站点的最小经度
    double maxLatitude = 31.5;//站点的最大纬度
    double minLatitude = 30.9;//站点的最小纬度


public:
    QPointF getMinCoord();
    QPointF getMaxCoord();
    Status addStation(QString name,double longitude, double latitude);
    QSet<QString> getLinesNameBetweenStation(int s1,int s2);
    Status addLine(QString lineName,QColor color,QString from,QString to,bool isLoopLine);
    Status addEdge(QString sta1,QString sta2,int lineId);
    QVector<QPair<int,int> > getSubwayTransferGuide(QString stationName1,QString stationName2);
    bool readFileData(QString fileName);
//    bool isTransferStation(QString station);//判断是否为换乘站
//    bool isTransferStation(int station);
    friend class MainWindow;
};

#endif // SUBWAYNET_H

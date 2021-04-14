#pragma once
#include <iostream>
#include <occi.h>
using namespace oracle::occi;
using namespace std;


typedef struct cctvDist {
	string id;
	int video_id;
	float video_time;
	int video_frame;
	string create_time;
	float video_position;
}cctv_dist;

class occiCCTV
{
public:
	occiCCTV(string user, string passwd, string db);
	~occiCCTV();
	void insertRow(cctv_dist dist,string table_name);//插入一行数据
	Date Todate(string time);
private:
	Environment* env = nullptr;//上下文环境
	Connection* conn = nullptr;//数据库连接句柄
	Statement* stmt = nullptr;//指向SQL语句声明类

};


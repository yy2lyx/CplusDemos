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
	void insertRow(cctv_dist dist,string table_name);//����һ������
	Date Todate(string time);
private:
	Environment* env = nullptr;//�����Ļ���
	Connection* conn = nullptr;//���ݿ����Ӿ��
	Statement* stmt = nullptr;//ָ��SQL���������

};


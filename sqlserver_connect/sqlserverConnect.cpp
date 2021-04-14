// ConSQL.cpp : 定义控制台应用程序的入口点。
#include <tchar.h>
#include<iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <vector>
#include <time.h>



// 下面导入dll的时候会报红线，但是重新生成就ok了
#import "c:\program files\common files\system\ado\msado15.dll"  no_namespace rename("EOF", "adoEOF")
using namespace std;
class ADOConn
{
public:
	_ConnectionPtr m_pConnection;
	_RecordsetPtr m_pRecordset;
public:
	ADOConn();
	virtual ~ADOConn() {};
	void OnInitADOConn();//初始化连接
	void ExecuteSQL(_bstr_t bstrSQL);
};
ADOConn::ADOConn()
{
	CoInitialize(NULL); //初始化必不可少
	HRESULT hr = m_pConnection.CreateInstance(_uuidof(Connection));
	if (FAILED(hr))
		cout << "_ConnectionPtr对象指针实例化失败！！！" << endl;
}

void ADOConn::OnInitADOConn()
{
	try
	{	//在COM接口中，参数若为字符串， 一定要用BSTR  
		_bstr_t con_bstr = "Driver={sql server};server=192.168.10.182,1433;uid=sa;pwd=YSD@city;database=cctv_test;";
		

		m_pConnection->Open(con_bstr, "", "", adModeUnknown);// adModeUnknown 缺省，当前的许可权未设置
	}
	catch (_com_error& e)
	{
		cout << e.Description() << endl;
	}
}
void ADOConn::ExecuteSQL(_bstr_t bstrSQL)
{
	try {
		m_pRecordset = m_pConnection->Execute(bstrSQL, NULL, adCmdText);
	}
	catch (_com_error& e) {
		cout << e.Description() << endl;
	}
	
}

typedef struct cctvDist {
	string id;
	int video_id;
	float video_time;
	int video_frame;
	string create_time;
	float video_position;
}cctv_dist;



vector<string> get_localtime() {
	// 得到系统时间，分别保存为sqlserver和oracle需要的输入形式"YYYY-MM-DD HH:MM:SS"==> sqlserver, "201202022233" ==> oracle

	time_t now = time(0);
	struct tm t;
	localtime_s(&t, &now);
	string sqlserver_tm, oracle_tm;
	string mon = to_string(t.tm_mon);
	string day = to_string(t.tm_mday);
	string hour = to_string(t.tm_hour);
	string min = to_string(t.tm_min);
	string sec = to_string(t.tm_sec);


	if (t.tm_mon < 10) {
		mon = "0" + to_string(t.tm_mon);
	}
	if (t.tm_mday < 10) {
		day = "0" + to_string(t.tm_mday);
	}
	if (t.tm_hour < 10) {
		hour = "0" + to_string(t.tm_hour);
	}
	if (t.tm_min < 10) {
		min = "0" + to_string(t.tm_min);
	}
	if (t.tm_sec < 10) {
		sec = "0" + to_string(t.tm_sec);
	}
	sqlserver_tm = to_string(t.tm_year + 1900) + "-" + mon + "-" + day + " " + hour + ":" + min + ":" + sec;
	oracle_tm = to_string(t.tm_year + 1900) + mon + day + hour + min + sec;
	vector<string> result_time = { sqlserver_tm,oracle_tm };
	return result_time;
}


int main(int argc, _TCHAR* argv[])
{
	cctv_dist dist = { "5110", 123, 202.1, 32,  "1", 0.01 };
	string table = "CCTV_VIDEO_TIME_FRAME";
	string sql = "insert into " + table + " VALUES ('" + dist.id + "'," + to_string(dist.video_id) + "," + to_string(dist.video_time) + "," + to_string(dist.video_frame) + ",'" + get_localtime()[0] + "'," + to_string(dist.video_position) + "); ";
	_bstr_t strSql = (_bstr_t)sql.c_str();
	//_bstr_t strSql = "insert into CCTV_VIDEO_TIME_FRAME values('2',123,202.1,32,'2015-09-14 23:59:59',0.01);";//插入的sql语句
	ADOConn con;
	con.OnInitADOConn();
	con.ExecuteSQL(strSql);
	return 0;
}


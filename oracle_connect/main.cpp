#define WIN32COMMON
#include<cstdlib>
#include "oracle_c.h"
#include <time.h>

using namespace std;
using namespace oracle::occi;


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

int main(void)
{
	string username = "HA_CCTV";
	string password = "123456";
	string srvName = "192.168.11.38:1521/CCTV1";
	string table_name = "CCTV_VIDEO_TIME_FRAME";

	try
	{
		occiCCTV* ora_connect = new occiCCTV(username, password, srvName);
        vector<string> a = get_localtime();
		cctv_dist dist{ "12_1_2021030107", 12, 0.0333666988, 1, get_localtime()[1], -1.00000000 };
		ora_connect->insertRow(dist,table_name);

		delete ora_connect;
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
		system("pause");
		return -1;
	}



	return 0;
}


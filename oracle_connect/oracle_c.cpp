#include "oracle_c.h"
#include <iomanip> 
//���캯��
occiCCTV::occiCCTV(string user, string passwd, string db)
{
	try
	{
		this->env = Environment::createEnvironment();//��������
		this->conn = env->createConnection(user, passwd, db);//��������
	}
	catch (SQLException ex)
	{
		cout << "Error number: " << ex.getErrorCode() << endl;
		cout << ex.getMessage() << endl;
	}

}

//��������
occiCCTV::~occiCCTV()
{
	if (this->env != nullptr)
	{
		this->env->terminateConnection(this->conn);//�ͷ�����
	}
	if (this->env)
	{
		Environment::terminateEnvironment(this->env);//�ͷŻ���
	}
}



//����һ������
void occiCCTV::insertRow(cctv_dist dist,string table_name)
{
	string sqlStmt = "INSERT INTO "+ table_name +" VALUES (:x1, :x2, :x3, :x4 ,:x5,:x6)";
	this->stmt = this->conn->createStatement(sqlStmt);
	try
	{
		this->stmt->setString(1, dist.id);
		this->stmt->setInt(2, dist.video_id);
		this->stmt->setFloat(3, dist.video_time);
		this->stmt->setInt(4, dist.video_frame);
		this->stmt->setDate(5, Todate(dist.create_time));
		//this->stmt->setString(5, dist.create_time);
		this->stmt->setFloat(6, dist.video_position);
		
		unsigned int res = this->stmt->executeUpdate();
		if (res > 0)
		{
			cout << "Data saved successfully ," << res << " �����ݣ�" << endl;
		}
	}
	catch (SQLException ex)
	{
		cout << "Exception thrown for insertRow of CCTVDist" << endl;
		cout << "Error number: " << ex.getErrorCode() << endl;
		cout << ex.getMessage() << endl;
	}
	this->conn->terminateStatement(this->stmt);//�ͷ�SQL���
}

Date occiCCTV::Todate(string strtime)
{
	// ��������ʽ���ַ���"20200607171123"ת��oracle��Ҫ��������ʽ
	try
	{
		int year = stoi((strtime.substr(0, 4)));
		unsigned int month = stoi((strtime.substr(4, 2)));
		unsigned int day = stoi((strtime.substr(6, 2)));
		unsigned int hour = stoi((strtime.substr(8, 2)));
		unsigned int minute = stoi((strtime.substr(10, 2)));
		unsigned int seconds = stoi((strtime.substr(12, 2)));
		Date date(this->env, year, month, day, hour, minute, seconds);
		return date;

	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
		return nullptr;
	}


}

#include "oracle_c.h"
#include <iomanip> 
//构造函数
occiCCTV::occiCCTV(string user, string passwd, string db)
{
	try
	{
		this->env = Environment::createEnvironment();//创建环境
		this->conn = env->createConnection(user, passwd, db);//创建连接
	}
	catch (SQLException ex)
	{
		cout << "Error number: " << ex.getErrorCode() << endl;
		cout << ex.getMessage() << endl;
	}

}

//析构函数
occiCCTV::~occiCCTV()
{
	if (this->env != nullptr)
	{
		this->env->terminateConnection(this->conn);//释放连接
	}
	if (this->env)
	{
		Environment::terminateEnvironment(this->env);//释放环境
	}
}



//插入一行数据
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
			cout << "Data saved successfully ," << res << " 行数据！" << endl;
		}
	}
	catch (SQLException ex)
	{
		cout << "Exception thrown for insertRow of CCTVDist" << endl;
		cout << "Error number: " << ex.getErrorCode() << endl;
		cout << ex.getMessage() << endl;
	}
	this->conn->terminateStatement(this->stmt);//释放SQL语句
}

Date occiCCTV::Todate(string strtime)
{
	// 将这种形式的字符串"20200607171123"转成oracle需要的输入形式
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

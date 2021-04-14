#include <io.h>
#include <direct.h>
#include <string>
#include <iostream>

using namespace std;

void createSingleDir(string prefix)
{
	// �����������ļ���
	
	if (_access(prefix.c_str(), 0) == -1)	//����ļ��в�����
		cout << prefix <<"not exist!" << endl;
		_mkdir(prefix.c_str());				//�򴴽�
}

void createDirectory(std::string path)
{
	// ע�⣺���Խ�������ļ��У��������һ���ļ��к���������'/'������D:/yeyan/vs_project/mkFileDir/1/2/3/
	int len = path.length();
	char tmpDirPath[256] = { 0 };
	for (int i = 0; i < len; i++)
	{
		tmpDirPath[i] = path[i];
		if (tmpDirPath[i] == '\\' || tmpDirPath[i] == '/')
		{
			if (_access(tmpDirPath, 0) == -1)
			{
				int ret = _mkdir(tmpDirPath);
				if (ret == -1) continue;
			}
		}
	}

}

int main() {
	// ��������ļ���
	string path = "D:/yeyan/vs_project/mkFileDir/1/2/3/";
	createDirectory(path);

	// ���������ļ���
	//std::string prefix = "D:/yeyan/vs_project/mkFileDir/1";
	//createSingleDir(prefix);
}

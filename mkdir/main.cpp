#include <io.h>
#include <direct.h>
#include <string>
#include <iostream>

using namespace std;

void createSingleDir(string prefix)
{
	// 仅建立单层文件夹
	
	if (_access(prefix.c_str(), 0) == -1)	//如果文件夹不存在
		cout << prefix <<"not exist!" << endl;
		_mkdir(prefix.c_str());				//则创建
}

void createDirectory(std::string path)
{
	// 注意：可以建立多层文件夹，但是最后一个文件夹后面必须加上'/'，比如D:/yeyan/vs_project/mkFileDir/1/2/3/
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
	// 建立多层文件夹
	string path = "D:/yeyan/vs_project/mkFileDir/1/2/3/";
	createDirectory(path);

	// 建立单层文件夹
	//std::string prefix = "D:/yeyan/vs_project/mkFileDir/1";
	//createSingleDir(prefix);
}

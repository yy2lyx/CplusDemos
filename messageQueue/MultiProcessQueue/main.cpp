#include "timer.h"
#include "consumer.h"
#include<Windows.h>
#include <fstream>
#include <vector>
#include <queue>
#include <iostream>
#include <string>
#include <sstream>
#include <thread>


using namespace std;


ThreadQueue<string> messageQueue;
ThreadQueue<int> idQueue;
mutex print_mtx;
int workers = 3;
int buffer = 0;
ofstream ofs_1, ofs_2, ofs_3;


int switch_case(vector<string> output, int i) {
	int d = i % workers;
	switch (d) {
	case 0:
		ofs_1 << output[i] << endl;
		return 0;
	case 1:
		ofs_2 << output[i] << endl;
		return 1;
	case 2:
		ofs_3 << output[i] << endl;
		return 2;
	}
}

void getVideoFromTxt(string video_path, int wait_seconds, vector<string>* output) {
	// 定时器扫描文档txt
	string s;
	ifstream ifs(video_path, ios::in);
	vector<string> vec;
	while (getline(ifs, s)) vec.push_back(s);

	cout << "TIMER:   output.size : " << output->size() << ",msgQueue.size" << messageQueue.size() << ",buffer:" << buffer << endl;
	if (!vec.empty()) {
		if (!output->empty()) {
			if (vec.back() != output->back()) {
				//cout << "vec.back:" << vec.back() << ",output.back:" << output->back() << ",msgQueue_len:" << messageQueue.size() << endl;
				int stop_index;
				for (int i = 0; i < vec.size(); i++) {
					if (vec[i] == output->back()) stop_index = i;
				}
				// 对队列进行增加处理
				for (int i = stop_index + 1; i < vec.size(); i++) {
					messageQueue.push(vec[i]);
					output->push_back(vec[i]);
					
					idQueue.push(buffer);
					buffer += 1;
				}

				string a = output->back();
				int c = output->size();
				int b = buffer;
				lock_guard<mutex> guard(print_mtx);
				cout << "Add works done!" << endl;
			}
		}
		else
		{
			for (int i = 0; i < vec.size(); i++) {
				messageQueue.push(vec[i]);
				output->push_back(vec[i]);
				idQueue.push(buffer);
				buffer += 1;
			}
			lock_guard<mutex> guard(print_mtx);

		}

	}
	else {
		cout << "No input data!" << endl;
	}
}




//string转换车wstring
std::wstring  StringToWString(const std::string& s)
{
	std::wstring wszStr;

	int nLength = MultiByteToWideChar(CP_ACP, 0, s.c_str(), -1, NULL, NULL);
	wszStr.resize(nLength);
	LPWSTR lpwszStr = new wchar_t[nLength];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), -1, lpwszStr, nLength);
	wszStr = lpwszStr;
	delete[] lpwszStr;
	return wszStr;
}


void gen_multiProcess(int id, string input_txt,string output_txt) {

	STARTUPINFO si;
	si.cb = sizeof(si);
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));
	string cmdLine = "D:/yeyan/vs_project/setTimer/x64/Debug/setTimer.exe " + input_txt + " " + output_txt;
	cout << cmdLine << endl;
	wstring str = StringToWString(cmdLine);

	BOOL bSuccess = CreateProcess(NULL,
		const_cast<LPWSTR>(str.c_str()),
		NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);

	if (bSuccess) {
		//handleOfProcess[id] = pi.hProcess;
		cout << "Process-" << id << "completed!" << endl;
	}
	else {
		cout << "Error:" << id << endl;
	}
}


void consumer(string consumer_id, ofstream* ofs, vector<string>* output)
{
	while (true)
	{
		string message;
		messageQueue.pop(message);
		cout << message << endl;
		{
			lock_guard<mutex> guard(print_mtx);
			
			// 将数据分配到三个文件中
			int id_q;
			idQueue.pop(id_q);
			{
				int txt_i = switch_case(*output, id_q);
				cout << "Big consumer-" << consumer_id << " receive: " << message << ",in txt_id:" << txt_i << ",queu-pop:" << id_q << endl;
			}
			
			*ofs << message << endl;

		}
		Sleep(1000);
	}
}





int main() {
	cout << "Main process start ... " << endl;
	vector<string> output;
	

	// 读取输入文件
	ifstream ifs("video.txt", ios::in);
	ofstream ofs("out.txt", ios::out | ios::app);
	ifstream ifs_out("out.txt", ios::in);

	if (!ifs.is_open())
	{
		cout << "文件打开失败" << endl;
	}
	if (!ifs_out.is_open())
	{
		cout << "文件打开失败" << endl;
	}
	string tmp1, tmp2;
	vector<string> input, tmp_input;
	while (getline(ifs, tmp1)) input.push_back(tmp1);
	while (getline(ifs_out, tmp2)) tmp_input.push_back(tmp2);
	if (input.empty()) {
		cout << "input : video.txt is empty!" << endl;
	}
	else {
		if (tmp_input.empty()) {
			for (int i = 0; i < input.size(); i++) {
				messageQueue.push(input[i]);
				output.push_back(input[i]);
				idQueue.push(buffer);
				buffer += 1;
			}
		}
		else
		{
			// 不相同
			int stop_index;
			for (int i = 0; i < input.size(); i++) {
				output.push_back(input[i]);
				
				if (input[i] == tmp_input.back()) stop_index = i;
			}
			buffer = stop_index+1 ;
			for (int i = stop_index + 1; i < input.size(); i++) {
				messageQueue.push(input[i]);
				idQueue.push(buffer);
				buffer += 1;
			}
		}
	}

	// 将队列中的数据划分为3份（均分），且从队列中出
	ofs_1.open("input_1.txt", ios::out | ios::app);
	ofs_2.open("input_2.txt", ios::out | ios::app);
	ofs_3.open("input_3.txt", ios::out | ios::app);

	// timer扫描
	int wait_sec = 1;
	// 单独启动一个线程持续扫描文件（每5秒）
	string path = "video.txt";
	Timer timer1;
	timer1.start(2000, std::bind(getVideoFromTxt, path, wait_sec, &output));

	// 开启多进程
	for (int i = 0; i < workers; i++) {
		string input_txt = "input_" + to_string(i + 1) + ".txt";
		string output_txt = "output_" + to_string(i + 1) + ".txt";
		gen_multiProcess(i, input_txt, output_txt);
	}

	// 大的ofs开始消费
	consumer("1", &ofs, &output);

	getchar();
	

}
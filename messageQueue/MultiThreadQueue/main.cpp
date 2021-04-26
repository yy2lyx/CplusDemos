#include "timer.h"
#include<Windows.h>
#include <fstream>
#include <vector>
#include <queue>
#include "consumer.h"
#include <iostream>
#include <string>
#include <chrono>
#include <sstream>
#include <thread>
using namespace std;

ThreadQueue<string> messageQueue;
mutex print_mtx;
vector<string> output;
ifstream ifs, ifs_out;


vector<string> stringFromTxt(string path) {
    string s;
    ifstream ifs(path, ios::in);
    vector<string> vec;
    while (getline(ifs, s)) vec.push_back(s);
    return vec;
}


void getVideoFromTxt(string video_path) {
    // ��ʱ��ɨ���ĵ�txt
    vector<string> in = stringFromTxt(video_path);

    cout << "output.size : " << output.size() << ",msgQueue.size" << messageQueue.size() << endl;

    if (!in.empty()) {
        if (!output.empty()) {
            if (in.back() != output.back()) {
                // ���뵽����
                int stop_index;
                for (int i = 0; i < in.size(); i++) {
                    if (in[i] == output.back()) stop_index = i;
                }
                for (int i = stop_index + 1; i < in.size(); i++) {
                    messageQueue.push(in[i]);
                    output.push_back(in[i]);              
                }
                lock_guard<mutex> guard(print_mtx);
            }
        }
        else
        {
            
            // ���뵽����
            for (int i = 0; i < in.size(); i++) {
                messageQueue.push(in[i]);
                output.push_back(in[i]);
            }
            lock_guard<mutex> guard(print_mtx);
            
            
        }
    }
}

vector<string> split(const string& str, const string& pattern)
{
    vector<string> res;
    if (str == "")
        return res;
    //���ַ���ĩβҲ����ָ����������ȡ���һ��
    string strs = str + pattern;
    size_t pos = strs.find(pattern);

    while (pos != strs.npos)
    {
        string temp = strs.substr(0, pos);
        res.push_back(temp);
        //ȥ���ѷָ���ַ���,��ʣ�µ��ַ����н��зָ�
        strs = strs.substr(pos + 1, strs.size());
        pos = strs.find(pattern);
    }

    return res;
}


void consumer(string consumer_id, ofstream* ofs)
{
    while (true)
    {
        string message;
        messageQueue.pop(message);
        {
            lock_guard<mutex> guard(print_mtx);
            cout << "consumer-" << consumer_id << " receive: " << message << endl;
            *ofs << message << endl;
        }
        Sleep(1000);
    }
}


int main(int argc, char* argv[]) {
    string input_txt = argv[1];
    string output_txt = argv[2];
    string consumer_id = split(input_txt, "_")[1];
    consumer_id = split(consumer_id, ".txt")[0];

    cout << "Consumer-" << consumer_id << "Start consume data..." << endl;

    //string input_txt = "video.txt";
    //string output_txt = "out.txt";

    // д���ļ�
    ofstream ofs(output_txt, ios::out | ios::app);
    ifs.open(input_txt, ios::in);
    ifs_out.open(output_txt, ios::in);

    // ��ʼ��
    string tmp1, tmp2;
    vector<string> input, tmp_input;
    while (getline(ifs, tmp1)) input.push_back(tmp1);
    while (getline(ifs_out, tmp2)) tmp_input.push_back(tmp2);
    if (input.empty()) {
        cout << "input is empty!" << endl;
    }
    else {
        if (tmp_input.empty()) {
            for (int i = 0; i < input.size(); i++) {
                messageQueue.push(input[i]);
                output.push_back(input[i]);
            }
        }
        else
        {
            // ����ͬ
            int stop_index;
            for (int i = 0; i < input.size(); i++) {
                output.push_back(input[i]);
                if (input[i] == tmp_input.back()) stop_index = i;
            }
            for (int i = stop_index + 1; i < input.size(); i++) {
                messageQueue.push(input[i]);
                
            }
        }
    }



    // ��������һ���̳߳���ɨ���ļ���ÿ5�룩
    Timer timer;
    timer.start(2000, std::bind(getVideoFromTxt, input_txt));

    consumer(consumer_id, &ofs);

    /* ���߳�
    thread csm1{ consumer, "1",&ofs };
    thread csm2{ consumer, "2",&ofs };
    csm1.join();
    csm2.join();
    */

    getchar();


    return 0;

}


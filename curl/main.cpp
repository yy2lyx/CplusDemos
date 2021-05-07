#include<iostream>
#include<string>
#include<curl\curl.h>
using namespace std;

//�����ļ����ݽ��պ���
size_t dl_req_reply(void* buffer, size_t size, size_t nmemb, void* user_p)
{
	FILE* fp = (FILE*)user_p;
	size_t return_size = fwrite(buffer, size, nmemb, fp);
	//cout << (char *)buffer << endl;
	return return_size;
}

//http GET�����ļ�����  
CURLcode dl_curl_get_req(const std::string& url, std::string filename)
{
	//int len = filename.length();
	//char* file_name = new char(len + 1);//char*�����һ�������ַ�\0
	//strcpy_s(file_name, len + 1, filename.c_str());

	const char* file_name = filename.c_str();
	char* pc = new char[1024];//�㹻��
	strcpy(pc, file_name);

	FILE* fp = fopen(pc, "wb");

	//curl��ʼ��  
	CURL* curl = curl_easy_init();
	// curl����ֵ 
	CURLcode res;
	if (curl)
	{
		//����curl������ͷ
		struct curl_slist* header_list = NULL;
		//header_list = curl_slist_append(header_list, "User-Agent: Mozilla/5.0 (Windows NT 10.0; WOW64; Trident/7.0; rv:11.0) like Gecko");
		header_list = curl_slist_append(header_list, "User-Agent: Mozilla/5.0 (Windows NT 10.0; WOW64; Trident/7.0; rv:11.0) like Gecko");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header_list);

		//��������Ӧͷ����0���������� 1��������
		curl_easy_setopt(curl, CURLOPT_HEADER, 0);

		//���������URL��ַ 
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

		//����ssl��֤
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);

		//CURLOPT_VERBOSE��ֵΪ1ʱ������ʾ��ϸ�ĵ�����Ϣ
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 0);

		curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);

		//�������ݽ��պ���
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &dl_req_reply);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

		curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);

		//���ó�ʱʱ��
		curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 60); // set transport and time out time  
		curl_easy_setopt(curl, CURLOPT_TIMEOUT, 60);

		// ��������  
		res = curl_easy_perform(curl);
	}
	// �ͷ�curl 
	curl_easy_cleanup(curl);
	//�ͷ��ļ���Դ
	fclose(fp);

	return res;
}
int main()
{
	//string dl_get_url = "http://192.168.10.242:7777/proxy9090/api/v1/files/download?id=2021036348391623416&preview=false";
	string dl_get_url = "localhost:9091/api/v1/files/download?id=asdfa&preview=false";
	
	string filename = "videos/1.mp4";
	dl_curl_get_req(dl_get_url, filename);

	cout << "������ɣ�" << endl;
	//getchar();
	return 0;
}


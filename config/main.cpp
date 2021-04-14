#include "configIni.h"
#include <string>


int main(){
	const char ConfigFile[] = "conf.ini";
    ConfigIni configSettings(ConfigFile);
	string mq_ip = configSettings.Read("mq_ip", mq_ip);
    int mq_port = configSettings.Read("mq_port", mq_port);
	
}
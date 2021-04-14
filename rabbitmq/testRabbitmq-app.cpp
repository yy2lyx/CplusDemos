#include "SimpleAmqpClient/SimpleAmqpClient.h"
#include <iostream>
#include <string>

std::string queue_name = "video_send3";
std::string exchange_name = "exchange_test3";



using namespace std;

void TestSend() {
    AmqpClient::Channel::ptr_t channel = AmqpClient::Channel::Create("localhost", 5672, "yy", "yy");

    //channel->DeclareQueue(queue_name, false, true, false, false);
    channel->DeclareExchange(exchange_name,AmqpClient::Channel::EXCHANGE_TYPE_TOPIC);
    //channel->BindQueue(queue_name, exchange_name, "");

    vector<string> video_path = {
        "2,D:/yeyan/CCTV/feilonglu/11.13/W24788_W24790（WG23820）.mp4",
        "3,D:/yeyan/CCTV/feilonglu/11.13/W24788_W24791(WG23818).mp4",
        "4,D:/yeyan/CCTV/feilonglu/11.13/W24791_W24792(WG23821).mp4",
        "5,D:/yeyan/CCTV/feilonglu/11.13/W24792_W24794(WG23822).mp4",
        "6,D:/yeyan/CCTV/feilonglu/11.13/W24795_W24794(WG23824).mp4",
        "7,D:/yeyan/CCTV/feilonglu/11.13/W24795_W24796(WG23825).mp4",
        "8,D:/yeyan/CCTV/feilonglu/11.13/W24797_W24796(WG23826).mp4",
        "9,D:/yeyan/CCTV/feilonglu/11.13/W24801_W24797(WG23827).mp4"
    };

    for (int i = 0; i < video_path.size(); i++) {
        channel->BasicPublish(exchange_name, "", AmqpClient::BasicMessage::Create(video_path[i]));
        std::cout << "[x] send " << video_path[i] << std::endl;
    }
}


int main() {
    TestSend();

    return 0;
}
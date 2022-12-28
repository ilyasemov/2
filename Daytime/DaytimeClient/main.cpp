#include <netinet/in.h>
#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;
//Алгоритм работы сетевого клиента: Подготовить адреснуые структуры(свою и удаленного сервера) формата IPv4, создать сокет для IPv4, привязать сокет к своему адресу,
//установить соединение с сервером, выполнить информационный обмен, закрыть сокет
int main() {
struct sockaddr_in {
 short sin_family;
 unsigned short sin_port;
 struct in_addr sin_addr;
 char sin_zero[8];
};
struct in_addr {
 unsigned long s_addr;
};
//Создание сокета IPv4
int s = socket(AF_INET, SOCK_DGRAM, 0); // UDP
if(s == -1) {
    cout << "Socket error\n";
    return 1;
}

 //Подготовка структуры с адресом клиента
sockaddr_in * self_addr = new (sockaddr_in);
self_addr->sin_family = AF_INET; // интернет протокол IPv4
self_addr->sin_port = htons(44214); // Порт
self_addr->sin_addr.s_addr = inet_addr("127.0.0.1"); //Адрес сети

 //Подготовка структуры с адресом сервера
sockaddr_in * srv_addr = new (sockaddr_in);
srv_addr->sin_family = AF_INET; // интернет протокол IPv4
srv_addr->sin_port = htons(44214); //Порт
srv_addr->sin_addr.s_addr = inet_addr("127.0.0.1"); //Адрес сети

//Установка соединения с сервером
int rc = connect(s,(const sockaddr*)srv_addr, sizeof(sockaddr_in));
if (rc == -1) { //Проверка
    cout << "Error: failed connect to server.\n";
    return 1;
}
else {
    //Выполнение информационного обмена
    //Передача данных
    cout << "We are connect to server!\n";
    char connection_msg[50] = "Hello, it's client!";
    send(s, connection_msg, sizeof(connection_msg), 0);
    char daytime[50];
    recv(s, daytime, sizeof(daytime), 0); //Принятие ответа
    cout << "Daytime from server: " << daytime << endl;
    cout << "Session close!" << endl;
    close(s);
    return 0;
}
}

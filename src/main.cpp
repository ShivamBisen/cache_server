#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <thread>
#include <netinet/in.h>
#include <unistd.h>
#include "../include/LRUCache.hpp"

using namespace std;

void handleClient(int clientSocket, LRUCache& cache){
    char buffer[1024];
    while(true){
        memset(buffer,0,sizeof(buffer));
        int bytes = read(clientSocket, buffer, sizeof(buffer));
        if(bytes <= 0){
            break;
        }
        stringstream ss(buffer);
        string cmd,key,value;
        int ttl = 60;
        ss >> cmd >> key;

        if(cmd == "SET"){
            ss >> value >> ttl;
            cache.set(key, value, ttl);
            string response = "STORED\n";
            send(clientSocket, response.c_str(), response.size(), 0);
        }else if(cmd == "GET"){
            string result = cache.get(key) + "\n";
            send(clientSocket, result.c_str(), result.size(), 0);
        }else if(cmd == "DELETE"){
            cache.remove(key);
            string response = "DELETED\n";
            send(clientSocket, response.c_str(), response.size(), 0);
        }else{
            string response = "ERROR: Unknown command\n";
            send(clientSocket, response.c_str(), response.size(), 0);
        }

    }
    close(clientSocket);
}
int main(){
    const int PORT = 8080;
    LRUCache cache(100);

    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    listen(serverSocket, 5);
    cout << "Server is running on port " << PORT << endl;
    while(true){
        sockaddr_in clientAddr{};
        socklen_t addrLen = sizeof(clientAddr);
        int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &addrLen);
        thread t(handleClient, clientSocket, ref(cache));
        t.detach(); // Detach the thread to handle multiple clients
        cout << "Client connected" << endl;
    }
    
    return 0;
}
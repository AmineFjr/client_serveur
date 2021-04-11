#include <iostream>
#include <thread>

#include <sys/time.h>
#include "socket.h"

using namespace std;
using namespace stdsock;

void worker(StreamSocket* client) {
    std::cout << "Got a client!" << std::endl;

    std::cout << client->getIP() << ":" << client->getPort() << std::endl;

    char* dateString; // Chaine de caractere contenant la date
    struct timeval time_value;
    gettimeofday(&time_value, NULL);
    dateString = ctime(&(time_value.tv_sec));

    client->send(dateString,strlen(dateString),0);
    cout << "Server: \t"<< dateString << endl;

    sleep(5);
  
    string Hello = "HELO";
    string welcome = "WELCOME"; 
    string menuStart = "TAP MENU TO SEE MENU";
    string cardStart = "TAP START TO START THE GAME";
    string card = "CARD" ;
    string quit = "QUIT";
    string menu = "MENU";
    string start = "START";
    string help = "HELP";
    string clear = "CLEAR"; 


    client->send(Hello);
    client->send(welcome);
    client->send(menuStart);
    client->send(cardStart);
    client->send(card);
    client->send(quit);
    client->send(menu);
    client->send(start);
    client->send(help);
    client->send(clear);


    string msg ; 
    
    int nb=client->read(msg);



    if(nb < 0){
            printf("[-]Error in receiving data.\n");
    }else{
            cout << "Server: \t"<< Hello << " " << msg <<  endl;
    }


    string number,carte ; 
    



    while(true){

        int num =client->read(number);
        char dernierElement = number.back();

        if(num < 0){
                printf("[-]Error in receiving data.\n");
        }else{
                cout << "Client: \t"<< dernierElement <<  endl;
        }
        cout << "CHOOSE CARD : "; 
        cin >> carte ; 
        client->send(carte);
    }





//    while (true) {
//        std::string msg;
//        if (client->read(msg) <= 0) {
//            break;
//        }

//        std::cout << msg;
//    }



    delete client;
    std::cout << "Client disconnected" << std::endl;
}


int main()
{
    ConnectionPoint *server=new ConnectionPoint(3490);

    int err= server->init();
    std::cout << server->getIP() << ":" << server->getPort() << std::endl;
    if (err != 0) {
        std::cout << strerror(err) << std::endl;
        exit(err);
    }

    while (true) {
        StreamSocket* client = server->accept();

        if (!client->valid()) {
            delete client;
            continue;
        }

        std::thread (worker, client).detach();
    }



    delete server;
    return 0;
}
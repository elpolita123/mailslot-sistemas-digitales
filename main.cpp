#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <tchar.h>
#include "factory.h"
#include "client.h"
#include "server.h"
#include "timer.h"
#define IID_server 1
#define IID_client 2
int main(int argc, char** argv) {
    IObject* client = create(2)
    Imailslotserver* server = create(1);
    while (client->sendmessage() == true) {
    }
    release(client);
    release(server);
    return 0;
}

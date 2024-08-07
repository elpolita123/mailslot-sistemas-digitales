#pragma once
#include "common.h"
#include "server.h"
#include "client.h"

#define IID_SERVER 1
#define IID_CLIENT 2
#define interval 5000

IObject* create(int type) {
    IObject* result = nullptr;
    switch (type) {
        case IID_SERVER:
            result = new MailslotServer(interval);
            break;
        case IID_CLIENT:
            result = new MailslotClient();
            break;
        default:
            break;
    }
    return result;
}
void release(IObject* obj) {
    delete obj;
}
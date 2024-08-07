#pragma once
#include <iostream>
#include <windows.h>
#include <string.h>
#include "timer.h"
#define interface struct
#define extend public
#define specialize public

interface Imailslotserver {
    virtual bool ismessagewaiting(void) = 0;
};

class Mailslotserver : extend Imailslotserver {
public:
    Mailslotserver(unsigned interval) : timer_(new Timer(new ConsoleTimedAction(this))) {
        create();
        timer_->start(interval);
    }

    virtual ~Mailslotserver() {
        close();
        timer_->stop();
        delete timer_;
    }

    virtual bool ismessagewaiting() {
        DWORD messageCount;
        GetMailslotInfoWrapper(NULL, NULL, &messageCount, NULL);
        for (DWORD i = 0; i < messageCount; ++i) {
            readmessage();
        }
        return true;
    }

private:
    LPCSTR lpName = "\\\\.\\mailslot\\ejemplo_mailslot";
    HANDLE hMailslot = NULL;
    Timer* timer_;

    virtual bool create() {
        hMailslot = CreateMailslot(lpName, 0, MAILSLOT_WAIT_FOREVER, NULL);
        std::cout << (hMailslot != INVALID_HANDLE_VALUE ? "Mailslot created successfully\n" : "Fail creating the mailslot\n");
        if (hMailslot == INVALID_HANDLE_VALUE) {
            std::cerr << "Exiting...\n";
            exit(0);
        }
        return hMailslot != INVALID_HANDLE_VALUE;
    }

    virtual bool close() {
        CloseHandle(hMailslot);
        std::cout << "Mailslot closed\n";
        return true;
    }

    bool GetMailslotInfoWrapper(DWORD* lpMaxMessageSize, DWORD* lpNextSize, DWORD* lpMessageCount, DWORD* lpReadTimeout) {
        return GetMailslotInfo(hMailslot, lpMaxMessageSize, lpNextSize, lpMessageCount, lpReadTimeout);
    }

    virtual bool readmessage() {
        char message[1024];
        DWORD bytesRead;
        DWORD messageSize = sizeof(message);
        if (ReadFile(hMailslot, message, messageSize, &bytesRead, NULL)) {
            message[bytesRead] = '\0';
            printMessage(message);
            return true;
        } else {
            std::cerr << "Error reading message. Error code: " << GetLastError() << std::endl;
            return false;
        }
    }

    bool printMessage(const char* message) {
        std::cout << "\nNew Message: " << message << std::endl;
        return true;
    }

    Mailslotserver(const Mailslotserver&) = delete;
    Mailslotserver& operator=(const Mailslotserver&) = delete;
};

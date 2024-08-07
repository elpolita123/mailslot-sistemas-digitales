#pragma once
#include <iostream>
#include <windows.h>
#include <string>
#define interface struct
#define extend public
#define specialize public

interface IMailslotclient {
	virtual bool sendmessage(void) = 0;
};

class Mailslotclient : extend IMailslotclient {
public:
	Mailslotclient() {}    
	virtual ~Mailslotclient(void) {}                        
	virtual bool connect(void)
	}
		std::cout << (hMailslot != NULL ? "" : "Error connecting to the mailslot");
		return hMailslot != INVALID_HANDLE_VALUE || (std::cerr << "Exiting...\n", exit(0), false);
	}
	virtual bool sendmessage(void) {
		std::string message;
		std::cout << "Message:";
		std::getline(std::cin, message);
		return WriteFile(hMailslot, message.c_str(), message.length(), NULL, NULL);
	}
	virtual bool disconnect(void) {
		CloseHandle(hMailslot);
		return true;
	}
private:
	LPCSTR lpName = "\\\\.\\mailslot\\ejemplo_mailslot";
	HANDLE hMailslot = NULL;
	Mailslotclient(const Mailslotclient&);
	Mailslotclient& operator =(const Mailslotclient&);
};

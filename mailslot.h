#pragma once
#include "server.h"
#include "client.h"
#define interface struct
#define implements public
interface IMailslot: implements Imailslotserver, implements IMailslotclient{
	virtual bool sendmessage(void) = 0;
}
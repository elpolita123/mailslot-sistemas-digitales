#pragma once
#include <iostream>
#include <windows.h>
#include <string.h>
#include "server.h"
#define interface struct
#define extend public

interface IAttachment {
    // Interfaz IAttachment
};

interface ITimedAction {
    virtual void execute() = 0;
};

class ConsoleTimedAction : extend ITimedAction {
public:
   ConsoleTimedAction (Imailslotserver* server){
   	mailslotserver = server;
   }
   virtual ~ConsoleTimedAction() {}

    virtual void execute(){
    mailslotserver->ismessagewaiting();
    }

private:
	ConsoleTimedAction(const ConsoleTimedAction&) = delete;
    ConsoleTimedAction& operator=(const ConsoleTimedAction&) = delete;
    Imailslotserver* mailslotserver = NULL;
};

interface ITimer {
    virtual bool start(unsigned interval) = 0;
    virtual bool change(unsigned interval, unsigned dueTime) = 0;
    virtual void stop() = 0;

};
class Timer :extend ITimer{
public:
    Timer(ITimedAction* action) : action_(action), timerQueue_(NULL) {}
    Timer() {}
    ~Timer() {
    }

    virtual bool start(unsigned interval) {
        DWORD flags = WT_EXECUTEINTIMERTHREAD;
        CreateTimerQueueTimer(&timerHandle_, NULL, TimerCallback, this, interval, interval, flags);
        return true;
    }

    virtual bool change(unsigned interval, unsigned dueTime) {
        ChangeTimerQueueTimer(timerQueue_, timerHandle_, dueTime, interval);
        return true;
    }

    virtual void stop() {
       DeleteTimerQueueTimer(timerQueue_,timerQueue_, NULL);
       CloseHandle(timerQueue_);
    }

private:
    ITimedAction* action_;
    HANDLE timerQueue_;
    HANDLE timerHandle_;
	Timer(const Timer&) = delete;
    Timer& operator=(const Timer&) = delete;
    static void CALLBACK TimerCallback(PVOID lpParameter, BOOLEAN TimerOrWaitFired) {
        Timer* timer = static_cast<Timer*>(lpParameter);
        timer->action_->execute();
    }
};

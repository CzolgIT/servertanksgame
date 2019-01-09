#ifndef Timer_h
#define Timer_h

#include "Main.h"

//The application time based timer
class Timer
{
public:
    //Initializes variables
    Timer();

    //The various clock actions
    void start();
    void stop();
    void pause();
    void unpause();

    //Gets the timer's time
    Uint32 getTicks();

    //Checks the status of the timer
    bool isStarted();
    bool isPaused();

    float getStepTime();
    float getFps();
    void update();

private:
    //The clock time when the timer started
    Uint32 mStartTicks;

    //The ticks stored when the timer was paused
    Uint32 mPausedTicks;

    //The timer status
    bool mPaused;
    bool mStarted;

    // tanksgame
    float stepTime;
    float fps;
    int count;
    float second;

};

#endif /* Timer_h */

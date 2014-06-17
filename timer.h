/*
 *  timer.h
 *  SDL Poker
 *
 *  Created by Chris McKnight on 4/13/10.
 *  Copyright 2010 Chris McKnight. All rights reserved.
 *
 */

#ifndef __TIMER_H__
#define __TIMER_H__

class Timer
{
    private:
        //The clock time when the timer started
        int startTicks;
        
        //The ticks stored when the timer was paused
        int pausedTicks;
        
        //The timer status
        bool paused;
        bool started;
        
    public:
        //Initializes variables
        Timer();
        
        //The various clock actions
        void start();
        void stop();
        void pause();
        void unpause();
        
        //Get the number of ticks since the timer started
        //or gets the number of ticks when the timer was paused
        int get_ticks();
        
        //Checks the status of the timer
        bool is_started();
        bool is_paused();
};

#endif

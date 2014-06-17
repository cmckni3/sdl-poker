/*
 *  player.h
 *  SDL Poker
 *
 *  Created by Chris McKnight on 4/13/10.
 *  Copyright 2010 Chris McKnight. All rights reserved.
 *
 */

#ifndef __PLAYER_H__
#define __PLAYER_H__

class Player
{
    public:
        Player();
    private:
        char* hand[5];
};

#endif
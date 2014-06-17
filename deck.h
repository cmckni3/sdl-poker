/*
 *  deck.h
 *  SDL Poker
 *
 *  Created by Chris McKnight on 4/13/10.
 *  Copyright 2010 Chris McKnight. All rights reserved.
 *
 */

extern char *deck_of_cards[];
extern char *deck_of_cards2[];

#ifndef __DECK_H__
#define __DECK_H__

class Deck
{
    public:
        Deck(char *arrayOfCardsarg[]);
        void swap(int subscript1, int subscript2);
        int randRange(int minimum, int maximum);
        void shuffle(int arraysize, int shufflenumber);
        void showCards(char *arrayOfCardsarg[], int arraysize);
        int cardVal(char *card);
        int highCard(char *arrayOfCardsarg[], int arraysize);
        int cardImage(char *card);
        bool OnePair(char *arrayOfCardsarg[], int arraysize);
        bool TwoPair(char *arrayOfCardsarg[], int arraysize);
        bool Threeofakind(char *arrayOfCardsarg[], int arraysize);
        bool Fourofakind(char *arrayOfCardsarg[], int arraysize);
        bool StraightFlush(char *arrayOfCardsarg[], int arraysize);
        bool Fullhouse(char *arrayOfCardsarg[], int arraysize);
        bool Royalflush(char *arrayOfCardsarg[], int arraysize);
        bool isFlush(char *arrayOfCardsarg[], int arraysize);
        int *sortInt(int myA[], bool descSort);
        bool isStraight(char *arrayOfCardsarg[], int arraysize);
};

#endif

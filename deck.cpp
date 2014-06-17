/*
 *  deck.cpp
 *  SDL Poker
 *
 *  Created by Chris McKnight on 4/13/10.
 *  Copyright 2010 Chris McKnight. All rights reserved.
 *
 */

#include "deck.h"
#include <iostream>

char *deck_of_cards[] =
{
    "2C", "3C", "4C", "5C", "6C", "7C", "8C", "9C",
    "TC", "JC", "QC", "KC", "AC", "2D", "3D", "4D",
    "5D", "6D", "7D", "8D", "9D", "TD", "JD", "QD",
    "KD", "AD", "2H", "3H", "4H", "5H", "6H", "7H",
    "8H", "9H", "TH", "JH", "QH", "KH", "AH", "2S",
    "3S", "4S", "5S", "6S", "7S", "8S", "9S", "TS",
    "JS", "QS", "KS", "AS"
};

char *deck_of_cards2[] =
{
    "2C", "3C", "4C", "5C", "6C", "7C", "8C", "9C",
    "TC", "JC", "QC", "KC", "AC", "2D", "3D", "4D",
    "5D", "6D", "7D", "8D", "9D", "TD", "JD", "QD",
    "KD", "AD", "2H", "3H", "4H", "5H", "6H", "7H",
    "8H", "9H", "TH", "JH", "QH", "KH", "AH", "2S",
    "3S", "4S", "5S", "6S", "7S", "8S", "9S", "TS",
    "JS", "QS", "KS", "AS"
};

/*
    Class constructor
*/
Deck::Deck(char *arrayOfCardsarg[])
{
}

/*
    Declare and creating card shuffle method
*/
void Deck::swap(int subscript1, int subscript2)
{
  char *temp; //Declaring a temporary varible for card shuffle method
  temp = deck_of_cards2[subscript1];
  deck_of_cards2[subscript1] = deck_of_cards2[subscript2];
  deck_of_cards2[subscript2] = temp;
}

/*
    Creates unique random numbers from 0 to 51 for swapping array elements.
*/
int Deck::randRange(int minimum, int maximum)
{
  int random;
  random = (rand() % maximum) + minimum;
  return random;
}

/*
    Calls swap and randRange then swaps elements, 
    and continues while loop number.
*/
void Deck::shuffle(int arraysize, int shufflenumber)
{
  int count = 0;
  int count2 = 26;
  int x;
  int y;
  int number = 0;
  while (number != shufflenumber)
  {
    while ((count < 25) && (count2 < 51))
    {
      x = randRange(0, 51);
      y = randRange(0, 51);
      swap(x, y);
      count++;
      count2++;
    }
    if ((count == 25) && (count2 == 51))
    {
      x = randRange(0, 51);
      y = randRange(0, 51);
      swap(x, y);
    }
    number++;
  }
}

/*
    Output cards and formatting output
*/
void Deck::showCards(char *arrayOfCardsarg[], int arraysize)
{
  int index;
  for (index = 0; index < arraysize - 1; index++)
  {
    printf("%s", arrayOfCardsarg[index]);
    printf(", ");
  }
  if (index == arraysize - 1)
  {
    printf("%s", arrayOfCardsarg[index]);
  }
}

/* 
    Returns value of card i.e. AD = 11, KD = 10, 
    face cards = value of face card
*/
int Deck::cardVal(char *card)
{
  char firstCharacter = card[0];
  int value = 0;
  if (firstCharacter == 'A')
  {
    value = 14;
  }
  else if (firstCharacter == 'K')
  {
    value = 13;
  }
  else if (firstCharacter == 'Q')
  {
    value = 12;
  }
  else if (firstCharacter == 'J')
  {
    value = 11;
  }
  else if (firstCharacter == 'T')
  {
    value = 10;
  }
  else if (firstCharacter == '9')
  {
    value = 9;
  }
  else if (firstCharacter == '8')
  {
    value = 8;
  }
  else if (firstCharacter == '7')
  {
    value = 7;
  }
  else if (firstCharacter == '6')
  {
    value = 6;
  }
  else if (firstCharacter == '5')
  {
    value = 5;
  }
  else if (firstCharacter == '4')
  {
    value = 4;
  }
  else if (firstCharacter == '3')
  {
    value = 3;
  }
  else if (firstCharacter == '2')
  {
    value = 2;
  }
  return value;
}

/*
    Return subscript of highest value card
*/
int Deck::highCard(char *arrayOfCardsarg[], int arraysize)
{
  int index;
  int max = 0;
  int subscript[arraysize];
  for (index = 0; index < arraysize; index++)
  {
    subscript[index] = cardVal(arrayOfCardsarg[index]);
  }
  for (index = 0; index < arraysize; index++)
  {
    if (subscript[index] > subscript[max])
    {
      max = index;
    }
  }
  return max;
}

/*
    Returns card image index to load card image
*/
int Deck::cardImage(char *card)
{
  int index = 0;
  std::string cardGraphics[] =
  {
    "card_graphics/2_clubs.gif", "card_graphics/3_clubs.gif", 
    "card_graphics/4_clubs.gif", "card_graphics/5_clubs.gif",
    "card_graphics/6_clubs.gif", "card_graphics/7_clubs.gif",
    "card_graphics/8_clubs.gif", "card_graphics/9_clubs.gif",
    "card_graphics/10_clubs.gif", "card_graphics/jack_clubs.gif",
    "card_graphics/queen_clubs.gif", "card_graphics/king_clubs.gif",
    "card_graphics/ace_clubs.gif", "card_graphics/2_spades.gif",
    "card_graphics/3_spades.gif", "card_graphics/4_spades.gif",
    "card_graphics/5_spades.gif", "card_graphics/6_spades.gif",
    "card_graphics/7_spades.gif", "card_graphics/8_spades.gif",
    "card_graphics/9_spades.gif", "card_graphics/10_spades.gif",
    "card_graphics/jack_spades.gif", "card_graphics/queen_spades.gif",
    "card_graphics/king_spades.gif", "card_graphics/ace_spades.gif",
    "card_graphics/2_diamonds.gif", "card_graphics/3_diamonds.gif",
    "card_graphics/4_diamonds.gif", "card_graphics/5_diamonds.gif",
    "card_graphics/6_diamonds.gif", "card_graphics/7_diamonds.gif",
    "card_graphics/8_diamonds.gif", "card_graphics/9_diamonds.gif",
    "card_graphics/10_diamonds.gif", "card_graphics/jack_diamonds.gif",
    "card_graphics/queen_diamonds.gif", "card_graphics/king_diamonds.gif",
    "card_graphics/ace_diamonds.gif", "card_graphics/2_hearts.gif",
    "card_graphics/3_hearts.gif", "card_graphics/4_hearts.gif",
    "card_graphics/5_hearts.gif", "card_graphics/6_hearts.gif",
    "card_graphics/7_hearts.gif", "card_graphics/8_hearts.gif",
    "card_graphics/9_hearts.gif", "card_graphics/10_hearts.gif",
    "card_graphics/jack_hearts.gif", "card_graphics/queen_hearts.gif",
    "card_graphics/king_hearts.gif", "card_graphics/ace_hearts.gif",
  };
  //char* cardimage = cardGraphics[0];
  int cardimageindex = 0;
  for (index = 0; index < 52; index++)
  {
    int underscore;
    std::string s = cardGraphics[index];
    underscore = s.rfind("_", s.length());
    char firstCharacter = card[0];
    char secondCharacter = card[1];
    char firstGraphicCharacter = toupper(cardGraphics[index][14]);
    char secondGraphicCharacter = toupper(cardGraphics[index][underscore + 1]);
    if (firstCharacter == 'T')
    {
      firstCharacter = '1';
    }
    if ((firstCharacter == firstGraphicCharacter) && (secondCharacter ==
      secondGraphicCharacter))
    {
      cardimageindex = index;
    }
  }
  return cardimageindex;
}

bool Deck::OnePair(char *arrayOfCardsarg[], int arraysize)
{
	bool value = false;
	int pairs = 0;
	char firstCharacter,
		 //secondCharacter,
		 firstCharacter2;
		 //secondCharacter2;
	
	for (int index = 0; index < arraysize; index++)
	{
		firstCharacter = arrayOfCardsarg[index][0];
		for (int index2 = index+1; index2 < arraysize; index2++)
		{
			firstCharacter2 = arrayOfCardsarg[index2][0];
			if (firstCharacter == firstCharacter2)
				pairs++;
		}
	}
	if (pairs == 1)
		value = true;
	return value;
}

bool Deck::TwoPair(char *arrayOfCardsarg[], int arraysize)
{
	bool value = false;
	int pairs = 0;
	char firstCharacter,
		 firstCharacter2;
	
	for (int index = 0; index < arraysize; index++)
	{
		firstCharacter = arrayOfCardsarg[index][0];
		for (int index2 = index+1; index2 < arraysize; index2++)
		{
			firstCharacter2 = arrayOfCardsarg[index2][0];
			if (firstCharacter == firstCharacter2)
				pairs++;
		}
	}
	if (pairs == 2)
		value = true;
	return value;
}

bool Deck::Threeofakind(char *arrayOfCardsarg[], int arraysize)
{
	bool value = false;
	int numcards[13];
	
	for (int index = 0; index < 13; index++)
	{
		numcards[index] = 0;
	}
	
	for (int index = 0; index < arraysize; index++)
	{
		numcards[cardVal(arrayOfCardsarg[index])-2]++;
	}
	
	for (int index = 0; index < 13; index++)
	{
		if (numcards[index] == 3)
			value = true;
	}
	
	return value;
}

bool Deck::Fourofakind(char *arrayOfCardsarg[], int arraysize)
{
	bool value = false;
	int numcards[13];
	
	for (int index = 0; index < 13; index++)
	{
		numcards[index] = 0;
	}
	
	for (int index = 0; index < arraysize; index++)
	{
		numcards[cardVal(arrayOfCardsarg[index])-2]++;
	}
	
	for (int index = 0; index < 13; index++)
	{
		if (numcards[index] == 4)
			value = true;
	}
	
	return value;
}

bool Deck::StraightFlush(char *arrayOfCardsarg[], int arraysize)
{
	bool value = false;
	
	if (isFlush(arrayOfCardsarg, arraysize) && 
		isStraight(arrayOfCardsarg, arraysize))
		value = true;
	
	return value;
}

bool Deck::Fullhouse(char *arrayOfCardsarg[], int arraysize)
{
	bool value = false;
	
	if (Threeofakind(arrayOfCardsarg, arraysize) &&
		OnePair(arrayOfCardsarg, arraysize))
		value = true;
	
	return value;
}

bool Deck::Royalflush(char *arrayOfCardsarg[], int arraysize)
{
	bool value = false;
	int numcards[13];
	
	for (int index = 0; index < 13; index++)
	{
		numcards[index] = 0;
	}
	
	for (int index = 0; index < arraysize; index++)
	{
		numcards[cardVal(arrayOfCardsarg[index])-2]++;
	}
	
	int sum = 0;
	printf("\n");
	for (int index = 8; index < 13; index++)
	{
		if (numcards[index] == 1)
			sum = sum + numcards[index];
	}
	
	if (sum == 5 && isFlush(arrayOfCardsarg, arraysize))
		value = true;
	
	return value;
}

/*
    Determines if hand is flush ie. same suit
*/
bool Deck::isFlush(char *arrayOfCardsarg[], int arraysize)
{
  int numberOfSpades = 0;
  int numberOfClubs = 0;
  int numberOfHearts = 0;
  int numberOfDiamonds = 0;
  bool value = false;
  char secondCharacter;
  for (int index = 0; index < arraysize; index++)
  {
    secondCharacter = arrayOfCardsarg[index][1];
    if (secondCharacter == 'S')
    {
      numberOfSpades++;
    }
    else if (secondCharacter == 'C')
    {
      numberOfClubs++;
    }
    else if (secondCharacter == 'H')
    {
      numberOfHearts++;
    }
    else if (secondCharacter == 'D')
    {
      numberOfDiamonds++;
    }
  }
  if ((numberOfSpades == arraysize) || (numberOfClubs == arraysize) || 
    (numberOfHearts == arraysize) || (numberOfDiamonds == arraysize))
  {
    value = true;
  }
  return value;
}

/*
    Sorts integer arrays
*/
int * Deck::sortInt(int myA[], bool descSort)
{
  int order;
  int tmp;
  if (!descSort)
    order = 0;
  else
    order = 1;
  for (int i = 0; i < sizeof(myA); i++)
  {

    for (int j = i; j < sizeof(myA); j++)
    {
      switch (order)
      {
        case 0:
          if (myA[i] > myA[j])
          {
            tmp = myA[j];
            myA[j] = myA[i];
            myA[i] = tmp;
          }
          break;

        case 1:


          if (myA[i] < myA[j])
          {
            tmp = myA[i];
            myA[i] = myA[j];
            myA[j] = tmp;
          }
          break;
      }
    }

  }
  return myA;

}


// isStraight doesn't work
/*
   Determines if hand is a straight ie. 9, 10, J, Q, K 
*/
bool Deck::isStraight(char *arrayOfCardsarg[], int arraysize)
{
  bool value = false;
  int number = 0;
  int index;
  int max = 0;
  int subscript[arraysize];
  int *newsub;
  for (index = 0; index < arraysize; index++)
  {
    subscript[index] = cardVal(arrayOfCardsarg[index]);
  }
  newsub = sortInt(subscript, true);
  max = 1;
  for (index = 0; index < arraysize; index++)
  {
    if (index == arraysize - 1){}
    else
    {
      if (newsub[index] - 1 == newsub[max])
      {
        max++;
        number++;
      }
    }
  }
  if (number == arraysize - 1)
  {
    value = true;
  }
  return value;
}

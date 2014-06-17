/*
 *  main.cpp
 *  SDL Poker
 *
 *  Created by Chris McKnight on 4/13/10.
 *  Copyright 2010 Chris McKnight. All rights reserved.
 *
 */

// TODO: Display all card images which requires card images to be resized
// TODO: Add betting and scoring
// TODO: Finish moving code out of main into the Deck class
// TODO: Move code related to card data into a Card class
// TODO: Game menu
// TODO: Game UI (buttons, inputs, etc)

// The headers
#include <stdio.h>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "deck.h"
#include "timer.h"
#include <math.h>

// Screen attributes
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

// The frames per second
const int FRAMES_PER_SECOND = 10;

// The surfaces
SDL_Surface *foo = NULL;
SDL_Surface *screen = NULL;
SDL_Surface *message = NULL;
SDL_Surface *background = NULL;
SDL_Surface *cardgraphic[52];

// The font
TTF_Font *font = NULL;

// Colors
SDL_Color black = 
{
  0, 0, 0
};
SDL_Color white = 
{
  255, 255, 255
};

// The event structure
SDL_Event event;

// Check to see if game already ran once
bool complete = false;

SDL_Surface *load_image(std::string filename)
{
  // The image that's loaded
  SDL_Surface *loadedImage = NULL;

  // The optimized surface that will be used
  SDL_Surface *optimizedImage = NULL;

  // Load the image
  loadedImage = IMG_Load(filename.c_str());

  // If the image loaded
  if (loadedImage != NULL)
  {
    // Create an optimized surface
    optimizedImage = SDL_DisplayFormat(loadedImage);

    // Free the old surface
    SDL_FreeSurface(loadedImage);

    // If the surface was optimized
    if (optimizedImage != NULL)
    {
      // Color key surface
      SDL_SetColorKey(optimizedImage, SDL_RLEACCEL | SDL_SRCCOLORKEY,
        SDL_MapRGB(optimizedImage->format, 0, 0xFF, 0xFF));
    }
  }

  // Return the optimized surface
  return optimizedImage;
}

void apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *destination,
  SDL_Rect *clip = NULL)
{
  // Holds offsets
  SDL_Rect offset;

  // Get offsets
  offset.x = x;
  offset.y = y;

  // Blit
  SDL_BlitSurface(source, clip, destination, &offset);
}

bool init()
{
  // Initialize all SDL subsystems
  if (SDL_Init(SDL_INIT_EVERYTHING) ==  - 1)
  {
    return false;
  }

  // Set up the screen
  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP,
    SDL_SWSURFACE);

  // If there was in error in setting up the screen
  if (screen == NULL)
  {
    return false;
  }

  // Set the window caption
  SDL_WM_SetCaption("SDL Poker", NULL);

  // If everything initialized fine
  return true;
}

bool load_files()
{
  // Load the images
  const char *cardGraphics[] =
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
  for (int index = 0; index < 52; index++)
  {
      cardgraphic[index] = load_image(cardGraphics[index]);
      if (cardgraphic[index] == NULL)
      {
          return false;
      }    
  }
  
  background = load_image("pattern.png"); 

  // Open the font
  font = TTF_OpenFont("times.ttf", 42);

  // If there was an error in loading the font
  if (font == NULL)
  {
    return false;
  }

  // If everything loaded fine
  return true;
}

void clean_up()
{
  // Free the surface
  for (int index = 0; index < 52; index++)
  {
    SDL_FreeSurface(cardgraphic[index]);
  }

  // Free the surfaces
  SDL_FreeSurface(message);

  // Close the font that was used
  TTF_CloseFont(font);

  // Quit SDL_ttf
  TTF_Quit();

  // Quit SDL
  SDL_Quit();
}

// Five card poker
int handSize = 5;

int main(int argc, char *args[])
{
  // Quit flag
  bool quit = false;

  // Initialize random number generator
  srand(time(0));
  
  // Initialize fonts
  if (init() == false)
  {
    char *error = SDL_GetError();
    fprintf(stderr, "Error: %s", error);
    TTF_Font *times = TTF_OpenFont("times.ttf", 12);
    SDL_Surface *text = TTF_RenderText_Solid(times, error, black);
    apply_surface(320, 240, text, screen);
    if (SDL_Flip(screen) ==  - 1)
    {
      return 1;
    }
    SDL_Delay(2000);
    return 1;
  }

  // Apply the background
  apply_surface(0, 0, background, screen);         
  
  // Update the screen
  if (SDL_Flip(screen) ==  -1)
  {
      return 1;
  }  

  if (TTF_Init() != 0)
  {
    fprintf(stderr, "True Type Font Initialization Failed");
    return 1;
  }

  // Load the files
  if (load_files() == false)
  {
    char *error = SDL_GetError();
    TTF_Font *times = TTF_OpenFont("times.ttf", 12);
    SDL_Surface *text = TTF_RenderText_Solid(times, error, black);
    apply_surface(320, 240, text, screen);
    if (SDL_Flip(screen) ==  -1)
    {
      return 1;
    }
    SDL_Delay(2000);
    TTF_CloseFont(times);
    return 1;
  }

  // The frame rate regulator
  Timer fps;

  // While the user hasn't quit
  while (quit == false)
  {
    // Start the frame timer
    fps.start();

    // While there's events to handle
    while (SDL_PollEvent(&event))
    {
      // If the user has Xed out the window
      if (event.type == SDL_QUIT)
      {
        // Quit the program
        quit = true;
      }
    }

    if (complete == false)
    {
      message = TTF_RenderText_Solid(font, "Welcome to Five Card Poker", black);
      // Apply the background
      apply_surface(0, 0, background, screen);
      // Show the message
      apply_surface((SCREEN_WIDTH - message->w) / 2, ((SCREEN_HEIGHT / 2) -
        message->h) / 2, message, screen);
      // Update the screen
      if (SDL_Flip(screen) ==  -1)
      {
          return 1;
      }
      SDL_Delay(2000);
      // Apply the background
      apply_surface(0, 0, background, screen);
      // Update the screen
      if (SDL_Flip(screen) ==  - 1)
      {
          return 1;
      }
    }

    if (complete != true)
    {
      Deck card = Deck(deck_of_cards2);
      int numberOfShuffles = 0;
      //printf("Enter the number of times to shuffle cards: ");
      //scanf("%d", &numberOfShuffles);
      //numberOfShuffles = 1000;
      numberOfShuffles = card.randRange(1000, (int)pow(2, 16));
      //printf("Enter the size of your hand: ");
      //scanf("%d", &handSize);
      if ((handSize > 52) || (handSize <= 0))
      {
        printf("Please enter a number 1 through 52: ");
        scanf("%d", &handSize);
      }
      char *handcards[handSize];
      const char *yesno = "yes";
      // printf("Would you like to take the first ");
      // printf("%d cards from the deck: ", handSize);
      // scanf("%s", &yesno);
      // if ((strchr(yesno, 'N') != NULL) || (strchr(yesno, 'n') != NULL))
      // {
      //   for (int index = 0; index < handSize; index++)
      //   {
      //     printf("Enter card %d: ", (index + (int)1));
      //     scanf("%s", handcards[index]);
      //   }
      // }
      // Using the card shuffle method
      printf("\nUnshuffled: ");
      card.showCards(deck_of_cards, 52);
      card.shuffle(52, numberOfShuffles);
      // Creates new array with hand size
      char *hand[handSize];
      // Put each deck of card to corresponding hand array
      if ((strchr(yesno, 'N') != NULL) || (strchr(yesno, 'n') != NULL))
      {
        for (int index = 0; index < handSize; index++)
        {
          hand[index] = handcards[index];
        }
      }
      else
      {
        for (int index = 0; index < handSize; index++)
        {
          hand[index] = deck_of_cards2[index];
        }
      }
      hand[0] = "TH";
      hand[1] = "9H";
      hand[2] = "9H";
      hand[3] = "9H";
      hand[4] = "TH";
      printf("\nShuffled: ");
      // Creates an array of cards
      card.showCards(deck_of_cards2, 52);
      printf("\nYour Hand:");
      card.showCards(hand, handSize);
		bool pair = card.OnePair(hand, handSize);
		printf("\nOne pair = %d", (int)pair);
		bool pair2 = card.TwoPair(hand, handSize);
		printf("\nTwo pair = %d", (int)pair2);
		bool three = card.Threeofakind(hand, handSize);
		printf("\nThree of a kind = %d", (int)three);
		bool four = card.Fourofakind(hand, handSize);
		printf("\nFour of a kind = %d", (int)four);
		bool sflush = card.StraightFlush(hand, handSize);
		printf("\nStraight flush = %d", (int)sflush);
		bool full = card.Fullhouse(hand, handSize);
		printf("\nFullhouse = %d", (int)full);
		bool royal = card.Royalflush(hand, handSize);
		printf("\nRoyal = %d", (int)royal);
      // Returns highest card in hand i.e. [0] is highest card then prints
      int high = card.highCard(hand, handSize);
      printf("\nHigh Card: %s", hand[high]);
      int cardimage = card.cardImage(hand[high]);
      // Draw card images
      apply_surface((SCREEN_WIDTH - cardgraphic[cardimage]->w) / 2, ((SCREEN_HEIGHT / 2) -
        cardgraphic[cardimage]->h) / 2, cardgraphic[cardimage], screen);
      // Update the screen
      if (SDL_Flip(screen) ==  -1)
      {
          return 1;
      }

      bool flush = card.isFlush(hand, handSize);
      bool straight = card.isStraight(hand, handSize);
      char secondCharacter = hand[0][1];
      if ((flush == true) && (straight != true))
      {
        if (secondCharacter == 'S')
        {
          printf(" flush in spades");
          SDL_Surface *flushgraphic = TTF_RenderText_Solid(font, "Flush in Spades", black);
          apply_surface((SCREEN_WIDTH - flushgraphic->w) / 2, ((SCREEN_HEIGHT) -
          flushgraphic->h), flushgraphic, screen);
          SDL_Flip(screen);
        }
        else if (secondCharacter == 'C')
        {
          printf(" flush in clubs");
          SDL_Surface *flushgraphic = TTF_RenderText_Solid(font, "Flush in Clubs", black);
          apply_surface((SCREEN_WIDTH - flushgraphic->w) / 2, ((SCREEN_HEIGHT) -
          flushgraphic->h), flushgraphic, screen);
          SDL_Flip(screen);
        }
        else if (secondCharacter == 'H')
        {
          printf(" flush in hearts");
          SDL_Surface *flushgraphic = TTF_RenderText_Solid(font, "Flush in Hearts", black);
          apply_surface((SCREEN_WIDTH - flushgraphic->w) / 2, ((SCREEN_HEIGHT) -
          flushgraphic->h), flushgraphic, screen);
          SDL_Flip(screen);
        }
        else if (secondCharacter == 'D')
        {
          printf(" flush in diamonds");
          SDL_Surface *flushgraphic = TTF_RenderText_Solid(font, "Flush in Diamonds", black);
          apply_surface((SCREEN_WIDTH - flushgraphic->w) / 2, ((SCREEN_HEIGHT) -
          flushgraphic->h), flushgraphic, screen);
          SDL_Flip(screen);
        }
      }
      else if ((straight == true) && (flush != true))
      {
          printf(" straight");
          SDL_Surface *straightgraphic = TTF_RenderText_Solid(font, "Straight", black);
          apply_surface((SCREEN_WIDTH - straightgraphic->w) / 2, ((SCREEN_HEIGHT) -
          straightgraphic->h), straightgraphic, screen);
          SDL_Flip(screen);
      }
      else if ((flush == true) && (straight == true))
      {
        if (secondCharacter == 'S')
        {
          printf(" flush and straight in spades");
          SDL_Surface *flushstraight = TTF_RenderText_Solid(font, "Flush and Straight in Spades", black);
          apply_surface((SCREEN_WIDTH - flushstraight->w) / 2, ((SCREEN_HEIGHT) -
          flushstraight->h), flushstraight, screen);
          SDL_Flip(screen);
        }
        else if (secondCharacter == 'C')
        {
          printf(" flush and straight in clubs");
          SDL_Surface *flushstraight = TTF_RenderText_Solid(font, "Flush and Straight in Clubs", black);
          apply_surface((SCREEN_WIDTH - flushstraight->w) / 2, ((SCREEN_HEIGHT) -
          flushstraight->h), flushstraight, screen);
          SDL_Flip(screen);
        }
        else if (secondCharacter == 'H')
        {
          printf(" flush and straight in hearts");
          SDL_Surface *flushstraight = TTF_RenderText_Solid(font, "Flush and Straight in Hearts", black);
          apply_surface((SCREEN_WIDTH - flushstraight->w) / 2, ((SCREEN_HEIGHT) -
          flushstraight->h), flushstraight, screen);
          SDL_Flip(screen);
        }
        else if (secondCharacter == 'D')
        {
          printf(" flush and straight in diamonds");
          SDL_Surface *flushstraight = TTF_RenderText_Solid(font, "Flush and Straight in Diamonds", black);
          apply_surface((SCREEN_WIDTH - flushstraight->w) / 2, ((SCREEN_HEIGHT) -
          flushstraight->h), flushstraight, screen);
          SDL_Flip(screen);
        }
      }
      complete = true;
    }

    // Update the screen
    if (SDL_Flip(screen) ==  -1)
    {
      return 1;
    }

    // Cap the frame rate
    while (fps.get_ticks() < 1000 / FRAMES_PER_SECOND)
    {
      //wait...
    }
  }

  // Clean up
  clean_up();
  return 0;
}

#include <stdio.h>
#include <stdlib.h>

#include "random.h"

#define CARDS_PER_SUIT 13
#define SUITS 4
#define DECK_SIZE (CARDS_PER_SUIT * SUITS)
#define HAND_SIZE 5

typedef enum {
  clubs = 0, spades, hearts, diamonds
} suit;
const char *suits[SUITS] = {"♣", "♠", "♥", "♦"};
const char *ranks[CARDS_PER_SUIT] = {"A", "2", "3", "4", "5", "6", "7",
                                     "8", "9", "10", "J", "Q", "K"};

typedef enum {
  none = 1, one_pair, three_of_a_kind, four_of_a_kind
} hand;
const char *hands[4] = {"Nothing", "One pair", "Three of a kind",
                        "Four of a kind"};

typedef struct {
  suit suit;
  char rank;
} card;

card *create_deck(void);

// Checks for the following poker hands:
// One pair (Two pair is considered one pair)
// Three of a kind
// Four of a kind
hand check_hand(card *hand);

void print_hand(card *hand);

void print_card_line(card card, uint line);

int main(void) {
  seed_with_timestamp();

  card *deck = create_deck();
  shuffle(deck, sizeof(card), DECK_SIZE);

  hand hand = check_hand(deck);
  printf("Your hand: %s\nYour cards: \n", hands[hand - 1]);
  print_hand(deck);

  free(deck);
  return 0;
}

card *create_deck(void) {
  card *deck = malloc(DECK_SIZE * sizeof(card));

  for (suit suit = 0; suit < SUITS; suit++) {
    for (char rank = 0; rank < CARDS_PER_SUIT; rank++) {
      int i = (int) suit * CARDS_PER_SUIT + rank;
      deck[i].suit = suit;
      deck[i].rank = (char) (rank + 1);
    }
  }

  return deck;
}

hand check_hand(card *hand) {
  char count[CARDS_PER_SUIT] = {0};

  for (int i = 0; i < HAND_SIZE; i++)
    count[hand[i].rank - 1]++;

  int max = 0;
  for (int i = 0; i < CARDS_PER_SUIT; i++)
    max = count[i] > max ? count[i] : max;

  return max;
}

void print_hand(card *hand) {
  for (int line = 0; line < 7; line++) {
    for (int i = 0; i < HAND_SIZE; i++) {
      print_card_line(hand[i], line);
    }
    putchar('\n');
  }
}

// The code here is an absolute mess but the cards look great!
void print_card_line(card card, uint line) {
  // Colors!
  if (card.suit == hearts || card.suit == diamonds) {
    printf("\033[1;31m");
  } else {
    printf("\033[1m");
  }

  char r = card.rank;
  const char *s = suits[card.suit];
  const char *corner = r >= 4 && r <= 10 ? s : " ";
  const char *middle = r == 2 || r == 3 || (r >= 8 && r <= 10) ? s : " ";
  const char *side = r >= 6 && r <= 10 ? s : " ";
  const char *center = (r % 2) == 1 || r > 9 ? s : " ";
  const char *ten = r == 10 ? s : " ";

  switch (line) {
    case 0:
      printf("╭───────╮");
      break;
    case 1:
      printf("│%-2s     │", ranks[r - 1]);
      break;
    case 2:
      if (r == 11) printf("│ ┌───┐ │");
      else if (r == 12) printf("│ ┏━━━┓ │");
      else if (r == 13) printf("│ ╔═══╗ │");
      else printf("│ %s %s %s │", corner, middle, corner);
      break;
    case 3:
      if (r == 11) printf("│ │ %s │ │", center);
      else if (r == 12) printf("│ ┃ %s ┃ │", center);
      else if (r == 13) printf("│ ║ %s ║ │", center);
      else printf("│ %s %s %s │", side, center, side);
      break;
    case 4:
      if (r == 11) printf("│ └───┘ │");
      else if (r == 12) printf("│ ┗━━━┛ │");
      else if (r == 13) printf("│ ╚═══╝ │");
      else printf("│ %s %s %s │", corner, middle, corner);
      break;
    case 5:
      printf("│   %s %2s│", ten, ranks[r - 1]);
      break;
    case 6:
      printf("╰───────╯");
      break;
    default:
      break;
  }

  printf("\033[0m"); // Clear color
}

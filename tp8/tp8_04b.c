#include <stdio.h>
#include <stdlib.h>

#include "my_getnum.h"
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

typedef struct {
  suit suit;
  char rank;
} card;

typedef enum {
  none = 1, one_pair, three_of_a_kind, four_of_a_kind
} hand_type;
const char *hands[4] = {"Nothing", "One pair", "Three of a kind",
                        "Four of a kind"};

typedef struct {
  hand_type type;
  char rank;
} hand;

card *create_deck(void);

card *deal(card **deck, int *undrawn);

int play_round(card **deck, int *undrawn, int scores[2]);

// Checks for the following poker hands:
// One pair (Two pair is considered one pair)
// Three of a kind
// Four of a kind
hand check_hand(card *hand);

void print_hand(card *p_hand);

void print_card_line(const card *card, uint line);

int main(void) {
  seed_with_timestamp();

  card *deck = create_deck();
  shuffle(deck, sizeof(card), DECK_SIZE);

  // Keep a pointer to the start of the deck to free memory, because deck
  // pointer is modified later
  card *full_deck = deck;

  int scores[2] = {0, 0};
  int undrawn = DECK_SIZE, stop = 0;

  while (!stop)
    stop = play_round(&deck, &undrawn, scores);

  if (scores[1] > scores[0]) printf("You win!\n");
  else if (scores[0] > scores[1]) printf("The house wins!\n");
  else printf("Draw!\n");

  free(full_deck);
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

card *deal(card **deck, int *undrawn) {
  card *p_hand = *deck;
  *deck += HAND_SIZE;
  *undrawn -= HAND_SIZE;

  return p_hand;
}

int play_round(card **deck, int *undrawn, int scores[2]) {
  card *house_cards = deal(deck, undrawn);
  card *player_cards = deal(deck, undrawn);

  hand player_hand = check_hand(player_cards);
  printf(
    "\nYour hand: %s (%s)\nYour cards: \n",
    hands[player_hand.type - 1],
    ranks[player_hand.rank - 1]
  );
  print_hand(player_cards);

  hand house_hand = check_hand(house_cards);
  printf(
    "\nHouse hand: %s (%s)\n",
    hands[house_hand.type - 1],
    ranks[house_hand.rank - 1]
  );

  if (player_hand.type == house_hand.type) {
    if (player_hand.rank == house_hand.rank) {
      // Draw
      scores[0]++;
      scores[1]++;
    } else {
      int player_wins = player_hand.rank > house_hand.rank;
      scores[player_wins]++;
    }
  } else {
    int player_wins = player_hand.type > house_hand.type;
    scores[player_wins]++;
  }

  printf("\nHouse score: %d\nPlayer score: %d\n\n", scores[0], scores[1]);

  // Assumes undrawn == DECK_SIZE the first time the function is called
  if (*undrawn < HAND_SIZE * 2)
    return 1;

  return !get_yes_no("Keep playing? (y/n) ");
}

hand check_hand(card *p_hand) {
  char count[CARDS_PER_SUIT] = {0};

  for (int i = 0; i < HAND_SIZE; i++)
    count[p_hand[i].rank - 1]++;

  hand best = {0, 0};
  for (int i = 0; i < CARDS_PER_SUIT; i++) {
    if (count[i] >= best.type) {
      best.type = count[i];
      best.rank = i + 1;
    }
  }

  return best;
}

void print_hand(card *p_hand) {
  for (int line = 0; line < 7; line++) {
    for (int i = 0; i < HAND_SIZE; i++) {
      print_card_line(&p_hand[i], line);
    }
    putchar('\n');
  }
}

// The code here is an absolute mess but the cards look great!
void print_card_line(const card *card, uint line) {
  // Colors!
  if (card->suit == hearts || card->suit == diamonds) {
    printf("\033[1;31m");
  } else {
    printf("\033[1m");
  }

  char r = card->rank;
  const char *s = suits[card->suit];
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

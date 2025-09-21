#include "poker.h"

void init_deck(DECK deck) {
    for (int suit = 0; suit < 4; suit++) {
        for (int rank = 1; rank <= 13; rank++) {
            deck[suit * 13 + rank - 1] = suit << 4 | rank;
        }
    }
}

int main() {
    DECK deck;
    init_deck(deck);

    for (int i = 0; i < 3; i++) {
        deck[i] = ((i % 4) << 4) | 1;
    }

    for (int i = 5; i < 10; i ++) {
        deck[i] = ((i % 4) << 4) | ((rand() % 13) + 1);
    }

    int* human = &deck[0];
    int* comp = &deck[5];

    printf("%d\n", compare_hands(human, comp));

    for (int i = 0; i < 5; i++) {
        deck[i] = ((i % 4) << 4) | (12 - (2 * i));
    }

    for (int i = 6; i < 9; i ++) {
        deck[i] = ((i % 4) << 4) | 13;
    }

    human = &deck[0];
    comp = &deck[5];

    printf("%d\n", compare_hands(human, comp));
}
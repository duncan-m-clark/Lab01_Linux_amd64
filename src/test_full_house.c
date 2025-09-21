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

    deck[0] = (0x20) | 1;
    deck[1] = (0x30) | 1;
    deck[3] = (0x10) | 13;
    deck[4] = (0x00) | 13;
    deck[2] = (0x00) | 13;

    deck[6] = (0x10) | 0x3;
    deck[7] = (0x20) | 0x4;
    deck[8] = (0x30) | 0x5;
    deck[9] = (0x20) | 0x6;
    deck[5] = (0x00) | 13;

    int* human = &deck[0];
    int* comp = &deck[5];

    printf("%d\n", compare_hands(human, comp));

    init_deck(deck);

    deck[0] = (0x20) | 1;
    deck[1] = (0x30) | 3;
    deck[3] = (0x10) | 13;
    deck[4] = (0x00) | 12;
    deck[2] = (0x00) | 13;

    deck[6] = (0x10) | 12;
    deck[7] = (0x20) | 10;
    deck[8] = (0x30) | 12;
    deck[9] = (0x20) | 10;
    deck[5] = (0x00) | 12;

    human = &deck[0];
    comp = &deck[5];

    printf("%d\n", compare_hands(human, comp));
}

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

    deck[0] = (0x20) | 0x1;
    deck[1] = (0x20) | 0xa;
    deck[2] = (0x20) | 0xb;
    deck[3] = (0x20) | 0xc;
    deck[4] = (0x20) | 0xd;

    deck[5] = (0x20) | 0x2;
    deck[6] = (0x20) | 0x3;
    deck[7] = (0x20) | 0x4;
    deck[8] = (0x20) | 0x5;
    deck[9] = (0x20) | 0x6;

    int* human = &deck[0];
    int* comp = &deck[5];

    printf("%d\n", compare_hands(human, comp));

    init_deck(deck);

    deck[0] = (0x20) | 0x1;
    deck[1] = (0x20) | 0xa;
    deck[2] = (0x20) | 0xb;
    deck[3] = (0x20) | 0xc;
    deck[4] = (0x20) | 0xd;

    deck[5] = (0x30) | 0x1;
    deck[6] = (0x30) | 0xa;
    deck[7] = (0x30) | 0xb;
    deck[8] = (0x30) | 0xc;
    deck[9] = (0x30) | 0xd;

    human = &deck[0];
    comp = &deck[5];

    printf("%d\n", compare_hands(human, comp));

    init_deck(deck);

    deck[0] = (0x20) | 0x1;
    deck[1] = (0x20) | 0xa;
    deck[2] = (0x20) | 0xb;
    deck[3] = (0x20) | 0xc;
    deck[4] = (0x20) | 0xd;

    deck[5] = (0x30) | 0x1;
    deck[6] = (0x30) | 0x2;
    deck[7] = (0x30) | 0x3;
    deck[8] = (0x30) | 0x4;
    deck[9] = (0x30) | 0x5;

    human = &deck[0];
    comp = &deck[5];

    printf("%d\n", compare_hands(human, comp));

    init_deck(deck);

    deck[0] = (0x20) | 0x1;
    deck[1] = (0x10) | 0x1;
    deck[2] = (0x30) | 0x1;
    deck[3] = (0x00) | 0x1;
    deck[4] = (0x20) | 0xc;

    deck[5] = (0x20) | 0xd;
    deck[6] = (0x10) | 0xd;
    deck[7] = (0x30) | 0xd;
    deck[8] = (0x00) | 0xd;
    deck[9] = (0x30) | 0xc;

    human = &deck[0];
    comp = &deck[5];

    printf("%d\n", compare_hands(human, comp));

    init_deck(deck);

    deck[0] = (0x20) | 0x1;
    deck[1] = (0x10) | 0xd;
    deck[2] = (0x30) | 0xd;
    deck[3] = (0x00) | 0xd;
    deck[4] = (0x20) | 0xd;

    deck[5] = (0x30) | 0x2;
    deck[6] = (0x20) | 0x2;
    deck[7] = (0x10) | 0x2;
    deck[8] = (0x00) | 0x2;
    deck[9] = (0x30) | 0x5;

    human = &deck[0];
    comp = &deck[5];

    printf("%d\n", compare_hands(human, comp));
}
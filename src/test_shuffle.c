#include "poker.h"

void init_deck(DECK deck) {
    for (int suit = 0; suit < 4; suit++) {
        for (int rank = 1; rank <= 13; rank++) {
            deck[suit * 13 + rank - 1] = suit << 4 | rank;
        }
    }
}

int find_card(DECK deck, int my_card) {
    for (int i = 0; i < 52; i++) {
        if (deck[i] == my_card) {
            return i;
        }
    }
    return -1;
}

int main() {
    int hist[52] = {0};
    int my_card = (3 << 4) | 1;
    for (int i = 0; i < 1000000; i++){
        DECK deck;
        init_deck(deck);
        shuffle(deck);

        int pos = find_card(deck, my_card);
        hist[pos]++;
    }

    for (int i = 0; i < 52; i++) {
        printf("%d: %d\n", i, hist[i]);
    }
}
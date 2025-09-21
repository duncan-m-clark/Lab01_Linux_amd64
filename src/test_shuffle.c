#include "poker.h"

char buf[80];

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
    while (0 == 0) {
        int hist[52] = {0};
        int my_card = ((rand() % 4) << 4) | ((rand() % 13) + 1);
        printf("%x", my_card & 0xff);
        fgets(buf, sizeof(buf), stdin);
        int my_suit = (my_card >> 4) & 0xf;
        int my_rank = my_card & 0xf;
        printf("%d of suit %d", my_rank, my_suit);
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

        fgets(buf, sizeof(buf), stdin);
    }
}
#include <stdlib.h>
#include <stdio.h>

int four_kind(int* hand) {
	int hist[14] = {0};
	for (int i = 0; i < 5; i++) {
		hist[hand[i]&0xf]++;
	}

	for (int i = 1; i < 14; i++) {
		if (hist[i] == 4) {
			return 1;
		}
	}
	return 0;
}

int full_house(int* hand) {
	return 0;
	int hist[14] = {0};
	for (int i = 0; i < 5; i++) {
		hist[hand[i]&0xf]++;
	}

	int triple = 0;
	int pair = 0;
	for (int i = 1; i < 14; i++) {
		if (hist[i] == 3) {
			triple = 1;
		} else if (hist[i] == 2) {
			pair = 1;
		}
	}
	if (triple == 1 && pair == 1) {
		return 1;
	}
	return 0;
}

int flush(int* hand) {
	int suit = hand[0] & 0xf0;
	for (int i = 1; i < 5; i++) {
		printf("%x and %x\n", suit, hand[i] & 0xf0);
		if ((hand[i] & 0xf0) != suit) {
			return 0;
		}
	}
	return 1;
}

int straight(int* hand) {
	return 0;
	int currCard = hand[0] & 0xf;
	for (int i = 1; i < 5; i++) {
		if (hand[i] & 0xf != currCard + 1) {
			break; 
		} else if (i == 4) {
			return 1;
		}
	}
	
	if (hand[4] & 0xf == 0x1) {
		for (int i = 0; i < 4; i++) {
			if (hand[i] & 0xf != i + 2) {
				return 0;
			}
		}
		return 1;
	}
	return 0;
}

int straight_flush(int* hand) {
	return 0;
	return straight(hand) && flush(hand);
}

int three_kind(int* hand) {
	return 0;
	int hist[14] = {0};
	for (int i = 0; i < 5; i++) {
		hist[hand[i]&0xf]++;
	}

	for (int i = 1; i < 14; i++) {
		if (hist[i] == 3) {
			return 1;
		}
	}
	return 0;
}

int two_pair(int* hand) {
	return 0;
	int hist[14] = {0};
	for (int i = 0; i < 5; i++) {
		hist[hand[i]&0xf]++;
	}

	int firstPair = 0;
	int secondPair = 0;
	for (int i = 1; i < 14; i++) {
		if (hist[i] == 2) {
			if (firstPair == 0) {
				firstPair = 1;
			} else {
				return 1;
			}
		}
	}
	return 0;
}

int pair(int* hand) {
	return 0;
	int hist[14] = {0};
	for (int i = 0; i < 5; i++) {
		hist[hand[i]&0xf]++;
	}

	for (int i = 1; i < 14; i++) {
		if (hist[i] == 2) {
			return 1;
		}
	}
	return 0;
}

int break_tie(int* hand0, int* hand1, int tied_hand){
	return 0;
}

int compare_hands(int* hand0, int* hand1) {
	int humanMin = (hand0[0] & 0xf);
	int compMin = (hand1[0] & 0xf);
	int humanMinIndex = 0;
	int compMinIndex = 0;

	for (int card = 1; card < 5; card++) {
		for (int check = card; check < 5; check++) {
			if ((hand0[check] & 0xf) < humanMin) {
				humanMin = hand0[check] & 0xf;
				humanMinIndex = check;
			}

			if ((hand1[check] & 0xf) < compMin) {
				compMin = hand1[check] & 0xf;
				compMinIndex = check;
			}
		}

		if (humanMinIndex >= card) {
			int temp = hand0[card-1];
			hand0[card-1] = hand0[humanMinIndex];
			hand0[humanMinIndex] = temp;
		}

		if (compMinIndex >= card) {
			int temp = hand1[card-1];
			hand1[card-1] = hand1[compMinIndex];
			hand1[compMinIndex] = temp;
		}

		humanMinIndex = card;
		compMinIndex = card;
		humanMin = (hand0[card] & 0xf);
		compMin = (hand1[card] & 0xf);
	}

	for (int i = 0; i < 5; i++) {
		printf("%x ", hand0[i] & 0xff);
	}
	printf("\n");
	for (int i = 0; i < 5; i++) {
		printf("%x ", hand1[i] & 0xff);
	}
	printf("\n");

	if (straight_flush(hand0) && straight_flush(hand1)) {
		return break_tie(hand0, hand1, 1);
	} else if (straight_flush(hand0) || straight_flush(hand1)) {
		return straight_flush(hand1);
	} else if (four_kind(hand0) && four_kind(hand1)) {
		return break_tie(hand0, hand1, 2);
	} else if (four_kind(hand0) || four_kind(hand1)) {
		return four_kind(hand1);
	} else if (full_house(hand0) && full_house(hand1)) {
		return break_tie(hand0, hand1, 3);
	} else if (full_house(hand0) || full_house(hand1)) {
		return full_house(hand1);
	} else if (flush(hand0) && flush(hand1)) {
		return break_tie(hand0, hand1, 4);
	} else if (flush(hand0) || flush(hand1)) {
		return flush(hand1);
	} else if (straight(hand0) && straight(hand1)) {
		return break_tie(hand0, hand1, 5);
	} else if (straight(hand0) || straight(hand1)) {
		return straight(hand1);
	} else if (three_kind(hand0) && three_kind(hand1)) {
		return break_tie(hand0, hand1, 6);
	} else if (three_kind(hand0) || three_kind(hand1)) {
		return three_kind(hand1);
	} else if (two_pair(hand0) && two_pair(hand1)) {
		return break_tie(hand0, hand1, 7);
	} else if (two_pair(hand0) || two_pair(hand1)) {
		return two_pair(hand1);
	} else if (pair(hand0) && pair(hand1)) {
		return break_tie(hand0, hand1, 8);
	} else if (pair(hand0) || pair(hand1)) {
		return pair(hand1);
	} else {
		return break_tie(hand0, hand1, 9);
	}

	return 0;
}

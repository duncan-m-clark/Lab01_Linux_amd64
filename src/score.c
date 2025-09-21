#include <stdlib.h>
#include <stdio.h>

int four_kind(int* hand) {
	int hist[14] = {0};
	for (int i = 0; i < 5; i++) {
		hist[(hand[i]&0xf)]++;
	}

	for (int i = 1; i < 14; i++) {
		if (hist[i] == 4) {
			return 1;
		}
	}
	return 0;
}

int full_house(int* hand) {
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
		if ((hand[i] & 0xf0) != suit) {
			return 0;
		}
	}
	return 1;
}

int straight(int* hand) {
	int currCard = hand[0] & 0xf;
	for (int i = 1; i < 5; i++) {
		if ((hand[i] & 0xf) != (currCard + 0x1)) {
			break; 
		} else if (i == 4) {
			return 1;
		}
		currCard = hand[i] & 0xf;
	}
	
	if ((hand[4] & 0xf) == 0x1) {
		if ((hand[3] & 0xf) == 0xd) {
			for (int i = 0; i < 4; i++) {
				if ((hand[i] & 0xf) != (i + 10)) {
					return 0;
				} else if (i == 3) {
					return 1;
				}
			}
		} else if ((hand[3] & 0xf) == 0x5) {
			for (int i = 0; i < 4; i++) {
				if ((hand[i] & 0xf) != (i + 2)) {
					return 0;
				} else if (i == 3) {
					return 1;
				}
			}
		}
	}
	return 0;
}

int straight_flush(int* hand) {
	return straight(hand) && flush(hand);
}

int three_kind(int* hand) {
	int hist[14] = {0};
	for (int i = 0; i < 5; i++) {
		hist[(hand[i]&0xf)]++;
	}

	for (int i = 1; i < 14; i++) {
		if (hist[i] == 3) {
			return 1;
		}
	}
	return 0;
}

int two_pair(int* hand) {
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

int break_tie(int* hand0, int* hand1, int tiedHand){
	int humanHigh = 0;
	int compHigh = 0;
	int humanHist[14] = {0};
	int compHist[14] = {0};

	switch (tiedHand) {
		case 1:
		case 2:
			humanHigh = hand0[4];
			compHigh = hand1[4];

			if ((humanHigh & 0xf) == 0x1) {
				if ((hand0[3] & 0xf) == 0x5) {
					humanHigh = hand0[3];
				} else {
					humanHigh = 14;
				}
			}

			if ((compHigh & 0xf) == 0x1) {
				if ((hand1[3] & 0xf) == 0x5) {
					compHigh = hand1[3];
				} else {
					compHigh = 14;
				}
			}

			if ((humanHigh & 0xf) == (compHigh & 0xf)) {
				return (humanHigh & 0xf0) > (compHigh & 0xf0) ? 0 : 1;
			}

			return (humanHigh & 0xf) > (compHigh & 0xf) ? 0 : 1;
		case 3:
			humanHigh = 0;
			compHigh = 0;
			for (int i = 0; i < 14; i++) {
				humanHist[i] = 0;
				compHist[i] = 0;
			}

			for (int i = 0; i < 5; i++) {
				humanHist[(hand0[i]&0xf)]++;
			}

			for (int i = 1; i < 14; i++) {
				if (humanHist[i] == 4) {
					humanHigh = i;
					break;
				}
			}

			for (int i = 0; i < 5; i++) {
				compHist[(hand1[i]&0xf)]++;
			}

			for (int i = 1; i < 14; i++) {
				if (compHist[i] == 4) {
					compHigh = i;
					break;
				}
			}

			if (humanHigh == 1) {
				humanHigh = 14;
			}

			if (compHigh == 1) {
				compHigh = 14;
			}
			
			return humanHigh > compHigh ? 0 : 1;
		case 4:
		case 5:
			humanHigh = 0;
			compHigh = 0;
			for (int i = 0; i < 14; i++) {
				humanHist[i] = 0;
				compHist[i] = 0;
			}

			for (int i = 0; i < 5; i++) {
				humanHist[(hand0[i]&0xf)]++;
			}

			for (int i = 1; i < 14; i++) {
				if (humanHist[i] == 3) {
					humanHigh = i;
					break;
				}
			}

			for (int i = 0; i < 5; i++) {
				compHist[(hand1[i]&0xf)]++;
			}

			for (int i = 1; i < 14; i++) {
				if (compHist[i] == 3) {
					compHigh = i;
					break;
				}
			}

			if (humanHigh == 1) {
				humanHigh = 14;
			}

			if (compHigh == 1) {
				compHigh = 14;
			}
			
			return humanHigh > compHigh ? 0 : 1;
		case 6:
			if ((hand0[4] & 0xf) == 0x1) {
				hand0[4] = (hand0[4] & 0xf0) | 0xe;
			}

			if ((hand1[4] & 0xf) == 0x1) {
				hand1[4] = (hand1[4] & 0xf0) | 0xe;
			}

			for (int i = 4; i >= 0; i--) {
				if ((hand0[i] & 0xf) != (hand1[i] & 0xf)) {
					return (hand0[i] & 0xf) > (hand1[i] & 0xf) ? 0 : 1;
				}
			}

			return (hand0[4] & 0xf0) > (hand1[4] & 0xf0) ? 0 : 1;
		case 7:
			break;
		case 8:
			break;
		case 9:
			break;
		default:
			return 0;
			break;
	}
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

	if ((hand0[0] & 0x0f) == 0x01) {
		while (1) {
			for (int i = 1; i < 5; i++) {
				int temp = hand0[i-1];
				hand0[i-1] = hand0[i];
				hand0[i] = temp;
			}

			if ((hand0[0] & 0x0f) != 0x01) {
				break;
			}
		}
	}

	if ((hand1[0] & 0x0f) == 0x01) {
		while (1) {
			for (int i = 1; i < 5; i++) {
				int temp = hand1[i-1];
				hand1[i-1] = hand1[i];
				hand1[i] = temp;
			}

			if ((hand1[0] & 0x0f) != 0x01) {
				break;
			}
		}
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
		printf("straight flush tie\n");
		return break_tie(hand0, hand1, 1);
	} else if (straight_flush(hand0) || straight_flush(hand1)) {
		printf("straight flush\n");
		return straight_flush(hand1);
	} else if (four_kind(hand0) && four_kind(hand1)) {
		printf("four kind tie\n");
		return break_tie(hand0, hand1, 3);
	} else if (four_kind(hand0) || four_kind(hand1)) {
		printf("four kind\n");
		return four_kind(hand1);
	} else if (full_house(hand0) && full_house(hand1)) {
		printf("full house tie\n");
		return break_tie(hand0, hand1, 4);
	} else if (full_house(hand0) || full_house(hand1)) {
		printf("full house\n");
		return full_house(hand1);
	} else if (flush(hand0) && flush(hand1)) {
		printf("flush tie\n");
		return break_tie(hand0, hand1, 6);
	} else if (flush(hand0) || flush(hand1)) {
		printf("flush\n");
		return flush(hand1);
	} else if (straight(hand0) && straight(hand1)) {
		printf("straight tie\n");
		return break_tie(hand0, hand1, 2);
	} else if (straight(hand0) || straight(hand1)) {
		printf("straight\n");
		return straight(hand1);
	} else if (three_kind(hand0) && three_kind(hand1)) {
		printf("three kind tie\n");
		return break_tie(hand0, hand1, 5);
	} else if (three_kind(hand0) || three_kind(hand1)) {
		printf("three kind\n");
		return three_kind(hand1);
	} else if (two_pair(hand0) && two_pair(hand1)) {
		printf("two pair tie\n");
		return break_tie(hand0, hand1, 7);
	} else if (two_pair(hand0) || two_pair(hand1)) {
		printf("two pair\n");
		return two_pair(hand1);
	} else if (pair(hand0) && pair(hand1)) {
		printf("pair tie\n");
		return break_tie(hand0, hand1, 8);
	} else if (pair(hand0) || pair(hand1)) {
		printf("pair\n");
		return pair(hand1);
	} else {
		printf("high card tie\n");
		return break_tie(hand0, hand1, 9);
	}

	return 0;
}

#include <stdlib.h>
#include <stdio.h>

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

		printf("Human:\n");
		for (int i = 0; i < 5; i++) {
			printf("%x\n", hand0[i] & 0xff);
		}

		printf("Comp:\n");
		for (int i = 0; i < 5; i ++) {
			printf("%x\n", hand1[i] & 0xff);
		}
	}
	return 0;
}

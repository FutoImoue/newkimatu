#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <Windows.h>
#include <time.h>
#define BUFFSIZE 1024
#define DAYS 365
#define CHARBUFF 124
struct ball {
	int x;
	int y;
	int haba;
	ball *nextball;
};
struct ivent {
	int x;
	int y;
};
struct ballAggregation
{
	ball *firstball;
};
int i, count2 = 0, j;
int limitx1 = 3;
boolean gamestart = false;
boolean gameover = false;
boolean latemode = false;//lateÉÇÅ[Éh
boolean upmode = false;
boolean invinciblemode = false;
boolean contact = false;
boolean reversemode = false;
boolean re = false;
int speed = 1000;//óéÇøÇƒÇ¢Ç≠ë¨Ç≥


ball *a;
ivent late;
ivent up;
ivent invincible;
ivent reverse;
int set = 0, set1 = 0, set2 = 0, set3 = 0;
void getGurrentDirectory(char *currentDirectory) {
	GetCurrentDirectory(CHARBUFF, currentDirectory);
}
void setside(int wid) {
	attrset(COLOR_PAIR(3));
	for (i = 0; i < 30; i++) {
		mvaddstr(i, limitx1, " ");
		mvaddstr(i, limitx1 + wid, " ");
	}
}

void displayWall(ballAggregation sample, int num1, int wid) {
	attrset(COLOR_PAIR(3));
	a = sample.firstball;
	for (i = 0; i < num1; i++) {
		if (a->y > 0 && a->y <= 20) {
			for (int k = 0; k < a->haba; k++) {
				if (k + a->x > limitx1&&k + a->x <limitx1 + wid) {
					mvaddstr(a->y, k + a->x, " ");
				}

			}
		}
		a = a->nextball;
	}
}
void decidecontact(ballAggregation sample, int num1, int count) {
	a = sample.firstball;
	for (i = 0; i < num1; i++) {
		for (j = 0; j < a->haba; j++) {
			if ((a->y == 20) && (a->x + j == count)) {
				gameover = true;
			}
		}
		a = a->nextball;
	}
}
void contactlateivent(int count) {
	if (late.y == 20 && late.x == count &&set == 0) {
		speed = speed * 2;
		set++;
	}
}
void contactUpivent(int count) {
	if (up.y == 20 && up.x == count &&set1 == 0) {
		speed = speed / 2;
		set1++;
	}
}
void contactInvincibleivent(int count) {
	if (invincible.y == 20 && invincible.x == count &&set2 == 0) {
		contact = true;
		set2++;
	}
}

void contactReverseivent(int count) {
	if (reverse.y == 20 && reverse.x == count &&set3 == 0) {
		re = true;
		set3++;
	}
}
void displaygameover() {
	attrset(COLOR_PAIR(1));

	mvprintw(LINES / 2 - 4, (COLS - 70) / 2, " GGGG    AAA   M     M  EEEEE        OOOO   V     V  EEEEE  RRRR       ");
	mvprintw(LINES / 2 - 3, (COLS - 70) / 2, "G    G  A   A  MM   MM  E           O    O  V     V  E      R   R      ");
	mvprintw(LINES / 2 - 2, (COLS - 70) / 2, "G       A   A  M M M M  E           O    O  V     V  E      R    R     ");
	mvprintw(LINES / 2 - 1, (COLS - 70) / 2, "G       AAAAA  M  M  M  EEEEE       O    O  V     V  EEEEE  RRRRR      ");
	mvprintw(LINES / 2, (COLS - 70) / 2, "G       A   A  M     M  E           O    O  V     V  E      R  R       ");
	mvprintw(LINES / 2 + 1, (COLS - 70) / 2, "G   GGG A   A  M     M  E           O    O   V   V   E      R   R      ");
	mvprintw(LINES / 2 + 2, (COLS - 70) / 2, "G    G  A   A  M     M  E           O    O    V V    E      R    R     ");
	mvprintw(LINES / 2 + 3, (COLS - 70) / 2, " GGGG   A   A  M     M  EEEEE        OOOO      V     EEEEE  R     R    ");

}
void displaygamestart() {
	attrset(COLOR_PAIR(1));

	mvprintw(LINES / 2 - 4, (COLS - 70) / 2, " GGGG    AAA   M     M  EEEEE        SSSS   TTTTTTT   AAA   RRRR    TTTTTTT    ");
	mvprintw(LINES / 2 - 3, (COLS - 70) / 2, "G    G  A   A  MM   MM  E           S    O     T     A   A  R   R      T");
	mvprintw(LINES / 2 - 2, (COLS - 70) / 2, "G       A   A  M M M M  E           S          T     A   A  R    R     T");
	mvprintw(LINES / 2 - 1, (COLS - 70) / 2, "G       AAAAA  M  M  M  EEEEE       S          T     AAAAA  RRRRR      T");
	mvprintw(LINES / 2, (COLS - 70) / 2, "G       A   A  M     M  E            SSSSS     T     A   A  R  R       T");
	mvprintw(LINES / 2 + 1, (COLS - 70) / 2, "G   GGG A   A  M     M  E                 S    T     A   A  R   R      T");
	mvprintw(LINES / 2 + 2, (COLS - 70) / 2, "G    G  A   A  M     M  E           S     S    T     A   A  R    R     T");
	mvprintw(LINES / 2 + 3, (COLS - 70) / 2, " GGGG   A   A  M     M  EEEEE       SSSSSS     T     A   A  R     R    T");
}
void setLateIvent(ballAggregation bA, int num, int wid) {


	a = bA.firstball;
	for (i = 0; i < num; i++) {
		if (a->y == 0) {
			late.y = 0;
			int x;
			while (true) {
				x = rand() % wid + limitx1 + 1;
				int sum = 0;
				for (j = a->x; j <= a->x + a->haba; j++) {
					if (x == j) {
						sum++;
					}
				}
				if (sum == 0) {
					break;
				}
			}
			late.x = x;
			break;
		}
		a = a->nextball;
	}
	latemode = true;
}
void setUpIvent(ballAggregation bA, int num, int wid) {


	a = bA.firstball;
	for (i = 0; i < num; i++) {
		if (a->y == 0) {
			up.y = 0;
			int x;
			while (true) {
				x = rand() % wid + limitx1 + 1;
				int sum = 0;
				for (j = a->x; j <= a->x + a->haba-1; j++) {
					if (x == j) {
						sum++;
					}
				}
				if (sum == 0) {
					break;
				}
			}
			up.x = x;
			break;
		}
		a = a->nextball;
	}
	upmode = true;
}
void setInvincibleIvent(ballAggregation bA, int num, int wid) {


	a = bA.firstball;
	for (i = 0; i < num; i++) {
		if (a->y == 0) {
			invincible.y = 0;
			int x;
			while (true) {
				x = rand() % wid + limitx1 + 1;
				int sum = 0;
				for (j = a->x; j <= a->x + a->haba; j++) {
					if (x == j) {
						sum++;
					}
				}
				if (sum == 0) {
					break;
				}
			}
			invincible.x = x;
			break;
		}
		a = a->nextball;
	}
	invinciblemode = true;
}

void setReverseIvent(ballAggregation bA, int num, int wid) {


	a = bA.firstball;
	for (i = 0; i < num; i++) {
		if (a->y == 0) {
			reverse.y = 0;
			int x;
			while (true) {
				x = rand() % wid + limitx1 + 1;
				int sum = 0;
				for (j = a->x; j <= a->x + a->haba; j++) {
					if (x == j) {
						sum++;
					}
				}
				if (sum == 0) {
					break;
				}
			}
			reverse.x = x;
			break;
		}
		a = a->nextball;
	}
	invinciblemode = true;
}


void fallWall(ballAggregation bA, int aa, int num) {
	a = bA.firstball;
	if (aa % speed == 0) {
		for (i = 0; i < num; i++) {
			a->y++;
			a = a->nextball;
		}

	}
}

void txtArray(double data) {
	char s[BUFFSIZE];
	FILE *fp;
	errno_t error;

	error = fopen_s(&fp, "time.txt", "w");
	if (error != 0)
		fprintf_s(stderr, "failed to open");
	else {
		fprintf(fp, "time=%lf\n", data);

	}
	fclose(fp);
}


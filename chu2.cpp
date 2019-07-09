#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <Windows.h>
#define BUFFSIZE 1024
#define DAYS 365
struct ball {
	int x;
	all *nextball;
};int y;
	
struct ballAggregation
{
	ball *firstball;
};
int i, count2 = 0, j;


#define CHARBUFF 124
void getGurrentDirectory(char *currentDirectory) {
	GetCurrentDirectory(CHARBUFF, currentDirectory);
}



int main(int argc, char *argv[]) {
	char currentDirectory[CHARBUFF];
	getGurrentDirectory(currentDirectory);
	char section[CHARBUFF];
	sprintf_s(section, "section1");
	char tem[CHARBUFF];
	sprintf_s(tem, "num1");

	char settingFile[CHARBUFF];
	sprintf_s(settingFile, "%s\\set.ini", currentDirectory);
	int num = GetPrivateProfileInt(section, tem, -1, settingFile);

	char width[CHARBUFF];
	sprintf_s(width, "width1");
	int width1 = GetPrivateProfileInt(section, width, -1, settingFile);
	ballAggregation bA;
	ball *previousball = NULL;
	for (int i = 0; i < num; i++) {
		ball *tmp = new ball();
		tmp->x = rand() % width1 + 4;
		tmp->y = 1 - i;
		tmp->nextball = NULL;
		if (i == 0) {
			bA.firstball = tmp;
		}
		else {
			previousball->nextball = tmp;
		}
		previousball = tmp;
	}
	previousball = bA.firstball;

	// èâä˙âª
	if (initscr() == NULL) {
		return 1;
	}
	int y_num[16];

	start_color();

	init_pair(1, COLOR_RED, COLOR_RED);

	init_pair(2, COLOR_WHITE, COLOR_BLACK);

	init_pair(3, COLOR_BLACK, COLOR_WHITE);

	attrset(COLOR_PAIR(3));

	int count = 0, countnum = 0;



	while (true) {
		erase();

		ball *a = bA.firstball;
		for (i = 0; i < num; i++) {
			if (a->y > 0 && a->y <= 20) {
				mvaddstr(a->y, a->x, ".");
			}

			for (j = 0 + count; j < 15 + count; j++) {
				if ((a->y == 20) && (a->x == j)) {
					countnum++;
				}
			}

			a = a->nextball;


		}

		mvprintw(20, width1 + 30, "count=%d", countnum);
		for (i = 0; i < 15; i++) {
			mvaddstr(20, i + count, "*");
		}
		fprintf_s(stdout, "2\n");
		noecho();
		cbreak();
		keypad(stdscr, TRUE);
		int key;
		key = getch();
		if (key == KEY_RIGHT) {
			count++;

		}
		if (key == KEY_LEFT) {
			count--;

		}
		a = bA.firstball;
		for (i = 0; i < num; i++) {
			a->y++;
			a = a->nextball;
		}

		refresh();
	}



	return 0;
}

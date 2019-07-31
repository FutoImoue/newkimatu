#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <Windows.h>
#include <time.h>
#include "method.h"
int main(int argc, char *argv[]) {
	// 初期化
	if (initscr() == NULL) {
		return 1;
	}
	start_color();

	init_pair(1, COLOR_RED, COLOR_BLACK);

	init_pair(2, COLOR_WHITE, COLOR_BLACK);

	init_pair(3, COLOR_BLACK, COLOR_WHITE);

	init_pair(4, COLOR_YELLOW, COLOR_BLACK);

	while (true) {
		gamestart = false;
		while (true) {
			noecho();
			cbreak();
			keypad(stdscr, TRUE);
			erase();
			mvaddstr(25, 40, "A:player");
			mvaddstr(26, 40, "*:change wall speed");
			mvaddstr(27, 40, "@:invincible");
			mvaddstr(28, 40, "-:reverse");
			displaygamestart();
			timeout(0);
			int key1 = getch();
			if (key1 == KEY_UP) {
				break;
			}
			refresh();

		}


		//iniファイル読み込み
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
		char speed1[CHARBUFF];
		sprintf_s(speed1, "speed1");
		int width1 = GetPrivateProfileInt(section, width, -1, settingFile);
		speed = GetPrivateProfileInt(section, speed1, -1, settingFile);
		ballAggregation bA;
		ball *previousball = NULL;
		for (int i = 0; i < num; i++) {
			ball *tmp = new ball();
			if (num < num/6) {
				tmp->haba = rand() % 3;
			}
			else if (num < num/6*2) {
				tmp->haba = rand() % 6;
			}
			else if (num < num/6*3) {
				tmp->haba = rand() % 9;
			}
			else if (num < num/6*4) {
				tmp->haba = rand() % 12;
			}
			else if (num < num/6*5) {
				tmp->haba = rand() % 14;
			}
			else {
				tmp->haba = rand() % 16;
			}
			tmp->x = 1 + rand() % width1 + limitx1;
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








		int count = width1/2+limitx1, countnum = 0;

		int aa = 0;
		int bb=0,cc=0;
		clock_t start = clock();


		int ran = rand() % 20,ran2=rand()%40, ran3 = rand() % 35, ran4 = rand() % 50;
		while (true) {
			if (aa%(speed * 5)==0) {
				set = 0, set1 = 0, set2 = 0,set3=0;
			}


			erase();
			aa++;
			setside(width1);//横壁設定
			displayWall(bA, num,width1);//壁表示
			attrset(COLOR_PAIR(4));
			mvaddstr(20, count, "A");//自身表示
			if (!contact) {
				decidecontact(bA, num, count);//接触判定
			}

			if (!reversemode&&aa % (speed * ran3) == 0) {//ran3個目でreverseイベント
				setReverseIvent(bA, num, width1);
				reversemode = true;
			}
			if (reversemode) {
				attrset(COLOR_PAIR(1));
				mvaddstr(reverse.y, reverse.x, "-");
				if (aa%speed == 0) {
					reverse.y++;
				}

			}
			if (reverse.y == 20) {
				reversemode = false;
			}
			

			if (!invinciblemode&&aa % (speed*ran4) == 0) {//ran4個目でinvicibleイベント
				setInvincibleIvent(bA, num, width1);
				invinciblemode = true;
			}
			if (invinciblemode) {
				attrset(COLOR_PAIR(1));
				mvaddstr(invincible.y, invincible.x, "@");
				if (aa%speed == 0) {
					invincible.y++;
				}

			}
			if (invincible.y == 20) {
				invinciblemode = false;
			}



			
			if (!latemode&&aa%(speed*ran)==0) {//ran個目でlateイベント
				setLateIvent(bA, num, width1);
				latemode = true;
			}	
			if (latemode ) {
				attrset(COLOR_PAIR(1));
				mvaddstr(late.y, late.x, "*");
				if (aa%speed == 0) {
					late.y++;
				}
				
			}
			if (late.y == 20) {
				latemode = false;
			}

			if (!upmode&&aa%(speed*ran2)==0) {//ran2個目でupイベント
				setUpIvent(bA, num, width1);
				upmode = true;
			}
			if (upmode) {
				attrset(COLOR_PAIR(1));
				mvaddstr(up.y, up.x, "*");
				if (aa%speed == 0) {
					up.y++;
				}

			}
			if (up.y == 20) {
				upmode = false;
			}

			//接触判定
			contactlateivent(count);
			contactUpivent(count);
			contactInvincibleivent(count);
			contactReverseivent(count);


			attrset(COLOR_PAIR(2));

			if (contact) {
				if (aa%speed == 0) {
					bb++;
				}
				if (bb == 20) {
					contact = false;
				}
			}

			if (re) {
				if (aa%speed == 0) {
					cc++;
				}
				if (cc == 20) {
					re = false;
				}
			}

			noecho();
			cbreak();
			keypad(stdscr, TRUE);
			int key;
			timeout(0);
			key = getch();
			if (key == KEY_RIGHT) {
				if (count < width1 +limitx1-1) {
					if (re) {
						count--;
					}
					else {
						count++;
					}
				}
			}
			if (key == KEY_LEFT) {
				if (count > limitx1 + 1) {
					if (re) {
						count++;
					}
					else {
						count--;
					}
				}

			}

			fallWall(bA, aa, num);//壁を落とす


			//壁にぶつかる
			if (gameover) {
				clock_t end = clock();
				while (1) {
					erase();
					displaygameover();
					mvprintw(22, 50, "time %lf秒", (double)(end - start) / 1000);
					txtArray((double)(end - start) / 1000);
					key = getch();
					if (key == KEY_UP) {
						gameover = false;
						gamestart = true;
						latemode = false;
						upmode = false;
						invinciblemode = false;
						contact = false;
						reversemode = false;
						re = false;
						break;
					}
					refresh();
				}
			}
			if (gamestart) {
				break;
			}

			refresh();
		}

	}

	return 0;
}

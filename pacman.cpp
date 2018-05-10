// FILE: main.cpp

// preprocessor
#include <iostream>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
using namespace std;
// declaration

struct Player {
    // position x, y
    int pos_x;
    int pos_y;

    // current direction of player
    // up: w
    // left: a
    // right: d
    // down: s
    char dir;
};


struct Ghost{
	// position x, y
    int pos_x;
    int pos_y;

    // current direction of player
    // up: w
    // left: a
    // right: d
    // down: s
    char dir;
};

#define num 9
char map[num][num];

void init_map(){
	// create wall
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            map[i][j] = '#';
        }
    }	
	
    // create fooood
    for (int i = 1; i < 8; i++) {
        for (int j = 1; j < 8; j++) {
            map[i][j] = '.';
        }
    }
    
	// create obstacle
	map[4][5] = map[3][6] = map[1][7] = map[7][5] = map[6][1] = 'X';
}

void display(){
	system ("cls");	
	for (int i = 0; i < 9; i++){
		for (int j = 0; j < 9; j++){
			cout << ' ' << map[i][j]; 
		}
		cout << ' ' <<endl;
	}
	_sleep(50);
}

void move(int x, int y, int dx, int dy){
	map[x][y] = ' ';
	x = x + dx;
	y = y + dy;
	map[x][y] = 'Q';
	display();
}

int checkF(){
	int count;
	for (int i = 1; i < 8; i++){
		for (int j = 1; j < 8; j++){
			if (map[i][j] == '.'){
				count ++;
			}
		}
	}
	return count;
}


int main() {
	
	init_map();
	
    Player quoc;
    //Ghost nam;
    quoc.pos_x = quoc.pos_y = 1;
    //nam.pos_x = nam.pos_y = 7;
    map[quoc.pos_x][quoc.pos_y] = 'Q';
    //map[nam.pos_x][nam.pos_y] = 'N';
    
	display();
	//====================================================PLAYER=============================================================//
	while (checkF() != 0){
		move(quoc.pos_x, quoc.pos_y, 0 , 1);
	}
}

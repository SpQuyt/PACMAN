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
	char name;
    // current direction of player
    // up: w
    // left: a
    // right: d
    // down: s
    char dir;
};


#define num 15
char map[num][num] = {	
		'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',
		'#','.','.','.','.','.','.','.','.','.','.','.','.','.','#',
		'#','.','#','#','#','#','#','#','.','#','.','#','#','.','#',
		'#','.','.','.','.','.','.','#','.','#','.','#','.','.','#',
		'#','.','.','.','.','.','.','#','.','#','.','#','.','.','#',
		'#','#','#','#','#','#','#','#','.','#','.','#','.','.','#',
		'#','.','.','.','.','.','.','.','.','#','.','#','.','.','#',
		'#','.','#','#','#','#','#','#','#','#','.','#','#','.','#',
		'#','.','.','.','.','.','.','.','.','.','.','.','.','.','#',
		'#','.','#','#','#','#','#','#','#','#','.','#','#','.','#',
		'#','.','.','.','.','.','.','.','.','.','.','.','.','.','#',
		'#','.','#','#','#','#','#','#','#','#','.','#','#','.','#',
		'#','.','#','.','.','.','.','.','.','.','.','.','.','.','#',
		'#','.','.','.','.','.','.','#','.','.','.','.','.','.','#',
		'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'	
	};
	
int eaten_map[num][num];


void init_map(){
	//init eaten map
	for (int i = 0; i < num; i++) {
        for (int j = 0; j < num; j++) {
            eaten_map[i][j] = 0;
        }
    }	
}

void display(){
	system ("cls");	
	for (int i = 0; i < num; i++){
		for (int j = 0; j < num; j++){
			cout << ' ' << map[i][j]; 
		}
		cout << ' ' <<endl;
	}
	_sleep(300);
}

void moveQ(Player &quoc, int dx, int dy){				//move of player
	map[quoc.pos_x][quoc.pos_y] = ' ';
	quoc.pos_x += dx;
	quoc.pos_y += dy;
	map[quoc.pos_x][quoc.pos_y] = quoc.name;
	eaten_map[quoc.pos_x][quoc.pos_y] = 1;

}

void moveN(Player &nam, char dir){						//move of ghost
	if (eaten_map[nam.pos_x][nam.pos_y] == 1){
		map[nam.pos_x][nam.pos_y] = ' ';
	}
	else{
		map[nam.pos_x][nam.pos_y] = '.';
	}
	switch(dir){
		case 'w':
			nam.pos_x += -1;
			nam.pos_y += 0;
			break;
		case 's':
			nam.pos_x += 1;
			nam.pos_y += 0;
			break;
		case 'a':
			nam.pos_x += 0;
			nam.pos_y += -1;
			break;
		case 'd':
			nam.pos_x += 0;
			nam.pos_y += 1;
			break;
	}
	map[nam.pos_x][nam.pos_y] = nam.name;

}

int checkF(){									// check if all food is eaten
	int count;
	for (int i = 1; i < num-1; i++){
		for (int j = 1; j < num-1; j++){
			if (map[i][j] == '.'){
				count ++;
			}
		}
	}
	return count;
}

int checkPvG (Player Q, Player N){				// check if player and ghosts meet
	if (Q.pos_x == N.pos_x && Q.pos_y == N.pos_y){
		return true;
	}
	else{
		return false;
	}
}


int checkWalls(Player &H, int dx, int dy){		//check if upward cell is a wall / obstacles
	if (map[H.pos_x + dx][H.pos_y + dy] == '#' || map[H.pos_x + dx][H.pos_y + dy] == 'N' || map[H.pos_x + dx][H.pos_y + dy] == 'H' || map[H.pos_x + dx][H.pos_y + dy] == 'X'){
		return true;
	}
	else{
		return false;
	}
}


void runningPlayer (Player &quoc){
	if (kbhit()){
		if (GetAsyncKeyState(VK_UP)){
			quoc.dir = 'w';
		}
		else if (GetAsyncKeyState(VK_DOWN)){
			quoc.dir = 's';
		}
		else if (GetAsyncKeyState(VK_RIGHT)){
			quoc.dir = 'd';
		}
		else if (GetAsyncKeyState(VK_LEFT)){
			quoc.dir = 'a';
		}
	}
	switch (quoc.dir){
		case 'a':
			if (checkWalls(quoc, 0, -1) == false){
				moveQ(quoc, 0, -1);break;
			}
			else{
				break;
			}
		case 'd':
			if (checkWalls(quoc, 0, 1) == false){
				moveQ(quoc, 0, 1);break;
			}
			else{
				break;
			}
		case 'w':
			if (checkWalls(quoc, -1, 0) == false){
				moveQ(quoc, -1, 0);break;
			}
			else{
				break;
			}
		case 's':
			if (checkWalls(quoc, 1, 0) == false){
				moveQ(quoc, 1, 0);break;
			}
			else{
				break;
			}
	}	
}

char gen_dir(Player &H){				//generate a random direction for ghosts
	int i = 0;
	int avail_next[4] = {};
	srand(time(NULL));
	if (checkWalls(H, 0, 1) == false){
		avail_next[i] = 'd';
		i++;
	}
	if (checkWalls(H, 0, -1) == false){
		avail_next[i] = 'a';
		i++;
	}
	if (checkWalls(H, 1, 0) == false){
		avail_next[i] = 's';
		i++;
	}
	if (checkWalls(H, -1, 0) == false){
		avail_next[i] = 'w';
		i++;
	}
	int random = rand() % i;

	i = 0;
	return avail_next[random];
}

void runningGhost (Player &nam){
	switch (nam.dir){
		case 'a':
			if (checkWalls(nam, 0, -1) == false){
				moveN(nam, nam.dir);
				break;
			}
			else{
				nam.dir = gen_dir(nam);
				moveN(nam, nam.dir);
				break;
			}
		case 'd':
			if (checkWalls(nam, 0, 1) == false){
				moveN(nam, nam.dir);
				break;
			}
			else{
				nam.dir = gen_dir(nam);
				moveN(nam, nam.dir);
				break;
			}
		case 'w':
			if (checkWalls(nam, -1, 0) == false){
				moveN(nam, nam.dir);
				break;
			}
			else{
				nam.dir = gen_dir(nam);
				moveN(nam, nam.dir);
				break;
			}
		case 's':
			if (checkWalls(nam, 1, 0) == false){
				moveN(nam, nam.dir);
				break;
			}
			else{
				nam.dir = gen_dir(nam);
				moveN(nam, nam.dir);
				break;
			}
	}	
}

int main() {
	
	init_map();
	
    Player quoc;				//player
    Player nam, huong, hong;	//ghosts
    
    quoc.pos_x = quoc.pos_y = 1;
	quoc.name = 'Q';
    nam.pos_x = nam.pos_y = 6;
	nam.name = 'N';
    huong.pos_x = huong.pos_y = 3;
	huong.name = 'X';
    hong.pos_x = hong.pos_y = 10;
	hong.name = 'H';

    
    map[quoc.pos_x][quoc.pos_y] = quoc.name;
    map[nam.pos_x][nam.pos_y] = nam.name;
    map[huong.pos_x][huong.pos_y] = huong.name;
    map[hong.pos_x][hong.pos_y] = hong.name;
    
	display();
	nam.dir = gen_dir(nam);
	huong.dir = gen_dir(huong);
	hong.dir = gen_dir(hong);
	
	//====================================================PLAYER=============================================================//

	while (checkF() != 0 && checkPvG(quoc,nam) == false && checkPvG(quoc,huong) == false && checkPvG(quoc,hong) == false){   
		runningPlayer(quoc);
		runningGhost(nam);
		runningGhost(huong);
		runningGhost(hong);
		display();
	}
}

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


#define num 9
char map[num][num];
int eaten_map[num][num];

void init_map(){
	//init eaten map
	for (int i = 0; i < num; i++) {
        for (int j = 0; j < num; j++) {
            eaten_map[i][j] = 0;
        }
    }	
    
	// create wall
    for (int i = 0; i < num; i++) {
        for (int j = 0; j < num; j++) {
            map[i][j] = '#';
        }
    }	
	
    // create fooood
    for (int i = 1; i < num-1; i++) {
        for (int j = 1; j < num-1; j++) {
            map[i][j] = '.';
        }
    }
    
	// create obstacle
	map[4][5] = map[3][6] = map[1][7] = map[7][5] = map[6][1] = '#';
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
	map[quoc.pos_x][quoc.pos_y] = 'Q';
	eaten_map[quoc.pos_x][quoc.pos_y] = 1;

}

void moveN(Player &nam, char dir){				//move of ghost
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
	map[nam.pos_x][nam.pos_y] = 'N';

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
	if (map[H.pos_x+dx][H.pos_y+dy] == '#'){
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

char gen_dir(int temp){				//generate a random direction for ghosts
	char dir;
	switch(temp){
		case 1:
			dir = 'w'; break;
		case 2:
			dir = 's'; break;
		case 3:
			dir = 'a'; break;
		case 4:
			dir = 'd'; break;
	}
	return dir;
}

void runningGhost (Player &nam){
	srand(time(NULL));
	switch (nam.dir){
		case 'a':
			if (checkWalls(nam, 0, -1) == false){
				moveN(nam, nam.dir);
				break;
			}
			else{
				nam.dir = gen_dir(rand() % 4 + 1);
				//moveN(nam, nam.dir);
				break;
			}
		case 'd':
			if (checkWalls(nam, 0, 1) == false){
				moveN(nam, nam.dir);
				break;
			}
			else{
				nam.dir = gen_dir(rand() % 4 + 1);
				//moveN(nam, nam.dir);
				break;
			}
		case 'w':
			if (checkWalls(nam, -1, 0) == false){
				moveN(nam, nam.dir);
				break;
			}
			else{
				nam.dir = gen_dir(rand() % 4 + 1);
				//moveN(nam, nam.dir);
				break;
			}
		case 's':
			if (checkWalls(nam, 1, 0) == false){
				moveN(nam, nam.dir);
				break;
			}
			else{
				nam.dir = gen_dir(rand() % 4 + 1);
				//moveN(nam, nam.dir);
				break;
			}
	}	
}

int main() {
	
	init_map();
	
    Player quoc;				//player
    Player nam, huong, hong;	//ghosts
    
    quoc.pos_x = quoc.pos_y = 1;
    nam.pos_x = nam.pos_y = 5;
    //huong.pos_x = huong.pos_y = 3;
    //hong.pos_x = hong.pos_y = 4;
    
    map[quoc.pos_x][quoc.pos_y] = 'Q';
    map[nam.pos_x][nam.pos_y] = 'N';
    //map[huong.pos_x][huong.pos_y] = 'N';
    //map[hong.pos_x][hong.pos_y] = 'N';
    
	display();
	nam.dir = gen_dir(rand() % 4 + 1);
	//huong.dir = gen_dir(rand() % 4 + 1);
	//hong.dir = gen_dir(rand() % 4 + 1);
	//====================================================PLAYER=============================================================//
	while (checkF() != 0 ){   //&& checkPvG(quoc,nam) == false && checkPvG(quoc,huong) == false && checkPvG(quoc,hong) == false
		//runningPlayer(quoc);
		runningGhost(nam);
		//runningGhost(huong);
		//runningGhost(hong);
		display();
	}
}

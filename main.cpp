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

int checkF (char **map){
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
	srand(time(NULL));
    // it's time to create map
    // create the blank playground size 9x9
	
    char **map;
    map = new char *[9];
    for(int i = 0; i < 9; i++)
        map[i] = new char[9];

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
    
    
    Player quoc;
    Ghost nam;
    quoc.pos_x = quoc.pos_y = 1;
    nam.pos_x = nam.pos_y = 7;
    map[quoc.pos_x][quoc.pos_y] = 'Q';
    map[nam.pos_x][nam.pos_y] = 'N';
    
    for (int i = 0; i < 9; i++){
    	for (int j = 0; j < 9; j++){
    		cout << ' ' << map[i][j]; 
		}
	cout << ' ' <<endl;
	}
	
	//====================================================PLAYER=============================================================//
	quoc.dir = 'd';
	while (checkF(map) != 0 && (quoc.pos_x != nam.pos_x || quoc.pos_y != nam.pos_y)){
		switch (quoc.dir){
			case 'w': 												//nut huong len tren
					if (map[quoc.pos_x - 1][quoc.pos_y] == 'X'){  //truong hop cham vat can
						if (GetAsyncKeyState(VK_RIGHT)) {
							quoc.dir = 'd';
							break;
						}
						else if (GetAsyncKeyState(VK_UP)) {
							quoc.dir = 'w';
							break;
						}
						else if (GetAsyncKeyState(VK_LEFT)) {
							quoc.dir = 'a';
							break;
						}
						else if (GetAsyncKeyState(VK_DOWN)){
							quoc.dir = 's';
							break;
						}
					}
					else if (GetAsyncKeyState(VK_DOWN)) {
						quoc.dir = 's';
						break;
					}
					else if (GetAsyncKeyState(VK_LEFT)) {
						quoc.dir = 'a';
						break;
					}
					else if (GetAsyncKeyState(VK_RIGHT)) {
						quoc.dir = 'd';
						break;
					}
					else if (quoc.pos_x == 1){ // truong hop cham tuong
						if (GetAsyncKeyState(VK_RIGHT)) {
							quoc.dir = 'd';
							break;
						}
						else if (GetAsyncKeyState(VK_UP)) {
							quoc.dir = 'w';
							break;
						}
						else if (GetAsyncKeyState(VK_LEFT)) {
							quoc.dir = 'a';
							break;
						}
						else if (GetAsyncKeyState(VK_DOWN)){
							quoc.dir = 's';
							break;
						}
					}
					else{
						map[quoc.pos_x][quoc.pos_y] = ' ';
						quoc.pos_x--;
						map[quoc.pos_x][quoc.pos_y] = 'Q';		
						system ("cls");	
						for (int i = 0; i < 9; i++){
						    for (int j = 0; j < 9; j++){
						    	cout << ' ' << map[i][j]; 
							}
								cout << ' ' <<endl;
						}
						usleep(100000);	usleep(100000); usleep(100000); usleep(100000);
					}
				break;
				
			case 'a': 													// nut huong ben trai
					if (map[quoc.pos_x][quoc.pos_y - 1] == 'X'){ // truong hop cham vat can
						if (GetAsyncKeyState(VK_RIGHT)) {
							quoc.dir = 'd';
							break;
						}
						else if (GetAsyncKeyState(VK_UP)) {
							quoc.dir = 'w';
							break;
						}
						else if (GetAsyncKeyState(VK_LEFT)) {
							quoc.dir = 'a';
							break;
						}
						else if (GetAsyncKeyState(VK_DOWN)){
							quoc.dir = 's';
							break;
						}
					}
					else if (GetAsyncKeyState(VK_DOWN)) {
						quoc.dir = 's';
						break;
					}
					else if (GetAsyncKeyState(VK_UP)) {
						quoc.dir = 'w';
						break;
					}
					else if (GetAsyncKeyState(VK_RIGHT)) {
						quoc.dir = 'd';
						break;
					}
					else if (quoc.pos_y == 1){ // truong hop cham tuong
						if (GetAsyncKeyState(VK_RIGHT)) {
							quoc.dir = 'd';
							break;
						}
						else if (GetAsyncKeyState(VK_UP)) {
							quoc.dir = 'w';
							break;
						}
						else if (GetAsyncKeyState(VK_LEFT)) {
							quoc.dir = 'a';
							break;
						}
						else if (GetAsyncKeyState(VK_DOWN)){
							quoc.dir = 's';
							break;
						}
					}
					else{
						map[quoc.pos_x][quoc.pos_y] = ' ';
						quoc.pos_y--;
						map[quoc.pos_x][quoc.pos_y] = 'Q';	
						system ("cls");	
						for (int i = 0; i < 9; i++){
						    for (int j = 0; j < 9; j++){
						    	cout << ' ' << map[i][j]; 
							}
								cout << ' ' <<endl;
						}
						usleep(100000);	usleep(100000); usleep(100000); usleep(100000);
					}
				break;
	
			case 'd': 														// nut huong ben phai
					if (map[quoc.pos_x][quoc.pos_y + 1] == 'X'){ // truong hop cham vat can
						if (GetAsyncKeyState(VK_RIGHT)) {
							quoc.dir = 'd';
							break;
						}
						else if (GetAsyncKeyState(VK_UP)) {
							quoc.dir = 'w';
							break;
						}
						else if (GetAsyncKeyState(VK_LEFT)) {
							quoc.dir = 'a';
							break;
						}
						else if (GetAsyncKeyState(VK_DOWN)){
							quoc.dir = 's';
							break;
						}
					}
					else if (GetAsyncKeyState(VK_DOWN)) {
						quoc.dir = 's';
						break;
					}
					else if (GetAsyncKeyState(VK_UP)) {
						quoc.dir = 'w';
						break;
					}
					else if (GetAsyncKeyState(VK_LEFT)) {
						quoc.dir = 'a';
						break;
					}
					else if (quoc.pos_y == 7){ // truong hop cham tuong
						if (GetAsyncKeyState(VK_RIGHT)) {
							quoc.dir = 'd';
							break;
						}
						else if (GetAsyncKeyState(VK_UP)) {
							quoc.dir = 'w';
							break;
						}
						else if (GetAsyncKeyState(VK_LEFT)) {
							quoc.dir = 'a';
							break;
						}
						else if (GetAsyncKeyState(VK_DOWN)){
							quoc.dir = 's';
							break;
						}
					}
					else{
						map[quoc.pos_x][quoc.pos_y] = ' ';
						quoc.pos_y++;
						map[quoc.pos_x][quoc.pos_y] = 'Q';	
						system ("cls");	
						for (int i = 0; i < 9; i++){
						    for (int j = 0; j < 9; j++){
						    	cout << ' ' << map[i][j]; 
							}
								cout << ' ' <<endl;
						}
						usleep(400000);
					}
				break;
				
			case 's': 														// nut huong xuong duoi
					if (map[quoc.pos_x + 1][quoc.pos_y] == 'X'){ // truong hop cham vat can
						if (GetAsyncKeyState(VK_RIGHT)) {
							quoc.dir = 'd';
							break;
						}
						else if (GetAsyncKeyState(VK_UP)) {
							quoc.dir = 'w';
							break;
						}
						else if (GetAsyncKeyState(VK_LEFT)) {
							quoc.dir = 'a';
							break;
						}
						else if (GetAsyncKeyState(VK_DOWN)){
							quoc.dir = 's';
							break;
						}
					}
					else if (GetAsyncKeyState(VK_RIGHT)) {
						quoc.dir = 'd';
						break;
					}
					else if (GetAsyncKeyState(VK_UP)) {
						quoc.dir = 'w';
						break;
					}
					else if (GetAsyncKeyState(VK_LEFT)) {
						quoc.dir = 'a';
						break;
					}
					else if (quoc.pos_x == 7){ 					// truong hop cham tuong
						if (GetAsyncKeyState(VK_RIGHT)) {
							quoc.dir = 'd';
							break;
						}
						else if (GetAsyncKeyState(VK_UP)) {
							quoc.dir = 'w';
							break;
						}
						else if (GetAsyncKeyState(VK_LEFT)) {
							quoc.dir = 'a';
							break;
						}
						else if (GetAsyncKeyState(VK_DOWN)){
							quoc.dir = 's';
							break;
						}
					}
					else{
						map[quoc.pos_x][quoc.pos_y] = ' ';
						quoc.pos_x++;
						map[quoc.pos_x][quoc.pos_y] = 'Q';	
						system ("cls");	
						for (int i = 0; i < 9; i++){
						    for (int j = 0; j < 9; j++){
						    	cout << ' ' << map[i][j]; 
							}
								cout << ' ' <<endl;
						}
						usleep(100000);	usleep(100000); usleep(100000); usleep(100000);
					}
				break;
		} // end of quoc
	
	//==========================================================GHOST======================================================//
	
	}
}

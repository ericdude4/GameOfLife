#include <iostream>
#include <malloc.h>
#include "random_generator.h"
using namespace std;

/*
Author: Eric Froese
Student Number: 5029954
Description: This program emulates the Game of Life, and simply prints
the resulting 20 generations to the console.
Course: COSC 4F00
Due Date: October 30, 2015
Assignment: 1
*/

int field [20][20];
int buffer [20][20];
int generation = 0;

void initField(){		// 1= live, 0= dead, 2 = dying (just for cool effect)
	int x, y, z;
	cout << "Seed 1: ";	//prompt user for seeds in terminal window
	cin >> x;
	cout << "Seed 2: ";
	cin >> y;
	cout << "Seed 3: ";
	cin >> z;
	random_generator randy(x, y, z);
	double state;
	for (int i = 0; i < 20; ++i){
		for (int j = 0; j < 20; ++j){
			state = randy.nextDouble();
			if (state < 0.6) field[i][j] = 0;
			if (state >= 0.6) field[i][j] = 1;
			buffer[i][j] = field[i][j];
		}
	}
}

int adjacent(int x, int y){
	int count = 0;
	int neighbor_x;
	int neighbor_y;

	for (int i = -1; i <= 1; ++i){ //itterate through the 8 surrounding locations
		for (int j = -1; j <= 1; ++j){
			if (i != 0 || j != 0){
				neighbor_x = x+i;
				neighbor_y = y+j;
				if (neighbor_x == -1) neighbor_x = 19;
				//neighbor_x = (neighbor_x == -1)? 19:neighbor_x;
				if (neighbor_x == 20) neighbor_x = 0;
				if (neighbor_y == -1) neighbor_y = 19;
				if (neighbor_y == 20) neighbor_y = 0;
				if (field[neighbor_x][neighbor_y] == 1) count ++;
			}
		}
	}
	return count;
}

void GameOfLife() {
	int adj;
	bool change = false;
	cout << "Generation: " << generation << endl;

    for (int x = 0; x < 20; ++x){
    	for (int y = 0; y < 20; ++y){
    		adj = adjacent(x,y);

    		if (field[x][y] == 1) {
    			cout << "X";//print out A for alive 
    		}

    		if (field[x][y] == 0) {
    			cout << " ";//print out ' ' for dead
    		}

    		if (field[x][y] == 0 && adj == 3){
    			buffer[x][y] = 1;	//birth
    			change = true;
    		}

    		if (field[x][y] == 1 && (adj < 2 || adj > 3)){
    			buffer[x][y] = 0; //death due to lonliness or overcrowding
    			change = true;
    		}
    	}
    	cout << endl;
    }
    cout << endl << endl;

	for (int i = 0; i < 20; ++i){
		for (int j = 0; j < 20; ++j){
			field[i][j] = buffer[i][j];	//copy buffer to field
		}
	}
	generation++;
}

int main(int argc, char **argv) {
	initField();	//set locations on field to dead
	while(generation < 21){
		GameOfLife();
	}
	return 0;
}

#ifdef __unix__
	#include <GL/freeglut.h>
#elif defined(_WIN32) || defined(WIN32)
	#include <freeglut.h>
#endif 
#include <iostream>
#include <malloc.h>
#include <FreeImage.h>
#include "random_generator.h"
using namespace std;

/*
Author: Eric Froese
Student Number: 5029954
Description: This program emulates the Game of Life, and utilizes the glut
library to display the game in a nice GUI. It also prints the resulting 
generations to the console. This program only executes up to generation 20,
or whenever a generation appears where there is no change from the previous
generation. If you have difficulty running this program do to the glut
libraries, I have also included "GameOfLife_noGUI.cpp" which simply prints
the resulting generations to the console.
Course: COSC 4F00
Due Date: October 30, 2015
Assignment: 1
*/

int field [20][20];	//this stores the field that is printed and used for simulation
int buffer [20][20];//this stores the changes between generations
int generation = 0;

void initField(){		// 1= live, 0= dead, 2 = dying (just for cool effect)
	int x, y, z;
	cout << "Seed 1: ";
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
			if (state < 0.6) field[i][j] = 0;	//dead
			if (state >= 0.6) field[i][j] = 1;	//alive
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

void keybd(unsigned char key, int x, int y) {
	switch (key) {
		case 'q':
		case 'Q':
			exit(0);
			break;
	}
}

void drawSquare(int x, int y, int s){

	if (s == 1) {
		glColor3f(255, 255, 255);
	}
	else if (s == 2) {
		glColor3f(0.2f,0.2f,0.2f);
	}
	else if (s == 0) {
		glColor3f(0,0,0);
	}

	glBegin(GL_POLYGON);
		glVertex2i(x*10, y*10);
		glVertex2i(x*10, y*10+10);
		glVertex2i(x*10+10, y*10+10);
		glVertex2i(x*10+10, y*10);
	glEnd();
}

void wasteTime(int time){	//slows down game by doing rediculous loop, as we were
							//taught in computer graphics
	time *= 100;
	int r = 1234567;
	int res;
	int i;

	for (i = 0; i < time; i++){
		r = ((r^2)*(r^4/r^-2))/r^-3;
	}
}

void poly(void) {
	if (generation >20) return;	//stop excecution after 20 generations
	int adj;
	bool change = false;
	cout << "Generation: " << generation << endl;

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    for (int x = 0; x < 20; ++x){
    	for (int y = 0; y < 20; ++y){
    		adj = adjacent(x,y);

    		if (field[x][y] == 1) {
    			drawSquare(x,y,1);
    			cout << "X";//print out A for alive 
    		}

    		if (field[x][y] == 0) {
    			drawSquare(x,y,0);
    			cout << " ";//print out * for dead
    		}

    		if (field[x][y] == 0 && adj == 3){
    			buffer[x][y] = 1;
    			change = true;
    		}

    		if (field[x][y] == 1 && (adj < 2 || adj > 3)){
    			buffer[x][y] = 2; //dead, make the square light grey at first to simulate dying
    			change = true;
    		}

    		if (field[x][y] == 2){
    			drawSquare(x,y,2);
    			buffer[x][y] = 0;//dead, but now set to zero so drawn as black square
    			cout << " ";
    			change = true;
    		}
    	}
    	cout << endl;
    }
    cout << endl << endl;
	wasteTime(300000);//this just slows down the program to be able to see the generations
	glFlush();
	for (int i = 0; i < 20; ++i){
		for (int j = 0; j < 20; ++j){
			field[i][j] = buffer[i][j];
		}
	}
	generation++;
	if (change == false) generation = 21; //stop excecution if no change this generation
}

int main(int argc, char **argv) {
	initField();	//set locations on field to dead

	glutInit(&argc, argv);

	glutCreateWindow("Get a Life!");
	//glutFullScreen();
	gluOrtho2D(0, 200, 0, 200);
	glutPostRedisplay();
	glutDisplayFunc(poly);
	glutIdleFunc(poly); //this is the method poly() that is called in the glut loop
	glutKeyboardFunc(keybd);
	glutMainLoop();

	return 0;
}
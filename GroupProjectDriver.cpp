//============================================================================
// Name        : Tetris Driver.cpp
// Author      : Dr. Booth
// Version     :
// Copyright   : Your copyright notice
// Description : Main Driver For Group Project
//============================================================================

#include <iostream>
#include "GroupProject.h"
using namespace std;

void Player(void);
GroupProject* app;

int main() {
	GLUT_Plotter* g = new GLUT_Plotter(); //Create plotter 
	app = new GroupProject(g);                 //Create Game (Tetris)
	g->RegisterIdleFunc(Player);          //Register Callback 
	g->MainLoop();                        //Enter main loop
	return 0;
}

void Player(void){
	app->Play();
}


#ifndef SUDOKU_EASYX_H
#define SUDOKU_EASYX_H

#include <conio.h>
#include <graphics.h>
#include <time.h>

int gameBoardCopy[15][15], holeBoard[15][15];
int highLightBoard[15][15], wrongHoleBoard[15][15];
int pause = 0;
int index = 1;
int pickednum = 1;
int process;
int seconds = 0, minutes = 0;
int restart, faults, endGame;
int allDone = 0, allRight = 0;
int noError = 0;

int showanswer = 0;
void JudgeInterface();
int AnswerCheck();
void InitDataSet();
void interface1();
void interface2();
void interface3();
void func1();
void func2();
void func3();
void end();
void GameDraw();
void GameUpdate();
void HighLight(int);
void (*fun[2])() = { func1,func3 };
COORD FindLeftUpperCorner(COORD);
int FindMistake();
int HoleCheck();
void GameInit(int[][15]);
void Dig();

COORD currentPos = { 0,0 }, numPos = { 10,0 }, coord, waitPos;
clock_t t1, t2;
ExMessage msg;

#endif;

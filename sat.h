
#ifndef WORKSHOP_GLOBAL_H
#define WORKSHOP_GLOBAL_H

#include <iostream>
#include <fstream>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
using namespace std;

#define CHOOSE_SOLUTION 500
#define NoAnwser -1
#define MAXSIZE 6 

typedef int status;

typedef struct VarNode {
    int data = 0;
    VarNode *next{};
}DataNode;

typedef struct ClauseNode {
    int num_of_var = 0;
    VarNode *right{};
    ClauseNode *down{};
}HeadNode;

struct consequence {
    int value = -1;
};

struct conse {
    int num = 0;
    int value = -1;
};

struct Count {
    int num = 0;
    int count = 0;
    Count *next=nullptr;
};

void initialInterface();
int Sat();
ClauseNode* CreateClause(int &,string &);
ClauseNode* CreateClauseForSudoku(int&, string&);
status DPLL_mini(ClauseNode *LIST,consequence *result);
status DPLL_Pro(ClauseNode* LIST, consequence* result);
ClauseNode* IsSingleClause(ClauseNode*);
status IsEmptyClause(ClauseNode*);
ClauseNode* ADDSingleClause(ClauseNode*,int);
ClauseNode* Duplication(ClauseNode*);
void DeleteClauseNode(ClauseNode*,ClauseNode*&); 
void DeleteVarNode(int,ClauseNode*&); 
void FreeClauseNode(ClauseNode* Clause);
int Choose_max(ClauseNode* LIST);

void show(struct consequence *,int);
void TrimBoard(int a[][15]);
void initboard(int a[][15]);
void randomDownPalace(int a[][15]);
int RandomBoardForDownPalace(int a[][15], int i, int j, int loc1, int loc2);
int RandomBoardForUpPalace(int a[][15], int i, int j, int loc1, int loc2);
int Digit1(int a[][15], int i, int j);
int Digit2(int a[][15], int i, int j);
void SudokuDisplay(conse* result, int VARNUM);
void UniquenessCheck(const int a[][15], const int b[][15]);
void InitialSkyLine(int a0[], int n);
void InitialTwodoku(int a[][15]);
void InitialGameBoard(const int a[][15], int b[][15], int numDigits);
void ShowInitialBoard(const int a[][15]);
string BoardTranslateIntoCnf(int a[][15],int holes);
string createSudokuToFile();
status SudoDPLL(ClauseNode *LIST,conse *result,int VARNUM);

int sudoku_easyx();

#endif  

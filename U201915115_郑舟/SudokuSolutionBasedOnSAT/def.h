//
// Created by 95498 on 2021/3/1.
//

#ifndef SOUKOUSOLUTIONBASEDONSAT_DEF_H
#define SOUKOUSOLUTIONBASEDONSAT_DEF_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <string.h>

extern int argumentsCounts,clausesCounts;
struct node
{
    int id;
    struct node *next;
};
struct clause
{
    struct node *clauseHead;
    struct clause *next;
};
extern int ans[];
extern double ranks[];

int creatClause(char *filePath ,struct clause **head);
int findUnitClause(struct clause *t);
void addClause(struct clause *s,int x);
void destroyClause(struct clause *t);
int copyCNF(struct clause* origin,struct clause **replication);
int DPLL(struct clause *s);
int betterDPLL(struct clause *s);
void destroyCNF(struct clause *s);
int dealWithClauseInOneLoop(struct clause *s,int x);
int CalculateWeight(struct clause *s);
void printAnswerToRes(const char filename[],int f,long t);
void playSudoku(char filename[80]);
//int scanAndTheChoice(struct clause *s);
#endif //SOUKOUSOLUTIONBASEDONSAT_DEF_H

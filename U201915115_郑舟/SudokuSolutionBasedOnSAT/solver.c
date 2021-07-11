//
// Created by 95498 on 2021/3/1.
//
#include "def.h"
int ans[5000];
int DPLL(struct clause *s)
{
    int f;
    while(s->clauseHead->id)
    {
        f=findUnitClause(s);
        int a=f>0?f:-f;
        ans[a]= f>0?1:0;
        if(dealWithClauseInOneLoop(s,f))    return 0;
        if(s->next==NULL) return 1;
    }//while
    struct clause *replication=NULL;
    int v=s->next->clauseHead->next->id;
    copyCNF(s,&replication);
    addClause(replication,v);
    if(DPLL(replication))   return 1;
    destroyCNF(replication);
    addClause(s,-v);
    if(DPLL(s))     return 1;
    else    return 0;
}

int betterDPLL(struct clause *s)
{
    int f;
    while(s->clauseHead->id)
    {
        f=findUnitClause(s);
        int a=f>0?f:-f;
        ans[a]= f>0?1:0;
        if(dealWithClauseInOneLoop(s,f))    return 0;
        if(s->next==NULL) return 1;
    }//while
//    printCNF(s);
//    printf("---------------------\n");
    struct clause *replication=NULL;
    int v=CalculateWeight(s);
//    if(v==200)
//        printf("\n");
    copyCNF(s,&replication);
    addClause(replication,v);
    if(betterDPLL(replication))   return 1;
    destroyCNF(replication);
    addClause(s,-v);
    if(betterDPLL(s))     return 1;
    else    return 0;
}
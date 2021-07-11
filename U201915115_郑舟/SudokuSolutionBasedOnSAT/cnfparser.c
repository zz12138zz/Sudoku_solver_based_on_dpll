//
// Created by 95498 on 2021/3/1.
//
#include "def.h"

int argumentsCounts=0,clausesCounts=0;
int creatClause(char *filePath ,struct clause **s)
{
    struct clause * head;
    head=(struct clause *)malloc(sizeof (struct clause));
    head->next=NULL;
    head->clauseHead=(struct node *)malloc(sizeof (struct clause));
    head->clauseHead->id=0;
    head->clauseHead->next=NULL;
    FILE *fp;
    char tips[20];
    int i;
    if ((fp = fopen(filePath, "r")) == NULL) return 0;
    do
    {
        fscanf(fp, "%s", &tips);
    } while (strcmp(tips, "p") != 0);
    fscanf(fp, "%s", &tips);
    fscanf(fp, "%d%d", &argumentsCounts, &clausesCounts);
    struct clause *ptr = head;
    for (i = 0; i < clausesCounts; i++)
    {
        ptr->next = (struct clause *) malloc(sizeof(struct clause));
        ptr = ptr->next;
        ptr->clauseHead = (struct node *) malloc(sizeof(struct node));
        ptr->clauseHead->id=0;
        ptr->clauseHead->next=NULL;
        ptr->next = NULL;
        struct node *temp = ptr->clauseHead;
        int x;
        do
        {
            fscanf(fp, "%d", &x);
            if (x != 0)
            {
                temp->next = (struct node *) malloc(sizeof(struct node));
                temp->next->id = x;
                temp->next->next = NULL;
                temp = temp->next;
                ptr->clauseHead->id++;
            }
        } while (x);
        if(ptr->clauseHead->id==1)
        {
            head->clauseHead->id++;
        }
    }
    fclose(fp);
    *s=head;
    return 1;
}

inline void destroyClause(struct clause *t)
{
    struct node *ptr = t->clauseHead;
    while (ptr)
    {
        struct node *temp = ptr;
        ptr = ptr->next;
        free(temp);
    }
    free(t);
}



inline int findUnitClause(struct clause *t)
{
    struct clause *ptr = t->next;
    while (ptr)
    {
        if (ptr->clauseHead->id==1) return ptr->clauseHead->next->id;
        ptr = ptr->next;
    }
    return 0;
}

inline void addClause(struct clause *s, int x)
{
    struct clause *ptr;
    ptr = (struct clause *) malloc(sizeof(struct clause));
    ptr->clauseHead = (struct node *) malloc(sizeof(struct node));
    ptr->clauseHead->id = 1;
    ptr->clauseHead->next = (struct node *) malloc(sizeof(struct node));
    ptr->clauseHead->next->id = x;
    ptr->clauseHead->next->next = NULL;
    ptr->next = s->next;
    s->next = ptr;
    s->clauseHead->id++;
}

int copyCNF(struct clause *origin, struct clause **replication)
{
    struct clause *copy = NULL;
    if((copy=(struct clause *) malloc(sizeof(struct clause)))==NULL)    return 0;
    copy->clauseHead=(struct node *)malloc(sizeof (struct node));
    copy->clauseHead ->id=origin->clauseHead->id;
    copy->clauseHead->next=NULL;
    copy->next = NULL;
    struct clause *ptrToOriginClause = origin->next;
    while (ptrToOriginClause)
    {
        struct clause *ptrToCopyClause = (struct clause *) malloc(sizeof(struct clause));
        ptrToCopyClause->clauseHead = (struct node *) malloc(sizeof(struct node));
        ptrToCopyClause->clauseHead->id = ptrToOriginClause->clauseHead->id;
        ptrToCopyClause->clauseHead->next = NULL;
        struct node *ptrToOriginLiteral = ptrToOriginClause->clauseHead->next;
        while (ptrToOriginLiteral)
        {
            struct node *ptrToCopyLiteral;
            ptrToCopyLiteral = (struct node *) malloc(sizeof(struct node));
            ptrToCopyLiteral->id = ptrToOriginLiteral->id;
            ptrToCopyLiteral->next = ptrToCopyClause->clauseHead->next;
            ptrToCopyClause->clauseHead->next = ptrToCopyLiteral;
            ptrToOriginLiteral = ptrToOriginLiteral->next;
        }
        ptrToOriginClause = ptrToOriginClause->next;
        ptrToCopyClause->next = copy->next;
        copy->next = ptrToCopyClause;
    }
    *replication = copy;
}

inline void destroyCNF(struct clause *s)
{
    struct clause *ptrToClause = s;
    struct clause *tempPtrToClause;
    while (ptrToClause)
    {
        tempPtrToClause = ptrToClause;
        ptrToClause = ptrToClause->next;
        destroyClause(tempPtrToClause);
    }
}

int dealWithClauseInOneLoop(struct clause *s,int x)
{
    int flag=1;
    struct clause *ptrToClause1=s;
    struct clause *ptrToClause2=s->next;
    while (ptrToClause2)
    {
        struct node *ptrToLiteral1=ptrToClause2->clauseHead;
        struct node *ptrToLiteral2=ptrToLiteral1->next;
        while (ptrToLiteral2)
        {
            if(ptrToLiteral2->id==x)
            {
                if(ptrToClause2->clauseHead->id==1) s->clauseHead->id--;
                struct clause *temp=ptrToClause2;
                ptrToClause1->next=ptrToClause2->next;
                ptrToClause2=ptrToClause2->next;
                destroyClause(temp);
                flag=0;
                break;
            }
            if(ptrToLiteral2->id==-x)
            {
                if((--ptrToClause2->clauseHead->id)==1)   s->clauseHead->id++;
                if(ptrToClause2->clauseHead->id==0) return 1;
                ptrToLiteral1->next=ptrToLiteral2->next;
                free(ptrToLiteral2);
                break;
            }
            ptrToLiteral1=ptrToLiteral1->next;
            ptrToLiteral2=ptrToLiteral2->next;
        }
        if(flag)
        {
            ptrToClause1=ptrToClause1->next;
            ptrToClause2=ptrToClause2->next;
        }
        else flag=1;
    }
    return 0;
}



double ranks[6010];
int CalculateWeight(struct clause *s)
{
    int i;
    for(i=0;i<=2*argumentsCounts;i++)
    {
        ranks[i]=0.0;
    }
    struct clause *ptr=s->next;
    while(ptr)
    {
        struct node *p=ptr->clauseHead->next;
        while (p)
        {
            int x=p->id>0?p->id:-p->id+argumentsCounts;
            ranks[x]+=1.0/pow(2,ptr->clauseHead->id);
            p=p->next;
        }
        ptr=ptr->next;
    }
    double maxCount=0.0;
    int bestLiteral=0;
    for(i=1;i<=2*argumentsCounts;i++)
    {
        maxCount=maxCount>ranks[i]?maxCount:ranks[i];
        bestLiteral=maxCount>ranks[i]?bestLiteral:i;
    }
    return bestLiteral>argumentsCounts?(argumentsCounts-bestLiteral):bestLiteral;
}

void printAnswerToRes(const char filename[], int f, long t)
{
    char answerName[1000];
    int i = 0;
    while (filename[i] != '.')
    {
        answerName[i] = filename[i];
        i++;
    }
    answerName[i] = '.';
    answerName[i + 1] = 'r';
    answerName[i + 2] = 'e';
    answerName[i + 3] = 's';
    answerName[i + 4] = '\0';
    FILE *fp;
    fp = fopen(answerName, "w+");
    fprintf(fp, "s %d\nv", f);
    for (i = 1; i <= argumentsCounts; i++)
    {
        fprintf(fp, " %d", i * (int) (2 * (ans[i] - 0.5)));
    }
    fprintf(fp, "\nt %ldms", t);
    fclose(fp);
}
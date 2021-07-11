//
// Created by 95498 on 2021/3/5.
//
#include "def.h"
//#include "sudoku.h"
#include <windows.h>
int rule_1(char filename[80]){
    FILE *fp;
    fp=fopen(filename,"a+");
    if(fp==NULL){
        printf("打开文件失败\n");
        return 0;
    }
    int i,j,k;                 //约束1，每一行，每一列，没有连续的三个0或者三个1
    for(i=1;i<=6;i++){             //每一行 考虑
        for(j=1;j<=4;j++){
            for(k=0;k<=2;k++){
                fprintf(fp,"%d ",(i-1)*6+j+k);
            }
            fprintf(fp,"0\n");
            for(k=0;k<=2;k++){
                fprintf(fp,"%d ",-((i-1)*6+j+k));
            }
            fprintf(fp,"0\n");
        }
    }
    for(j=1;j<=6;j++){            //每一列考虑
        for(i=1;i<=4;i++){
            for(k=0;k<=2;k++){
                for(k=0;k<=2;k++){
                    fprintf(fp,"%d ",(i-1)*6+j+k*6);
                }
                fprintf(fp,"0\n");
                for(k=0;k<=2;k++){
                    fprintf(fp,"%d ",-((i-1)*6+j+k*6));
                }
                fprintf(fp,"0\n");
            }
        }
    }
    fclose(fp);
    return 1;
} //此时，子句数为96个，变元为1~36

int rule_2(char filename[80]){      //每一行 ，每一列的0与1数目相等（=3），即任意4个单元，不全为0，不全为1
    FILE *fp;
    fp=fopen(filename,"a+");
    if(fp==NULL){
        printf("打开文件失败\n");
        return 0;
    }
    int i,j,k,w;
    int n;
    for(n=0;n<=5;n++){       //考虑行
        for(i=1;i<=3;i++){
            for(j=2;j<=4;j++){
                for(k=3;k<=5;k++){
                    for(w=4;w<=6;w++){
                        if(i<j&&j<k&&k<w){
                            fprintf(fp,"%d %d %d %d 0\n",i+6*n,j+6*n,k+6*n,w+6*n);
                            fprintf(fp,"%d %d %d %d 0\n",-(i+6*n),-(j+6*n),-(k+6*n),-(w+6*n));
                        }

                    }
                }

            }
        }
    }
    for(n=0;n<=5;n++){       //考虑列
        for(i=1;i<=13;i=i+6){
            for(j=7;j<=19;j=j+6){
                for(k=13;k<=25;k=k+6){
                    for(w=19;w<=31;w=w+6){
                        if(i<j&&j<k&&k<w){
                            fprintf(fp,"%d %d %d %d 0\n",i+n,j+n,k+n,w+n);
                            fprintf(fp,"%d %d %d %d 0\n",-(i+n),-(j+n),-(k+n),-(w+n));
                        }

                    }
                }

            }
        }
    }
    fclose(fp);
    return 1;
}

int rule_3(char filename[80]){                //没有两行，两列相同
    FILE *fp;
    fp=fopen(filename,"a+");
    if(fp==NULL){
        printf("打开文件失败\n");
        return 0;
    }
    int i,j,k,w,r,s,t;
    for(i=1;i<=6;i++){              //考虑行
        for(k=1;k<=6-i;k++){
            for(w=0;w<=6;w++){     //标记有几个为负
                if(w==0){
                    for(j=1;j<=6;j++){
                        fprintf(fp,"%d %d ",(i-1)*6+j,(i-1)*6+j+6*k);
                    }
                    fprintf(fp,"0\n");
                }
                else if(w==1){            //一个为负
                    for(r=1;r<=6;r++){       //标记当前对哪个数为负
                        for(j=1;j<=6;j++){
                            if(j==r) fprintf(fp,"%d %d ",-((i-1)*6+j),-((i-1)*6+j+6*k));
                            else fprintf(fp,"%d %d ",(i-1)*6+j,(i-1)*6+j+6*k);
                        }
                        fprintf(fp,"0\n");
                    }
                }
                else if(w==2){  //两个为负
                    for(r=1;r<=6;r++){
                        for(s=r+1;s<=6;s++){
                            for(j=1;j<=6;j++){
                                if(j==r||j==s)  fprintf(fp,"%d %d ",-((i-1)*6+j),-((i-1)*6+j+6*k));
                                else fprintf(fp,"%d %d ",(i-1)*6+j,(i-1)*6+j+6*k);
                            }
                            fprintf(fp,"0\n");
                        }
                    }
                }
                else if(w==3){  //三个为负
                    for(r=1;r<6;r++){
                        for(s=r+1;s<=6;s++){
                            for(t=s+1;t<=6;t++){
                                for(j=1;j<=6;j++){
                                    if(j==r||j==s||j==t) fprintf(fp,"%d %d ",-((i-1)*6+j),-((i-1)*6+j+6*k));
                                    else fprintf(fp,"%d %d ",(i-1)*6+j,(i-1)*6+j+6*k);
                                }
                                fprintf(fp,"0\n");
                            }
                        }
                    }
                }
                else if(w==4){           //四个为负
                    for(r=1;r<=6;r++){
                        for(s=r+1;s<=6;s++){
                            for(j=1;j<=6;j++){
                                if(j==r||j==s)  fprintf(fp,"%d %d ",(i-1)*6+j,(i-1)*6+j+6*k);
                                else fprintf(fp,"%d %d ",-((i-1)*6+j),-((i-1)*6+j+6*k));
                            }
                            fprintf(fp,"0\n");
                        }
                    }
                }
                else if(w==5){
                    for(r=1;r<=6;r++){       //标记当前对哪个数为负
                        for(j=1;j<=6;j++){
                            if(j==r) fprintf(fp,"%d %d ",(i-1)*6+j,(i-1)*6+j+6*k);
                            else fprintf(fp,"%d %d ",-((i-1)*6+j),-((i-1)*6+j+6*k));
                        }
                        fprintf(fp,"0\n");
                    }
                }
                else if(w==6){       //六个为负
                    for(j=1;j<=6;j++){
                        fprintf(fp,"%d %d ",-((i-1)*6+j),-((i-1)*6+j+6*k));
                    }
                    fprintf(fp,"0\n");
                }
            }

        }
    }

    for(i=1;i<=6;i++){   //考虑列
        for(k=i+1;k<=6;k++){
            for(w=0;w<=6;w++){
                if(w==0){
                    for(j=1;j<=6;j++){
                        fprintf(fp,"%d %d ",i+(j-1)*6,k+(j-1)*6);
                    }
                    fprintf(fp,"0\n");
                }
                else if(w==1){
                    for(r=1;r<=6;r++){       //标记当前对哪个数为负
                        for(j=1;j<=6;j++){
                            if(j==r) fprintf(fp,"%d %d ",-(i+(j-1)*6),-(k+(j-1)*6));
                            else fprintf(fp,"%d %d ",i+(j-1)*6,k+(j-1)*6);
                        }
                        fprintf(fp,"0\n");
                    }
                }
                else if(w==2){
                    for(r=1;r<=6;r++){
                        for(s=r+1;s<=6;s++){
                            for(j=1;j<=6;j++){
                                if(j==r||j==s)  fprintf(fp,"%d %d ",-(i+(j-1)*6),-(k+(j-1)*6));
                                else fprintf(fp,"%d %d ",i+(j-1)*6,k+(j-1)*6);
                            }
                            fprintf(fp,"0\n");
                        }
                    }
                }
                else if(w==3){  //三个为负
                    for(r=1;r<6;r++){
                        for(s=r+1;s<=6;s++){
                            for(t=s+1;t<=6;t++){
                                for(j=1;j<=6;j++){
                                    if(j==r||j==s||j==t) fprintf(fp,"%d %d ",-(i+(j-1)*6),-(k+(j-1)*6));
                                    else fprintf(fp,"%d %d ",i+(j-1)*6,k+(j-1)*6);
                                }
                                fprintf(fp,"0\n");
                            }
                        }
                    }
                }
                else if(w==4){           //四个为负
                    for(r=1;r<=6;r++){
                        for(s=r+1;s<=6;s++){
                            for(j=1;j<=6;j++){
                                if(j==r||j==s)  fprintf(fp,"%d %d ",i+(j-1)*6,k+(j-1)*6);
                                else fprintf(fp,"%d %d ",-(i+(j-1)*6),-(k+(j-1)*6));
                            }
                            fprintf(fp,"0\n");
                        }
                    }
                }
                else if(w==5){
                    for(r=1;r<=6;r++){       //标记当前对哪个数为负
                        for(j=1;j<=6;j++){
                            if(j==r) fprintf(fp,"%d %d ",i+(j-1)*6,k+(j-1)*6);
                            else fprintf(fp,"%d %d ",-(i+(j-1)*6),-(k+(j-1)*6));
                        }
                        fprintf(fp,"0\n");
                    }
                }
                else if(w==6){       //六个为负
                    for(j=1;j<=6;j++){
                        fprintf(fp,"%d %d ",-(i+(j-1)*6),-(k+(j-1)*6));
                    }
                    fprintf(fp,"0\n");
                }
            }
        }
    }
    fclose(fp);
    return 1;
}
int Gotoxy(int x, int y) //定位光标位置
{
    HANDLE handle; //定义句柄变量handle
    COORD coord; //定义结构体coord (坐标系coord)
    coord.X = x; //横坐标x
    coord.Y = y; //纵坐标y
    handle = GetStdHandle(STD_OUTPUT_HANDLE); //获取控制台输出句柄(值为-11)
    SetConsoleCursorPosition(handle, coord); //移动光标
}

void printSudoku(int solution[])
{
    Gotoxy(0,12);
    int i,j;
    for(i=1;i<=6;i++)
    {
        for(j=1;j<=6;j++)
        {
            if(solution[(i-1)*6+j]!=-1)
            {
                printf(" %d",solution[(i-1)*6+j]);
            }
            else
            {
                printf(" _");
            }
        }
        printf("\n");
    }
}

int creatSudoku(const int *initial, int counts, char filename[], int blank, int sudoku[],int function)
{
    FILE *fp;
    fp = fopen(filename, "w");
    if (fp == NULL)
    {
        printf("打开文件失败\n");
        return 0;
    }
    fprintf(fp,"p cnf 36 %d\n", counts + 2376);
    int i = 0;
    while (initial[i] != 0)
    {
        fprintf(fp,"%d 0\n", initial[i]);
        i++;
    }
    fclose(fp);
    rule_1(filename);
    rule_2(filename);
    rule_3(filename);
    if(function)    printf("数独文件写入成功！\n");
    struct clause *head;
    if(creatClause(filename,&head)==0)  return 0;
    if(function)    printf("数独生成中\n");
    if(betterDPLL(head)==0)    return 0;
    for (i = 1;i <= 36; i++)
    {
        sudoku[i] = ans[i];
    }
    i = 0;
    while (i < blank)
    {
        int hole;
        hole = rand() % 36 + 1;
        if (sudoku[hole] != -1)
        {
            sudoku[hole] = -1;
            i++;
        }
    }
    return 1;
}
void playSudoku(char filename[80])//将棋盘的初始条件以及三个约束，变成cnf公式，写入文件
{
    srand((unsigned)time(NULL));
    int x=rand()%36+1;
    int y;
    do{
        y=rand()%36+1;
    } while (x==y);
    int sudoku[37];
    int blank=rand()%10+15;
//    int blank=1;
    int initial[3]={x,y,0};
    if(creatSudoku(initial,2,filename,blank,sudoku,1)==0) printf("数独生成失败");
    else    printf("数独生成成功");
    int i;
    int userSolution[37];
    for(i=1;i<=36;i++)
    {
        userSolution[i]=sudoku[i];
    }
    printSudoku(userSolution);
    int position,value,flag=1;
    do{
        printf("请输入坐标以及您要填的答案，如若在第二行第三列填1，则输入23 1,若需要查看答案请输入0 0\n请输入：      \b\b\b\b\b\b"
               "\n                          \n                          "
               "\n                           \n                         ");
        Gotoxy(8,19);
        scanf("%d%d",&position,&value);
        if(position!=0)
        {
            if(position<0||(position>0&&position<11)||position/10>6||position%10>6||(value!=0&&value!=1))
            {
                printf("输入非法");
                getchar();
                getchar();
                Gotoxy(0,20);
                printf("        ");
                Gotoxy(0,18);
                continue;
            }
            position = ((position / 10) - 1) * 6 + position % 10;
            if (sudoku[position]!=-1)
            {
                printf("坐标非法");
                getchar();
                getchar();
                Gotoxy(0,20);
                printf("        ");
                Gotoxy(0,18);
                continue;
            }
            if(userSolution[position]==-1)  blank--;
            userSolution[position] = value;
            printSudoku(userSolution);
            if(blank==0)
            {
                int solution[40],temp[40];
                for(i=1;i<=36;i++)
                {
                    solution[i-1]=i*(int)((userSolution[i]-0.5)*2);
                }
                solution[i]=0;
                int f=creatSudoku(solution,36,filename,0,temp,0);
                if(f==1)
                {
                    printf("\n\n\n恭喜你，解答正确\n                 \n          ");
                    position=0;
                    flag=0;
                }
                else
                {
                    printf("\n\n\n抱歉，您的答案有误\n\n");
                    getchar();
                    getchar();
                    Gotoxy(0,20);
                    printf("        ");
                    Gotoxy(0,18);
                }
            }
        }
    }while(position!=0);
    if(flag==1)
    {
        printf("参考答案如下：                  \n");
        for (i = 1; i <= 36; i++)
        {
            if (i % 6 == 1)printf("\n");
            printf(" %d", ans[i]);
        }
    }
}

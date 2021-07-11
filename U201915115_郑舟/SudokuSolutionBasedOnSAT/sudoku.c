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
        printf("���ļ�ʧ��\n");
        return 0;
    }
    int i,j,k;                 //Լ��1��ÿһ�У�ÿһ�У�û������������0��������1
    for(i=1;i<=6;i++){             //ÿһ�� ����
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
    for(j=1;j<=6;j++){            //ÿһ�п���
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
} //��ʱ���Ӿ���Ϊ96������ԪΪ1~36

int rule_2(char filename[80]){      //ÿһ�� ��ÿһ�е�0��1��Ŀ��ȣ�=3����������4����Ԫ����ȫΪ0����ȫΪ1
    FILE *fp;
    fp=fopen(filename,"a+");
    if(fp==NULL){
        printf("���ļ�ʧ��\n");
        return 0;
    }
    int i,j,k,w;
    int n;
    for(n=0;n<=5;n++){       //������
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
    for(n=0;n<=5;n++){       //������
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

int rule_3(char filename[80]){                //û�����У�������ͬ
    FILE *fp;
    fp=fopen(filename,"a+");
    if(fp==NULL){
        printf("���ļ�ʧ��\n");
        return 0;
    }
    int i,j,k,w,r,s,t;
    for(i=1;i<=6;i++){              //������
        for(k=1;k<=6-i;k++){
            for(w=0;w<=6;w++){     //����м���Ϊ��
                if(w==0){
                    for(j=1;j<=6;j++){
                        fprintf(fp,"%d %d ",(i-1)*6+j,(i-1)*6+j+6*k);
                    }
                    fprintf(fp,"0\n");
                }
                else if(w==1){            //һ��Ϊ��
                    for(r=1;r<=6;r++){       //��ǵ�ǰ���ĸ���Ϊ��
                        for(j=1;j<=6;j++){
                            if(j==r) fprintf(fp,"%d %d ",-((i-1)*6+j),-((i-1)*6+j+6*k));
                            else fprintf(fp,"%d %d ",(i-1)*6+j,(i-1)*6+j+6*k);
                        }
                        fprintf(fp,"0\n");
                    }
                }
                else if(w==2){  //����Ϊ��
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
                else if(w==3){  //����Ϊ��
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
                else if(w==4){           //�ĸ�Ϊ��
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
                    for(r=1;r<=6;r++){       //��ǵ�ǰ���ĸ���Ϊ��
                        for(j=1;j<=6;j++){
                            if(j==r) fprintf(fp,"%d %d ",(i-1)*6+j,(i-1)*6+j+6*k);
                            else fprintf(fp,"%d %d ",-((i-1)*6+j),-((i-1)*6+j+6*k));
                        }
                        fprintf(fp,"0\n");
                    }
                }
                else if(w==6){       //����Ϊ��
                    for(j=1;j<=6;j++){
                        fprintf(fp,"%d %d ",-((i-1)*6+j),-((i-1)*6+j+6*k));
                    }
                    fprintf(fp,"0\n");
                }
            }

        }
    }

    for(i=1;i<=6;i++){   //������
        for(k=i+1;k<=6;k++){
            for(w=0;w<=6;w++){
                if(w==0){
                    for(j=1;j<=6;j++){
                        fprintf(fp,"%d %d ",i+(j-1)*6,k+(j-1)*6);
                    }
                    fprintf(fp,"0\n");
                }
                else if(w==1){
                    for(r=1;r<=6;r++){       //��ǵ�ǰ���ĸ���Ϊ��
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
                else if(w==3){  //����Ϊ��
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
                else if(w==4){           //�ĸ�Ϊ��
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
                    for(r=1;r<=6;r++){       //��ǵ�ǰ���ĸ���Ϊ��
                        for(j=1;j<=6;j++){
                            if(j==r) fprintf(fp,"%d %d ",i+(j-1)*6,k+(j-1)*6);
                            else fprintf(fp,"%d %d ",-(i+(j-1)*6),-(k+(j-1)*6));
                        }
                        fprintf(fp,"0\n");
                    }
                }
                else if(w==6){       //����Ϊ��
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
int Gotoxy(int x, int y) //��λ���λ��
{
    HANDLE handle; //����������handle
    COORD coord; //����ṹ��coord (����ϵcoord)
    coord.X = x; //������x
    coord.Y = y; //������y
    handle = GetStdHandle(STD_OUTPUT_HANDLE); //��ȡ����̨������(ֵΪ-11)
    SetConsoleCursorPosition(handle, coord); //�ƶ����
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
        printf("���ļ�ʧ��\n");
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
    if(function)    printf("�����ļ�д��ɹ���\n");
    struct clause *head;
    if(creatClause(filename,&head)==0)  return 0;
    if(function)    printf("����������\n");
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
void playSudoku(char filename[80])//�����̵ĳ�ʼ�����Լ�����Լ�������cnf��ʽ��д���ļ�
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
    if(creatSudoku(initial,2,filename,blank,sudoku,1)==0) printf("��������ʧ��");
    else    printf("�������ɳɹ�");
    int i;
    int userSolution[37];
    for(i=1;i<=36;i++)
    {
        userSolution[i]=sudoku[i];
    }
    printSudoku(userSolution);
    int position,value,flag=1;
    do{
        printf("�����������Լ���Ҫ��Ĵ𰸣������ڵڶ��е�������1��������23 1,����Ҫ�鿴��������0 0\n�����룺      \b\b\b\b\b\b"
               "\n                          \n                          "
               "\n                           \n                         ");
        Gotoxy(8,19);
        scanf("%d%d",&position,&value);
        if(position!=0)
        {
            if(position<0||(position>0&&position<11)||position/10>6||position%10>6||(value!=0&&value!=1))
            {
                printf("����Ƿ�");
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
                printf("����Ƿ�");
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
                    printf("\n\n\n��ϲ�㣬�����ȷ\n                 \n          ");
                    position=0;
                    flag=0;
                }
                else
                {
                    printf("\n\n\n��Ǹ�����Ĵ�����\n\n");
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
        printf("�ο������£�                  \n");
        for (i = 1; i <= 36; i++)
        {
            if (i % 6 == 1)printf("\n");
            printf(" %d", ans[i]);
        }
    }
}

#include "def.h"
//int main()
//{
//    int f;
//    struct clause *head;
//    creatClause("D:\\workfile\\程序设计综合课程设计任务及指导学生包\\SAT测试备选算例\\满足算例\\M\\ec-mod2c-rand3bip-sat-250-2.shuffled-as.sat05-2534.cnf",&head);
//    clock_t start,finish;
//    start=clock();
//    f=betterDPLL(head);
//    finish=clock();
//    printf("%d %ld ms",f,finish-start);
//}


int main()
{
    setbuf(stdout, NULL);
    struct clause *head1, *head2;
    int op = 1;
    char filename[1000];
    while (op)
    {
        system("cls");
        printf("\n\n");
        printf("      请选择需要实现的功能 \n");
        printf("------------------------------------------------------\n");
        printf("    	  1. 求解SAT       2. 玩数独游戏\n");
        printf("          0. 退出                   \n");
        printf("------------------------------------------------------\n");
        printf("    请选择你的操作[0~2]:");
        scanf("%d", &op);
        switch (op)
        {
            case 1:
            {
                int op_1;
                printf("\n请输入文件名：");
                while(1)
                {
                    scanf("%s",filename);
                    if(creatClause(filename,&head1)==1) break;
                    else    printf("文件不存在，请重新输入文件名：");
                }
                creatClause(filename, &head2);
                //输出CNF
                printf("\n共有%d个变元，%d个子句\n", argumentsCounts, clausesCounts);
                printf("是否输出cnf文件\n1.是\n2.否\n请选择:");
                do
                {
                    scanf("%d", &op_1);
                    if (op_1 != 1 && op_1 != 2) printf("请输入正确的序号:");
                } while (op_1 != 1 && op_1 != 2);
                if (op_1 == 1)
                {
                    putchar('\n');
                    struct clause *ptr = head1->next;
                    while (ptr)
                    {
                        struct node *p = ptr->clauseHead->next;
                        while (p)
                        {
                            printf("%d ", p->id);
                            p = p->next;
                        }
                        printf("\n");
                        ptr = ptr->next;
                    }
                }

                //DPLL计算
                printf("请选择使用何种算法\n1.未优化变元选择策略\n2.优化变元选择策略\n您的选择是：");
                int op_2;
                do
                {
                    scanf("%d", &op_2);
                    if (op_2 != 1 && op_2 != 2) printf("请输入正确的序号:");
                } while (op_2 != 1 && op_2 != 2);
                printf("DPLL求解中......\n");
                clock_t start, finish;
                int f;
                start = clock();
                if(op_2==1)   f = DPLL(head1);
                else    f=betterDPLL(head1);
                finish = clock();
                if (f == 1)
                {
                    printf("\n有解，执行时间 %ld ms", finish - start);
                }
                else
                {
                    printf("\n无解，执行时间 %ld ms", finish - start);
                }
                printf("\n是否输出解文件\n1.是\n2.否\n请选择：");
                do
                {
                    scanf("%d", &op_1);
                    if (op_1 != 1 && op_1 != 2) printf("请输入正确的序号:");
                } while (op_1 != 1 && op_1 != 2);
                if(op_1==1)
                {
                    printf("已输出至cnf文件所在文件夹下同名res文件中\n");
                    printAnswerToRes(filename, f, finish - start);
                }
                printf("是否执行另一种算法\n1.是\n2.否\n请选择:");
                do
                {
                    scanf("%d", &op_1);
                    if (op_1 != 1 && op_1 != 2) printf("请输入正确的序号:");
                } while (op_1 != 1 && op_1 != 2);
                if (op_1 == 1)
                {
                    double t1 = (double) finish - (double) start;
                    start = clock();
                    if(op_2==1) betterDPLL(head2);
                    else    DPLL(head2);
                    finish = clock();
                    if(op_2==1)
                    {
                        if(t1==0)   printf("执行时间%ld ms，无法计算优化率",finish - start);
                        else    printf("\n执行时间%ld ms,优化率：%f%%", finish - start, ((t1 - (finish - start)) / t1) * 100);
                    }
                    else
                    {
                        if(finish-start==0) printf("执行时间%ld ms，无法计算优化率",finish - start);
                        else printf("\n执行时间%ld ms,优化率%f%%", finish - start,
                               (((finish - start) - t1) / (finish - start)) * 100);
                    }
                    getchar();
                    getchar();
                }
                break;
            }
            case 2:
            {
                printf("即将创建数独文件，请输入文件名，文件将存储在程序所在的文件夹下：");
                char path[1000],sudokuFilename[1000];
                strcpy(path,".\\");
                scanf("%s",sudokuFilename);
                strcat(path,sudokuFilename);
                playSudoku(path);
                getchar();
                getchar();
                break;
            }
            case 0:
            {
                break;
            }
            default:
            {
                printf("请输入正确的序号！");
                getchar();
                getchar();
                break;
            }
        }//end of switch
    }//end of while
    printf("欢迎再次使用！");
    getchar();
    getchar();
    return 0;
}

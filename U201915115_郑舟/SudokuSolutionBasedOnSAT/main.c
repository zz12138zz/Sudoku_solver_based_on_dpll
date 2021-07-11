#include "def.h"
//int main()
//{
//    int f;
//    struct clause *head;
//    creatClause("D:\\workfile\\��������ۺϿγ��������ָ��ѧ����\\SAT���Ա�ѡ����\\��������\\M\\ec-mod2c-rand3bip-sat-250-2.shuffled-as.sat05-2534.cnf",&head);
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
        printf("      ��ѡ����Ҫʵ�ֵĹ��� \n");
        printf("------------------------------------------------------\n");
        printf("    	  1. ���SAT       2. ��������Ϸ\n");
        printf("          0. �˳�                   \n");
        printf("------------------------------------------------------\n");
        printf("    ��ѡ����Ĳ���[0~2]:");
        scanf("%d", &op);
        switch (op)
        {
            case 1:
            {
                int op_1;
                printf("\n�������ļ�����");
                while(1)
                {
                    scanf("%s",filename);
                    if(creatClause(filename,&head1)==1) break;
                    else    printf("�ļ������ڣ������������ļ�����");
                }
                creatClause(filename, &head2);
                //���CNF
                printf("\n����%d����Ԫ��%d���Ӿ�\n", argumentsCounts, clausesCounts);
                printf("�Ƿ����cnf�ļ�\n1.��\n2.��\n��ѡ��:");
                do
                {
                    scanf("%d", &op_1);
                    if (op_1 != 1 && op_1 != 2) printf("��������ȷ�����:");
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

                //DPLL����
                printf("��ѡ��ʹ�ú����㷨\n1.δ�Ż���Ԫѡ�����\n2.�Ż���Ԫѡ�����\n����ѡ���ǣ�");
                int op_2;
                do
                {
                    scanf("%d", &op_2);
                    if (op_2 != 1 && op_2 != 2) printf("��������ȷ�����:");
                } while (op_2 != 1 && op_2 != 2);
                printf("DPLL�����......\n");
                clock_t start, finish;
                int f;
                start = clock();
                if(op_2==1)   f = DPLL(head1);
                else    f=betterDPLL(head1);
                finish = clock();
                if (f == 1)
                {
                    printf("\n�н⣬ִ��ʱ�� %ld ms", finish - start);
                }
                else
                {
                    printf("\n�޽⣬ִ��ʱ�� %ld ms", finish - start);
                }
                printf("\n�Ƿ�������ļ�\n1.��\n2.��\n��ѡ��");
                do
                {
                    scanf("%d", &op_1);
                    if (op_1 != 1 && op_1 != 2) printf("��������ȷ�����:");
                } while (op_1 != 1 && op_1 != 2);
                if(op_1==1)
                {
                    printf("�������cnf�ļ������ļ�����ͬ��res�ļ���\n");
                    printAnswerToRes(filename, f, finish - start);
                }
                printf("�Ƿ�ִ����һ���㷨\n1.��\n2.��\n��ѡ��:");
                do
                {
                    scanf("%d", &op_1);
                    if (op_1 != 1 && op_1 != 2) printf("��������ȷ�����:");
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
                        if(t1==0)   printf("ִ��ʱ��%ld ms���޷������Ż���",finish - start);
                        else    printf("\nִ��ʱ��%ld ms,�Ż��ʣ�%f%%", finish - start, ((t1 - (finish - start)) / t1) * 100);
                    }
                    else
                    {
                        if(finish-start==0) printf("ִ��ʱ��%ld ms���޷������Ż���",finish - start);
                        else printf("\nִ��ʱ��%ld ms,�Ż���%f%%", finish - start,
                               (((finish - start) - t1) / (finish - start)) * 100);
                    }
                    getchar();
                    getchar();
                }
                break;
            }
            case 2:
            {
                printf("�������������ļ����������ļ������ļ����洢�ڳ������ڵ��ļ����£�");
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
                printf("��������ȷ����ţ�");
                getchar();
                getchar();
                break;
            }
        }//end of switch
    }//end of while
    printf("��ӭ�ٴ�ʹ�ã�");
    getchar();
    getchar();
    return 0;
}

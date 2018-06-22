#include<time.h>
#include<stdlib.h>
extern void Wheel_cre(void);
#include"define.h"
extern int wheel_choose(void);
extern double Rand(void);

extern int num_pro;//��Ʒ��Ŀ
extern int num_mac;//������Ŀ
extern int chromlength; //Ⱦɫ�峤��
extern int chrom[chromnum][300]; //������Ⱥ����
extern int chrom1[chromnum][300];//�Ӵ���Ⱥ����
extern int machinenum[30][30];//����� i ��������j��������ʹ�û�����  ������ 
extern int machinetime[30][30];// ����� i ��������j�������  �ķ�ʱ��
extern double adaption[chromnum];
extern double sum;
extern int total_time;
extern HANDLE hMutex;//�߳̾��
extern int present_time;//��ǰ����ʱ��
extern int mnum, checktime;//mnum���޵Ļ����ţ�checktime����ʱ��
extern struct machine mach[30][30];//��һ��30Ϊ������ţ��ڶ���30Ϊ�ڼ��ι���
struct timesstruct
{
	int pro;//��Ʒ��
	int find;//�ڼ��γ��� 
}str[2][200];
//�������Ⱦɫ��
void chromcreate(int g)// ���������Ⱥ ����
{
	int i, j, k, l;
	int a[chromnum] = { 0 };
	for (i = 0; i < g; i++)
	{
		for (j = 0; j < chromlength; j++)
		{
			while (1)
			{
				k =rand() % (num_pro);
				a[k]++;
				if (a[k] <= num_mac)
				{
					chrom[i][j] = k;
					//printf("%d", chrom[i][j]);
					//if (j == chromlength - 1)
					//printf("\n");
					break;
				
				}

			}
		}
		for (l = 0; l <g; l++)
			a[l] = 0;
	}
}

void cross(int k, int l, int a)//���ô��򽻲淨 k l Ϊ������Ⱦɫ��ı�ţ�aΪ�Ӵ����
{
	int i, j;//, g;
	int f1[200], f2[200], c1[200];// c2[200];
	for (i = 0; i < chromlength; i++)//����Ⱦɫ�帳ֵ
	{
		f1[i] = chrom[k][i];//Ⱦɫ��f1
		f2[i] = chrom[l][i];//Ⱦɫ��f2
		c1[i] = -1;         //�Ӵ�
	}
//	for (i = 0; i < chromlength; i++)
//	{
//		printf("%d ", f1[i]);
//	}
//	printf("\n ");
//	for (i = 0; i < chromlength; i++)
//	{
//		printf("%d ", f2[i]);
//	}
//	printf("\n ");
	int times1[num_pro1] = { 0 };
	int times2[num_pro1] = { 0 };
	int timetime_1[300];
	for (i = 0; i < chromlength; i++)//��ʼ��timetime_1
	{
		timetime_1[i] = -1;
	}
	int r1=1, r2=0, temp;
	r1 = rand() % (chromlength);
	r2 = rand() % (chromlength);
	if (r1 > r2)
	{
			temp = r1;
			r1 = r2;
			r2 = temp;
	}
	//�ṹ���ʼ��
//	printf("%d %d ", r1,r2);
//	printf("\n ");

	for (j = 0; j < chromlength; j++)
		{
			str[0][j].find = 0;
			str[0][j].pro = -1;
		}
	for (i = r1; i < r2; i++)//ѡ�������Ƹ��Ӵ���Ӧ���� 
	{
		c1[i] = f1[i];
	}
	for (i = 0, j = 0; i < chromlength; i++)//��¼ѡ������Ĳ�Ʒ���ǵڼ��γ��֣���0��ʼ 
	{
		times1[f1[i]]++;
		if (i >= r2) { break; }
		if (i >= r1)
		{
			str[0][j].pro = f1[i];
			str[0][j].find = times1[f1[i]];
			j++;
		}
	}
//	for (i = 0; i < 30; i++)
//	{
//		printf("%d,%d  ", str[0][i].pro, str[0][i].find);
//	}
//	printf("\n ");
	for (i = 0; i < chromlength; i++)//��Ǹ���
	{
		times2[f2[i]]++;
		for (j = 0; str[0][j].pro != -1; j++)
		{
			if (f2[i] == str[0][j].pro)                                 //pro=f2[i]    find= times2[f2[i]]
			{
				if (times2[f2[i]] == str[0][j].find)
				{
					timetime_1[j] = i;//Ҫ���-1 ���±�Ĵ�������
				//	printf("%d ", i);
				}
			}
		}
	}
	for (i = 0; i < chromlength; i++)
	{
		if ((timetime_1[i]) != -1)
		{
			f2[(timetime_1[i])] = -1;
		}
	}
	//�������Ӵ���ֵ
	for (i = 0, j = 0; (i < chromlength,j < chromlength); )
	{
			if (f2[i] != -1)
			{
				if (c1[j] == -1)
				{
					c1[j] = f2[i];
					j++;
					i++;
				}
				else
				{
					j++;
				}
			}
			else
			{
				i++;
			}
	}	
//	for (i = 0; i < chromlength; i++)
//	{
//		printf("%d ", f2[i]);
//	}
//	printf("\n");
//	for (i = 0; i < chromlength; i++)
//	{
//	printf("%d ", c1[i]);
//
//	}
//	printf("\n ");
    for (i = 0; i < chromlength; i++)
    {
	chrom1[a][i] = c1[i];
	}
	
//system("pause");
}

void variation(int f1)//�����㷨
{
	//int k;
	double l = Rand();
	if (l < p2)
	{
		int temp, location1, location2;//����λ��1��2
		location1 = rand() % (num_pro);
		location2 = rand() % (num_pro);
		while (location1 == location2)
			location2 = rand() % (num_pro);

		temp = chrom1[f1][location1];
		chrom1[f1][location1] = chrom1[f1][location2];
		chrom1[f1][location2] = temp;
	//	for (k = 0; k < chromlength; k++)
	//		printf("%d", chrom1[f1][k]);
	}
}

/*int end_judge()//�ж��Ƿ�ֹͣ����
{
	int q,j,k=0,l=0;
	for (q = 0; q < chromnum; q++)
		{
			for (j = 0; j < chromlength; j++)
			{
				if(chrom[q][j] == chrom[q + 1][j]){k++;}
			}
			if (k == chromlength) 
			{ l++;}
			k = 0;
		}

	//printf("%d", l);

	if (l > same) { return 1; }
	else { return 0; }
}*/

void chromcreate1(int g)// ���������Ⱥ ����
{
	int i, j, k, l;
	int a[chromnum] = { 0 };

	for (i = 0; i < g; i++)
		for (j = 0; j < chromlength; j++)
			chrom[i][j] = -1;

	int n;
	for (i = 0; i < g; i++)
	{
		for (j = 0; j < num_mac; j++)
		{	
			while (1)
			{
				n = rand() % (chromlength);
				if (chrom[i][n] == -1)
				{
					chrom[i][n] = j;
					//printf("%d", chrom[i][j]);
					//if (j == chromlength - 1)
					//printf("\n");
					break;

				}

			}
		}
	}
}
#include<stdio.h>
#include"define.h"
#include<time.h>
#include<conio.h>
#include<stdlib.h>
extern double  adapt_count1(int i);
extern double  adapt_count(int i);

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
void adaption_compare()//����Ⱦɫ������ ����
{
	double adapt[chromnum];//����ÿ��Ⱦɫ�����Ӧ��
	int i=0, j=0, min=0,k=0;
	double temp1=0.00;
	int temp=0;
	for (i = 0; i < chromnum; i++)
		adapt[i] = adapt_count(i);
	for (i = 0; i < chromnum-1; i++)
	{
		min = i;
		for (j = i + 1; j <= chromnum - 1; j++)
		{
			if (adapt[min] > adapt[j])
			{min = j;}
		}
		temp1 =adapt[i];
		adapt[i] = adapt[min];
		adapt[min] = temp1;
		for (k = 0; k < chromlength; k++)
		{
			temp = chrom[i][k];
			chrom[i][k] = chrom[min][k];
			chrom[min][k] = temp;
		}
	}
	//for (i = 0; i < chromnum; i++)
	//{
	//	printf("%lf\n", adapt_count(i));
	//}
}
void adaption_compare1()//�Ӵ�Ⱦɫ������ 
{
	double adapt1[chromnum];//����ÿ��Ⱦɫ�����Ӧ��
	int i = 0, j = 0, min = 0, k = 0;
	double temp1 = 0.00;
	int temp = 0;
	for (i = 0; i < chromnum; i++)
		adapt1[i] = adapt_count1(i);
	for (i = 0; i < chromnum - 1; i++)
	{
		min = i;
		for (j = i + 1; j <= chromnum - 1; j++)
		{
			if (adapt1[min] > adapt1[j])
			{
				min = j;
			}
		}
		temp1 = adapt1[i];
		adapt1[i] = adapt1[min];
		adapt1[min] = temp1;
		for (k = 0; k < chromlength; k++)
		{
			temp = chrom1[i][k];
			chrom1[i][k] = chrom1[min][k];
			chrom1[min][k] = temp;
		}
	}
	//for (i = 0; i < chromnum; i++)
	//{
	//	printf("%lf\n", adapt_count1(i));
	//}
}
void replace(void)//���������滻�Ӵ���� ����
{
	int i;
	for(i=0;i<chromlength;i++)
	{
		chrom1[0][i] = chrom[chromnum-1][i];
	}
	
}
void data_translation()//�Ӵ���ֵ���������� ����
{
	int i, j;
	for (i = 0; i < chromnum; i++)
	{
		for (j = 0; j < chromlength; j++)
		{
			chrom[i][j] = chrom1[i][j];
		}
	}
}
double Rand() //����
{
	double r;
	r = (rand() % 100)*0.01;
	return r;
}
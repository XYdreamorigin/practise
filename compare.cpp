#include<stdio.h>
#include"define.h"
#include<time.h>
#include<conio.h>
#include<stdlib.h>
extern double  adapt_count1(int i);
extern double  adapt_count(int i);

extern int num_pro;//产品数目
extern int num_mac;//机器数目
extern int chromlength; //染色体长度
extern int chrom[chromnum][300]; //父代种群数组
extern int chrom1[chromnum][300];//子代种群数组
extern int machinenum[30][30];//储存第 i 个工件第j道工序所使用机器的  机器号 
extern int machinetime[30][30];// 储存第 i 个工件第j道工序的  耗费时间
extern double adaption[chromnum];
extern double sum;
extern int total_time;
extern HANDLE hMutex;//线程句柄
extern int present_time;//当前机器时间
extern int mnum, checktime;//mnum检修的机器号，checktime检修时长
extern struct machine mach[30][30];//第一个30为机器序号，第二个30为第几次工作
void adaption_compare()//父代染色体排序 正常
{
	double adapt[chromnum];//保存每个染色体的适应度
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
void adaption_compare1()//子代染色体排序 
{
	double adapt1[chromnum];//保存每个染色体的适应度
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
void replace(void)//父代最优替换子代最差 正常
{
	int i;
	for(i=0;i<chromlength;i++)
	{
		chrom1[0][i] = chrom[chromnum-1][i];
	}
	
}
void data_translation()//子代数值传给到父代 正常
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
double Rand() //正常
{
	double r;
	r = (rand() % 100)*0.01;
	return r;
}
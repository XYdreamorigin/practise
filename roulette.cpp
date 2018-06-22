#include<stdlib.h>
#include<stdio.h>
#include"define.h"
extern void sum_adapt();
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
double probability[chromnum];
void Wheel_cre(void) //正常
{
	int i;
	sum_adapt();//适应度求和
	for (i = 0; i < chromnum; i++)
	{
		//printf("%.6lf\n", adapt_count(i));
		probability[i] = adaption[i] / sum;
	}
}

int wheel_choose()//正常
{
	int i;
	double r = rand() / (RAND_MAX + 1.0);
	double m = 0;
	for (i = 0; i < chromnum; i++)
	{
		m = m + probability[i];
		if (r<m)
		{
			break;
		}
		//while (pick < 0.0001)
		//pick = ((double)rand()) / RAND_MAX;
	}
	return i;
}

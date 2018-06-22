#include"define.h"
#include<stdio.h>
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


double  adapt_count(int i)//参数为第i条染色体,父代染色体适应度计算  正常
{
	//int adaption //适应度，即完成所有工序的所需总时间
	int j =0;//
	int time = 0,mac = 0;
	int macnum[300] = {0};//储存机器空闲时间点的一维数组，大小大于num_mac
	int macnum1[30];//储存机器出现次数的一维数组，大小大于num_mac
	int pro_statime[chromnum][chromnum] = {0};
	int pro_endtime[chromnum][chromnum] = {0};
	double max_time = 0.00;
	int times[300]={0};//记录次数
	int k=0 ;//第K道工序
	for (j = 0; j < 30; j++)//macnum1初始化
	{
		macnum1[j] = -1;
	}
	//for (i; i < chromnum; i++)//染色体数量
	  //求解某个染色体的适应度
		for (j=0; j <chromlength; j++) //染色体长度
		{
			k = chrom[i][j];
			times[k]++;//k第几次出现  
			
				time = machinetime[k][times[k]-1];//加工时间 
				mac = machinenum[k][times[k]-1];//对应机器号 
				macnum1[mac]++; //
				if (times[k] != 1)
				{
					if (macnum[mac]<pro_endtime[k][times[k] - 2])
					{pro_statime[k][times[k] - 1] = pro_endtime[k][times[k] - 2];}
					else
					{pro_statime[k][times[k] - 1] = macnum[mac];}
				}
				if (times[k] == 1)
				{pro_statime[k][times[k] - 1] = macnum[mac];}
				pro_endtime[k][times[k]-1] = time + pro_statime[k][times[k]-1];//2
				macnum[mac] = pro_endtime[k][times[k]-1];//3
				if(max_time < pro_endtime[k][times[k]-1]){ max_time = pro_endtime[k][times[k]-1]; }//Tip
				//更新机器状态结构体数据
				mach[mac][macnum1[mac]].time_sta = pro_endtime[k][times[k] - 1] - time;
				mach[mac][macnum1[mac]].time_end = pro_endtime[k][times[k] - 1];
				mach[mac][macnum1[mac]].pro = k;
				mach[mac][macnum1[mac]].cess = times[k] - 1;
		}
		total_time=(int)max_time;
		max_time = (double)max_time;
		return 1.00 / max_time;
		max_time = 0.00;
}

double  adapt_count1(int i)//参数为第i条染色体,子代染色体适应度计算  正常
{
	//int adaption //适应度，即完成所有工序的所需总时间
	int j = 0;//
	int time = 0, mac = 0;
	int macnum[30] = { 0 };//储存机器空闲时间点的一维数组，大小大于num_mac
	int macnum1[30];//储存机器出现次数的一维数组，大小大于num_mac
	int pro_statime[chromnum][chromnum] = { 0 };
	int pro_endtime[chromnum][chromnum] = { 0 };
	double max_time = 0.00;
	int times[30] = { 0 };//记录次数
	int k = 0;//第K道工序
	for (j = 0; j < 30; j++)//macnum1初始化
	{
		macnum1[j] = -1;
	}
	//for (i; i < chromnum; i++)//染色体数量
	//求解某个染色体的适应度
	for (j = 0; j <chromlength; j++) //染色体长度
	{
		k = chrom1[i][j];
		times[k]++;//k第几次出现  
		{
			time = machinetime[k][times[k] - 1];//加工时间 60
			mac = machinenum[k][times[k] - 1];//对应机器号 0
			macnum1[mac]++; //0
			if (times[k] != 1)
			{
				if (macnum[mac]<pro_endtime[k][times[k] - 2])
				{
					pro_statime[k][times[k] - 1] = pro_endtime[k][times[k] - 2];
				}
				else
				{
					pro_statime[k][times[k] - 1] = macnum[mac];
				}
			}
			if (times[k] == 1)
			{
				pro_statime[k][times[k] - 1] = macnum[mac];
			}
			pro_endtime[k][times[k] - 1] = time + pro_statime[k][times[k] - 1];//2
			macnum[mac] = pro_endtime[k][times[k] - 1];//3
			if (max_time < pro_endtime[k][times[k] - 1]) { max_time = pro_endtime[k][times[k] - 1]; }//Tip
																									 //更新机器状态结构体数据
			mach[mac][macnum1[mac]].time_sta = pro_endtime[k][times[k] - 1] - time;
			mach[mac][macnum1[mac]].time_end = pro_endtime[k][times[k] - 1];
			mach[mac][macnum1[mac]].pro = k;
			mach[mac][macnum1[mac]].cess = times[k] - 1;


		}
	}
	

	total_time = (int)max_time;
	max_time = (double)max_time;
//	printf("total_time:%d  ", total_time);
	return 1.00 / max_time;
	max_time = 0.00;
}

void sum_adapt()//父代染色体适应度求和 正常
{
	
	sum = 0.00;
	int i=0;
	for (i = 0; i < chromnum; i++)
	{
		
		adaption[i] = adapt_count(i);
		//printf("**%lf\n", adaption[i]);
		sum = adaption[i] + sum;
	}

}
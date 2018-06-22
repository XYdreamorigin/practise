#include<time.h>
#include<stdlib.h>
extern void Wheel_cre(void);
#include"define.h"
extern int wheel_choose(void);
extern double Rand(void);

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
struct timesstruct
{
	int pro;//产品号
	int find;//第几次出现 
}str[2][200];
//随机生成染色体
void chromcreate(int g)// 创建随机种群 正常
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

void cross(int k, int l, int a)//采用次序交叉法 k l 为两条父染色体的编号，a为子代编号
{
	int i, j;//, g;
	int f1[200], f2[200], c1[200];// c2[200];
	for (i = 0; i < chromlength; i++)//父代染色体赋值
	{
		f1[i] = chrom[k][i];//染色体f1
		f2[i] = chrom[l][i];//染色体f2
		c1[i] = -1;         //子代
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
	for (i = 0; i < chromlength; i++)//初始化timetime_1
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
	//结构体初始化
//	printf("%d %d ", r1,r2);
//	printf("\n ");

	for (j = 0; j < chromlength; j++)
		{
			str[0][j].find = 0;
			str[0][j].pro = -1;
		}
	for (i = r1; i < r2; i++)//选中区域复制给子代相应区域 
	{
		c1[i] = f1[i];
	}
	for (i = 0, j = 0; i < chromlength; i++)//记录选中区域的产品号是第几次出现，从0开始 
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
	for (i = 0; i < chromlength; i++)//标记父代
	{
		times2[f2[i]]++;
		for (j = 0; str[0][j].pro != -1; j++)
		{
			if (f2[i] == str[0][j].pro)                                 //pro=f2[i]    find= times2[f2[i]]
			{
				if (times2[f2[i]] == str[0][j].find)
				{
					timetime_1[j] = i;//要标记-1 的下表的储存数组
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
	//父代给子代赋值
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

void variation(int f1)//变异算法
{
	//int k;
	double l = Rand();
	if (l < p2)
	{
		int temp, location1, location2;//变异位置1，2
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

/*int end_judge()//判断是否停止函数
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

void chromcreate1(int g)// 创建随机种群 正常
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
#include<stdio.h>
#include"define.h"
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
//命令行输入 
void input_com()
{
	char a = '0';
	int i = 0, j = 0;
	scanf("%d %d", &num_pro, &num_mac);//输入产品与机器数目
	while (1)
	{
		while (1)
		{
			scanf("%d %d", &machinenum[i][j], &machinetime[i][j]);
			j++;
			if ((a = getchar()) == '\n')break;
		}
		j = 0;
		i++;
	}
	i = 0;
	j = 0;
}
//文件输入 正常
void input_file()
{
	int i = 0, j = 0;
	FILE *fp = fopen("input.txt", "r");
	fscanf(fp, "%d %d", &num_pro, &num_mac);
	for (i = 0; i < num_pro; i++)
	{
		for (j = 0; j < num_mac; j++)
		{
			fscanf(fp, "%d %d", &machinenum[i][j], &machinetime[i][j]);
		}
	}
	i = 0, j = 0;
	fclose(fp);


	//printf("%d %d\n ", num_pro, num_mac);
	//for (i; i < num_pro; i++)
	//{
	//	for (j = 0; j < num_mac; j++)
	//	{
	//		printf("%d %d ", machinenum[i][j], machinetime[i][j]);
	//	}
	//	printf("\n");
	//}
}
//system("pause");
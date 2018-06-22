/*#include<stdio.h>
#include"define.h"

struct timesstruct
{
	int pro;//产品号
	int find;//第几次出现 
}str[2][200];

void rearrangement()
{
	int i, j, k, x, y;
	int mnum;// 是机器号
	int checktime;// 是检修时长
	//假设此时正在加工第x个工件的第y到工序
	int temp[100];
	//machinenum[x][y] = mnum;   加工第x个工件的第y到工序的机器为将要检修的机器
	for (i = 0; i < chromlength; i++)
	{
		if (x == chrom1[0][i])
			j++;
		if (j == y)
			break;
	}
	for (i = i + 1, j = 0; i < chromlength; i++, j++)//j<chromlength-i-1;
	{
		temp[j] = chrom1[0][i];
	}
	int kl, position;//kl为随机要换的位置
	position = i + 1;
	kl = rand() % (chromlength - i - 1) + (i + 1);
	for (k = 0; k < 50; k++)
	{
		for (j = 0; j < chromlength - i - 1;)
		{
			kl = rand() % (chromlength - i - 1) + (i + 1);
			while (temp[kl] != 0)
			{
				chrom1[0][position] = temp[kl];
				temp[kl] = 0;
				position++;
				j++;
			}
		}
	}
}*/
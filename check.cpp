/*#include<stdio.h>
#include"define.h"

struct timesstruct
{
	int pro;//��Ʒ��
	int find;//�ڼ��γ��� 
}str[2][200];

void rearrangement()
{
	int i, j, k, x, y;
	int mnum;// �ǻ�����
	int checktime;// �Ǽ���ʱ��
	//�����ʱ���ڼӹ���x�������ĵ�y������
	int temp[100];
	//machinenum[x][y] = mnum;   �ӹ���x�������ĵ�y������Ļ���Ϊ��Ҫ���޵Ļ���
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
	int kl, position;//klΪ���Ҫ����λ��
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
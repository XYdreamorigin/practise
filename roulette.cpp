#include<stdlib.h>
#include<stdio.h>
#include"define.h"
extern void sum_adapt();
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
double probability[chromnum];
void Wheel_cre(void) //����
{
	int i;
	sum_adapt();//��Ӧ�����
	for (i = 0; i < chromnum; i++)
	{
		//printf("%.6lf\n", adapt_count(i));
		probability[i] = adaption[i] / sum;
	}
}

int wheel_choose()//����
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

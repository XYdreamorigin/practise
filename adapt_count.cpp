#include"define.h"
#include<stdio.h>
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


double  adapt_count(int i)//����Ϊ��i��Ⱦɫ��,����Ⱦɫ����Ӧ�ȼ���  ����
{
	//int adaption //��Ӧ�ȣ���������й����������ʱ��
	int j =0;//
	int time = 0,mac = 0;
	int macnum[300] = {0};//�����������ʱ����һά���飬��С����num_mac
	int macnum1[30];//����������ִ�����һά���飬��С����num_mac
	int pro_statime[chromnum][chromnum] = {0};
	int pro_endtime[chromnum][chromnum] = {0};
	double max_time = 0.00;
	int times[300]={0};//��¼����
	int k=0 ;//��K������
	for (j = 0; j < 30; j++)//macnum1��ʼ��
	{
		macnum1[j] = -1;
	}
	//for (i; i < chromnum; i++)//Ⱦɫ������
	  //���ĳ��Ⱦɫ�����Ӧ��
		for (j=0; j <chromlength; j++) //Ⱦɫ�峤��
		{
			k = chrom[i][j];
			times[k]++;//k�ڼ��γ���  
			
				time = machinetime[k][times[k]-1];//�ӹ�ʱ�� 
				mac = machinenum[k][times[k]-1];//��Ӧ������ 
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
				//���»���״̬�ṹ������
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

double  adapt_count1(int i)//����Ϊ��i��Ⱦɫ��,�Ӵ�Ⱦɫ����Ӧ�ȼ���  ����
{
	//int adaption //��Ӧ�ȣ���������й����������ʱ��
	int j = 0;//
	int time = 0, mac = 0;
	int macnum[30] = { 0 };//�����������ʱ����һά���飬��С����num_mac
	int macnum1[30];//����������ִ�����һά���飬��С����num_mac
	int pro_statime[chromnum][chromnum] = { 0 };
	int pro_endtime[chromnum][chromnum] = { 0 };
	double max_time = 0.00;
	int times[30] = { 0 };//��¼����
	int k = 0;//��K������
	for (j = 0; j < 30; j++)//macnum1��ʼ��
	{
		macnum1[j] = -1;
	}
	//for (i; i < chromnum; i++)//Ⱦɫ������
	//���ĳ��Ⱦɫ�����Ӧ��
	for (j = 0; j <chromlength; j++) //Ⱦɫ�峤��
	{
		k = chrom1[i][j];
		times[k]++;//k�ڼ��γ���  
		{
			time = machinetime[k][times[k] - 1];//�ӹ�ʱ�� 60
			mac = machinenum[k][times[k] - 1];//��Ӧ������ 0
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
																									 //���»���״̬�ṹ������
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

void sum_adapt()//����Ⱦɫ����Ӧ����� ����
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
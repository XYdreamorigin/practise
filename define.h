#pragma once
#include<windows.h>
#include<time.h>
//��������

const int chromnum = 350;//Ⱦɫ������������ʼ���������
const double p1 = 0.90;//�������
const double p2 = 0.50;//�������
const int  generation_max= 30;//������
const int  num_pro1 = 30;//�����Ͳ�Ʒ��Ŀ
const int  num_mac1 = 30; // �����ͻ�����Ŀ
const int  timetimes = 90;//ÿ��ʱ����
const int  sleep = 2000;//����˯��ʱ��
const int  check_times = 10;//�����ܴ���
const int ttime = 3000;//��������ʱ��
const int ratio = 3;//�ӹ�ʱ���
const int real_time = 2;//��ʵ����
const int total_sleep = 40000;//�����˯��ʱ��



extern int num_pro;//��Ʒ��Ŀ
extern int num_mac;//������Ŀ
extern int chromlength; //Ⱦɫ�峤��
extern int chrom[chromnum][300]; //������Ⱥ����
extern int chrom1[chromnum][300];//�Ӵ���Ⱥ����
extern int chrom2[chromnum][300];//��������֮����������
extern int machinenum[30][30];//����� i ��������j��������ʹ�û�����  ������ 
extern int machinetime[30][30];// ����� i ��������j�������  �ķ�ʱ��
extern double adaption[chromnum];
extern double sum;
extern int total_time;
extern HANDLE hMutex;//�߳̾��
extern int present_time;//��ǰ����ʱ��
extern int mnum, checktime;//mnum���޵Ļ����ţ�checktime����ʱ��
extern int sign;
extern int x, y;
extern int ctimes;
extern int clock_time;
extern clock_t start, end;
extern double total_clock;
extern int total_times;
extern int difference[check_times];
//��������״̬�ṹ��
struct machine
{
	int time_sta;//������ʼ����ʱ��
	int time_end;//������������ʱ��
	int pro;     //���������ڼӹ��Ĳ�Ʒ��
	int cess;    //���������ڼӹ��Ĳ�Ʒ�Ĺ����
};
extern struct machine mach[30][30];//��һ��Ϊ�����ţ��ڶ���Ϊ�����ϵڼ�������
extern struct machine mach1[30][30];
struct macnum2
{
	int check_sta;
	int check_end;
	int num;
	int time;//����ʱ�䳤��
};
extern struct macnum2 mac2[check_times];//������޵Ĵ���
struct mac
{
	int x;//����Ĺ�����
	int y;//����Ĺ����
};
extern struct mac mac3[100];//���治��Ĺ����ź͹����
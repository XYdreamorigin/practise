#pragma once
#include"define.h"
#include<windows.h>
int num_pro;//��Ʒ��Ŀ
int num_mac;//������Ŀ
int chromlength; //Ⱦɫ�峤��
int chrom[chromnum][300]; //������Ⱥ����
int chrom1[chromnum][300];//�Ӵ���Ⱥ����
int machinenum[30][30];//����� i ��������j��������ʹ�û�����  ������ 
int machinetime[30][30];// ����� i ��������j�������  �ķ�ʱ��
double adaption[chromnum];
double sum;
int total_time;
HANDLE hMutex;//�߳̾��
int present_time;//��ǰ����ʱ��
int mnum=-1, checktime=0;//mnum���޵Ļ����ţ�checktime����ʱ��
struct machine mach[30][30];//��һ��30Ϊ������ţ��ڶ���30Ϊ�ڼ��ι���
struct machine mach1[30][30]; 
int sign;
struct macnum2 mac2[check_times];
int x, y;
int chrom2[chromnum][300];//��������֮����������
int ctimes; //ȫ�ָ�������
int clock_time;//��ǰʱ��ʱ��
double total_clock;//����ܼ�ʱʱ��
clock_t start, end;
int total_times;//���ܶ��Ĺ�����������������
struct mac mac3[100];//���治��Ĺ����ź͹����
int difference[check_times];//�������ֵ���ʱ��
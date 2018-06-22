#include<stdio.h>
#include <stdlib.h>
#include"define.h"
#include<windows.h>
#include<time.h>
extern clock_t start, end;
extern void input_com();
extern void input_file();
extern void chromcreate(int i);
extern void Wheel_cre(void);
extern void cross(int k, int l,int a);
extern void variation(int i);
extern void adaption_compare();
extern void replace(void);
extern void data_translation();
extern void output_file(double a);
extern double Rand();
extern void adaption_compare1(void);
extern void replace(void);
extern int wheel_choose(void);
extern void data_translation();
//extern int end_judge();
extern void output_com();
extern double  adapt_count(int i);
extern DWORD WINAPI check(LPVOID pPararneter);
extern DWORD WINAPI working_printf(LPVOID pPararneter);
//extern DWORD WINAPI state_update(LPVOID pPararneter);//�߳��ͻ���״̬��ֵ
extern void output_picture1(int HI);
extern int output_picture(void);
//extern DWORD WINAPI update_printf(LPVOID pPararneter);
extern double total_clock;

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
extern struct macnum2 mac2[check_times];
extern struct machine mach1[30][30];
extern void output_com1();
//extern void chromcreate1(int g);
//extern void chromcreate_1(void);
//#include<graphics.h>
int main()
{
		struct machine begin = { -1, -1, -1, -1 };
		int l, k, i, g;
		srand((unsigned)time(NULL));
		input_file();                   //�������� 
		//input_com();
		double a = clock();//���⿪ʼ��ʱ
		total_clock = a;
		chromlength = num_pro * num_mac;//Ⱦɫ�峤�ȸ�ֵ  
										//	printf("%d", chromlength);
		chromcreate(chromnum);                  //���������Ⱥ  //����
										//sum_adapt();
		for (i = 0; i < generation_max; i++)
		{
			Wheel_cre();                    //��������
			adaption_compare();              //��������
		   //����
			for (l = 0, k = (chromnum / 2); k < chromnum; k++, l++)
			{
				int a = wheel_choose();
				int	b = wheel_choose();
				if (Rand() < p1)
				{
					cross(b, a, l);
					cross(a, b, k);
				}
				else
				{
					for (g = 0; g < chromlength; g++)
					{
						chrom1[l][g] = chrom[l][g];
						chrom1[k][g] = chrom[k][g];
					}
				}


			}
//			adaption_compare();              //��������
			adaption_compare1();             //�Ӵ�����
			//����
			for (k = 0; k < chromnum; k++)
			{
				variation(k);
			}

			replace();                       //��Ӣ���ԡ����������滻�Ӵ����
			adaption_compare1();             //�Ӵ�����
			data_translation();              //�Ӹ���ת��
			chromcreate(chromnum - 20);
			adaption_compare();              //��������
			
			adapt_count(chromnum-1);
			printf("%d\n", total_time);	
		//	if(end_judge(same)==1){ chromcreate(same); }
			

		}
	//	adaption_compare();                    //��������
											  //��ʼ����״̬�ṹ������
		for (l = 0; l < 30; l++)
		{
			for (k = 0; k < 30; k++)
			{
				mach[l][k].time_end = -1;
				mach[l][k].time_sta = -1;
				mach[l][k].pro = -1;
				mach[l][k].cess = -1;
			}
		}
		adapt_count(chromnum - 1);             //�������Ÿ�����Ӧ�ȼ���
		output_com();                              //������
		/*
		for (i = 0; i < chromlength; i++)
		{
			printf("%d ", chrom[chromnum - 1][i]);
		}
		printf("\n");
		*/

		double b = clock();//�������
		printf("Time Used:%.3lfs\n", (b - a) / 1000);//������ĵ�λ�Ǻ���
		printf("End Time:%d\n", total_time);
		output_file((b - a) / 1000);
		for (l = 0; l < 30; l++)
		{
			for (k = 0; k < 30; k++)
			{
				mach1[l][k].time_end = mach[l][k].time_end;
				mach1[l][k].time_sta = mach[l][k].time_sta;
				mach1[l][k].pro = mach[l][k].pro;
				mach1[l][k].cess = mach[l][k].cess;
			}
		}
		//ģ��ӹ���ʼ��ʹ���߳�
		//����״̬�ṹ�����鸳ֵ
		for (i = 0; i < check_times; i++)
		{
			mac2[i].check_end = -1;
			mac2[i].check_sta = -1;
			mac2[i].num = -1;
			mac2[i].time = -1;
		}
		/*
//		for (int i = 0; i < check_times; i++)
//		{
			mac2[0].check_end = 200;
			mac2[0].check_sta = 0;
			mac2[0].num = 0;
			mac2[0].time = 200;
//		}
*/      output_picture();
		HANDLE hThread1, hThread2;// hThread3, hThread4;
		start = clock();

		hThread1 = CreateThread(NULL, 0, working_printf, NULL, 0, NULL);//��ӡ��ǰ����״̬��ֻ��ʱ���йأ��Ҹ��µ�ǰ����״̬
		hThread2 = CreateThread(NULL, 0, check, NULL, 0, NULL);// �������ָ���Ҫ��ָͣ��
		CloseHandle(hThread1);
		CloseHandle(hThread2);

		Sleep(total_sleep);
		system("pause");
	//	Sleep(((total_time/timetimes)*2000)+2000);
		return 0;

	}
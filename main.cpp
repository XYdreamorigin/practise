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
//extern DWORD WINAPI state_update(LPVOID pPararneter);//线程型机器状态赋值
extern void output_picture1(int HI);
extern int output_picture(void);
//extern DWORD WINAPI update_printf(LPVOID pPararneter);
extern double total_clock;

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
		input_file();                   //数据输入 
		//input_com();
		double a = clock();//从这开始计时
		total_clock = a;
		chromlength = num_pro * num_mac;//染色体长度赋值  
										//	printf("%d", chromlength);
		chromcreate(chromnum);                  //创建随机种群  //正常
										//sum_adapt();
		for (i = 0; i < generation_max; i++)
		{
			Wheel_cre();                    //创建轮盘
			adaption_compare();              //父代排序
		   //交叉
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
//			adaption_compare();              //父代排序
			adaption_compare1();             //子代排序
			//变异
			for (k = 0; k < chromnum; k++)
			{
				variation(k);
			}

			replace();                       //精英策略。父代最优替换子代最差
			adaption_compare1();             //子代排序
			data_translation();              //子父代转换
			chromcreate(chromnum - 20);
			adaption_compare();              //父代排序、
			
			adapt_count(chromnum-1);
			printf("%d\n", total_time);	
		//	if(end_judge(same)==1){ chromcreate(same); }
			

		}
	//	adaption_compare();                    //父代排序
											  //初始机器状态结构体数组
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
		adapt_count(chromnum - 1);             //父代最优个体适应度计算
		output_com();                              //输出结果
		/*
		for (i = 0; i < chromlength; i++)
		{
			printf("%d ", chrom[chromnum - 1][i]);
		}
		printf("\n");
		*/

		double b = clock();//到这结束
		printf("Time Used:%.3lfs\n", (b - a) / 1000);//算出来的单位是毫秒
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
		//模拟加工开始，使用线程
		//检修状态结构体数组赋值
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

		hThread1 = CreateThread(NULL, 0, working_printf, NULL, 0, NULL);//打印当前机器状态，只与时间有关，且更新当前机器状态
		hThread2 = CreateThread(NULL, 0, check, NULL, 0, NULL);// 插入检修指令，需要暂停指令
		CloseHandle(hThread1);
		CloseHandle(hThread2);

		Sleep(total_sleep);
		system("pause");
	//	Sleep(((total_time/timetimes)*2000)+2000);
		return 0;

	}
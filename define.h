#pragma once
#include<windows.h>
#include<time.h>
//公共变量

const int chromnum = 350;//染色体数量，即初始解的数量。
const double p1 = 0.90;//交叉概率
const double p2 = 0.50;//变异概率
const int  generation_max= 30;//最大代数
const int  num_pro1 = 30;//常量型产品数目
const int  num_mac1 = 30; // 常量型机器数目
const int  timetimes = 90;//每次时间间隔
const int  sleep = 2000;//程序睡眠时间
const int  check_times = 10;//检修总次数
const int ttime = 3000;//程序运行时间
const int ratio = 3;//加工时间比
const int real_time = 2;//现实秒数
const int total_sleep = 40000;//最后总睡眠时间



extern int num_pro;//产品数目
extern int num_mac;//机器数目
extern int chromlength; //染色体长度
extern int chrom[chromnum][300]; //父代种群数组
extern int chrom1[chromnum][300];//子代种群数组
extern int chrom2[chromnum][300];//检修命令之后的随机数组
extern int machinenum[30][30];//储存第 i 个工件第j道工序所使用机器的  机器号 
extern int machinetime[30][30];// 储存第 i 个工件第j道工序的  耗费时间
extern double adaption[chromnum];
extern double sum;
extern int total_time;
extern HANDLE hMutex;//线程句柄
extern int present_time;//当前机器时间
extern int mnum, checktime;//mnum检修的机器号，checktime检修时长
extern int sign;
extern int x, y;
extern int ctimes;
extern int clock_time;
extern clock_t start, end;
extern double total_clock;
extern int total_times;
extern int difference[check_times];
//机器工作状态结构体
struct machine
{
	int time_sta;//机器开始工作时间
	int time_end;//机器结束工作时间
	int pro;     //机器上正在加工的产品号
	int cess;    //机器上正在加工的产品的工序号
};
extern struct machine mach[30][30];//第一个为机器号，第二个为机器上第几道工作
extern struct machine mach1[30][30];
struct macnum2
{
	int check_sta;
	int check_end;
	int num;
	int time;//检修时间长短
};
extern struct macnum2 mac2[check_times];//储存检修的次数
struct mac
{
	int x;//不变的工件号
	int y;//不变的工序号
};
extern struct mac mac3[100];//储存不变的工件号和工序号
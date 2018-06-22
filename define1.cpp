#pragma once
#include"define.h"
#include<windows.h>
int num_pro;//产品数目
int num_mac;//机器数目
int chromlength; //染色体长度
int chrom[chromnum][300]; //父代种群数组
int chrom1[chromnum][300];//子代种群数组
int machinenum[30][30];//储存第 i 个工件第j道工序所使用机器的  机器号 
int machinetime[30][30];// 储存第 i 个工件第j道工序的  耗费时间
double adaption[chromnum];
double sum;
int total_time;
HANDLE hMutex;//线程句柄
int present_time;//当前机器时间
int mnum=-1, checktime=0;//mnum检修的机器号，checktime检修时长
struct machine mach[30][30];//第一个30为机器序号，第二个30为第几次工作
struct machine mach1[30][30]; 
int sign;
struct macnum2 mac2[check_times];
int x, y;
int chrom2[chromnum][300];//检修命令之后的随机数组
int ctimes; //全局辅助变量
int clock_time;//当前时钟时间
double total_clock;//最后总计时时间
clock_t start, end;
int total_times;//不能动的工件总数，基因总数
struct mac mac3[100];//储存不变的工件号和工序号
int difference[check_times];//储存绝对值差的时间
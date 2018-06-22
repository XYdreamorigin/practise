#include"define.h"
#include<stdio.h>
#include<windows.h>
#include<time.h>
extern clock_t start, end;
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
extern int x, y;
extern struct mac mac3[100];//储存不变的工件号和工序号
extern HANDLE hMutex;//线程句柄
extern int present_time;//当前机器时间
extern int mnum, checktime;//mnum检修的机器号，checktime检修时长
extern struct machine mach[30][30];//第一个30为机器序号，第二个30为第几次工作
extern int sign;
extern struct macnum2 mac2[check_times];
extern int chrom2[chromnum][300];//检修命令之后的随机数组
extern int ctimes;
extern int clock_time;
extern double  adapt_count(int i);
extern int find_num(int i);
extern void output_com1();
extern void output_picture1(int HI);
extern void output_file1(double a);
int tempb = 0;
extern int total_times;
extern int difference[check_times];
char s[50];//机器工作状态


int adapt_count2(int i)//参数为第i条染色体,父代染色体适应度计算  正常
{
	//int adaption //适应度，即完成所有工序的所需总时间
	int j = 0, total_time1;//
	int time = 0, mac = 0;
	int macnum[300] = { 0 };//储存机器空闲时间点的一维数组，大小大于num_mac
	int macnum1[30];//储存机器出现次数的一维数组，大小大于num_mac
	int pro_statime[chromnum][chromnum] = { 0 };
	int pro_endtime[chromnum][chromnum] = { 0 };
	int max_time = 0;
	int times[300] = { 0 };//记录次数
	int k = 0;//第K道工序
	for (j = 0; j < 30; j++)//macnum1初始化
	{
		macnum1[j] = -1;
	}
	//for (i; i < chromnum; i++)//染色体数量
	//求解某个染色体的适应度
	for (j = 0; j <chromlength; j++) //染色体长度
	{
		k = chrom[i][j];
		times[k]++;//k第几次出现  

		time = machinetime[k][times[k] - 1];//加工时间 
		mac = machinenum[k][times[k] - 1];//对应机器号 
		macnum1[mac]++; //
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
																								 //更新机器状态结构体数据
		mach[mac][macnum1[mac]].time_sta = pro_endtime[k][times[k] - 1] - time;
		mach[mac][macnum1[mac]].time_end = pro_endtime[k][times[k] - 1];
		mach[mac][macnum1[mac]].pro = k;
		mach[mac][macnum1[mac]].cess = times[k] - 1;
	}
	total_time1 = max_time;
	//max_time = (double)max_time;
	return total_time1;
	//max_time = 0.00;
}
void rearrangement()//产生了50个新的染色体，但是检修之前的序列没有发生改变
{
	int i, j;
	int chrom3[chromnum][300], temp2[chromnum][100],chrom4[chromnum][300];
	for (i = 0; i < chromnum; i++)
	{
		for (j = 0; j < chromlength; j++)
		{
			chrom3[i][j] = -1;//初始化为-1
			chrom4[i][j] = -1;
		}
	}
	for (i = 0; i < chromnum; i++)
		for (j = 0; j < chromlength; j++)
			temp2[i][j] = chrom[chromnum - 1][j];

	int times[100] = { 0 };
	for (i = 0; i < total_times+1; i++)//找出不应该变化的值
	{
		for (j = 0; j < chromlength; j++)
		{
			if (mac3[i].x == chrom[chromnum - 1][j])
				times[mac3[i].x]++;
			if (times[mac3[i].x] - 1 == mac3[i].y)
			{
				chrom3[0][j] = chrom[chromnum - 1][j];
				temp2[0][j] = -1;
				times[mac3[i].x] = 0;
				break;
			}
		}
	}
	/*
	for (i = 0; i < chromlength; i++)
	{
		printf("%d", chrom3[0][i]);
	}
	printf("\n\n");
	for (i = 0; i < chromlength; i++)
	{
		printf("%d", chrom4[0][i]);
	}
	printf("\n\n");
	*/
	int judge=0;
	for (int k = 0; k < chromnum; k++)
	{
		for (i = 0, j = 0; (i < chromlength, j < chromlength); )
		{
			if (chrom3[k][i] != -1)
			{
				if (chrom4[k][j] == -1)
				{
					chrom4[k][j] = chrom3[k][i];
					chrom3[k][i] = -1;
					j++;
					i++;
					judge++;
					if (judge == total_times + 1)
						break;
				}
				else
				{
					j++;
				}
			}
			else
			{
				i++;
			}
		}
	}
	/*

	for (i = 0; i < chromlength; i++)
	{
		printf("%d", chrom4[0][i]);
	}
	printf("\n\n");
	*/

	for (i = 0; i < chromnum; i++)
	{
		for (j = 0; j < chromlength; j++)
		{
			chrom4[i][j] = chrom4[0][j];//批量赋不应该变化的值；
			temp2[i][j] = temp2[0][j];
		}
	}

	int position;
	for (i = 0; i < chromnum; i++)
	{
		for (j = 0; j < chromlength; j++)
		{
			if (temp2[i][j]!= -1)
			{
				position = rand() % chromlength;
				while (chrom4[i][position] != -1)
				{
					position = rand() % chromlength;
				}
					chrom4[i][position] = temp2[i][j];
					temp2[i][j] = -1;
			}
		}
	}
	for (i = 0; i < chromnum; i++)
	{
		for (j = 0; j < chromlength; j++)
		{
			chrom2[i][j] = chrom4[i][j];
		}
	}
	/*
	for (int n = 0; n < chromnum; n++)
	{
		for (i = 0; i < chromlength; i++)
		{
			printf("%d", chrom4[n][i]);
		}
		printf("\n");
	}
	*/
}
void rearrangement1()//产生了50个新的染色体，但是检修之前的序列没有发生改变
{
	int i, j, k, n, position, point;

	//假设此时正在加工第x个工件的第y到工序
	int temp[100] = { 0 };
	//machinenum[x][y] = mnum;   
	srand((unsigned)time(NULL));
	
/*	printf("%d^^^^^^^%d",x1,y1);
	for (i = 0, j = 0; i < chromlength; i++)
	{
		if (x1 == chrom[chromnum - 1][i])
			j++;
		if (j-1 == y1)
			break;
	}//判断在染色体上出现的位置*/
	position = total_times;
	printf("*%d*\n", position);
	for (i = 0; i < chromnum; i++)
		for (j = 0; j < position; j++)
			chrom2[i][j] = chrom[chromnum - 1][j];//让50个数组在检修点之前的序列与最优解一样


	for (n = 0; n < chromnum; n++)
	{
		for (i = position, j = 0; i < chromlength; i++)//将检修之后的基因放进新的数组
		{
			temp[j] = chrom[chromnum - 1][i];
			j++;
		}

		point = rand() % 20;
		i = position+1;

		for (k = 0; k < j; k++)
		{

			while (temp[point] == -1)           //将检修之后的基因随机排序赋值给chrom2
			{
				point = rand() % j;
			}

			chrom2[n][i] = temp[point];
			temp[point] = -1;
			i++;
		}
	}
	for (n = 0; n < chromnum; n++)
	{
		for (i = 0; i < chromlength; i++)
		{
			chrom[n][i] = chrom2[n][i];
		};
	}
	
	for (n = 0; n < chromnum; n++)
	{
	for (i = 0; i < chromlength; i++)
	{
	printf("%d", chrom2[n][i]);
	}
	printf("\n");
	}
	
}
void short_DNA()   //满足检修时没有工件在加工的DNA序列得到最短时间
{
	int min_time = 2000, total_time1, best;// , pro;
	int i, j, n;
	//pro = find_num();
	for (i = 0; i < chromnum; i++)
	{
		for (j = 0; j < chromlength; j++)
		{
			chrom[i][j] = chrom2[i][j];
		}
	}
	for (n = 0; n < chromnum; n++)
	{
		total_time1 = adapt_count2(n);
		if (total_time1 < min_time)
		{
			min_time = total_time1;
			best = n;
		}

	}
	for (i = 0; i < chromlength; i++)
	{
		chrom[chromnum - 1][i] = chrom2[best][i];
	};
	//printf("%d\n", min_time);

	//return best;
}
//线程2 插入检修指令
DWORD WINAPI check(LPVOID pPararneter)
{
	x = -1;
	y = -1;
	total_times = -1;
	ctimes = 0;
	char h;
	//不动的工件工序结构体数组初始化
	for (int i = 0; i < 100; i++)
	{
		mac3[i].x = -1;
		mac3[i].y = -1;
	}
	//初始化绝对值差值
	for (int i = 0; i < check_times; i++)
	{
		difference[i] = 0;
	}
	while (tempb != num_mac)//主循环结束条件，条件为tempb空闲机器变量等于机器数量
	{
		h = getchar();
		if (h == 'C')
		{
			scanf("%d %d", &mnum, &checktime);//输入机器号与加工时间
		}
		end = clock();
		clock_time = int((((double)(end - start)) / CLK_TCK) * ratio*real_time);
	//	clock_time = int((((double)(end - start)) / CLK_TCK) *12);
	//	printf("%d**", clock_time);
		for (int i = 0; i < num_pro; i++)
		{   //clock_time为接受检修指令的确切机器时间,尚未赋值
			if (mach[mnum][i].time_sta <= clock_time && mach[mnum][i].time_end >= clock_time)
			{
				x = mach[mnum][i].pro;//x为机器检修前最后一件产品的工件号
				y = mach[mnum][i].cess;//y为机器检修前最后一件产品的工序号
				machinetime[x][y] = machinetime[x][y] + checktime;//延长机器检修前最后一个工作状态的结束时间延长了
																  //机器状态结构体赋值
				mac2[ctimes].check_sta = mach[mnum][i].time_end;
				mac2[ctimes].check_end = mach[mnum][i].time_end + checktime;
				mac2[ctimes].num = mnum;
				mac2[ctimes].time = checktime;
				ctimes++;
				//
				break;
			}
			if (mach[mnum][i].time_sta >= clock_time)
			{
				x = mach[mnum][i - 1].pro;
				y = mach[mnum][i - 1].cess;
				machinetime[x][y] = machinetime[x][y] + checktime + clock_time - mach[mnum][i - 1].time_end;//延长机器检修前最后一个工作状态的结束时间延长了
				difference[ctimes] = clock_time - mach[mnum][i - 1].time_end;
				//机器状态结构体赋值
				mac2[ctimes].check_sta = clock_time;
				mac2[ctimes].check_end = clock_time + checktime;
				mac2[ctimes].num = mnum;
				mac2[ctimes].time = checktime;
				ctimes++;

				break;
			}
		}
		//统计不变的基因
		for (int i = 0; i < num_mac; i++)
		{
			for (int j = 0; j < num_pro; j++)
			{
				if (clock_time >= mach[i][j].time_end)
				{
					total_times++;
					mac3[total_times].x = mach[i][j].pro;
					mac3[total_times].y = mach[i][j].cess;
				}
				else if (mach[i][j].time_sta <= clock_time && mach[i][j].time_end >= clock_time)
				{
					total_times++;
					mac3[total_times].x = mach[i][j].pro;
					mac3[total_times].y = mach[i][j].cess;
				}
				if (clock_time < mach[i][j].time_sta) { break; }
			}
		}
		//			for (int i = 0; i <= total_times; i++)
		//			{
		//				printf("%d %d**", mac3[i].x, mac3[i].y); 
		//
		//			}
//		printf("##%d##", total_times);
//		printf("##%d %d**", mac2[0].check_sta, mac2[0].check_end);
		rearrangement();
		short_DNA();
		total_times = -1;

		//不动的工件工序结构体数组初始化
		for (int i = 0; i < 100; i++)
		{
			mac3[i].x = -1;
			mac3[i].y = -1;
		}
	}
	//ReleaseMutex(hMutex);//释放句柄
	return 0;
}
//线程1 更新机器结构体数据,与输出数据
DWORD WINAPI working_printf(LPVOID pPararneter)
	{
	int i, j, k, tempa = 0, present_time = 0, tempc = 0;
		while (tempb!=num_mac)//主线程，每2S输出一次，结束条件，条件为tempb空闲机器变量等于机器数量
		{
			adapt_count(chromnum - 1);//更新mach[][]结构体二维数组，储存机器状态
			present_time = present_time + (ratio*real_time);
			for (int kb = 0; kb < num_mac; kb++)//机器号
			{
				for (j = 0; j < num_pro; j++)//机器上的工作号
				{
					for (k = 0; k < check_times;k++)  //判断是否为检修
					{
						if (mac2[k].num==kb)
						{
							if (present_time < mac2[k].check_end&&present_time >= mac2[k].check_sta)
							{
							//	printf("%d %d 检修  -  %d %d\n", present_time, kb, present_time- mac2[k].check_sta, mac2[k].check_end- present_time);
								tempa = 1;
								tempc = 1;
								break;
							}
						}
					}
					if (tempa == 1)
					{
						tempa = 0;
						break;
					}
					 //present_time为每2S的时间间隔点，对应6
					//加工状态判定
					//如果加工
					if (present_time >= mach[kb][j].time_sta&&present_time < mach[kb][j].time_end)
					{
					//	printf("%d %d 加工 %d-%d %d %d\n", present_time,kb, mach[kb][j].pro, mach[kb][j].cess, present_time - mach[kb][j].time_sta, mach[kb][j].time_end - present_time);
						tempc = 1;
						break;
					}
					//否则 空闲
				//	else
					/*
					if (j + 1 < num_pro)
					{
						if (present_time <= mach[kb][j + 1].time_sta || mach[kb][j + 1].time_sta == -1)
						{
							if (present_time < mach[kb][j].time_sta)
							{
								printf("%d %d 空闲  -  %d %d\n", present_time, kb, present_time, mach[kb][j].time_sta - present_time);
								tempb++;
								break;
							}
							else
								if (mach[kb][j + 1].time_sta != -1)
								{
									printf("%d %d 空闲  -  %d %d\n", present_time, kb, present_time - mach[kb][j].time_end, mach[kb][j + 1].time_sta - present_time);
									tempb++;
									break;
								}
						}
					}*/
				}
				if (tempc== 1) { tempc = 0; }
				else
				{
				//	printf("空闲");
					tempc = 0;
					tempb++;
				}
			}
			if (tempb != num_mac) { tempb = 0; }
	//		printf("%d\n",present_time);
			output_picture1(present_time);
			Sleep(sleep);
		}
		output_com1();
		double q = clock();
		printf("Time Used:%.3lfs\n", (q - total_clock) / 1000);//算出来的单位是毫秒
		printf("End Time:%d\n", total_time);
		output_file1((q - total_clock) / 1000);
		output_picture1(present_time);
		return 0;
	}
/*
	DWORD WINAPI state_update(LPVOID pPararneter)//线程型机器状态赋值
	{
		//while (present_time <= total_time)
		//{
		int j = 0, q = 0, g = 0;//g为检修结构体数组的下标
		int time = 0, mac = 0;
		int macnum[300] = { 0 };//储存机器空闲时间点的一维数组，大小大于num_mac
		int macnum1[30];//储存机器出现次数的一维数组，大小大于num_mac
		int pro_statime[chromnum][chromnum] = { 0 };
		int pro_endtime[chromnum][chromnum] = { 0 };
		double max_time = 0.00;
		int times[300] = { 0 };//记录次数
		int k = 0;//第K道工序
		for (j = 0; j < 30; j++)//macnum1初始化
		{
			macnum1[j] = -1;
		}
		//检修信息结构体赋值
			for (j = 0; j <check_times; j++)
			{
				mac2[j].check_end = -1;
				mac2[j].check_sta = -1;
				mac2[j].num = -1;
			}
		//机器状态信息提取
			while (present_time <= total_time)
			{
				j = 0, q = 0, time = 0, mac = 0, macnum[300] = { 0 }, pro_statime[chromnum][chromnum] = { 0 }, pro_endtime[chromnum][chromnum] = { 0 }, max_time = 0.00, times[300] = { 0 }, k = 0;

				for (j = 0; j < chromlength; j++) //染色体长度
				{  //是否检修判别条件
					
					if (checktime > 0)
					{
						if (macnum[mnum] > present_time)
						{
							macnum[mnum] = macnum[mnum] + checktime;
						}
						else
						{
							macnum[mnum] = present_time + checktime;
						}
						//将检修信息赋值到检修结构体中
						mac2[g].check_end = macnum[mnum];
						mac2[g].check_sta = macnum[mnum] - checktime;
						mac2[g].num = mnum;
						g++;
						checktime = 0;
					}
					
					if (mnum != -1)
					{
						if ((present_time - macnum[mnum]) <= timetimes && (present_time - macnum[mnum]) >= 0)
						{
							macnum[mnum] = present_time + checktime;
							mac2[g].check_end = macnum[mnum];
							mac2[g].check_sta = macnum[mnum] - checktime;
							mac2[g].num = mnum;
							g++;
							checktime = 0;
							mnum = -1;
						}
					}

					//
					k = chrom[chromnum - 1][j];//j为染色体上的位置序号
					times[k]++;//k第几次出现  

					time = machinetime[k][times[k] - 1];//加工时间 
					mac = machinenum[k][times[k] - 1];//对应机器号 
					macnum1[mac]++; //
					if (times[k] != 1)
					{
						if (macnum[mac] < pro_endtime[k][times[k] - 2])
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
					//机器状态结构体赋值																					 //更新机器状态结构体数据
					mach[mac][macnum1[mac]].time_sta = pro_endtime[k][times[k] - 1] - time;
					mach[mac][macnum1[mac]].time_end = pro_endtime[k][times[k] - 1];
					mach[mac][macnum1[mac]].pro = k;
					mach[mac][macnum1[mac]].cess = times[k] - 1;
				}
				Sleep(3000);
			}
		total_time = (int)max_time;
		max_time = (double)max_time;
		max_time = 0.00;
	//	}

		return 0;
	}
	*//*
	DWORD WINAPI update_printf(LPVOID pPararneter)
	{
	    int present_time = 0;//a为当前时间点，机器时间单位
		int i = 0, g = 0;//g为检修结构体数组的下标
		
	while (present_time <= ttime)
	{
		present_time = present_time + 90;
		int b = 0, c = 0;
		int j = 0;
		int time = 0 ,mac = 0;
		int macnum[300] = { 0 };//储存机器空闲时间点的一维数组，大小大于num_mac
		int macnum1[30];//储存机器出现次数的一维数组，大小大于num_mac
		int pro_statime[chromnum][chromnum] = { 0 };
		int pro_endtime[chromnum][chromnum] = { 0 };
		double max_time = 0.00;
		int times[300] = { 0 };//记录次数
		int k = 0;//第K道工序
		int present_time1 = 0;
		for (j = 0; j < 30; j++)//macnum1初始化
		{
			macnum1[j] = -1;
		}
			for (j = 0; j < chromlength; j++) //染色体长度
			{
				k = chrom[chromnum - 1][j];//j为染色体上的位置序号
				times[k]++;//k第几次出现  
				time = machinetime[k][times[k] - 1];//加工时间 
				mac = machinenum[k][times[k] - 1];//对应机器号 
				macnum1[mac]++; //
				int temp = 0;
				
				//
				//提取此机器下一个工作的开始时间，temp为次值
				if (times[k] != 1)
				{
					if (macnum[mac] < pro_endtime[k][times[k] - 2])
					{
						temp = pro_endtime[k][times[k] - 2];
					}
					else
					{
						temp = macnum[mac];
					}
				}
				if (times[k] == 1)
				{
					temp = macnum[mac];
				}
				//
				if (times[k] != 1)
				{
					if (macnum[mac] < pro_endtime[k][times[k] - 2])
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
				pro_endtime[k][times[k] - 1] = time + pro_statime[k][times[k] - 1];
				macnum[mac] = pro_endtime[k][times[k] - 1];
				if (max_time < pro_endtime[k][times[k] - 1]) { max_time = pro_endtime[k][times[k] - 1]; }
				//检修判断
				for (i = 0; i < check_times; i++)
				{
					if (mac == mac2[i].num)
					{
						if (macnum[mac] >= mac2[i].check_sta&&macnum[mac] <= mac2[i].check_end)
						{
							macnum[mac] = mac2[i].check_end;
						}
						
						if (temp >= mac2[i].check_sta)
						{
							macnum[mac] = mac2[i].check_end;
						}

					}
				}

				//机器状态结构体赋值  只有机器最后最后工序时间小于当前时间才能赋值
	//			if (pro_endtime[k][times[k] - 1] >= present_time)
	//			{
				mach[mac][macnum1[mac]].time_sta = pro_endtime[k][times[k] - 1] - time;
				mach[mac][macnum1[mac]].time_end = pro_endtime[k][times[k] - 1];
				mach[mac][macnum1[mac]].pro = k;
				mach[mac][macnum1[mac]].cess = times[k] - 1;
				//			}
			}
//	    total_time = (int)max_time;
//	    max_time = (double)max_time;
//	    max_time = 0.00;

	//输出
	if (present_time >900) break;
		for (i = 0; i < num_mac; i++)
		{
			for (j = 0; j < num_pro; j++)
			{
				if (present_time >= mach[i][j].time_sta&&present_time <= mach[i][j].time_end)
				{
					printf("%d %d %s %d-%d %d %d", present_time, i, s, mach[i][j].pro, mach[i][j].cess, present_time - mach[i][j].time_sta, mach[i][j].time_end - present_time);
					b = 1;
					break;
				}
			}
			//判断是检修还是空闲
			if (b == 0)
			{
				for (k = 0; k < check_times; k++)
				{
					if (mac2[k].num == mnum)
					{
						if (present_time <= mac2[k].check_end&&present_time >= mac2[k].check_sta)
						{
							printf("检修");
							c = 1;
							break;
						}
					}
				}
				if (c == 1) { c = 0; }
				else { printf("空闲"); }
			}
			if (b == 1) { b = 0; }
			printf("\n");
		}
		printf("*************************************\n");
		Sleep(3000);
	}
	return 0;
}*//*
//线程1 打印当前机器状态
DWORD WINAPI working_printf1(LPVOID pPararneter)
	{
	 int i = 0, j = 0, b = 0, k = 0,c=0;
		int present_time = 0;//a为当前时间点，机器时间单位
		while (1)
		{
			present_time = present_time + timetimes;
			if (present_time > total_time) break;
			for (i = 0; i < num_mac; i++)
			{
				for (j = 0; j < num_pro; j++)
				{


					if (present_time >= mach[i][j].time_sta&&present_time <= mach[i][j].time_end)
					{
						printf("%d %d %s %d-%d %d %d", present_time, i, s, mach[i][j].pro, mach[i][j].cess, present_time - mach[i][j].time_sta, mach[i][j].time_end - present_time);
						b = 1;
						break;
					}

				}
				//判断是检修还是空闲
				if (b == 0)
				{
					for (k = 0; k < check_times; k++)
					{
						if (mac2[k].num == mnum)
						{
							if (present_time >= mac2[k].check_end&&present_time <= mac2[k].check_sta)
							{
								printf("检修");
								c = 1;
								break;
							}
						}
			
					}
					if (c == 1){c = 0;}
					if (c == 0){printf("空闲");}
				}
				if (b == 1){b = 0;}
				printf("\n");
			}
			printf("*************************************");
			printf("\n");
			Sleep(1000);
		}
		return 0;
	}
	*/
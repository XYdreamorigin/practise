#include<stdio.h>
extern double  adapt_count(int i);
#include"define.h"
#define SHOW_CONSOLE
#include<graphics.h>
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
extern int mnum;
extern int checktime;
extern int ctimes;
#include <graphics.h>
void output_com()
{
	
	int i = 0, j = 0;
	//adaption_compare();//父代适应度排序
	//adapt_count(0);
	//printf("%d", total_time);
	for(i = 0; i < num_mac; i++) 
	{
		printf("M%d",i);
		for (j = 0; j < num_pro; j++)
		{
			printf( " (%d,%d-%d,%d)",mach[i][j].time_sta,mach[i][j].pro,mach[i][j].cess,mach[i][j].time_end);
		}
		printf("\n");
	}
	//printf("Time Used:%.3lf",runtime );
	//printf("End Time:%d", total_time);
}
void output_file(double a)
{
	FILE *fp1 = fopen("output1.txt", "w+");
	int i = 0, j = 0;
	//adaption_compare();//父代适应度排序
	//adapt_count(0);
	//printf("%d", total_time);
	for (i = 0; i < num_mac; i++)
	{
		//fprintf("M%d", i);
		fprintf(fp1, "M%d", i);
		for (j = 0; j < num_pro; j++)
		{
			fprintf(fp1, " (%d,%d-%d,%d)", mach[i][j].time_sta, mach[i][j].pro, mach[i][j].cess, mach[i][j].time_end);
		}
		fprintf(fp1, "\n");
	}
	fprintf(fp1, "Time Used:%.3lfs\n", a);//算出来的单位是毫秒
	fprintf(fp1, "End Time:%d\n", total_time);
	fclose(fp1);
}
void output_com1()
{

	int i = 0, j = 0, k = 0, tempa = 0;
	//adaption_compare();//父代适应度排序
	//adapt_count(0);
	//printf("%d", total_time);
	for (i = 0; i < num_mac; i++)
	{
		printf("M%d", i);
		for (j = 0; j < num_pro; j++)
		{
			for (k = 0; k < check_times; k++)  //判断是否为检修
			{
				if (mac2[k].num == i)
				{
					if (mach[i][j].time_end == mac2[k].check_end)//&&present_time >= mac2[k].check_sta)
					{
						printf(" (%d,%d-%d,%d)", mach1[i][j].time_sta, mach1[i][j].pro, mach1[i][j].cess, mach1[i][j].time_end);
						printf(" (%d,检修,%d)", mac2[k].check_sta, mac2[k].check_end);
						tempa = 1;
					//	break;
					}
				}
			}
			if (tempa == 1)
			{
				tempa = 0;
			}
			else
			{
				printf(" (%d,%d-%d,%d)", mach[i][j].time_sta, mach[i][j].pro, mach[i][j].cess, mach[i][j].time_end);
			}
			
		}
		printf("\n");
	}
}
void output_file1(double a)
{
	FILE *fp1 = fopen("output2.txt", "w+");
	int i = 0, j = 0, k = 0, tempa = 0;
	//adaption_compare();//父代适应度排序
	//adapt_count(0);
	//printf("%d", total_time);
	for (i = 0; i < num_mac; i++)
	{
		//fprintf("M%d", i);
		fprintf(fp1, "M%d", i);
		for (j = 0; j < num_pro; j++)
		{
			//fprintf(fp1, " (%d,%d-%d,%d)", mach[i][j].time_sta, mach[i][j].pro, mach[i][j].cess, mach[i][j].time_end);
			for (k = 0; k < check_times; k++)  //判断是否为检修
			{
				if (mac2[k].num == i)
				{
					if (mach[i][j].time_end == mac2[k].check_end)//&&present_time >= mac2[k].check_sta)
					{
						fprintf(fp1, " (%d,%d-%d,%d)", mach1[i][j].time_sta, mach1[i][j].pro, mach1[i][j].cess, mach1[i][j].time_end);
						fprintf(fp1, " (%d,检修,%d)", mac2[k].check_sta, mac2[k].check_end);
						tempa = 1;
						//	break;
					}
				}
			}
			if (tempa == 1)
			{
				tempa = 0;
			}
			else
			{
				fprintf(fp1, " (%d,%d-%d,%d)", mach[i][j].time_sta, mach[i][j].pro, mach[i][j].cess, mach[i][j].time_end);
			}
		}
		fprintf(fp1, "\n");
	}
	fprintf(fp1, "Time Used:%.3lfs\n", a);//算出来的单位是毫秒
	fprintf(fp1, "End Time:%d\n", total_time);
	fclose(fp1);
}
int find_num(int i)//寻找检修时机器正在加工第几个工件
{
	int j;
	for (j = 0; j < num_pro; j++)
	{
		if (mach[i][j].pro == x)
			break;
	}
	return j;
}


int output_picture(void)
{
	int i, j;
	initgraph(1500, 600);
	setfont(18, 0, "宋体");
	setbkcolor(BLACK);
	char s[6];
	char s1[6];
	char m = 'M';
	for (i = 0; i < num_mac; i++)
	{
		outtextxy(0, i * 40, m);//在指定的位置打印M
		sprintf(s1, "%d", i);
		outtextxy(10, i * 40, s1);//将机器号格式化输出字符串，在M后打印机器好号
		
	}
	for (i = 0; i < num_mac; i++)//该循环用来打印同一个工件在不同机器上的甘特图
	{
		for (j = 0; j < num_pro; j++)
		{
			if (mach[i][j].pro == 0)
			{
				setfillcolor(EGERGB(0xFF, 0x0, 0x0));
				bar(mach[i][j].time_sta + 30, i* 40, mach[i][j].time_end+30, i*40 + 20);
			}
			if (mach[i][j].pro == 1)
			{
				setfillcolor(EGERGB(0xDD, 0x6D, 0x22));
				bar(mach[i][j].time_sta + 30, i * 40, mach[i][j].time_end + 30, i * 40 + 20);
			}
			if (mach[i][j].pro == 2)
			{
				setfillcolor(EGERGB(0xCC, 0xCC, 0x33));
				bar(mach[i][j].time_sta + 30, i * 40, mach[i][j].time_end + 30, i * 40 + 20);
			}
			if (mach[i][j].pro == 3)
			{
				setfillcolor(EGERGB(0x66, 0xff, 0x00));
				bar(mach[i][j].time_sta + 30, i * 40, mach[i][j].time_end + 30, i * 40 + 20);
			}
			if (mach[i][j].pro == 4)
			{
				setfillcolor(EGERGB(0x66, 0xff, 0xff));
				bar(mach[i][j].time_sta + 30, i * 40, mach[i][j].time_end + 30, i * 40 + 20);
			}
			if (mach[i][j].pro == 5)
			{
				setfillcolor(EGERGB(0x66, 0x66, 0xff));
				bar(mach[i][j].time_sta + 30, i * 40, mach[i][j].time_end + 30, i * 40 + 20);
			}
			if (mach[i][j].pro == 6)
			{
				setfillcolor(EGERGB(0x33, 0x33, 0x99));
				bar(mach[i][j].time_sta + 30, i * 40, mach[i][j].time_end + 30, i * 40 + 20);
			}
			if (mach[i][j].pro == 7)
			{
				setfillcolor(EGERGB(0x00, 0x99, 0xCC));
				bar(mach[i][j].time_sta + 30, i * 40, mach[i][j].time_end + 30, i * 40 + 20);
			}
			if (mach[i][j].pro == 8)
			{
				setfillcolor(EGERGB(0xF0, 0x80, 0x80));
				bar(mach[i][j].time_sta + 30, i * 40, mach[i][j].time_end + 30, i * 40 + 20);
			}
			if (mach[i][j].pro == 9)
			{
				setfillcolor(EGERGB(0xff, 0xff, 0xcc));
				bar(mach[i][j].time_sta + 30, i * 40, mach[i][j].time_end + 30, i * 40 + 20);
			}
		}//画矩形，同一个工件一样的填充色
	}
	setfont(10, 0, "宋体");//将字体变小
	for (i = 0; i < num_mac; i++)//该循环用来打印每一个工序的开始时间和结束时间
	{
		for (j = 0; j < num_pro; j++)
		{
			sprintf_s(s, "%d", mach[i][j].time_sta);//在该工件开始位置打印起始时间
			outtextxy(mach[i][j].time_sta + 30, i * 40 + 20, s);
			if (mach[i][j].time_end != mach[i][j + 1].time_end)
			{
				sprintf_s(s, "%d", mach[i][j].time_end);//在该工件开始位置打印结束时间
				outtextxy(mach[i][j].time_end + 30, i * 40 + 20, s);
			}
		}
	}
	//getch();
	//delay_ms(0);

	//closegraph();
	return 0;
}
void output_picture1(int HI)
{

	
	int i, j;
	initgraph(1500, 600);
	
	setfont(18, 0, "宋体");
	setbkcolor(BLACK);
	char s[6];
	char s1[6];
	char m = 'M';
	for (i = 0; i < num_mac; i++)
	{
		outtextxy(0, i * 40, m);//在指定的位置打印M
		sprintf(s1, "%d", i);
		outtextxy(10, i * 40, s1);//将机器号格式化输出字符串，在M后打印机器好号

	}
	for (i = 0; i < num_mac; i++)//该循环用来打印同一个工件在不同机器上的甘特图
	{
		for (j = 0; j < num_pro; j++)
		{
			if (mach1[i][j].pro == 0)
			{
				setfillcolor(EGERGB(0xFF, 0x0, 0x0));
				bar(mach1[i][j].time_sta + 30, i * 40, mach1[i][j].time_end + 30, i * 40 + 20);
			}
			if (mach1[i][j].pro == 1)
			{
				setfillcolor(EGERGB(0xDD, 0x6D, 0x22));
				bar(mach1[i][j].time_sta + 30, i * 40, mach1[i][j].time_end + 30, i * 40 + 20);
			}
			if (mach1[i][j].pro == 2)
			{
				setfillcolor(EGERGB(0xCC, 0xCC, 0x33));
				bar(mach1[i][j].time_sta + 30, i * 40, mach1[i][j].time_end + 30, i * 40 + 20);
			}
			if (mach1[i][j].pro == 3)
			{
				setfillcolor(EGERGB(0x66, 0xff, 0x00));
				bar(mach1[i][j].time_sta + 30, i * 40, mach1[i][j].time_end + 30, i * 40 + 20);
			}
			if (mach1[i][j].pro == 4)
			{
				setfillcolor(EGERGB(0x66, 0xff, 0xff));
				bar(mach1[i][j].time_sta + 30, i * 40, mach1[i][j].time_end + 30, i * 40 + 20);
			}
			if (mach1[i][j].pro == 5)
			{
				setfillcolor(EGERGB(0x66, 0x66, 0xff));
				bar(mach1[i][j].time_sta + 30, i * 40, mach1[i][j].time_end + 30, i * 40 + 20);
			}
			if (mach1[i][j].pro == 6)
			{
				setfillcolor(EGERGB(0x33, 0x33, 0x99));
				bar(mach1[i][j].time_sta + 30, i * 40, mach1[i][j].time_end + 30, i * 40 + 20);
			}
			if (mach1[i][j].pro == 7)
			{
				setfillcolor(EGERGB(0x00, 0x99, 0xCC));
				bar(mach1[i][j].time_sta + 30, i * 40, mach1[i][j].time_end + 30, i * 40 + 20);
			}
			if (mach1[i][j].pro == 8)
			{
				setfillcolor(EGERGB(0xF0, 0x80, 0x80));
				bar(mach1[i][j].time_sta + 30, i * 40, mach1[i][j].time_end + 30, i * 40 + 20);
			}
			if (mach1[i][j].pro == 9)
			{
				setfillcolor(EGERGB(0xff, 0xff, 0xcc));
				bar(mach1[i][j].time_sta + 30, i * 40, mach1[i][j].time_end + 30, i * 40 + 20);
			}
		}//画矩形，同一个工件一样的填充色
	}
	setfont(10, 0, "宋体");//将字体变小
	for (i = 0; i < num_mac; i++)//该循环用来打印每一个工序的开始时间和结束时间
	{
		for (j = 0; j < num_pro; j++)
		{
			sprintf_s(s, "%d", mach1[i][j].time_sta);//在该工件开始位置打印起始时间
			outtextxy(mach1[i][j].time_sta + 30, i * 40 + 20, s);
			if (mach1[i][j].time_end != mach1[i][j + 1].time_end)
			{
				sprintf_s(s, "%d", mach1[i][j].time_end);//在该工件开始位置打印结束时间
				outtextxy(mach1[i][j].time_end + 30, i * 40 + 20, s);
			}
		}
	}
	//getch();

	//closegraph();
	//return 0;


	setfont(18, 0, "宋体");
	int length, move;
	move = num_mac * 40;
	for (i = 0; i < num_mac; i++)
	{
		outtextxy(0, i * 40 + move, m);//在指定的位置打印M
		sprintf(s1, "%d", i);
		outtextxy(10, i * 40 + move, s1);//将机器号格式化输出字符串，在M后打印机器好号
	}
	int k;
	for (i = 0; i < num_mac; i++)//该循环用来打印同一个工件在不同机器上的甘特图
	{
		for (j = 0; j < num_pro; j++)
		{
			length = i * 40;
			if (mach[i][j].pro == 0)
			{
				setfillcolor(EGERGB(0xFF, 0x0, 0x0));
				bar(mach[i][j].time_sta + 30, length + move, mach[i][j].time_end + 30, length + move + 20);
			}
			if (mach[i][j].pro == 1)
			{
				setfillcolor(EGERGB(0xDD, 0x6D, 0x22));
				bar(mach[i][j].time_sta + 30, length + move, mach[i][j].time_end + 30, length + move + 20);
			}
			if (mach[i][j].pro == 2)
			{
				setfillcolor(EGERGB(0xCC, 0xCC, 0x33));
				bar(mach[i][j].time_sta + 30, length + move, mach[i][j].time_end + 30, length + move + 20);
			}
			if (mach[i][j].pro == 3)
			{
				setfillcolor(EGERGB(0x66, 0xff, 0x00));
				bar(mach[i][j].time_sta + 30, length + move, mach[i][j].time_end + 30, length + move + 20);
			}
			if (mach[i][j].pro == 4)
			{
				setfillcolor(EGERGB(0x66, 0xff, 0xff));
				bar(mach[i][j].time_sta + 30, length + move, mach[i][j].time_end + 30, length + move + 20);
			}
			if (mach[i][j].pro == 5)
			{
				setfillcolor(EGERGB(0x66, 0x66, 0xff));
				bar(mach[i][j].time_sta + 30, length + move, mach[i][j].time_end + 30, length + move + 20);
			}
			if (mach[i][j].pro == 6)
			{
				setfillcolor(EGERGB(0x33, 0x33, 0x99));
				bar(mach[i][j].time_sta + 30, length + move, mach[i][j].time_end + 30, length + move + 20);
			}
			if (mach[i][j].pro == 7)
			{
				setfillcolor(EGERGB(0x00, 0x99, 0xCC));
				bar(mach[i][j].time_sta + 30, length + move, mach[i][j].time_end + 30, length + move + 20);
			}
			if (mach[i][j].pro == 8)
			{
				setfillcolor(EGERGB(0xF0, 0x80, 0x80));
				bar(mach[i][j].time_sta + 30, length + move, mach[i][j].time_end + 30, length + move + 20);
			}
			if (mach[i][j].pro == 9)
			{
				setfillcolor(EGERGB(0xff, 0xff, 0xcc));
				bar(mach[i][j].time_sta + 30, length + move, mach[i][j].time_end + 30, length + move + 20);
			}
		}//画矩形，同一个工件一样的填充色

		setfont(10, 0, "宋体");//将字体变小
		
		for (k = 0; k < num_mac; k++)//该循环用来打印每一个工序的开始时间和结束时间
		{
			for (j = 0; j < num_pro; j++)
			{
				sprintf_s(s, "%d", mach[k][j].time_sta);//在该工件开始位置打印起始时间
				outtextxy(mach[k][j].time_sta + 30, k * 40 + 20 + move, s);
				if (mach[k][j].time_end != mach[k][j + 1].time_end)
				{
					sprintf_s(s, "%d", mach[k][j].time_end);//在该工件开始位置打印结束时间
					outtextxy(mach[k][j].time_end + 30, k * 40 + 20 + move, s);
				}
			}
		}
	}
	

	for (i = 0; i < check_times; i++)
	{
		if (mac2[i].num != -1)
		{
			int  pro;
			pro = find_num(mac2[i].num);
			setfillcolor(WHITE);
			bar(mac2[i].check_sta+ 30, mac2[i].num * 40 + move, mac2[i].check_end + 30 , mac2[i].num * 40 + move + 20);
			sprintf_s(s, "%d", mac2[i].check_sta);//检修开始时间
			outtextxy(mac2[i].check_sta + 30, mac2[i].num * 40 + 20 + move, s);
			sprintf_s(s, "%d", mac2[i].check_end);//检修结束时间
			outtextxy(mac2[i].check_end + 30 , mac2[i].num * 40 + 20 + move, s);
			
			if (x != -1)
			{
			setfillcolor(BLACK);
			//bar(1000, 432, 1046, 543);
			bar(mac2[i].check_sta-difference[i] + 30, mac2[i].num * 40 + move, mac2[i].check_sta + 30, mac2[i].num * 40 + move + 20);
			sprintf_s(s, "%d", mac2[i].check_sta - difference[i] + 30);
			outtextxy(mac2[i].check_sta - difference[i] + 30, mac2[i].num * 40 + move + 20, s);

			}
			
		}
		else
		  i++;

	}
	setfillcolor(BLACK);
	bar(HI + 30, move, 2000,num_mac*40 + move + 20);
}

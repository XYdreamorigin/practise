#include"define.h"
#include<stdio.h>
#include<windows.h>
#include<time.h>
extern clock_t start, end;
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
extern int x, y;
extern struct mac mac3[100];//���治��Ĺ����ź͹����
extern HANDLE hMutex;//�߳̾��
extern int present_time;//��ǰ����ʱ��
extern int mnum, checktime;//mnum���޵Ļ����ţ�checktime����ʱ��
extern struct machine mach[30][30];//��һ��30Ϊ������ţ��ڶ���30Ϊ�ڼ��ι���
extern int sign;
extern struct macnum2 mac2[check_times];
extern int chrom2[chromnum][300];//��������֮����������
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
char s[50];//��������״̬


int adapt_count2(int i)//����Ϊ��i��Ⱦɫ��,����Ⱦɫ����Ӧ�ȼ���  ����
{
	//int adaption //��Ӧ�ȣ���������й����������ʱ��
	int j = 0, total_time1;//
	int time = 0, mac = 0;
	int macnum[300] = { 0 };//�����������ʱ����һά���飬��С����num_mac
	int macnum1[30];//����������ִ�����һά���飬��С����num_mac
	int pro_statime[chromnum][chromnum] = { 0 };
	int pro_endtime[chromnum][chromnum] = { 0 };
	int max_time = 0;
	int times[300] = { 0 };//��¼����
	int k = 0;//��K������
	for (j = 0; j < 30; j++)//macnum1��ʼ��
	{
		macnum1[j] = -1;
	}
	//for (i; i < chromnum; i++)//Ⱦɫ������
	//���ĳ��Ⱦɫ�����Ӧ��
	for (j = 0; j <chromlength; j++) //Ⱦɫ�峤��
	{
		k = chrom[i][j];
		times[k]++;//k�ڼ��γ���  

		time = machinetime[k][times[k] - 1];//�ӹ�ʱ�� 
		mac = machinenum[k][times[k] - 1];//��Ӧ������ 
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
																								 //���»���״̬�ṹ������
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
void rearrangement()//������50���µ�Ⱦɫ�壬���Ǽ���֮ǰ������û�з����ı�
{
	int i, j;
	int chrom3[chromnum][300], temp2[chromnum][100],chrom4[chromnum][300];
	for (i = 0; i < chromnum; i++)
	{
		for (j = 0; j < chromlength; j++)
		{
			chrom3[i][j] = -1;//��ʼ��Ϊ-1
			chrom4[i][j] = -1;
		}
	}
	for (i = 0; i < chromnum; i++)
		for (j = 0; j < chromlength; j++)
			temp2[i][j] = chrom[chromnum - 1][j];

	int times[100] = { 0 };
	for (i = 0; i < total_times+1; i++)//�ҳ���Ӧ�ñ仯��ֵ
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
			chrom4[i][j] = chrom4[0][j];//��������Ӧ�ñ仯��ֵ��
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
void rearrangement1()//������50���µ�Ⱦɫ�壬���Ǽ���֮ǰ������û�з����ı�
{
	int i, j, k, n, position, point;

	//�����ʱ���ڼӹ���x�������ĵ�y������
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
	}//�ж���Ⱦɫ���ϳ��ֵ�λ��*/
	position = total_times;
	printf("*%d*\n", position);
	for (i = 0; i < chromnum; i++)
		for (j = 0; j < position; j++)
			chrom2[i][j] = chrom[chromnum - 1][j];//��50�������ڼ��޵�֮ǰ�����������Ž�һ��


	for (n = 0; n < chromnum; n++)
	{
		for (i = position, j = 0; i < chromlength; i++)//������֮��Ļ���Ž��µ�����
		{
			temp[j] = chrom[chromnum - 1][i];
			j++;
		}

		point = rand() % 20;
		i = position+1;

		for (k = 0; k < j; k++)
		{

			while (temp[point] == -1)           //������֮��Ļ����������ֵ��chrom2
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
void short_DNA()   //�������ʱû�й����ڼӹ���DNA���еõ����ʱ��
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
//�߳�2 �������ָ��
DWORD WINAPI check(LPVOID pPararneter)
{
	x = -1;
	y = -1;
	total_times = -1;
	ctimes = 0;
	char h;
	//�����Ĺ�������ṹ�������ʼ��
	for (int i = 0; i < 100; i++)
	{
		mac3[i].x = -1;
		mac3[i].y = -1;
	}
	//��ʼ������ֵ��ֵ
	for (int i = 0; i < check_times; i++)
	{
		difference[i] = 0;
	}
	while (tempb != num_mac)//��ѭ����������������Ϊtempb���л����������ڻ�������
	{
		h = getchar();
		if (h == 'C')
		{
			scanf("%d %d", &mnum, &checktime);//�����������ӹ�ʱ��
		}
		end = clock();
		clock_time = int((((double)(end - start)) / CLK_TCK) * ratio*real_time);
	//	clock_time = int((((double)(end - start)) / CLK_TCK) *12);
	//	printf("%d**", clock_time);
		for (int i = 0; i < num_pro; i++)
		{   //clock_timeΪ���ܼ���ָ���ȷ�л���ʱ��,��δ��ֵ
			if (mach[mnum][i].time_sta <= clock_time && mach[mnum][i].time_end >= clock_time)
			{
				x = mach[mnum][i].pro;//xΪ��������ǰ���һ����Ʒ�Ĺ�����
				y = mach[mnum][i].cess;//yΪ��������ǰ���һ����Ʒ�Ĺ����
				machinetime[x][y] = machinetime[x][y] + checktime;//�ӳ���������ǰ���һ������״̬�Ľ���ʱ���ӳ���
																  //����״̬�ṹ�帳ֵ
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
				machinetime[x][y] = machinetime[x][y] + checktime + clock_time - mach[mnum][i - 1].time_end;//�ӳ���������ǰ���һ������״̬�Ľ���ʱ���ӳ���
				difference[ctimes] = clock_time - mach[mnum][i - 1].time_end;
				//����״̬�ṹ�帳ֵ
				mac2[ctimes].check_sta = clock_time;
				mac2[ctimes].check_end = clock_time + checktime;
				mac2[ctimes].num = mnum;
				mac2[ctimes].time = checktime;
				ctimes++;

				break;
			}
		}
		//ͳ�Ʋ���Ļ���
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

		//�����Ĺ�������ṹ�������ʼ��
		for (int i = 0; i < 100; i++)
		{
			mac3[i].x = -1;
			mac3[i].y = -1;
		}
	}
	//ReleaseMutex(hMutex);//�ͷž��
	return 0;
}
//�߳�1 ���»����ṹ������,���������
DWORD WINAPI working_printf(LPVOID pPararneter)
	{
	int i, j, k, tempa = 0, present_time = 0, tempc = 0;
		while (tempb!=num_mac)//���̣߳�ÿ2S���һ�Σ���������������Ϊtempb���л����������ڻ�������
		{
			adapt_count(chromnum - 1);//����mach[][]�ṹ���ά���飬�������״̬
			present_time = present_time + (ratio*real_time);
			for (int kb = 0; kb < num_mac; kb++)//������
			{
				for (j = 0; j < num_pro; j++)//�����ϵĹ�����
				{
					for (k = 0; k < check_times;k++)  //�ж��Ƿ�Ϊ����
					{
						if (mac2[k].num==kb)
						{
							if (present_time < mac2[k].check_end&&present_time >= mac2[k].check_sta)
							{
							//	printf("%d %d ����  -  %d %d\n", present_time, kb, present_time- mac2[k].check_sta, mac2[k].check_end- present_time);
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
					 //present_timeΪÿ2S��ʱ�����㣬��Ӧ6
					//�ӹ�״̬�ж�
					//����ӹ�
					if (present_time >= mach[kb][j].time_sta&&present_time < mach[kb][j].time_end)
					{
					//	printf("%d %d �ӹ� %d-%d %d %d\n", present_time,kb, mach[kb][j].pro, mach[kb][j].cess, present_time - mach[kb][j].time_sta, mach[kb][j].time_end - present_time);
						tempc = 1;
						break;
					}
					//���� ����
				//	else
					/*
					if (j + 1 < num_pro)
					{
						if (present_time <= mach[kb][j + 1].time_sta || mach[kb][j + 1].time_sta == -1)
						{
							if (present_time < mach[kb][j].time_sta)
							{
								printf("%d %d ����  -  %d %d\n", present_time, kb, present_time, mach[kb][j].time_sta - present_time);
								tempb++;
								break;
							}
							else
								if (mach[kb][j + 1].time_sta != -1)
								{
									printf("%d %d ����  -  %d %d\n", present_time, kb, present_time - mach[kb][j].time_end, mach[kb][j + 1].time_sta - present_time);
									tempb++;
									break;
								}
						}
					}*/
				}
				if (tempc== 1) { tempc = 0; }
				else
				{
				//	printf("����");
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
		printf("Time Used:%.3lfs\n", (q - total_clock) / 1000);//������ĵ�λ�Ǻ���
		printf("End Time:%d\n", total_time);
		output_file1((q - total_clock) / 1000);
		output_picture1(present_time);
		return 0;
	}
/*
	DWORD WINAPI state_update(LPVOID pPararneter)//�߳��ͻ���״̬��ֵ
	{
		//while (present_time <= total_time)
		//{
		int j = 0, q = 0, g = 0;//gΪ���޽ṹ��������±�
		int time = 0, mac = 0;
		int macnum[300] = { 0 };//�����������ʱ����һά���飬��С����num_mac
		int macnum1[30];//����������ִ�����һά���飬��С����num_mac
		int pro_statime[chromnum][chromnum] = { 0 };
		int pro_endtime[chromnum][chromnum] = { 0 };
		double max_time = 0.00;
		int times[300] = { 0 };//��¼����
		int k = 0;//��K������
		for (j = 0; j < 30; j++)//macnum1��ʼ��
		{
			macnum1[j] = -1;
		}
		//������Ϣ�ṹ�帳ֵ
			for (j = 0; j <check_times; j++)
			{
				mac2[j].check_end = -1;
				mac2[j].check_sta = -1;
				mac2[j].num = -1;
			}
		//����״̬��Ϣ��ȡ
			while (present_time <= total_time)
			{
				j = 0, q = 0, time = 0, mac = 0, macnum[300] = { 0 }, pro_statime[chromnum][chromnum] = { 0 }, pro_endtime[chromnum][chromnum] = { 0 }, max_time = 0.00, times[300] = { 0 }, k = 0;

				for (j = 0; j < chromlength; j++) //Ⱦɫ�峤��
				{  //�Ƿ�����б�����
					
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
						//��������Ϣ��ֵ�����޽ṹ����
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
					k = chrom[chromnum - 1][j];//jΪȾɫ���ϵ�λ�����
					times[k]++;//k�ڼ��γ���  

					time = machinetime[k][times[k] - 1];//�ӹ�ʱ�� 
					mac = machinenum[k][times[k] - 1];//��Ӧ������ 
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
					//����״̬�ṹ�帳ֵ																					 //���»���״̬�ṹ������
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
	    int present_time = 0;//aΪ��ǰʱ��㣬����ʱ�䵥λ
		int i = 0, g = 0;//gΪ���޽ṹ��������±�
		
	while (present_time <= ttime)
	{
		present_time = present_time + 90;
		int b = 0, c = 0;
		int j = 0;
		int time = 0 ,mac = 0;
		int macnum[300] = { 0 };//�����������ʱ����һά���飬��С����num_mac
		int macnum1[30];//����������ִ�����һά���飬��С����num_mac
		int pro_statime[chromnum][chromnum] = { 0 };
		int pro_endtime[chromnum][chromnum] = { 0 };
		double max_time = 0.00;
		int times[300] = { 0 };//��¼����
		int k = 0;//��K������
		int present_time1 = 0;
		for (j = 0; j < 30; j++)//macnum1��ʼ��
		{
			macnum1[j] = -1;
		}
			for (j = 0; j < chromlength; j++) //Ⱦɫ�峤��
			{
				k = chrom[chromnum - 1][j];//jΪȾɫ���ϵ�λ�����
				times[k]++;//k�ڼ��γ���  
				time = machinetime[k][times[k] - 1];//�ӹ�ʱ�� 
				mac = machinenum[k][times[k] - 1];//��Ӧ������ 
				macnum1[mac]++; //
				int temp = 0;
				
				//
				//��ȡ�˻�����һ�������Ŀ�ʼʱ�䣬tempΪ��ֵ
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
				//�����ж�
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

				//����״̬�ṹ�帳ֵ  ֻ�л�����������ʱ��С�ڵ�ǰʱ����ܸ�ֵ
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

	//���
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
			//�ж��Ǽ��޻��ǿ���
			if (b == 0)
			{
				for (k = 0; k < check_times; k++)
				{
					if (mac2[k].num == mnum)
					{
						if (present_time <= mac2[k].check_end&&present_time >= mac2[k].check_sta)
						{
							printf("����");
							c = 1;
							break;
						}
					}
				}
				if (c == 1) { c = 0; }
				else { printf("����"); }
			}
			if (b == 1) { b = 0; }
			printf("\n");
		}
		printf("*************************************\n");
		Sleep(3000);
	}
	return 0;
}*//*
//�߳�1 ��ӡ��ǰ����״̬
DWORD WINAPI working_printf1(LPVOID pPararneter)
	{
	 int i = 0, j = 0, b = 0, k = 0,c=0;
		int present_time = 0;//aΪ��ǰʱ��㣬����ʱ�䵥λ
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
				//�ж��Ǽ��޻��ǿ���
				if (b == 0)
				{
					for (k = 0; k < check_times; k++)
					{
						if (mac2[k].num == mnum)
						{
							if (present_time >= mac2[k].check_end&&present_time <= mac2[k].check_sta)
							{
								printf("����");
								c = 1;
								break;
							}
						}
			
					}
					if (c == 1){c = 0;}
					if (c == 0){printf("����");}
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
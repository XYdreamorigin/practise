
//�������ļ�Ҳ���������ˣ�δ���޸� 

//��������
int num_pro;//��Ʒ��Ŀ
int num_mac;//������Ŀ
#define chromnum 250//Ⱦɫ������������ʼ���������
#define p1 0.95 //�������
#define p2 0.05 //�������
#define generation_max 200//������
#define num_pro1 30//�����Ͳ�Ʒ��Ŀ
#define num_mac1 30//�����ͻ�����Ŀ

int chromlength; //Ⱦɫ�峤��
int chrom[chromnum][300]; //������Ⱥ����
int chrom1[chromnum][300];//�Ӵ���Ⱥ����
int machinenum[30][30];//����� i ��������j��������ʹ�û�����  ������ 
int machinetime[30][30];// ����� i ��������j�������  �ķ�ʱ��
double adaption[chromnum];
double sum;
int total_time;

//��������״̬�ṹ��
struct machine 
{
	int time_sta;//������ʼ����ʱ��
	int time_end;//������������ʱ�䰴=
	int pro;     //���������ڼӹ��Ĳ�Ʒ��
	int cess;    //���������ڼӹ��Ĳ�Ʒ�Ĺ����
}mach[30][30];//��һ��30Ϊ������ţ��ڶ���30Ϊ�ڼ��ι���



#include<stdio.h>
#include <stdlib.h>
#include"define.h"
#include<time.h>
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
extern void data_translation();
//extern int end_judge();
extern void output_com();
extern double  adapt_count(int i);
//extern void chromcreate_1(void);
int main()
{	
	struct machine begin = { -1, -1, -1, -1 };
	int l, k, i, g;
	srand((unsigned)time(NULL));
	input_file();                   //�������� 
	//input_com();
	double a = clock();//���⿪ʼ��ʱ
	chromlength = num_pro * num_mac;//Ⱦɫ�峤�ȸ�ֵ  
									//	printf("%d", chromlength);
	chromcreate(chromnum);                  //���������Ⱥ  //����
									//sum_adapt();
	for (i = 0; i < generation_max; i++)
	{
		//if ((generation_max / i )== 2) { chromcreate(i); }
		Wheel_cre();                    //��������
	   //����
		for (l = 0, k = (chromnum / 2); k < chromnum; k++, l++)
		{
			int a = wheel_choose(), b = wheel_choose();
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
		adaption_compare();              //��������
		adaption_compare1();             //�Ӵ�����
		//����
		for (k = 0; k < chromnum/2; k++)
			variation(k);

		replace();                       //��Ӣ���ԡ����������滻�Ӵ����
		adaption_compare1();             //�Ӵ�����
		data_translation();              //�Ӹ���ת��
		adaption_compare();              //��������
		adapt_count(chromnum-1);
		printf("%d\n", total_time);	
			
		}
	//	adaption_compare();                    //��������
											  //��ʼ����״̬�ṹ������
	for (l = 0; l < num_mac; l++)
		for (k = 0; k < num_mac; k++)
			mach[l][k] = begin;


	adapt_count(chromnum - 1);             //�������Ÿ�����Ӧ�ȼ���
	output_com();                              //������

	double b = clock();//�������
	printf("Time Used:%.3lfs\n", (b - a) / 1000);//������ĵ�λ�Ǻ���
	printf("End Time:%d\n", total_time);
	output_file((b - a) / 1000);
	system("pause");
}






#include<stdio.h>
#include"define.h"
//���������� 
void input_com()
{
	char a = '0';
	int i = 0, j = 0;
	scanf("%d %d", &num_pro, &num_mac);//�����Ʒ�������Ŀ
	while (1)
	{
		while (1)
		{
			scanf("%d %d", &machinenum[i][j], &machinetime[i][j]);
			j++;
			if ((a = getchar()) == '\n')break;
		}
		j = 0;
		i++;
	}
	i = 0;
	j = 0;
}
//�ļ����� ����
void input_file()
{
	int i = 0, j = 0;
	FILE *fp = fopen("input.txt", "r");
	fscanf(fp, "%d %d", &num_pro, &num_mac);
	for (i = 0; i < num_pro; i++)
	{
		for (j = 0; j < num_mac; j++)
		{
			fscanf(fp, "%d %d", &machinenum[i][j], &machinetime[i][j]);
		}
	}
	i = 0, j = 0;
	fclose(fp);
}






#include<time.h>
#include<stdlib.h>
extern void Wheel_cre(void);
#include"define.h"
extern int wheel_choose(void);
struct timesstruct
{
	int pro;//��Ʒ��
	int find;//�ڼ��γ��� 
}str[2][200];
//�������Ⱦɫ��
void chromcreate(int g)// ���������Ⱥ ����
{
	int i, j, k, l;
	int a[chromnum] = { 0 };
	for (i = 0; i < g; i++)
	{
		for (j = 0; j < chromlength; j++)
		{
			while (1)
			{
				k =rand() % (num_pro);
				a[k]++;
				if (a[k] <= num_mac)
				{
					chrom[i][j] = k;
					break;
				}
			}
		}
		for (l = 0; l <g; l++)
			a[l] = 0;
	}
}



void cross(int k, int l, int a)//���ô��򽻲淨 k l Ϊ������Ⱦɫ��ı�ţ�aΪ�Ӵ����
{
	int i, j, g;
	int f1[200], f2[200], c1[200], c2[200];
	int times1[num_pro1] = { 0 };
	int times2[num_pro1] = { 0 };
	int timetime_1[300];
	int r1 = 1, r2 = 0, temp;

	for (i = 0; i < chromlength; i++)//����Ⱦɫ�帳ֵ
	{
		f1[i] = chrom[k][i];//Ⱦɫ��f1
		f2[i] = chrom[l][i];//Ⱦɫ��f2
		c1[i] = -1;         //�Ӵ�
	}

	for (i = 0; i < chromlength; i++)//��ʼ��timetime_1
		timetime_1[i] = -1;

	r1 = rand() % (chromlength);
	r2 = rand() % (chromlength);
	if (r1 > r2)
	{
			temp = r1;
			r1 = r2;
			r2 = temp;
	}

	for (j = 0; j < chromlength; j++)
		{
			str[0][j].find = 0;
			str[0][j].pro = -1;
		}

	for (i = r1; i < r2; i++)//ѡ�������Ƹ��Ӵ���Ӧ���� 
		c1[i] = f1[i];

	for (i = 0, j = 0; i < chromlength; i++)//��¼ѡ������Ĳ�Ʒ���ǵڼ��γ��֣���0��ʼ 
	{
		times1[f1[i]]++;
		if (i >= r2) { break; }
		if (i >= r1)
		{
			str[0][j].pro = f1[i];
			str[0][j].find = times1[f1[i]];
			j++;
		}
	}

	for (i = 0; i < chromlength; i++)//��Ǹ���
	{
		times2[f2[i]]++;
		for (j = 0; str[0][j].pro != -1; j++)
		{
			if (f2[i] == str[0][j].pro)   //pro=f2[i]    find= times2[f2[i]]
			{
				if (times2[f2[i]] == str[0][j].find)
					timetime_1[j] = i;//Ҫ���-1 ���±�Ĵ�������
			}
		}
	}
	for (i = 0; i < chromlength; i++)
		if ((timetime_1[i]) != -1)
			f2[(timetime_1[i])] = -1;

	//�������Ӵ���ֵ
	for (i = 0, j = 0; (i < chromlength,j < chromlength); )
	{
		if (f2[i] != -1)
		{
			if (c1[j] == -1)
			{
				c1[j] = f2[i];
				j++;
				i++;
			}
			else
			j++;
		}
		else
		i++;
	}	

    for (i = 0; i < chromlength; i++)
	chrom1[a][i] = c1[i];
}

void variation(int f1)//�����㷨
{
	int k, l;
	l = Rand();
	if (l < p2)
	{
		int temp, location1, location2;//����λ��1��2
		location1 = rand() % (num_pro);
		location2 = rand() % (num_pro);
		while (location1 == location2)
			location2 = rand() % (num_pro);

		temp = chrom1[f1][location1];
		chrom1[f1][location1] = chrom1[f1][location2];
		chrom1[f1][location2] = temp;
	}
}

/*int end_judge()//�ж��Ƿ�ֹͣ����
{
	int q,j,k=0,l=0;
	for (q = 0; q < chromnum; q++)
		{
			for (j = 0; j < chromlength; j++)
			{
				if(chrom[q][j] == chrom[q + 1][j]){k++;}
			}
			if (k == chromlength) 
			{ l++;}
			k = 0;
		}

	//printf("%d", l);

	if (l > same) { return 1; }
	else { return 0; }
}*/





#include<stdio.h>
#include"define.h"
#include<time.h>
#include<conio.h>
#include<stdlib.h>
extern double  adapt_count1(int i);
extern double  adapt_count(int i);
void adaption_compare()//����Ⱦɫ������ ����
{
	double adapt[chromnum];//����ÿ��Ⱦɫ�����Ӧ��
	int i=0, j=0, min=0,k=0;
	double temp1=0.00;
	int temp=0;
	for (i = 0; i < chromnum; i++)
		adapt[i] = adapt_count(i);
	for (i = 0; i < chromnum-1; i++)
	{
		min = i;
		for (j = i + 1; j <= chromnum - 1; j++)
		{
			if (adapt[min] > adapt[j])
			{min = j;}
		}
		temp1 =adapt[i];
		adapt[i] = adapt[min];
		adapt[min] = temp1;
		for (k = 0; k < chromlength; k++)
		{
			temp = chrom[i][k];
			chrom[i][k] = chrom[min][k];
			chrom[min][k] = temp;
		}
	}
}

void adaption_compare1()//�Ӵ�Ⱦɫ������ 
{
	double adapt1[chromnum];//����ÿ��Ⱦɫ�����Ӧ��
	int i = 0, j = 0, min = 0, k = 0;
	double temp1 = 0.00;
	int temp = 0;
	for (i = 0; i < chromnum; i++)
		adapt1[i] = adapt_count1(i);
	for (i = 0; i < chromnum - 1; i++)
	{
		min = i;
		for (j = i + 1; j <= chromnum - 1; j++)
		{
			if (adapt1[min] > adapt1[j])
			{
				min = j;
			}
		}
		temp1 = adapt1[i];
		adapt1[i] = adapt1[min];
		adapt1[min] = temp1;
		for (k = 0; k < chromlength; k++)
		{
			temp = chrom1[i][k];
			chrom1[i][k] = chrom1[min][k];
			chrom1[min][k] = temp;
		}
	}
}
void replace(void)//���������滻�Ӵ���� ����
{
	int i;
	for (i = 0; i < chromlength; i++)
		chrom1[0][i] = chrom[chromnum - 1][i];
}

void data_translation()//�Ӵ���ֵ���������� ����
{
	int i, j;
	for (i = 0; i < chromnum; i++)
	{
		for (j = 0; j < chromlength; j++)
		{
			chrom[i][j] = chrom1[i][j];
		}
	}
}
double Rand() //����
{
	double r;
	r = (rand() % 100)*0.01;
	return r;
}




#include"define.h"
#include<stdio.h>


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
				pro_statime[k][times[k] - 1] = pro_endtime[k][times[k] - 2];
				else
				pro_statime[k][times[k] - 1] = macnum[mac];
			}
			if (times[k] == 1)
			pro_statime[k][times[k] - 1] = macnum[mac];

			pro_endtime[k][times[k]-1] = time + pro_statime[k][times[k]-1];//2
			macnum[mac] = pro_endtime[k][times[k]-1];//3

			if(max_time < pro_endtime[k][times[k]-1])
			max_time = pro_endtime[k][times[k]-1];//Tip

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
		macnum1[j] = -1;


	//���ĳ��Ⱦɫ�����Ӧ��
	for (j = 0; j <chromlength; j++) //Ⱦɫ�峤��
	{
		k = chrom1[i][j];
		times[k]++;//k�ڼ��γ���  

		time = machinetime[k][times[k] - 1];//�ӹ�ʱ�� 60
		mac = machinenum[k][times[k] - 1];//��Ӧ������ 0
		macnum1[mac]++; //0
		if (times[k] != 1)
		{
			if (macnum[mac]<pro_endtime[k][times[k] - 2])
			pro_statime[k][times[k] - 1] = pro_endtime[k][times[k] - 2];
	
			else
			pro_statime[k][times[k] - 1] = macnum[mac];

		}

		if (times[k] == 1)
		pro_statime[k][times[k] - 1] = macnum[mac];

		pro_endtime[k][times[k] - 1] = time + pro_statime[k][times[k] - 1];//2
		macnum[mac] = pro_endtime[k][times[k] - 1];//3

		if (max_time < pro_endtime[k][times[k] - 1])
		max_time = pro_endtime[k][times[k] - 1]; //Tip
																								 //���»���״̬�ṹ������
		mach[mac][macnum1[mac]].time_sta = pro_endtime[k][times[k] - 1] - time;
		mach[mac][macnum1[mac]].time_end = pro_endtime[k][times[k] - 1];
		mach[mac][macnum1[mac]].pro = k;
		mach[mac][macnum1[mac]].cess = times[k] - 1;
		
	}
	total_time = (int)max_time;
	max_time = (double)max_time;
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
		sum = adaption[i] + sum;
	}
}


#include<stdlib.h>
#include<stdio.h>
#include"define.h"
double probability[chromnum];
void Wheel_cre(void) //����
{
	int i;
	sum_adapt();//��Ӧ�����
	for (i = 0; i < chromnum; i++)
		probability[i] = adaption[i] / sum;
}

int wheel_choose()//����
{
	int i;
	double r = rand() / (RAND_MAX + 1.0);
	double m = 0;
	for (i = 0; i < chromnum; i++)
	{
		m = m + probability[i];
		if (r<m)
		break;
	}
	return i;
}




#include<stdio.h>
extern double  adapt_count(int i);
#include"define.h"
void output_com()
{
	
	int i = 0, j = 0;
	for(i = 0; i < num_mac; i++) 
	{
		printf("M%d",i);
		for (j = 0; j < num_pro; j++)
		{
			printf( " (%d,%d-%d,%d)",mach[i][j].time_sta,mach[i][j].pro,mach[i][j].cess,mach[i][j].time_end);
		}
		printf("\n");
	}
}
void output_file(double a)
{
	FILE *fp1 = fopen("output.txt", "w+");
	int i = 0, j = 0;
	for (i = 0; i < num_mac; i++)
	{
		fprintf(fp1, "M%d", i);
		for (j = 0; j < num_pro; j++)
		{
			fprintf(fp1, " (%d,%d-%d,%d)", mach[i][j].time_sta, mach[i][j].pro, mach[i][j].cess, mach[i][j].time_end);
		}
		fprintf(fp1, "\n");
	}
	fprintf(fp1, "Time Used:%.3lfs\n", a);//������ĵ�λ�Ǻ���
	fprintf(fp1, "End Time:%d\n", total_time);
	fclose(fp1);
}

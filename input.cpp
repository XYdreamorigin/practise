#include<stdio.h>
#include"define.h"
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


	//printf("%d %d\n ", num_pro, num_mac);
	//for (i; i < num_pro; i++)
	//{
	//	for (j = 0; j < num_mac; j++)
	//	{
	//		printf("%d %d ", machinenum[i][j], machinetime[i][j]);
	//	}
	//	printf("\n");
	//}
}
//system("pause");
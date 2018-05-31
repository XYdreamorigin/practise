#include<stdio.h>

int main()
{
	printf("请输入两个二进制数：\n");
	int number1,number2,temp;//需要相加的二进制数 
	int i,j,d,c=0,length1=1,length2=1;//length为二进制数长度
	int a[100],b[100],ab[100];
	scanf("%d%d",&number1,&number2);
	temp=number1;
	while(temp>9)
	{
		temp=temp/10;
		length1++;
	}
//	printf("%d",length1);
//	printf("\n");
	for(i=0;i<length1;i++)
	{
		a[i]=number1%10;
		number1=number1/10;
	}
	temp=number2;
	while(temp>9)
	{
		temp=temp/10;
		length2++;
	}
//	printf("%d",length2);
//	printf("\n");
	for(i=0;i<length2;i++)
	{
		b[i]=number2%10;
		number2=number2/10;
	}
	if(length1<length2)
		j=length2;
	else
	j=length1;
	for(i=0;i<j;i++)
	{
		d=(a[i]+b[i]+c)/2;
		ab[i]=a[i]+b[i]+c-2*d;
		c=d;
	}
	ab[j]=c;
	if(ab[j]==0)
	for(i=j-1;i>=0;i--)
	printf("%d",ab[i]);
	else
	for(i=j;i>=0;i--)
	printf("%d",ab[i]);
	return 0;
	
}

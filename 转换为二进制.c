#include<stdio.h>

int main() 
{
	int a[300];
	int number,number1,i,j;
	printf("请输入一个数\n");
	scanf("%d",&number);
	if(number==1)
	printf("%d",number);
	else
	{
		for(i=0;i<300;i++)
	{
		a[i]=number%2;
		number=number/2;
		if(number==1)
		{
			a[i+1]=1;
			break;
		}
	
	}
	for(j=i+1;j>=0;j--)
	printf("%d",a[j]);
	}
	
	return 0;
}

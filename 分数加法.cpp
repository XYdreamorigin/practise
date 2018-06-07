#include<stdio.h>
#include<math.h>
int main()
{
	int group,a,b,i,num,den;//numerator是分子，denominator是分母 
	int group1[400],a1[400],b1[400];
	scanf("%d",&group);
	
	for(i=0;i<group;)
	{
		scanf("%d%d",&a1[i],&b1[i]);
		if(a1[i<=2&&b1[i]]<=20)
		i++;
		else
		scanf("%d%d",&a1[i],&b1[i]);
	}
	
	
	for(i=0;i<group;i++)
	{
		if(a1[i]<=b1[i])
		{
			num=pow(2,b1[i]-a1[i])+1;
			den=pow(2,b1[i]);
			printf("%d/%d\n",num,den);
		 } 
		else
		{
			num=pow(2,a1[i]-b1[i])+1;
			den=pow(2,a1[i]);
			printf("%d/%d\n",num,den);
		}
	}
	return 0;
 } 

#include<stdio.h>

int main()
{
	int hour1[50000],hour2[50000],minute1[50000],minute2[50000],gap[50000],i,group;
	scanf("%d",&group);
	if(1<=group<=50000)
	{
		for(i=0;i<group;i++)
		{
			scanf("%d:%d",&hour1[i],&minute1[i]);
			scanf("%d:%d",&hour2[i],&minute2[i]);
		}
		for(i=0;i<group;i++)
		{	
			if(0<=hour1[i]&&hour1[i]<24&&0<=hour2[i]&&hour2[i]<24&&0<=minute1[i]&&minute1[i]<60&&0<=minute2[i]&&minute2[i]<60)
			{
				if(hour1[i]<=hour2[i])
				gap[i]=(hour2[i]-hour1[i])*60+minute2[i]-minute1[i];
	
				if(hour1[i]>hour2[i])
				gap[i]=1440-hour1[i]*60-minute1[i]+hour2[i]*60+minute2[i];	
			}
		}
		i=0;
		
		if(0<=hour1[i]&&hour1[i]<24&&0<=hour2[i]&&hour2[i]<24&&0<=minute1[i]&&minute1[i]<60&&0<=minute2[i]&&minute2[i]<60)
			for(i;i<group;i++)
			{
				if(i==group-1)
				printf("%d",gap[i]);
				else
				printf("%d\n",gap[i]);	
			}
	
	}
	
	return 0;
 } 

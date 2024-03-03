#include<stdio.h>
int main()
{
	long unsigned int n=0,i=0,k=0,x=0,y=0,z=0;
	scanf("%d",&n);
	for(i=n;i>=1;i--)
	{	k=i;
		x=1;
		while(k>=10)
		{
			z=k%10;
			y=(k/10)%10;
			if(y>z)
			{
				x=0;
				break;
			}
			k=k/10;
		}
		if(x==1) break;

	}
	printf("%d",i);
	return 0;
}
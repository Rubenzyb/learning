#include<stdio.h>
int main(){
	int a=0,b=0,c=0,n=0;
	scanf("%d",&n);
	for(a=0;3*a<n;a++)
	{
		for(b=a+1;2*b<(n-a);b++)
		{
			c=n-a-b;
			if(c*c==a*a+b*b)
			goto out;
		}
	}
	out: printf("%d",a*b*c);
	return 0;
}
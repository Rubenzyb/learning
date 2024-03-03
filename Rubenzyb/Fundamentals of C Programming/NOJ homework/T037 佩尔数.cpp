#include <stdio.h>
int PA(int);
int PB(int);
int main()
{
	int input=0,chose=0;
	scanf("%d",&input);
	chose=input%2;
	if(!chose)printf("%d",PB(input));
	else printf("%d",PA(input));
	return 0;
}
int PA(int n)
{
	if(n==0)return 0;
	else if(n==1) return 1;
	return 2*PA(n-1)+PA(n-2);
}
int PB(int n)
{
	int p0=0,p1=1,pn,i;
	for(i=0;i<=n;i++){
		if(i==0)pn=p0;
		else if(i==1)pn=p1;
		else{
			pn=2*p1+p0;
			p0=p1;
			p1=pn;
		}
	}
	return pn;
}
#include<stdio.h>
inline int HarshadNumber(int);
int main()
{
	int n=0,count=0;
	scanf("%d",&n);
	do{
		n=HarshadNumber(n);
		if(n!=0) count++;
	}while(n>1);
	printf("%d",count);

}
inline int HarshadNumber(int n)
{
	int t=n,s=0;
	while(t) {
		s=s+t%10;
		t=t/10;
	}
	if (s&&n%s==0) return n/s;
	return 0;
}
#include<stdio.h>
int Count(int);
void Print(int);
int main()
{
	int a=0,b=0,i=0,j=0,sum=0,base=1;
	scanf("%d %d",&a,&b); 
	int count1=Count(b);
	int s[count1];
	int b1=b;
	for(i=0;i<count1;i++){
		s[i]=b1%10;
		b1/=10;
	}
	int count=Count(a*s[count1-1])+count1;
	printf("%*d\nx%*d\n",count,a,count-1,b);
	Print(count);
	for(i=0;i<count1-1;i++){
		s[i]*=a;
		printf("%*d\n",count-i,s[i]);
		sum+=s[i]*base;
		base*=10;
	}
	s[i]*=a;
	printf("+");
	printf("%*d\n",count-i-1,s[i]);
	sum+=s[i]*base;
	Print(count);
	printf("%*d",count,sum);
	return 0;
}
int Count(int n)
{
	int count=0,n1=n;
	while(n1>0){
		n1/=10;
		count++;
	}
	return count;
}
void Print(int count)
{
	int i=0;
	for(i=0;i<count;i++){
		printf("-");
	}
	printf("\n");
}
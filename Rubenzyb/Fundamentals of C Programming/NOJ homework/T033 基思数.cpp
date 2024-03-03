#include<stdio.h>
int Is_keith(int);
int Count(int);
int main()
{
	int n=0;
	scanf("%d",&n);
	if(Is_keith(n)) printf("Yes");
	else printf("No");
	return 0;
}
int Is_keith(int n)
{
	int i=0,j=0,n1=n,sum=0,judge=0,count=Count(n);
	int a[count];
	for(i=0;i<count;i++){
		a[count-i-1]=n1%10;
		n1/=10;
	}
	for(i=0;;i++){
		for(j=0;j<count;j++)sum+=a[j];
		if(sum==n){
			judge=1;
			break;
		}
		else if(sum>n){
			judge=0;
			break;
		}
		else {
			i%=count;
			a[i]=sum;
			sum=0;
		}
	}
	return judge;
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
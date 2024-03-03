#include<stdio.h>
double intercept(double,double,double);
double slope(double,double,long long int,long long int x[],long long int y[]);
int main()
{
	double a=0,b=0,x1=0,y1=0;
	long long int n=0,i=0;
	scanf("%lld",&n);
	long long int x[n],y[n];
	for(i=0;i<n;i++){
		scanf("%lld",&x[i]);
		x1+=x[i];
		scanf("%lld",&y[i]);
		y1+=y[i];
		getchar();
	}
	x1=x1/n;
	y1=y1/n;
	b=slope(x1,y1,n,x,y);
	a=intercept(x1,y1,b);
	printf("Y=%.4lf+%.4lf*X",a,b);
	return 0;
}
double slope(double x1,double y1,long long int n,long long int x[],long long int y[])
{
	double sum1=0,sum2=0,b=0;
	long long int i=0;
	for(i=0;i<n;i++){
		sum1+=(x[i]-x1)*(y[i]-y1);
		sum2+=(x[i]-x1)*(x[i]-x1); 
	}
	b=sum1/sum2;
	return b;
}
double intercept(double x1,double y1,double b)
{
	double a=0;
	a=y1-b*x1;
	return a;
}
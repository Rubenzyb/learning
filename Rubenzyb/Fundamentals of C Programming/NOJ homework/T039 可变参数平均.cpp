#include<stdio.h>
double avg(double,double,double);
int main(){
	int i=0;
	double a[5];
	for(i=0;i<5;i++){
		scanf("%lf",&a[i]);
	}
	printf("%.4lf",(avg(a[0],a[1],0)/2-avg(a[2],a[3],a[4])/3));
	return 0;
}
double avg(double a,double b, double c){
	return (a+b+c);
}

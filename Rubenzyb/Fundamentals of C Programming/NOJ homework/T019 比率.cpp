#include<stdio.h>
int main(){
	double a=0;
	int b=0,c=1,d=0,i=0;
	scanf("%lf",&a);
	while(a-(int)a!=0){
		a=10*a;
		c=10*c;
	}
	b=(int)a;
	(b>c)?(d=c):(d=b);
	for(i=d;i>=1;i--){
		if(b%i==0&&c%i==0)
		 {b=b/i;c=c/i;break;}
	}
	printf("%d/%d",b,c);
	return 0;
}
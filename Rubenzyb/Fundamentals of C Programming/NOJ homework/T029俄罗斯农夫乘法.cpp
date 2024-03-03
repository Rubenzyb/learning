#include<stdio.h>
int main()
{
	long long a=0,b=0,sum=0;
	scanf("%lld %lld",&a,&b);
	if(a==0){
		printf("%lld",0);
		return 0;
	}
	else if(a<0){
			a=-a;
			b=-b;
	}
	if(a%2!=0)sum+=b;
	printf("%lld %lld\n",a,b);
	while(a>1){
		a=a>>1;b=b<<1;
		printf("%lld %lld\n",a,b);
		if(a%2!=0)sum+=b;
	}
	printf("%lld",sum);
}	
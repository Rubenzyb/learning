#include<stdio.h>
#include<math.h>
int Sum_prime(unsigned int,unsigned int);
int Judge_prime(unsigned int);
int main()
{
	unsigned int a=0,b=0;
	scanf("%u %u",&a,&b);
	printf("%d",Sum_prime(a,b));
	return 0;
}
int Sum_prime(unsigned int a,unsigned int b)
{
	unsigned int i=0,a1=a;
	int sum=0;
	if(a1<=6){
		if(b<=6){
			for(i=a1;i<=b;i++)sum+=Judge_prime(i);
			return sum;
		}
		else{
			for(i=a1;i<=5;i++)sum+=Judge_prime(i);
			a1=7;
		}

	}
	i=a1/6;
	while(i*6+1<a1){
		if(6*i+5>=a1)sum+=Judge_prime(6*i+1);
		i++;
	}
	for(i;(6*i+5)<=b;i++){
		sum+=Judge_prime(6*i+1);
		sum+=Judge_prime(6*i+5);
	}
	for(i;(6*i+1)<=b;i++){
		sum+=Judge_prime(6*i+1);
	}
	return sum;
}
int Judge_prime(unsigned int i){
		if(i==1)return 0;
		int judge=1;
		unsigned int j=0;

		for(j=2;j<=(unsigned int)sqrt((double)i);j++){
			if(i%j==0){
				judge=0;
				break;
			}

		}
		return judge;
}
#include<stdio.h>
int main(){
	long unsigned int n=0,sum=0;
	unsigned int i=0,j=0,count=0;
	scanf("%d",&n);
	for(i=1;i<=n;i++){
		for(j=0;j<=(n-1);j++){
			sum=(2*i+j)*(j+1)/2;
			if(sum==n) count++;
			else if(sum>n)break;
		}
	}
	printf("%d",count);
	return 0;
}
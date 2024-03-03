#include<stdio.h>
void result(int n);

int main(){
	int n=0;
	scanf("%d",&n);
	result(n);
	return 0;
}

void result(int n){
	int x=n;
	printf("%d",x);
	while(x!=1){
		if(x%2==0) x=x/2;
		else x=3*x+1;
		printf(" ");
		printf("%d",x);
	}
}
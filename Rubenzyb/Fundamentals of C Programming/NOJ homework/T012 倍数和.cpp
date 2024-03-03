#include<stdio.h>
int main(){
	int t=0,i=0,j=0,n=0;
	int a[t];
	scanf("%d",&t);

	for(i=0;i<t;i++){scanf("%d",&a[i]);}
	for(i=0;i<t;i++){
		for(j=0;j<a[i];j++){
		if(j%3==0||j%5==0)n=j+n;
		}
		printf("%d\n",n);
		n=0;
	}

	return 0;
}
#include<stdio.h>
int sum(int a,int b, int c, int d);
int main(){
	int i=0;
	int a[6];
	for(i=0;i<6;i++){
		scanf("%d",&a[i]);
	}
	printf("%d",(sum(a[0],a[1],0,0)-sum(a[2],a[3],a[4],a[5])));
	return 0;
}
int sum(int a,int b, int c, int d){
	return (a+b+c+d);
}
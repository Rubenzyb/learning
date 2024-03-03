#include<stdio.h>
int Count(int,int);
int main()
{
	int n=0,m=0;
	scanf("%d %d",&n,&m);
	if(Count(n,m))printf("Yes");
	else printf("No");
	return 0;
}
int Count(int n,int m)
{
	int i=0,count=0;
	for(i=1;i<=n;i++){
		int j=0;
		for(j=1;j<=m;j++){
			int a=0;
			scanf("%d",&a);
			if(a) continue;
			else count++;
		}
		getchar();
	}
	if((m*n-count)<=n||(m*n-count)<=m||count>=0.95*m*n) return 1;
	else return 0;
}
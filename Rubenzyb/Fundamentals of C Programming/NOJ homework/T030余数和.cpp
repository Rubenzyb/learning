#include <stdio.h>
int main() {
	int n,k,i;
	long long sum;
	scanf("%d %d",&n,&k);
	for(i=2,sum=0;i<=n;i++) sum+=k%i;
	printf("%ld",sum);
	return 0;
}

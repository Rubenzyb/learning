#include <stdio.h>
int main() {
	int n,i;
	scanf("%d",&n);
	for(i=1;n>i;i++)n-=i;
	printf("%d",n);
	return 0;
}

//简化速通版 
#include <stdio.h> 
int main() {
	int i;
//读取数组长度和数组内容 
	int n; 
	scanf("%d",&n);
	int a[n];
	for(i=0;i<n;i++){
		scanf("%d",&a[i]);
	}
	
	int m;
	scanf("%d",&m);
	int b[m];
	for(i=0;i<m;i++){
		scanf("%d",&b[i]);
	}
	
//以指针扫描两个数组，按照大小顺序输出 
	int *pa=&a[0],*pb=&b[0];
	while(pa<=&a[n-1]&&pb<=&b[m-1]){
		
		if(*pa<=*pb){
			printf("%d\n",*pa);
			pa++;
		}
		
		else if(*pa>*pb){
			printf("%d\n",*pb);
			pb++;
		}
	}

//若数组a或数组b还有剩余的元素，直接输出到新数组的末尾 
	while(pa<=&a[n-1]){
		printf("%d\n",*pa);
		pa++;
	}
	
	while(pb<=&b[m-1]){
		printf("%d\n",*pb);
		pb++;
	}
	
	return 0; 
}

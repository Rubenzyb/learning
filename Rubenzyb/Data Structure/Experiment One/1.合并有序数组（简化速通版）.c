//����ͨ�� 
#include <stdio.h> 
int main() {
	int i;
//��ȡ���鳤�Ⱥ��������� 
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
	
//��ָ��ɨ���������飬���մ�С˳����� 
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

//������a������b����ʣ���Ԫ�أ�ֱ��������������ĩβ 
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

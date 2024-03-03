#include<stdio.h>
int Count(int,int,int,int,int);
int main()
{
	int T,i,n;
	scanf("%d",&T);
	int A[T],B[T],C[T],D[T],E[T];
	for(i=0;i<T;i++){
		scanf("%d %d %d %d %d",&A[i],&B[i],&C[i],&D[i],&E[i]); 
		getchar();
	}
	for(i=0;i<T-1;i++){
		n=Count(A[i],B[i],C[i],D[i],E[i]);
		if(n) printf("YES\n");
		else  printf("NO\n");
	}
	n=Count(A[i],B[i],C[i],D[i],E[i]);
	if(n) printf("YES");
	else  printf("NO");
	return 0;
}
int Count(int A,int B,int C,int D,int E)
{
	int MAX=0,MIN=0,ABC=A+B+C;
	int max,mid,min;
	if(ABC>D+E) return 0;
	if(D>E){MAX=D;MIN=E;}
	else{MAX=E;MIN=D;}	
	if(A>B){
		if(C>A) {max=C;mid=A;min=B;}
		else if(C>B){max=A;mid=C;min=B;}
		else{max=A;mid=B;min=C;}
	}
	else{
		if(C>B) {max=C;mid=B;min=A;}
		else if(C>A){max=B;mid=C;min=A;}
		else{max=B;mid=A;min=C;}
	}
	
	if(min>MIN) return 0;
	if(max+mid<=MAX) return 1;
	if(mid>MIN) return 0;
	if(max+min<=MAX) return 1;
	if(max>MIN) return 0;
	if(mid+min<=MAX) return 1;
}
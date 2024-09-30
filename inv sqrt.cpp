#include<stdio.h>
#include<math.h>
int main(){
	int num;
	double val;
	printf("Enter the number:");
	scanf("%d",&num);
	val=1/sqrt(num);
	printf("the inv sqrt is %d",val);
	return 0;
}
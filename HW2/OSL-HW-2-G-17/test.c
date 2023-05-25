#include<stdio.h>

int main() {
		int input;
		int output=1;
		printf("Please Enter Number: \n");
		scanf("%d",&input);
		for(int i=input ; i>0 ; i--){
			output = output*3;
		}
		printf("%d",output);
		return 0;
}


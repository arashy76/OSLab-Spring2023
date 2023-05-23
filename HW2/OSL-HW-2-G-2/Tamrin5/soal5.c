#include <stdio.h>

void swap(int arr[],int a){
    int temp = arr[a];
    arr[a] = arr[a+1];
    arr[a+1] = temp;
}

void bubbleSort(int arr[], int size) {
    int i, j;
    for (i = 0; i < size-1; i++) {
        for (j = 0; j < size-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                swap(arr,j);
            }
        }
    }
}

void calculateMiddle(int arr[], int size){
    int middle;
    if(size%2 == 0) {
        middle = (arr[size/2] + arr[size/2 - 1])/2;
    }
    else {
        middle = arr[size/2];
    }
    printf("The middle is: %d\n",middle);
}

int main() {
    int n;
    printf("Enter n: ");
    scanf("%d", &n);
    printf("Enter integers:\n");
    int arr[n];
    for(int i=0; i<n; i++) {
        scanf("%d", &arr[i]);
    }
    bubbleSort(arr,n);
    calculateMiddle(arr, n);
    return 0;
}



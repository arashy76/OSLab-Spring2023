#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;
    printf("Enter n: ");
    scanf("%d", &n);
    int NUM [n];
    int c;
    for(int i=0;i<n;i++)
    {
    printf("Enter %d:",i+1);
    scanf("%d", &NUM[i]);
    }

		for (int i = 0; i < n-1; i++)
		{
			for (int j = 0; j < n-i-1; j++)
			{
				if (NUM[j] < NUM[j+1])
				{
					double c = NUM[j];
					NUM[j] = NUM[j+1];
					NUM[j+1] = c;
				}
			}
		}

    for(int i=0;i<n;++i)
    {
    printf("%d ,",NUM[i]);
    }
    return 0;
}

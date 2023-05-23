// OSLab MBR GU
#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 1000

int main()
{
    int n, i;
    // Array lists for get strings from input and result for concatenation of strings
    char str[MAX_LENGTH], result[MAX_LENGTH];

    // If you want to see guide in terminal
    // printf("Enter the number of strings: ");
    // get n from input
    scanf("%d", &n);
    // in the beginning for the first value of result array we set \0
    result[0] = '\0';
    // get string input for n time
    for (i = 0; i < n; i++)
    {
        // If you want to see guide in terminal
        // printf("Enter string %d: ", i + 1);
        // get string from input and store to the str
        scanf("%s", str);

        // For make concatenation of all strings together
        strcat(result, str);
    }

    // show Result at the end on terminal wtih comment
    // printf("Result: %s\n", result);

    // show just Result at the end on terminal
    printf("%s\n", result);
    return 0;
}

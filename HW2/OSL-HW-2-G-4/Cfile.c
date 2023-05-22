#include <stdio.h>
#include <math.h>

double Mean(int numbers[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += numbers[i];
    }
    return (double)sum / size;
}

double Deviation(int numbers[], int size, double mean) {
    double squaredDifferencesSum = 0.0;

    for (int i = 0; i < size; i++) {
        double difference = (double)numbers[i] - mean;
        squaredDifferencesSum += difference * difference;
    }

    double meanOfSquaredDifferences = squaredDifferencesSum / size;
    return sqrt(meanOfSquaredDifferences);
}

int main() {
    int n;
    scanf("%d", &n);

    int numbers[n];

    for (int i = 0; i < n; i++) {
        scanf("%d", &numbers[i]);
    }

    double mean = Mean(numbers, n);
    double standardDeviation = Deviation(numbers, n, mean);

    printf("Mean: %f\n", mean);
    printf("Standard Deviation: %f\n", standardDeviation);

    return 0;
}

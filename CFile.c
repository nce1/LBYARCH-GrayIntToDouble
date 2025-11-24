#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "cfunction.h"

extern void imgCvtGrayIntToDouble(long long int totalPixels, long long int *pixels, double *output);

int main(){
	int h, w;
	printf("Input height and width: ");
	scanf("%d", &h);
    scanf("%d", &w);	

    FILE *fptr = fopen("ConvertedPixels.txt", "w");
    long long int totalPixels = (long long int)h * w;
    long long int* pixels = (long long int*) malloc (totalPixels * sizeof(long long int));
    double* output = (double*) malloc (totalPixels * sizeof(double));

    if (pixels == NULL || output == NULL){
        printf("Error: Could not allocate enough memory on the heap.\n");
        return 1;
    } 

    printf("Input pixel values per row:\n");
    for (int i = 0; i < totalPixels; i++){
        if ((i+1) % w == 0)
            scanf_s("%lld", &pixels[i]);
        else
            scanf_s("%lld, ", &pixels[i]);
    }

    clock_t start = clock();
    imgCvtGrayIntToDouble(totalPixels, pixels, output);
    //imgCvtGrayIntToDoubleC(totalPixels, pixels, output);
    clock_t end = clock();

    double totalTime = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Running time: %f seconds\n", totalTime);

    printf("Output:\n");
    for (int i = 0; i < totalPixels; i++){
        double value = ((double*) output)[i];
        //printf("%.2f ", value);
        fprintf(fptr, "%.2f ", value);
        if ((i+1) % w == 0){
            //printf("\n");
            fprintf(fptr, "\n");
        }
	} 
    fclose(fptr);
    free(pixels);
    return 0;
}
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

extern void imgCvtGrayIntToDouble(int h, int w, int *pixels, double *output);
int main(){
	int h = 100, w = 100;
	printf("Input height and width: ");
	scanf("%d", &h);
    scanf("%d", &w);	

    long long totalPixels = (long long)h * w;
    int *pixels = (int*)malloc(totalPixels * sizeof(int));
    double *output = (double*)malloc(totalPixels * sizeof(double));

    if (pixels == NULL || output == NULL){
        printf("Error: Could not allocate enough memory on the heap.\n");
        return 1;
    }

    printf("Input pixel values per row:\n");
    for (int i = 0; i < h; i++){
        for (int j = 0; j < w; j++){
            pixels[i * w + j] = 64;
            if (j > 0)
                scanf(" ,");
            scanf("%d",  &pixels[i * w + j]);
        }
    }

    clock_t start = clock();
    imgCvtGrayIntToDouble(h, w, pixels, output);
    clock_t end = clock();

    double totalTime = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Running time: %f seconds\n", totalTime);
    
    printf("Output:\n");
    
    for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++){
            printf("%.2f ", ((double*) output)[(i * w) + j]);
        }
        printf("\n");
	} 
    
    free(pixels);
    free(output);    
    return 0;
}
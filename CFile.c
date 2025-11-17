#include <stdio.h>

extern void imgCvtGrayIntToDouble(int h, int w, int *pixels, double *output);
int main(){
	int h, w;
	printf("Enter the height: ");
	scanf("%d", &h);
	printf ("Enter the width: ");
	scanf("%d", &w);
	
	int pixels[h][w];
    double output[h][w];
    printf("Enter the pixel values:\n");
	for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++)
			scanf("%d", &pixels[i][j]);
	}

	imgCvtGrayIntToDouble(h, w, (int*) pixels, (double*) output);
    printf("Output:\n");
    for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++)
            printf("%.2f ", ((double*) output)[(i * w) + j]);
        printf("\n");
	}
}
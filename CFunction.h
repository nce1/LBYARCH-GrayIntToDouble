#ifndef CFUNCTION_H
#define CFUNCTION_H
void imgCvtGrayIntToDoubleC(long long int totalPixels, long long int *pixels, double *output){
    for (int i = 0; i < totalPixels; i++){
        output[i] = pixels[i] / 255.0;
    }
}
#endif
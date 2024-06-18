#ifndef RGB2LAB_H
#define RGB2LAB_H

#define MAX_COLOR_SIZE 3

void lab2rgb(const double lab[MAX_COLOR_SIZE], double rgb[MAX_COLOR_SIZE]);
void rgb2lab(const double rgb[MAX_COLOR_SIZE], double lab[MAX_COLOR_SIZE]);
double deltaE(const double labA[MAX_COLOR_SIZE], const double labB[MAX_COLOR_SIZE]);

#endif // RGB2LAB_H
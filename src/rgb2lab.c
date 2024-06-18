#include <math.h>

// Assuming max size for RGB and Lab arrays is 3
#define MAX_COLOR_SIZE 3

void lab2rgb(const double lab[MAX_COLOR_SIZE], double rgb[MAX_COLOR_SIZE]) {
    double y = (lab[0] + 16) / 116,
           x = lab[1] / 500 + y,
           z = y - lab[2] / 200;

    x = 0.95047 * ((x * x * x > 0.008856) ? x * x * x : (x - 16/116) / 7.787);
    y = 1.00000 * ((y * y * y > 0.008856) ? y * y * y : (y - 16/116) / 7.787);
    z = 1.08883 * ((z * z * z > 0.008856) ? z * z * z : (z - 16/116) / 7.787);

    double r = x *  3.2406 + y * -1.5372 + z * -0.4986;
    double g = x * -0.9689 + y *  1.8758 + z *  0.0415;
    double b = x *  0.0557 + y * -0.2040 + z *  1.0570;

    r = (r > 0.0031308) ? (1.055 * pow(r, 1/2.4) - 0.055) : 12.92 * r;
    g = (g > 0.0031308) ? (1.055 * pow(g, 1/2.4) - 0.055) : 12.92 * g;
    b = (b > 0.0031308) ? (1.055 * pow(b, 1/2.4) - 0.055) : 12.92 * b;

    rgb[0] = max(0.0, min(1.0, r)) * 255;
    rgb[1] = max(0.0, min(1.0, g)) * 255;
    rgb[2] = max(0.0, min(1.0, b)) * 255;
}

void rgb2lab(const double rgb[MAX_COLOR_SIZE], double lab[MAX_COLOR_SIZE]) {
    double r = rgb[0] / 255,
           g = rgb[1] / 255,
           b = rgb[2] / 255,
           x, y, z;

    r = (r > 0.04045) ? pow((r + 0.055) / 1.055, 2.4) : r / 12.92;
    g = (g > 0.04045) ? pow((g + 0.055) / 1.055, 2.4) : g / 12.92;
    b = (b > 0.04045) ? pow((b + 0.055) / 1.055, 2.4) : b / 12.92;

    x = (r * 0.4124 + g * 0.3576 + b * 0.1805) / 0.95047;
    y = (r * 0.2126 + g * 0.7152 + b * 0.0722) / 1.00000;
    z = (r * 0.0193 + g * 0.1192 + b * 0.9505) / 1.08883;

    x = (x > 0.008856) ? pow(x, 1/3) : (7.787 * x) + 16/116;
    y = (y > 0.008856) ? pow(y, 1/3) : (7.787 * y) + 16/116;
    z = (z > 0.008856) ? pow(z, 1/3) : (7.787 * z) + 16/116;

    lab[0] = (116 * y) - 16;
    lab[1] = 500 * (x - y);
    lab[2] = 200 * (y - z);
}

double deltaE(const double labA[MAX_COLOR_SIZE], const double labB[MAX_COLOR_SIZE]) {
    double deltaL = labA[0] - labB[0];
    double deltaA = labA[1] - labB[1];
    double deltaB = labA[2] - labB[2];
    double c1 = sqrt(labA[1] * labA[1] + labA[2] * labA[2]);
    double c2 = sqrt(labB[1] * labB[1] + labB[2] * labB[2]);
    double deltaC = c1 - c2;
    double deltaH = deltaA * deltaA + deltaB * deltaB - deltaC * deltaC;
    deltaH = deltaH < 0 ? 0 : sqrt(deltaH);
    double sc = 1.0 + 0.045 * c1;
    double sh = 1.0 + 0.015 * c1;
    double deltaLKlsl = deltaL / (1.0);
    double deltaCkcsc = deltaC / (sc);
    double deltaHkhsh = deltaH / (sh);
    double i = deltaLKlsl * deltaLKlsl + deltaCkcsc * deltaCkcsc + deltaHkhsh * deltaHkhsh;
    return i < 0 ? 0 : sqrt(i);
}
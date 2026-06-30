#include "handleData.h"

/* Adjust number of float significative digits */
float round_sig(float x, int n)
{
    if (x == 0.0f) return 0.0f;

    float absx = fabsf(x);
    float scale = powf(10.0f, n - 1 - floorf(log10f(absx)));
    return roundf(x * scale) / scale;
}
#ifndef _BIQUAD_H
#define _BIQUAD_H

#include <vector>
#include "jack_client.h"

class biquad {

public:

biquad();
~biquad();

void set_coef(const std::vector<float> coeff_vector);

typedef jack_default_audio_sample_t sample_t;

void process(jack_nframes_t nframes, const sample_t * const in, sample_t *const out);

private:

// Coeficientes del filtro
double _b0;
double _b1;
double _b2;
double _a1;
double _a2;

// Guardan valores intermedios y temporales
// Utilizando metodo transpuesto
double _x1;
double _x2;
double _y1;
double _y2;

};



#endif
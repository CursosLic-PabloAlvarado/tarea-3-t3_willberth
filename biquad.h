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
float _b0;
float _b1;
float _b2;
float _a1;
float _a2;

// Guardan valores intermedios y temporales
// Utilizando metodo transpuesto
double _w1;
double _w2;

};



#endif
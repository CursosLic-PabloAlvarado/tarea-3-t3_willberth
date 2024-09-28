#ifndef _BIQUAD_H
#define _BIQUAD_H

#include <vector>
#include "jack_client.h"

class biquad {

public:

biquad();
~biquad();

void set_coef(const std::vector<float> coeff_vector);

void process(jack_nframes_t nframes, const jack::client::sample_t *const in, jack::client::sample_t *const out);

private:

// Coeficientes del filtro
float _b0;
float _b1;
float _b2;
float _a1;
float _a2;

// Guardan valores intermedios y temporales
// Utilizando metodo transpuesto
float _w1;
float _w2;

};



#endif
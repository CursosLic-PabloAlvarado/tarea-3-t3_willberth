#include "biquad.h"

biquad::biquad(){
};

biquad::~biquad(){
};

void biquad::set_coef(const std::vector<float> coeff_vector){
    // Estableciendo los valores de los coefficientes segun el vector indicado
    _b0 = coeff_vector[0];
    _b1 = coeff_vector[1];
    _b2 = coeff_vector[2];
    _a1 = coeff_vector[4];
    _a2 = coeff_vector[5];

    // Inicializando estados en 0
    _w1 = 0;
    _w2 = 0;
};

void biquad::process(jack_nframes_t nframes, 
            const sample_t *const in, 
            sample_t *const out){

    const sample_t* start_ptr = in;        //Puntero al inicio del buffer de entrada
    const sample_t* end_ptr=in+nframes;    //Puntero al final del buffer de entrada
    sample_t* out_ptr=out;                 //Puntero al inicio del buffer de salida

    while(start_ptr!=end_ptr){
        // Se realiza la implementación del filtro por medio de las ecuaciones de diferencias
        *out_ptr = ((*start_ptr) * _b0) + _w1;
        _w1 = ((*start_ptr) * _b1) - ((*out_ptr) * _a1) + _w2;
        _w2 = ((*start_ptr) * _b2) - ((*out_ptr) * _a2);

        // Se incrementan los punteros
        start_ptr++;
        out_ptr++;
    }
}; 
#include "cascade.h"
#include "biquad.h"

cascade::cascade(){
};

cascade::~cascade(){
};

void cascade::set_cascade_coef(const std::vector<std::vector<float>>& filter_coefs) {
    // Se realiza un ciclo para todos los vectores de coeficientes
    for (const auto& coefs : filter_coefs) {
        biquad filter;                          // Se genera el filtro biquad
        filter.set_coef(coefs);                 // Se utiliza el metodo de establecer coeficientes del biquad 
        _sos_filters.push_back(filter);         // Se incluye al filtro en la cadena de filtros de segundo orden
    }
}

void cascade::process(jack_nframes_t nframes, const sample_t * const in, sample_t *const out){
    // Se verifica que no haya filtros en _sos_filters
    if (_sos_filters.empty()){
        memcpy(out, in, sizeof(sample_t)*nframes);  // Si no hay filtros se procede a copiar la entrada directamente a la salida
        return;
    }

    // Se generan dos buffers temporales, para las muestras procesadas intermedias
    std::vector<sample_t> buffer_1(nframes);
    std::vector<sample_t> buffer_2(nframes);

    // Se copia en el buffer 1 los datos a los que apunta in
    memcpy(buffer_1.data(), in, sizeof(sample_t) * nframes);

    // Ciclo para encadenar la salida de un filtro con la entrada del siguiente
    for (auto& filter : _sos_filters) {
        filter.process(nframes, buffer_1.data(), buffer_2.data());  // Se procesa con el metodo de biquad utilizando buffer 1 
                                                                    // como entrada y buffer 2 como salida
        std::swap(buffer_1,buffer_2);       // Se intercambian los datos de la salida con los de la entrada
                                            // En la proxima iteración del ciclo se procesa efectivamente la salida del primer filtro como
                                            // entrada del segundo
    }

    // Se copian las muestras procesadas del buffer 1 apartir de donde apunta out
    std::copy(buffer_1.begin(), buffer_1.end(), out);

};
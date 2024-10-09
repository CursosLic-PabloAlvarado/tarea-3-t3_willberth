#include "parallel_simd_df2.h"

parallel_simd_df2::parallel_simd_df2() {
    // Inicialización de los coeficientes SIMD para las b y a (vectores de coeficientes)
    // Filtro butterworth paso banda
    b0_fx = _mm_setzero_ps();  // b0 se inicializa en cero
    // b1_fx y b2_fx contienen los coeficientes de los numeradores de las tres etapas de biquads
    b1_fx = _mm_setr_ps(-0.0195213, -0.0566642, 0.0767639, 0.0);
    b2_fx = _mm_setr_ps(0.0193573, 0.0601341, -0.0769582, 0.0);
    // a1_fx y a2_fx son los coeficientes del denominador para las mismas etapas
    a1_fx = _mm_setr_ps(-1.9792, -1.9066, -1.8992, 0.0);
    a2_fx = _mm_setr_ps(0.9801, 0.9213, 0.9028, 0.0);
    // k_x es un valor constante que se suma al resultado
    k_x = 0.0001;

    // Inicialización de los registros de retraso a cero
    w_n = _mm_setzero_ps();
    w_n_1 = _mm_setzero_ps();
    w_n_2 = _mm_setzero_ps();
    y_n = _mm_setzero_ps();
    x_n = _mm_setzero_ps();
}

parallel_simd_df2::~parallel_simd_df2() {
    // Destructor vacío (no hay recursos dinámicos que liberar)
}

void parallel_simd_df2::set_cascade_coef(const std::vector<std::vector<float> > &filter_coefs, const float k) {
    // Cada fila de `filter_coefs` representa los coeficientes de un filtro biquad
    int index = 0;
    for (const auto &coefs: filter_coefs) {
        // Cargar coeficientes en los arrays regulares
        b0_fxx[index] = coefs[0];  // Coeficiente b0
        b1_fxx[index] = coefs[1];  // Coeficiente b1
        b2_fxx[index] = coefs[2];  // Coeficiente b2
        a1_fxx[index] = coefs[4];  // Coeficiente a1
        a2_fxx[index] = coefs[5];  // Coeficiente a2

        index++;
    }
    k_x = k;  // Establecer el valor constante de k
}

void parallel_simd_df2::process(jack_nframes_t nframes, const sample_t *const in, sample_t *const out) {
    // Procesamiento de datos en paralelo usando instrucciones SIMD (AVX/AVX2)
    const sample_t *start_ptr = in; // Puntero al inicio del buffer de entrada
    const sample_t *end_ptr = in + nframes; // Puntero al final del buffer de entrada
    sample_t *out_ptr = out; // Puntero al inicio del buffer de salida

    while (start_ptr != end_ptr) {
        // Convertir el valor de entrada actual a un vector SIMD de 4 valores repetidos
        x_n = _mm_set1_ps(*start_ptr);

        // Ecuación de diferencias para y_n (la salida del biquad)
        y_n = _mm_add_ps(
            _mm_fmadd_ps(b0_fx, w_n, _mm_mul_ps(b1_fx, w_n_1)),  // b0 * w_n + b1 * w_n_1
            _mm_mul_ps(b2_fx, w_n_2)  // + b2 * w_n_2
        );

        // Actualización de los registros de estado (w_n) con la entrada x_n
        w_n = _mm_add_ps(
            _mm_fnmsub_ps(a1_fx, w_n_1, _mm_mul_ps(a2_fx, w_n_2)),  // -a1 * w_n_1 + a2 * w_n_2
            x_n  // + x_n
        );

        // Sumar horizontalmente los valores SIMD y_n para obtener un único valor final
        __m128 sum1 = _mm_hadd_ps(y_n, y_n); // Suma horizontal de pares
        __m128 sum2 = _mm_hadd_ps(sum1, sum1); // Suma de los resultados anteriores

        // Convertir el resultado SIMD en un valor escalar y sumarle k_x
        *out_ptr = _mm_cvtss_f32(sum2) + k_x;

        // Desplazar los registros de retraso
        w_n_2 = w_n_1;
        w_n_1 = w_n;

        // Avanzar los punteros de entrada y salida
        start_ptr++;
        out_ptr++;
    }
}

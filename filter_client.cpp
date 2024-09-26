/**
 * passthrough_client.cpp
 *
 * Copyright (C) 2023-2024  Pablo Alvarado
 * EL5805 Procesamiento Digital de Señales
 * Escuela de Ingeniería Electrónica
 * Tecnológico de Costa Rica
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the authors nor the names of its contributors may be
 *    used to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "filter_client.h"

#include <cstring>

filter_client::filter_client() : jack::client(),
                                    pass_on(true),
                                    client_buffer_size(1024),
                                    sample_rate(48000),
                                    sample_time(1/sample_rate),
                                    buffer_size(sample_rate * 6)

{

}

filter_client::~filter_client() = default;


jack::client_state filter_client::init() {
    jack::client_state init_state =  jack::client::init();
    set_sample_rate(sample_rate);
    set_buffer_size(client_buffer_size);
    return init_state;
}

  
/**
 * The process callback for this JACK application is called in a
 * special realtime thread once for each audio cycle.
 *
 * This client does nothing more than copy data from its input
 * port to its output port. It will exit when stopped by 
   * the user (e.g. using Ctrl-C on a unix-ish operating system)
   */
bool filter_client::process(jack_nframes_t nframes,
                                 const sample_t *const in,
                                 sample_t *const out) {
    const sample_t* startptr = in;          //Puntero al inicio del buffer de entrada
    const sample_t* endptr=in+nframes;    //Puntero al final del buffer de entrada
    sample_t* outptr=out;                 //Puntero al inicio del buffer de salida


    // Modo passthrough
    if (pass_on){
        while(startptr!=endptr){

            *outptr = *startptr * ganancia_actual;  //Multiplicar cada sample del frame por la ganancia

            cb_in.push_front(*startptr);          // Hace push en el frente del buffer de entrada

            cb_out.push_front(*outptr);           // Hace push en el frente del buffer de salida

            outptr+=1;                              //Incrementar el puntero del sample de salida
            startptr+=1;                            //Incrementar el puntero del sample de entrada
        }
    }

  return true;
}
  

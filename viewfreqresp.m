## Grupo Wilberth
## Solución de la tarea 3.
## EL5805 Procesamiento digital de señales

## matfile: Archivo .mat con los valores para el filtro
## Fs: Frecuencia de muestreo 

function viewfreqresp(matfile, Fs = 48000)

pkg load signal

# Recuperando la matriz SOS del archivo
Data = load(matfile, "SOS");

# Se combinan o transforman los sistemas de segundo orden en un solo sistema
[B A] = sos2tf(Data.SOS);

# w: Omega representa frecuencia angular 
w = linspace(2*pi/Fs, pi, 1024*4);

# z: Variable de la de función de transferencia
z = exp(1j*w);

# num - dem: Numerador y Denominador de la Funcion de transferencia evaluados
num = polyval(B,z);
den = polyval(A,z);

# Respuesta en frecuencia
H = num./den;

# Magnitud en decibeles
H_dB = 20*log10(abs(H));

# Primer plot de la magnitud en dB
subplot(2, 1, 1);
semilogx(w.*(Fs/(2*pi)),H_dB,"Linewidth",3);

# Configuración de los ejes y titulos
xlim([1 w(end)*(Fs/(2*pi))]);
ylim([-100 5]);
xlabel('Frecuencia (Hz)');
ylabel('Magnitud (dB)');
grid on;



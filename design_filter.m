## Grupo Wilberth
## Solución de la tarea 3.
## EL5805 Procesamiento digital de señales

pkg load signal

# Fs: Frecuencia de muestreo
# Order: Orden de los filtros

Fs = 48000;
Order = 3;

# Flp: Frecuencia de corte LowPass
# Fhp: Frecuencia de corte HighPass
# Flb: Frecuencia de corte inferior (BandPass - BandStop)
# Fub: Frecuencia de corte superior (BandPass - BandStop)

Flp = 440;
Fhp = 600;
Flb = 220;
Fub = 1000;

# Ripple: Rizado en banda de paso (dB)
# Atten: Atenuacion de banda de rechazo (dB)

Ripple = 1;
Atten = 50;

# B - A: Coeficientes del filtro
# SOS: Matriz de coeficientes para cascada de filtros de segundo orden

# Elliptic Filters
# Lowpass
[B,A] = ellip(Order,Ripple, Atten, Flp/(Fs/2));
SOS = tf2sos(B,A);
save("./mat-files/ellip_lp.mat", "SOS");      # Guarda el archivo en la carpeta de mat-files con el respectivo nombre

# Highpass
[B,A] = ellip(Order,Ripple, Atten, Fhp/(Fs/2), 'high');
SOS = tf2sos(B,A);
save("./mat-files/ellip_hp.mat", "SOS");

# Bandpass
[B,A] = ellip(Order,Ripple,Atten,[Flb/(Fs/2) Fub/(Fs/2)]);
SOS = tf2sos(B,A);
save("./mat-files/ellip_bp.mat", "SOS");

# BandStop
[B,A] = ellip(Order,Ripple,Atten,[Flb/(Fs/2) Fub/(Fs/2)],'stop');
SOS = tf2sos(B,A);
save("./mat-files/ellip_bs.mat", "SOS");

# Butterworth Filters
# Lowpass
[B,A] = butter(Order,Flp/(Fs/2),'low');
SOS = tf2sos(B,A)
save("./mat-files/butter_lp.mat", "SOS");


# Highpass
[B,A] = butter(Order,Flp/(Fs/2),'high');
SOS = tf2sos(B,A)
save("./mat-files/butter_hp.mat", "SOS");

# Bandpass
[B,A] = butter(Order,[Flb/(Fs/2) Fub/(Fs/2)],'bandpass');
SOS = tf2sos(B,A)
save("./mat-files/butter_bp.mat", "SOS");

# Bandstop
[B,A] = butter(Order,[Flb/(Fs/2) Fub/(Fs/2)],'stop');
SOS = tf2sos(B,A)
save("./mat-files/butter_bs.mat", "SOS");

# Chebyshev Type I
#LowPass
[B,A] = cheby1(Order, Ripple, Flp/(Fs/2), 'low');
SOS = tf2sos(B,A)
save("./mat-files/cheby1_lp.mat", "SOS");

#HighPass
[B,A] = cheby1(Order, Ripple, Flp/(Fs/2), 'low');
SOS = tf2sos(B,A)
save("./mat-files/cheby1_hp.mat", "SOS");

#BandPass
[B,A] = cheby1(Order, Ripple, [Flb/(Fs/2) Fub/(Fs/2)], 'low');
SOS = tf2sos(B,A)
save("./mat-files/cheby1_bp.mat", "SOS");

#StopBand
[B,A] = cheby1(Order, Ripple, [Flb/(Fs/2) Fub/(Fs/2)], 'low');
SOS = tf2sos(B,A)
save("./mat-files/cheby1_bs.mat", "SOS");

# Chebyshev Type II
#LowPass
[B,A] = cheby2(Order, Ripple, Flp/(Fs/2), 'low');
SOS = tf2sos(B,A)
save("./mat-files/cheby2_lp.mat", "SOS");

#HighPass
[B,A] = cheby2(Order, Ripple, Flp/(Fs/2), 'low');
SOS = tf2sos(B,A)
save("./mat-files/cheby2_hp.mat", "SOS");

#BandPass
[B,A] = cheby2(Order, Ripple, [Flb/(Fs/2) Fub/(Fs/2)], 'low');
SOS = tf2sos(B,A)
save("./mat-files/cheby2_bp.mat", "SOS");

#StopBand
[B,A] = cheby2(Order, Ripple, [Flb/(Fs/2) Fub/(Fs/2)], 'low');
SOS = tf2sos(B,A)
save("./mat-files/cheby2_bs.mat", "SOS");



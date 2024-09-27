## Grupo Wilberth
## Solución de la tarea 3.
## EL5805 Procesamiento digital de señales

## matfile: Archivo .mat con los valores para el filtro
## soundfile: Archivo .wav con el audio a probar
## Fs: Frecuencia de muestreo 

function listen_filter(matfile, soundfile, Fs = 48000)

pkg load signal

# Obteniendo las muestras del audio, y su frecuencia de muestreo
[audio sound_Fs] = audioread(soundfile);

# Si la frecuencia de muestreo del .wav es distinta a la
# Fs indicada en la función se requiere un resample del
# audio
if Fs ~= sound_Fs
    audio = resample(audio, Fs, sound_Fs);
end

# Se reproduce el audio original obtenido
sound(audio, Fs);

# Recuperando la matriz SOS del archivo
Data = load(matfile, "SOS");

# Se extraen temporalmente los valores de los coeficientes
# del numerador y denominador
B_temp = Data.SOS(:,1:3);
A_temp = Data.SOS(:,4:6);

# Se inicializan los valores del denominador y numerador final
B = [1 0 0];
A = [1 0 0];

for i = 1:size(Data.SOS, 1)
    # Se realiza la convolución del coeficiente B y B_temp
    # Esto permite obtener los coeficientes de la multiplicación de los numeradores y denominadores
    # (A + Bz + Cz²)*(D + Ez + Fz²) = (G + Hz + Iz² + Jz³ + Kz⁴)
    # conv([A B C], [D E F]) = [G H I J K]
    B = conv(B,B_temp(i,:));
    A = conv(A,A_temp(i,:));
end

# Aplicando el filtro al audio
audio_filtered = filter(B, A, audio);

# Reproduciendo el audio filtrado
sound(audio_filtered, Fs);

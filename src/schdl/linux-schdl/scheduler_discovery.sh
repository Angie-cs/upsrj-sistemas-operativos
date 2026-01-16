
# Práctica: Exploración del Scheduler Real en Linux (Ubuntu 22.04)
#
# En esta práctica se explora el scheduler real del kernel Linux, llamado Completely Fair Scheduler (CFS).

# Paso 1: Identificar dónde vive el kernel
# El código fuente del kernel Linux NO se encuentra en /home,
# sino en el directorio /usr/src

echo "[Paso 1] Contenido del directorio /usr/src"
pwd
ls /usr/src
echo

# Paso 2: Identificar el código fuente del kernel
# Ubuntu distribuye el código del kernel en un archivo comprimido llamado linux-source-6.8.0.tar.bz2

echo "[Paso 2] Código fuente del kernel Linux"
cd /usr/src || exit 1
ls
echo

# Paso 3: Localizar el scheduler real del kernel el scheduler se encuentra dentro del directorio: kernel/sched/
# El archivo fair.c implementa el Completely Fair Scheduler

echo "[Paso 3] Localizando el scheduler real (fair.c)"
tar -tjf linux-source-6.8.0.tar.bz2 | grep "kernel/sched/fair.c"
echo

# Paso 4: Mostrar el código fuente real del scheduler fair.c implementa el Completely Fair Scheduler (CFS)

echo "[Paso 4] Mostrando el código fuente del scheduler (CFS)"
echo "Archivo: kernel/sched/fair.c"
echo

tar -xOf linux-source-6.8.0.tar.bz2 linux-source-6.8.0/kernel/sched/fair.c | cat

# Análisis y relación con teoría
#
# - Linux NO implementa directamente FCFS, SJF o RR.
# - Utiliza CFS, que reparte el tiempo de CPU de manera justa.
# - Cada proceso tiene un tiempo virtual (vruntime).
# - El proceso con menor vruntime es el siguiente en ejecutarse.
#
# Relación con algoritmos vistos en clase:
# - FCFS: no es justo, un proceso largo bloquea a los demás.
# - SJF: eficiente, pero requiere conocer el tiempo de ejecución.
# - RR: reparte CPU equitativamente, pero ignora uso previo de CPU.
#
# CFS combina equidad, preempción y escalabilidad.

# Pregunta de reflexión:
#
# ¿Por qué Linux no implementa directamente FCFS, SJF o RR?
#
# Porque estos algoritmos son teóricos y no escalan bien en
# sistemas reales con múltiples CPUs, miles de procesos,
# prioridades dinámicas y necesidad de equidad.


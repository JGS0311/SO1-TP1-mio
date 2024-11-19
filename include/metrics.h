/**
 * @file metrics.h
 * @brief Funciones para obtener el uso de CPU y memoria desde el sistema de archivos /proc.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
/**
 * @brief define el tamaño del buffer
 */
#define BUFFER_SIZE 256

/**
 * @brief Obtiene el porcentaje de uso de memoria desde /proc/meminfo.
 *
 * Lee los valores de memoria total y disponible desde /proc/meminfo y calcula
 * el porcentaje de uso de memoria.
 *
 * @return Uso de memoria como porcentaje (0.0 a 100.0), o -1.0 en caso de error.
 */
double get_memory_usage();

/**
 * @brief Obtiene el porcentaje de uso de CPU desde /proc/stat.
 *
 * Lee los tiempos de CPU desde /proc/stat y calcula el porcentaje de uso de CPU
 * en un intervalo de tiempo.
 *
 * @return Uso de CPU como porcentaje (0.0 a 100.0), o -1.0 en caso de error.
 */
double get_cpu_usage();

/**
 *@brief Obtiene el porcentaje de uso del disco desde /proc/diskstats.
 *
 *Toma los sectores leidos y escritos del /proc/diskstats y calcula el porcentaje de uso en base a esos valores.
 *
 *@return Porcentaje de uso del disco (0.0 a 100.0), o -1.0 en caso de error.
 */
double get_disk_usage();

/**
*@brief Obtiene el numero de procesos activos desde /proc/loadavg.
*
*Lee el /proc/loadavg y extrae el numero de proceso activos en el sistema.
*
@return Devuelve el numero de procesos activos, o -1.0 en caso de error.
*/
double get_active_processes();

/**
 *@brief Obtiene el trafico de red desde /proc/net/dev.
 *
 *@return Trafico de red en bytes, o -1.0 en caso de error.
 */
double get_network_traffic();

/**
 *@brief Obtiene el numero de cambios de contexto desde /proc/stat.
 *
 *@return Numero de cambios de contexto, o -1.0 en caso de error.
 */
double get_context_switches();

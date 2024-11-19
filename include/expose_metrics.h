/**
 * @file expose_metrics.h
 * @brief Programa para leer el uso de CPU y memoria y exponerlos como métricas de Prometheus.
 */
#ifndef EXPOSE_METRICS_H
/**
 * @brief expose metrics
 */
#define EXPOSE_METRICS_
#include "metrics.h"
#include <errno.h>
#include <prom.h>
#include <promhttp.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // Para sleep
/**
 * @brief define el tamaño del buffer
 */
#define BUFFER_SIZE 256

/**
 * @brief Actualiza la métrica de uso de CPU.
 */
void update_cpu_gauge();

/**
 * @brief Actualiza la métrica de uso de memoria.
 */
void update_memory_gauge();

/**
 * @brief Función del hilo para exponer las métricas vía HTTP en el puerto 8000.
 * @param arg Argumento no utilizado.
 * @return NULL
 */
void* expose_metrics(void* arg);

/**
 * @brief Inicializar mutex y métricas.
 */
int init_metrics();

/**
 * @brief Destructor de mutex
 */
void destroy_mutex();

/**
 *@brief monitorea el estado de almacenamiento en un servidor.
 */
void update_disk_gauge();

/**
 *@brief monitorea los procesos activos.
 */
void update_active_processes_gauge();

/**
 *@brief monitorea la actividad de red entre diferentes puestos.
 */
void update_network_traffic_gauge();

/**
 *@brief lleva un conteo del numero de cambios de contexto.
 */
void update_context_switches_gauge();

#endif

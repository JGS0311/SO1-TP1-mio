/**
 * @file main.c
 * @brief Entry point of the system
 */
#include "expose_metrics.h"
#include <stdbool.h>
/**
 * @brief tiempo de espera para ejecutar el main
 */
#define SLEEP_TIME 1

/**
 * @brief main
 */
int main()
{

    if (init_metrics() != EXIT_SUCCESS)
    {
        fprintf(stderr, "Error al inicializar las metricas\n");
        return EXIT_FAILURE;
    }
    fprintf(stderr, "metricas inicializadas\n");

    // Creamos un hilo para exponer las métricas vía HTTP
    pthread_t tid;
    if (pthread_create(&tid, NULL, expose_metrics, NULL) != 0)
    {
        fprintf(stderr, "Error al crear el hilo del servidor para exponer metricas HTTP\n");
        return EXIT_FAILURE;
    }
    fprintf(stderr, "hilo creado con exito\n");
    // Bucle principal para actualizar las métricas cada segundo
    while (true)
    {
        update_cpu_gauge();
        update_memory_gauge();
        update_disk_gauge();
        update_active_processes_gauge();
        update_network_traffic_gauge();
        update_context_switches_gauge();

        sleep(SLEEP_TIME);
    }
    fprintf(stderr, "  FIN\n");
    return 0;
}

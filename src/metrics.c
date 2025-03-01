#include "metrics.h"

double get_memory_usage()
{
    FILE* fp;
    char buffer[BUFFER_SIZE];
    unsigned long long total_mem = 0, free_mem = 0;

    // Abrir el archivo /proc/meminfo
    fp = fopen("/proc/meminfo", "r");
    if (fp == NULL)
    {
        perror("Error al abrir /proc/meminfo");
        return -1.0;
    }

    // Leer los valores de memoria total y disponible
    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        if (sscanf(buffer, "MemTotal: %llu kB", &total_mem) == 1)
        {
            continue; // MemTotal encontrado
        }
        if (sscanf(buffer, "MemAvailable: %llu kB", &free_mem) == 1)
        {
            break; // MemAvailable encontrado, podemos dejar de leer
        }
    }

    fclose(fp);

    // Verificar si se encontraron ambos valores
    if (total_mem == 0 || free_mem == 0)
    {
        fprintf(stderr, "Error al leer la información de memoria desde /proc/meminfo\n");
        return -1.0;
    }

    // Calcular el porcentaje de uso de memoria
    double used_mem = total_mem - free_mem;
    double mem_usage_percent = (used_mem / total_mem) * 100.0;

    return mem_usage_percent;
}

double get_cpu_usage()
{
    static unsigned long long prev_user = 0, prev_nice = 0, prev_system = 0, prev_idle = 0, prev_iowait = 0,
                              prev_irq = 0, prev_softirq = 0, prev_steal = 0;
    unsigned long long user, nice, system, idle, iowait, irq, softirq, steal;
    unsigned long long totald, idled;
    double cpu_usage_percent;

    // Abrir el archivo /proc/stat
    FILE* fp = fopen("/proc/stat", "r");
    if (fp == NULL)
    {
        perror("Error al abrir /proc/stat");
        return -1.0;
    }

    char buffer[BUFFER_SIZE * 4];
    if (fgets(buffer, sizeof(buffer), fp) == NULL)
    {
        perror("Error al leer /proc/stat");
        fclose(fp);
        return -1.0;
    }
    fclose(fp);

    // Analizar los valores de tiempo de CPU
    int ret = sscanf(buffer, "cpu  %llu %llu %llu %llu %llu %llu %llu %llu", &user, &nice, &system, &idle, &iowait,
                     &irq, &softirq, &steal);
    if (ret < 8)
    {
        fprintf(stderr, "Error al parsear /proc/stat\n");
        return -1.0;
    }

    // Calcular las diferencias entre las lecturas actuales y anteriores
    unsigned long long prev_idle_total = prev_idle + prev_iowait;
    unsigned long long idle_total = idle + iowait;

    unsigned long long prev_non_idle = prev_user + prev_nice + prev_system + prev_irq + prev_softirq + prev_steal;
    unsigned long long non_idle = user + nice + system + irq + softirq + steal;

    unsigned long long prev_total = prev_idle_total + prev_non_idle;
    unsigned long long total = idle_total + non_idle;

    totald = total - prev_total;
    idled = idle_total - prev_idle_total;

    if (totald == 0)
    {
        fprintf(stderr, "Totald es cero, no se puede calcular el uso de CPU!\n");
        return -1.0;
    }

    // Calcular el porcentaje de uso de CPU
    cpu_usage_percent = ((double)(totald - idled) / totald) * 100.0;

    // Actualizar los valores anteriores para la siguiente lectura
    prev_user = user;
    prev_nice = nice;
    prev_system = system;
    prev_idle = idle;
    prev_iowait = iowait;
    prev_irq = irq;
    prev_softirq = softirq;
    prev_steal = steal;

    return cpu_usage_percent;
}

double get_disk_usage()
{
    FILE* fp;
    char buffer[BUFFER_SIZE];
    unsigned long long read_sectors = 0, write_sectors = 0;

    fp = fopen("/proc/diskstats", "r");
    if (fp == NULL)
    {
        perror("Error al abrir /proc/diskstats");
        return -1.0;
    }

    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        if (sscanf(buffer, " 8 0 %*s %*s %llu %*s %*s %llu", &read_sectors, &write_sectors) == 2)
        {
            break;
        }
    }

    fclose(fp);

    double disk_usage_percent =
        ((double)(read_sectors + write_sectors) / (read_sectors + write_sectors + 1000000)) * 100.0;
    return disk_usage_percent;
}

double get_active_processes()
{
    FILE* fp;
    char buffer[BUFFER_SIZE];
    double active_processes;

    fp = fopen("/proc/loadavg", "r");
    if (fp == NULL)
    {
        perror("Error al abrir /proc/loadavg");
        return -1.0;
    }

    if (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        sscanf(buffer, "%*s %*s %*s %*s %lf", &active_processes);
    }

    fclose(fp);
    return active_processes;
}

double get_network_traffic()
{
    FILE* fp;
    char buffer[BUFFER_SIZE];
    unsigned long long received = 0, transmitted = 0;

    fp = fopen("/proc/net/dev", "r");
    if (fp == NULL)
    {
        perror("Error al abrir /proc/net/dev");
        return -1.0;
    }

    // Saltar las dos primeras líneas que no contienen datos útiles
    fgets(buffer, sizeof(buffer), fp);
    fgets(buffer, sizeof(buffer), fp);

    // Leer el tráfico de red
    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        char interface[16]; // Para almacenar el nombre de la interfaz
        sscanf(buffer, "%15s %llu %*u %*u %*u %*u %*u %*u %llu", interface, &received, &transmitted);
        // Puedes acumular los valores de tráfico aquí si es necesario
    }

    fclose(fp);
    // Devuelve el tráfico total en bytes (puedes modificarlo según tus necesidades)
    return received + transmitted;
}

double get_context_switches()
{
    FILE* fp;
    char buffer[BUFFER_SIZE];
    unsigned long long context_switches = 0;

    fp = fopen("/proc/stat", "r");
    if (fp == NULL)
    {
        perror("Error al abrir /proc/stat");
        return -1.0;
    }

    // Leer el archivo y buscar el valor de cambios de contexto
    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        if (sscanf(buffer, "ctxt %llu", &context_switches) == 1)
        {
            break; // Cambios de contexto encontrados
        }
    }

    fclose(fp);
    return context_switches;
}

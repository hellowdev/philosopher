#include "philo.h"

typedef struct s_threads
{
    pthread_mutex_t *mute;
    pthread_t       thread;
}   t_share;

typedef struct s_ar
{
    t_share threads;
    int i;
}   t_arg;



void    *thread_func(void *j)
{
    t_arg *data;
    data = (t_arg *)j;
    int f = 0;
    printf("her\n");
    while (f < 50000)
    {
        pthread_mutex_lock(data->threads.mute);
        f++;
        data->i++;
        pthread_mutex_unlock(data->threads.mute);
    }
    return (NULL);
}

int main()
{
    t_arg   data;
    data.threads.mute = malloc(1 * sizeof(pthread_mutex_t));
    data.i = 0;

    pthread_mutex_init(data.threads.mute, NULL);
    pthread_create(&data.threads.thread, NULL, thread_func, &data);
    pthread_join(data.threads.thread, NULL);
   

    printf("%d\n", data.i);
}
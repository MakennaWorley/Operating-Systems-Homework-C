/**
 * Simple program that generates 10 random numbers
 * between -1.0 and +1.0
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <pthread.h>

#define N 4

long long total_points;
long long points_in_circle = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* monte_carlo_pi(void* arg) {
    long long local_points = total_points / N;
    long long local_in_circle = 0;

    for (long long i = 0; i < local_points; i++) {
        double x = (rand() / (double)RAND_MAX) * 2.0 - 1.0;
        double y = (rand() / (double)RAND_MAX) * 2.0 - 1.0;

        if (x * x + y * y <= 1.0) {
            local_in_circle++;
        }
    }

    pthread_mutex_lock(&mutex);
    points_in_circle += local_in_circle;
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <number_of_points>\n", argv[0]);
        return 1;
    }

    total_points = atoll(argv[1]);

    if (total_points <= 0) {
        printf("Error: Number of points must be a positive integer.\n");
        return 1;
    }

    // seed the random number generator
    srandom((unsigned)time(NULL));

    pthread_t threads[N];

    for (int i = 0; i < N; i++) {
        pthread_create(&threads[i], NULL, monte_carlo_pi, NULL);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);

    double pi_estimate = 4.0 * points_in_circle / total_points;
    printf("Estimated π: %f\n", pi_estimate);

    return 0;
}

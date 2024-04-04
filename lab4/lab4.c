#include <windows.h>
#include <stdio.h>
#include <time.h>

#define THREADS_NUM 10
#define ARRAY_SIZE 1e8


struct parameters {
	int* array;
	int start;
	int end;
};

DWORD WINAPI ThreadRoutine(void* param)
{
	struct parameters* p = (struct parameters*)param;
   for(int i = p->start; i < p->end; i++) {
        p->array[i] += 1;
    }
    free(param);
    return 0;
}

int main()
{
    double times[THREADS_NUM];
    for(int k = 1; k < THREADS_NUM; k++)
    {
        HANDLE hHandles[THREADS_NUM];
        DWORD ThreadId;

        int* array = (int*)calloc(ARRAY_SIZE, sizeof(int));
        array[0] = 1; // 0! = 1

        clock_t start = clock();
        for (int i=0; i < k ;i++) {
            struct parameters* p = (struct parameters*)malloc(sizeof(struct parameters));
            if (p == NULL) {
                fprintf(stderr, "Could not allocate memory for parameters\n");
                exit(1);
            }
            p->array = array;
            p->start = ARRAY_SIZE / k * i;
            p->end = ARRAY_SIZE / k * (i + 1);
            hHandles[i] = CreateThread(NULL,0,ThreadRoutine,p,0,&ThreadId);
            if (hHandles[i] == NULL) {
                fprintf(stderr,"Could not create Thread\n");
                exit(0);
            }
            //else printf("Thread %d was created\n",ThreadId);
        }
        for (int i=0 ;i < k; i++) {
            WaitForSingleObject(hHandles[i],INFINITE);
        }
        clock_t end = clock();
        double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

        // for(int i = 0; i < ARRAY_SIZE; i++) {
        //     printf("%d = %d\n", i, array[i]);
        // }

        free(array);
        times[k] = time_spent;
    }
    for(int i = 1; i < THREADS_NUM; i++)
    {
        printf("Time spent for %d threads: %f\n", i+1, times[i]);
    }
   // printf("Time spent: %f\n", time_spent);
    return 0;

}
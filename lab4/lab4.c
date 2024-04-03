#include <windows.h>
#include <stdio.h>
#include <time.h>

#define THREADS_NUM 5
#define ARRAY_SIZE 10000000


struct parameters {
	int* array;
	int start;
	int end;
};

DWORD WINAPI ThreadRoutine(void* param)
{
	struct parameters* p = (struct parameters*)param;
   for(int i = p->start; i < p->end; i++) {
        p->array[i] = p->array[i-1] * i + 1;
    }
    return 0;
}

int main()
{
    HANDLE hHandles[10];
    DWORD ThreadId;

    int* array = (int*)calloc(ARRAY_SIZE * sizeof(int), sizeof(int));
	array[0] = 1; // 0! = 1

    clock_t start = clock();
    for (int i=0; i < THREADS_NUM ;i++) {
        struct parameters p;
        p.array = array;
        p.start = ARRAY_SIZE / THREADS_NUM * i;
        p.end = ARRAY_SIZE / THREADS_NUM * (i + 1);
        hHandles[i] = CreateThread(NULL,0,ThreadRoutine,&p,0,&ThreadId);
        if (hHandles[i] == NULL) {
            fprintf(stderr,"Could not create Thread\n");
            exit(0);
        }
        else printf("Thread %d was created\n",ThreadId);
    }
    for (int i=0;i < 5;i++) {
        WaitForSingleObject(hHandles[i],INFINITE);
    }
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;


    free(array);
    printf("Time spent: %f\n", time_spent);
    return 0;

}
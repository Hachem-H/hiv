#pragma once

#include <stdint.h>
#include <stdlib.h>

#ifdef _WIN32
    #include <windows.h>
    #include <synchapi.h>
#else
    #include <pthread.h>
    #include <unistd.h>
#endif

typedef struct hiv_Thread_t
{
#ifdef _WIN32
    HANDLE native;
    DWORD id;
#else
    pthread_t native;
#endif
} hiv_Thread;

static hiv_Thread* hiv_CreateThread(void(*callback)(void*), void* args)
{
    hiv_Thread thread = (hiv_Thread) malloc(sizeof(hiv_Thread));
    {
        #ifdef _WIN32
            thread->native = CreateThread(0, 0, callback, args, 0, &thread->id);
        #else
            pthread_create(&thread->native, NULL, callback, args);
        #endif
    }

    return thread;
}

static void hiv_JoinThread(hiv_Thread* thread)
{
    #ifdef _WIN32
        WaitForSingleObject(thread->native, INFINITE);
    #else
        pthread_join(thread->native), NULL;
    #endif
}

static void hiv_Sleep(uint32_t seconds)
{
    #ifdef _WIN32
        Sleep(seconds * 1000);
    #else
        sleep(seconds);
    #endif
}

static void hiv_CloseThread(hiv_Thread* thread)
{
    #ifdef _WIN32
        CloseHandle(thread->native);
    #else
        pthread_detach(thread->native);
    #endif
    
    free(thread);
}

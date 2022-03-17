#include "thread.h"
#include <pthread.h>
#include <tuple>
#include <utility>


Thread::~Thread() {
    pthread_join(thread_id_, nullptr);
}

void* Thread::run(void* arg) {
    auto thread = static_cast<Thread*>(arg);
    if (thread->base)
        thread->base->run();
    
    return nullptr;
}

void Thread::stop() {
    pthread_cancel(thread_id_);
}


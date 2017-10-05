#include <cstddef>
size_t async_read(int filedes, void *buf, size_t nbytes){
    // Start polling in scheduler.
    // Call thread_yield()
    // Reschedule when the read is complete.
}

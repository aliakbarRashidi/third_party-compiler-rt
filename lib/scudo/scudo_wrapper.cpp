#include "scudo/scudo_allocator.h"

#include <string.h>

using namespace __scudo;

extern "C" {

const char *__default_options() {
  return "allocator_may_return_null=true " // sanitizer_common options
         "log_to_syslog=true "
         // "allocator_release_to_os_interval_ms=5000 "
         "abort_on_error=true "
         "QuarantineSizeKb=0 "             // scudo options
         "ThreadLocalQuarantineSizeKb=0 "
         "ZeroContents=false "
         "DeallocationTypeMismatch=false "
         "DeleteSizeMismatch=false ";
}

void* calloc(size_t nmemb, size_t size) {
  return scudoCalloc(nmemb, size);
}
void free(void* ptr) {
  scudoFree(ptr, FromMalloc);
}
/*struct mallinfo mallinfo() {
  struct mallinfo res;
  memset(&res, 0, sizeof(res));
  return res;
}*/
void *malloc(size_t size) {
  return scudoMalloc(size, FromMalloc);
}
size_t malloc_usable_size(const void* ptr) {
  return scudoMallocUsableSize(const_cast<void*>(ptr));
}
void *memalign(size_t alignment, size_t size) {
  return scudoMemalign(alignment, size);
}
int posix_memalign(void** memptr, size_t alignment, size_t size) {
  return scudoPosixMemalign(memptr, alignment, size);
}
void* realloc(void* ptr, size_t size) {
  return scudoRealloc(ptr, size);
}
void *pvalloc(size_t size) {
  return scudoPvalloc(size);
}
void *valloc(size_t size) {
  return scudoValloc(size);
}
void *aligned_alloc(size_t alignment, size_t size) {
  return scudoAlignedAlloc(alignment, size);
}
/*int iterate(uintptr_t, size_t, void (*)(uintptr_t, size_t, void*), void*) {
  return 0;
}*/
void malloc_disable() {
}
void malloc_enable() {
}
int mallopt(int param, int value) {
  return 0;
}
int mallctl(const char *name, void *oldp, size_t *oldlenp, void *newp, size_t newlen) {
  return 0;
}
void* memalign_round_up_boundary(size_t boundary, size_t size) {
  if (boundary != 0) {
    if (!IsPowerOfTwo(boundary))
      boundary = RoundUpToPowerOfTwo(boundary);
  } else
    boundary = 1;
  return scudoMemalign(boundary, size);
}

}


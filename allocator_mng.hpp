#pragma once
#define  typename template<typename T>
#include <iostream>
#include <stdlib.h>
#include <sys/mman.h>
using namespace std;

// Allocator wrapper's namespace
namespace alloc {
namespace linux {
  typename int smart_mlock(T *&pptr, const size_t size) {
    return mlock((T*)pptr, size);
  }
  typename int smart_munlock(T* &pptr, const size_t size) {
    return munlock((T*)pptr, size);
  }
  typename T* smart_mremap(T* old, const size_t old_size, const size_t new_size, int flags) {
    return (T*)mremap(old, old_size, new_size, flags);
  }
  
} // namespace linux
/* Очищает память и убирает эффект "висячего" указателя */
typename void _free(T *&pptr) {
  free(pptr);
  pptr = nullptr;
}
/*
 * Аллоцирует память по размеру типа + некоторый запас
 * @param add Запас
 */
typename T *smart_alloc(const int add = 0) {
  return (T *)malloc(sizeof(T) + add);
}
/*
 * Тоже самое что и malloc, только забивает нулями
 * @param number кол-во блоков
 * @param add Запас памяти
 */
typename T *smart_calloc(const int number,  int add = 0) {
  return (T *)calloc(number, sizeof(T) + add);
}

/*
 * Алоцирует память, выровненую по alignement размером типа + add
 */
typename T *smart_alignedalloc(const size_t alignement, size_t add = 0) {
  return (T *)aligned_alloc(alignement, sizeof(T) + add);
}

typename T *smart_realloc(T *pointer, size_t new_size = 0) {
  return (T *)realloc(pointer, new_size);
}
} // namespace alloc
#pragma once
#include <iostream>
#include <memory>
#include <stdlib.h>
#include <sys/mman.h>
using namespace std;

// Allocator wrapper's namespace
namespace alloc {
namespace linux_func {
template <typename T> int smart_mlock(T *&pptr, const size_t size) {
    return mlock((T*)pptr, size);
  }
template <typename T> int smart_munlock(T* &pptr, const size_t size) {
    return munlock((T*)pptr, size);
  }
template <typename T> T* smart_mremap(T* old, const size_t old_size, const size_t new_size, int flags) {
    return (T*)mremap(old, old_size, new_size, flags);
  }
  
} // namespace linux
template <typename T>
T* smart_align(std::size_t alignment, std::size_t size, T*& ptr, std::size_t& space) {
  return (T*)align(align, size, ptr, space);
}
/* Очищает память и убирает эффект "висячего" указателя */
template <typename T> void _free(T *&pptr) {
  free(pptr);
  pptr = nullptr;
}
/*
 * Аллоцирует память по размеру типа + некоторый запас
 * @param add Запас
 */
template <typename T> T *smart_alloc( int add = 0) {
  return (T *)malloc(sizeof(T) + add);
}
template <typename T> T *smart_alloc_manual(const size_t size,  int add = 0) {
  return (T *)malloc(size + add);
}
/*
 * Тоже самое что и malloc, только забивает нулями
 * @param number кол-во блоков
 * @param add Запас памяти
 */
template <typename T> T *smart_calloc(const int number,  int add = 0) {
  return (T *)calloc(number, sizeof(T) + add);
}

/*
 * Алоцирует память, выровненую по alignement размером типа + add
 */
template <typename T> T *smart_alignedalloc(const size_t alignement, size_t add = 0) {
  return (T *)aligned_alloc(alignement, sizeof(T) + add);
}

template <typename T> T *smart_realloc(T *pointer, size_t new_size = 0) {
  return (T *)realloc(pointer, new_size);
}
} // namespace alloc
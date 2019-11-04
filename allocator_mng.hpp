#pragma once
#define  typename template<typename T>
#include <iostream>
#include <stdlib.h>
using namespace std;

// Allocator wrapper's namespace
namespace alloc {
/* Очищает память и убирает эффект "висячего" указателя */
typename void _free(T *&pptr) {
  free(pptr);
  pptr = nullptr;
}
/*
 * Аллоцирует память по размеру типа + некоторый запас
 * @param add Запас
 */
typename T *smart_alloc(int add = 0) {
  return (T *)malloc(sizeof(T) + add);
}
/*
 * Тоже самое что и malloc, только забивает нулями
 * @param number кол-во блоков
 * @param add Запас памяти
 */
typename T *smart_calloc(int number = 0, int add = 0) {
  return (T *)calloc(number, sizeof(T) + add);
}

/*
 * Алоцирует память, выровненую по alignement размером типа + add
 */
typename T *smart_alignedalloc(size_t alignement, size_t add = 0) {
  return (T *)aligned_alloc(alignement, sizeof(T) + add);
}

typename T *smart_realloc(T *pointer, size_t new_size = 0) {
  return (T *)realloc(pointer, new_size);
}
} // namespace alloc
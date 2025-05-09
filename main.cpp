#include "larrow/base/alloc.h"
#include "larrow/base/storage.h"
#include <cstddef>
#include <iostream>

int main() {
  auto& a = base::CPUAllocator::instance();
  void* ptr = a.allocate(1024);
  a.release(ptr);

  base::Storage storage(1024); 
}
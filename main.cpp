#include "larrow/base/alloc.h"
#include "larrow/base/storage.h"
#include <cstddef>
#include <iostream>
#include <memory>
#include <vector>

int main() {
  std::shared_ptr<base::Storage> storage2 = base::Storage::create(2048);

  std::shared_ptr<base::Storage> storage_ptr = base::Storage::create(1024);
  std::cout << "change dierection." << std::endl;
  storage_ptr = storage2->shared_ptr();
  std::cout << "change end." << std::endl;
}
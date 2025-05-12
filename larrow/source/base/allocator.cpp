#include "larrow/base/allocator.h"
#include "larrow/base/device_type.h"
#include "larrow/utils/debug.h"
#include <cstddef>
#include <cstdlib>
#include <malloc.h>
#include <sched.h>

namespace base {
CPUAllocator &CPUAllocator::instance() {
  static CPUAllocator inst{};
  return inst;
}

void *CPUAllocator::allocate(size_t size) const {
  LOG_FUNC();

  if (size == 0) {
    return nullptr;
  }

  size_t adjusted_size = (size + ALIGNMENT - 1) & ~(ALIGNMENT - 1);

#ifdef _WIN32
  void *ptr = _aligned_malloc(adjusted_size, ALIGNMENT);
#else
  void *ptr = std::aligned_alloc(ALIGNMENT, adjusted_size);
#endif

  return ptr;
}

void CPUAllocator::release(void *ptr) const {
  LOG_FUNC();

  if (ptr) {
#ifdef _WIN32
    _aligned_free(ptr);
#else
    std::free(ptr);
#endif
  }
}

DeviceType CPUAllocator::getDeviceType() const { return DeviceType::CPU; }
} // namespace base
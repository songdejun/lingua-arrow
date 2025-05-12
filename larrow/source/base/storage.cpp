#include "larrow/base/storage.h"
#include "larrow/base/alloc.h"
#include "larrow/base/device_type.h"
#include <cstring>
#include <memory>
#include <shared_mutex>

namespace base {
Storage::~Storage() {
  if (ptr_) {
    allocator_.release(ptr_);
  }
}
#
std::shared_ptr<Storage> Storage::create() {
  return std::shared_ptr<Storage>(new Storage(), [](Storage *p) { delete p; });
}

std::shared_ptr<Storage> Storage::create(size_t size,
                                         DeviceAllocator &allocator) {
  return std::shared_ptr<Storage>(new Storage(size, allocator),
                                  [](Storage *p) { delete p; });
}

Storage::Storage(size_t size, DeviceAllocator &allocator)
    : size_(size), allocator_(allocator) {
  device_type_ = allocator_.getDeviceType();
  ptr_ = allocator_.allocate(size_);
}

// 不应该由storage层实现深拷贝
// void Storage::deep_copy(const Storage &src) {
//   // storage只会处于已分配和空白初始化状态
//   // 对于已分配状态释放分配的内存
//   if (ptr_) {
//     allocator_.release(ptr_);
//   }

//   size_ = src.size_;
//   device_type_ = src.allocator_.getDeviceType();
//   allocator_ = src.allocator_;
//   ptr_ = src.ptr_;
// }

void Storage::copy(const Storage &src) {
  // 如果已分配的内存小于src分配的内存大小,则重新分配内存
  if (size_ < src.size_) {
    // 分配但内存小和未分配状态都有可能进入if
    // 对于已分配状态释放分配的内存
    if (ptr_) {
      allocator_.release(ptr_);
    }
    ptr_ = allocator_.allocate(src.size_);
  }

  // else use dest_mem[0:src_mem.size] to copy data.
  size_ = src.size_;

  if (this->device_type_ == DeviceType::CPU &&
      src.device_type_ == DeviceType::CPU) {
    std::memcpy(ptr_, src.ptr_, size_);
  }
}

void *Storage::ptr() { return ptr_; }
const void *Storage::ptr() const { return ptr_; }
size_t Storage::size() const { return size_; }
DeviceAllocator &Storage::allocator() const { return allocator_; }
DeviceType Storage::device_type() const { return device_type_; }
// // void setDeviceType(DeviceType device_type);
std::shared_ptr<Storage> Storage::shared_ptr() { return shared_from_this(); }

} // namespace base
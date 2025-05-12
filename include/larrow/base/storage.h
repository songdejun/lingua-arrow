#pragma once

#include "larrow/base/allocator.h"
#include "larrow/base/device_type.h"
#include "larrow/utils/noncopyable.h"
#include <cstddef>
#include <memory>

namespace base {
class Storage : public utils::NonCopyabale,
                public std::enable_shared_from_this<Storage> {
public:
  static std::shared_ptr<Storage> create();
  static std::shared_ptr<Storage>
  create(size_t size, DeviceAllocator &allocator = CPUAllocator::instance());
  virtual ~Storage();

  // bool allocate();
  // void deep_copy(const Storage &src);
  void copy(const Storage &src);
  void *ptr();
  const void *ptr() const;
  size_t size() const;
  DeviceAllocator &allocator() const;
  DeviceType device_type() const;
  // void setDeviceType(DeviceType device_type);
  std::shared_ptr<Storage> shared_ptr();

private:
  explicit Storage() = default;
  explicit Storage(size_t size,
                   DeviceAllocator &allocator = CPUAllocator::instance());
  size_t size_ = 0;
  DeviceType device_type_ = DeviceType::CPU;
  DeviceAllocator &allocator_ = CPUAllocator::instance();
  void *ptr_ = nullptr;
};
} // namespace base
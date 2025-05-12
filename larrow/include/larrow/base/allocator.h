#pragma once
#include "larrow/base/device_type.h"
#include <memory>

namespace base {
constexpr size_t ALIGNMENT = 32;

class DeviceAllocator {
public:
  virtual void release(void *ptr) const = 0;
  virtual void *allocate(size_t size) const = 0;
  virtual DeviceType getDeviceType() const = 0;

protected:
  DeviceAllocator() = default;
  virtual ~DeviceAllocator() = default;
};

class CPUAllocator final : public DeviceAllocator {
public:
  static constexpr DeviceType device_type_ = DeviceType::CPU;

  void release(void *ptr) const override;
  void *allocate(size_t size) const override;
  DeviceType getDeviceType() const override;

  static CPUAllocator &instance();

  ~CPUAllocator() = default;
  CPUAllocator(const CPUAllocator &) = delete;
  CPUAllocator &operator=(const CPUAllocator &) = delete;

private:
  CPUAllocator() = default;
};


} // namespace base
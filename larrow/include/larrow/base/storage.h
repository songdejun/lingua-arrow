#include "larrow/base/alloc.h"
#include "larrow/base/device_type.h"
#include "larrow/utils/noncopyable.h"
#include <cstddef>
#include <memory>

namespace base {
class Storage : public utils::NonCopyabale,
                std::enable_shared_from_this<Storage> {
public:
  explicit Storage() = default;
  explicit Storage(size_t size,
                   DeviceAllocator &allocator = CPUAllocator::instance());
  virtual ~Storage();

  // bool allocate();
  void deep_copy(const Storage &src);
  void copy(const Storage &src);
  void *ptr();
  const void *ptr() const;
  size_t size() const;
  DeviceAllocator& allocator() const;
  DeviceType device_type() const;
  DeviceType device_type();
  // void setDeviceType(DeviceType device_type);
  std::shared_ptr<Storage> shared_ptr();

private:
  size_t size_ = 0;
  DeviceType device_type_ = DeviceType::CPU;
  DeviceAllocator& allocator_ = CPUAllocator::instance();
  void *ptr_ = nullptr;
};
} // namespace base
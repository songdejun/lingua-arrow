#pragma once

#include "larrow/base/allocator.h"
#include "larrow/base/storage.h"
#include "memory"
#include "vector"
#include <cstddef>
#include <exception>
#include <future>
#include <memory>
#include <vector>

namespace base {
enum class DataType {
  fp32,
  int8,
  int32,
};
}

namespace tensor {
/*
 * States of a tensor:
 * 1. A tensor with no storage allocated. i.e. a tensor with an allocated
 * storage on CPU for size of 0.
 * 2. A tensor with an allocated storage on CPU for size of @size_.
 * 3. A tensor with an allocated storage on CUDA for size of @size_.
 */
class Tensor {
public:
  Tensor() = default;
  Tensor(base::DataType data_type, std::vector<size_t> dims,
         base::DeviceAllocator &allocator);
  // tensor& to_cpu();
  // tensor& to_cuda();
  bool empty() const;
  template <typename T> T *ptr();
  template <typename T> const T *ptr() const;
  Tensor &reshape(std::vector<size_t> dims);
  std::shared_ptr<base::Storage> storage() const;
  size_t size() const;
  std::vector<size_t> dims() const;
  std::vector<size_t> strides() const;
  base::DataType date_type() const;
  void reset(base::DataType data_type, std::vector<size_t> dims,
             base::DeviceAllocator &allocator);
  void reset(base::DataType data_type, std::vector<size_t> dims);

private:
  size_t dim2size(std::vector<size_t> dims) const;
  base::DataType data_type_ = base::DataType::fp32;
  size_t size_ = 0;
  std::vector<size_t> dims_ = {0};
  std::vector<size_t> strides_ = {1};
  std::shared_ptr<base::Storage> storage_ = {};
};
} // namespace tensor
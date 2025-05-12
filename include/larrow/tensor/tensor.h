#pragma once

#include "larrow/base/allocator.h"
#include "larrow/base/storage.h"
#include "larrow/base/data_type.h"
#include "memory"
#include "vector"
#include <cstddef>
#include <exception>
#include <future>
#include <memory>
#include <vector>

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
  Tensor(std::vector<size_t> dims,
         base::DataType data_type = base::DataType::fp32,
         base::DeviceAllocator &allocator = base::CPUAllocator::instance());
  // tensor& to_cpu();
  // tensor& to_cuda();
  bool empty() const;
  Tensor &reshape(std::vector<size_t> dims);
  std::shared_ptr<base::Storage> storage() const;
  size_t num() const;
  std::vector<size_t> dims() const;
  std::vector<size_t> strides() const;
  std::vector<size_t> strides(std::vector<size_t> dims) const;
  base::DataType date_type() const;
  void reset(base::DataType data_type, std::vector<size_t> dims,
             base::DeviceAllocator &allocator);
  void reset(base::DataType data_type, std::vector<size_t> dims);
  Tensor& permute(std::vector<size_t> axis_orders);
  template <typename T> T &index(size_t offset);
  template <typename T> const T &index(size_t offset) const;
  template <typename T> T *ptr();
  template <typename T> const T *ptr() const;
  template <typename T> T *ptr(size_t offset);
  template <typename T> const T *ptr(size_t offset) const;

private:
  size_t dim2num(std::vector<size_t> dims) const;
  base::DataType data_type_ = base::DataType::fp32;
  size_t num_ = 0;
  std::vector<size_t> dims_ = {0};
  std::vector<size_t> strides_ = {1};
  std::shared_ptr<base::Storage> storage_ = {};
};
} // namespace tensor
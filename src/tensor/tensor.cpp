#include "larrow/tensor/tensor.h"
#include "larrow/base/allocator.h"
#include "larrow/base/data_type.h"
#include "larrow/base/storage.h"
#include <algorithm>
#include <cstddef>
#include <exception>
#include <numeric>
#include <stdexcept>
#include <vector>

namespace tensor {
Tensor::Tensor(std::vector<size_t> dims, base::DataType data_type,
               base::DeviceAllocator &allocator)
    : data_type_(data_type), dims_(dims) {
  num_ = dim2num(dims_);
  storage_ =
      base::Storage::create(num() * base::size_of(data_type_), allocator);
}

size_t Tensor::dim2num(std::vector<size_t> dims) const {
  return std::accumulate(dims.begin(), dims.end(), 1,
                         std::multiplies<size_t>());
}

bool Tensor::empty() const { return num_ == 0; }

std::vector<size_t> Tensor::strides(std::vector<size_t> dims) const {
  std::vector<size_t> strides = std::vector<size_t>(dims.size());
  size_t suffix_product = 1;
  for (int i = dims.size() - 1; i >= 0; i--) {
    strides[i] = suffix_product;
    suffix_product *= dims[i];
  }
  return strides;
}

Tensor &Tensor::reshape(std::vector<size_t> dims) {
  size_t new_num = dim2num(dims);
  if (new_num != num_) {
    throw std::invalid_argument("Error: New dimensions are not compatible with "
                                "the number of elements in the tensor.");
  }

  dims_ = dims;

  strides_ = strides(dims_);

  return *this;
}

std::shared_ptr<base::Storage> Tensor::storage() const {
  return storage_->shared_ptr();
}

size_t Tensor::num() const { return num_; }

std::vector<size_t> Tensor::dims() const { return dims_; }

std::vector<size_t> Tensor::strides() const { return strides_; }

base::DataType Tensor::date_type() const { return data_type_; }

void Tensor::reset(base::DataType data_type, std::vector<size_t> dims,
                   base::DeviceAllocator &allocator) {
  dims_ = dims;
  num_ = dim2num(dims_);
  strides_ = strides(dims_);
  storage_ = base::Storage::create(num_, allocator);
}

void Tensor::reset(base::DataType data_type, std::vector<size_t> dims) {
  base::DeviceAllocator &allocator = storage_->allocator();
  reset(data_type, dims, allocator);
}

template <typename T> T &Tensor::index(size_t offset) {
  if (num_ == 0) {
    throw std::runtime_error(
        "Error: This tensor hasn't been allocated storage.");
  }

  if (offset > num_ - 1) {
    throw std::range_error("Error: Offset exceeds the num of tensor.");
  }

  T &val = *(static_cast<T *>(storage_->ptr()) + offset);
  return val;
}

template <typename T> const T &Tensor::index(size_t offset) const {
  if (num_ == 0) {
    throw std::runtime_error(
        "Error: This tensor hasn't been allocated storage.");
  }

  if (offset > num_ - 1) {
    throw std::range_error("Error: Offset exceeds the num of tensor.");
  }

  const T &val = *(static_cast<T *>(storage_->ptr()) + offset);
  return val;
}

template <typename T> T *Tensor::ptr() {
  if (num_ == 0) {
    throw std::runtime_error(
        "Error: This tensor hasn't been allocated storage.");
  }
  return storage_->ptr();
}

template <typename T> const T *Tensor::ptr() const {
  if (num_ == 0) {
    throw std::runtime_error(
        "Error: This tensor hasn't been allocated storage.");
  }
  return storage_->ptr();
}

template <typename T> T *Tensor::ptr(size_t offset) {
  if (num_ == 0) {
    throw std::runtime_error(
        "Error: This tensor hasn't been allocated storage.");
  }

  if (offset > num_ - 1) {
    throw std::range_error("Error: Offset exceeds the num of tensor.");
  }

  return static_cast<T *>(storage_->ptr()) + offset;
}

template <typename T> const T *Tensor::ptr(size_t offset) const {
  if (num_ == 0) {
    throw std::runtime_error(
        "Error: This tensor hasn't been allocated storage.");
  }

  if (offset > num_ - 1) {
    throw std::range_error("Error: Offset exceeds the num of tensor.");
  }

  return static_cast<const T *>(storage_->ptr()) + offset;
}
} // namespace tensor
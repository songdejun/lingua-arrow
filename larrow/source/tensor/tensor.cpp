#include "larrow/tensor/tensor.h"
#include "larrow/base/storage.h"
#include <algorithm>
#include <numeric>
#include <vector>

namespace tensor {
Tensor::Tensor(base::DataType data_type, std::vector<size_t> dims,
               base::DeviceAllocator &allocator)
    : data_type_(data_type), dims_(dims) {
  size_ = dim2size(dims_);
  storage_ = base::Storage::create(size(), allocator);
}

size_t dim2size(std::vector<size_t> dims) {
  return std::accumulate(dims.begin(), dims.end(), 1, std::multiplies<size_t>());
}

bool Tensor::empty() const { return size_ == 0; }

template <typename T> T *Tensor::ptr() { return storage_->ptr(); }

template <typename T> const T *Tensor::ptr() const { return storage_->ptr(); }

Tensor &Tensor::reshape(std::vector<size_t> dims) {
  size_t new_size = dim2size(dims);
  if (new_size != size_) {
    throw std::invalid_argument("Error: New dimensions are not compatible with "
                                "the number of elements in the tensor.");
  }

  dims_ = dims;

  strides_ = std::vector<size_t>(dims_.size());
  size_t suffix_product = 1;
  for (int i = dims_.size() - 1; i >= 0; i--) {
    strides_[i] = suffix_product;
    suffix_product *= dims_[i];
  }

  return *this;
}

std::shared_ptr<base::Storage> Tensor::storage() const {
  return storage_->shared_ptr();
}

size_t Tensor::size() const { return size_; }

std::vector<size_t> Tensor::dims() const { return dims_; }

std::vector<size_t> Tensor::strides() const { return strides_; }

base::DataType Tensor::date_type() const { return data_type_; }

void Tensor::reset(base::DataType data_type, std::vector<size_t> dims,
                   base::DeviceAllocator &allocator) {
                    dims_ = dims;
                    size_ = dim2size(dims_);
      std::accumulate(dims_.begin(), dims_.end(), 1, std::multiplies<size_t>());
                    storage_ = base::Storage::create(size_, allocator);
                   }
void Tensor::reset(base::DataType data_type, std::vector<size_t> dims) {}
} // namespace tensor
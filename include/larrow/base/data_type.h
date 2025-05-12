#pragma once

namespace base {
enum class DataType {
  fp32,
  int8,
  int32,
};

inline int size_of(DataType data_type) {
  switch (data_type) {
  case DataType::fp32:
    return 4;
  case DataType::int8:
    return 1;
  case DataType::int32:
    return 4;
  }
}
} // namespace base
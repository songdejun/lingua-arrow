project('larrow', 'cpp', version: '1.0', default_options: ['cpp_std=c++17'])

inc = include_directories('include')
src_root = 'src'

base_src = files(
    src_root / 'base/allocator.cpp',
    src_root / 'base/storage.cpp')

tensor_src = files(
    src_root / 'tensor/tensor.cpp'
)

larrow_src = [base_src, tensor_src]

larrow = shared_library('larrow', sources: larrow_src, include_directories: inc)

main_src = files(
    'main.cpp')

executable('main', sources: main_src, link_with: larrow, include_directories: inc)
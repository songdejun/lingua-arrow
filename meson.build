project('larrow', 'cpp', version: '1.0', default_options: ['cpp_std=c++17'])

inc = include_directories('larrow/include')
src_root = 'larrow/source'

base_src = files(
    # src_root / 'base/base.cpp',
    src_root / 'base/alloc.cpp',
    src_root / 'base/storage.cpp')


src = [base_src]

larrow= shared_library('larrow', sources: src, include_directories: inc)

main_src = [files('main.cpp')]
executable('main', sources:main_src, link_with: larrow, include_directories: inc)
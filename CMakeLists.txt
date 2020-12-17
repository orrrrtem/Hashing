cmake_minimum_required(VERSION 3.12)
project(Hashing)

set(CMAKE_CXX_STANDARD 17)

add_executable(Hashing main.cpp ChainHash.hpp hashing.hpp universal_hashing.hpp utils.hpp hash_base.hpp chain_hash_cell.hpp benchmarks.hpp open_hash.hpp open_hash_cell.hpp cuckoo.hpp)
//
// Created by Артем Аросланкин on 16.12.2020.
//

#ifndef HASHING_HASH_BASE_HPP
#define HASHING_HASH_BASE_HPP

#pragma once

#include <iostream>
#include <string>
#include <math.h>
#include <random>
#include <array>
#include <random>

#include "universal_hashing.hpp"

template<typename KeyType = uint32_t, typename ValueType = uint32_t>
class hash_base {
public:

    hash_base() = default;

//    explicit hash_base(uint32_t count, hash_function<KeyType>* hash_func) : table_size(count), hash_func(hash_func) {
//        hash_func->table_size = table_size;
//    }

    virtual ~hash_base() = default;

    virtual void insert(const KeyType& key, const ValueType& value) = 0;

    virtual bool search(const KeyType& key) const  = 0;

    virtual void remove(const KeyType& key) = 0;

private:
//    uint32_t table_size = 0;
//    hash_function<KeyType>* hash_func;
};

#endif //HASHING_HASH_BASE_HPP

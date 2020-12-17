//
// Created by Артем Аросланкин on 16.12.2020.
//

#ifndef HASHING_HASHING_HPP
#define HASHING_HASHING_HPP

#pragma once

#include <iostream>
#include <cstdint>

template<typename KeyType>
struct hash_function {
    hash_function() = default;
    explicit hash_function(uint32_t size) : table_size(size) {}
    virtual inline uint32_t get_value(const KeyType& key) const = 0;
    inline uint32_t get_table_size() const {
        return table_size;
    }
    virtual inline void update() = 0;
    uint32_t table_size = 0;
};
#endif //HASHING_HASHING_HPP

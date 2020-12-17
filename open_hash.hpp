//
// Created by Артем Аросланкин on 16.12.2020.
//

#ifndef HASHING_OPEN_HASH_HPP
#define HASHING_OPEN_HASH_HPP

#pragma once

#include <iostream>
#include <string>
#include <math.h>
#include <random>
#include <array>
#include <random>

#include "hash_base.hpp"
#include "universal_hashing.hpp"
#include "open_hash_cell.hpp"
#include "utils.hpp"

using namespace std;

template<typename KeyType = uint32_t, typename ValueType = uint32_t>
class open_hash: public hash_base<KeyType, ValueType> {
public:
    using cell = open_hash_element<KeyType, ValueType>;

    open_hash() = default;

    explicit open_hash(uint32_t count, hash_function<KeyType>* hash_func) : table_size(count), hash_func(hash_func) {
        hash_func->table_size = table_size;
        table = vector<cell>(count);
        //table = new cell* [count]();
//        for(int i = 0; i < table_size;i++) {
//            table[i] = new cell;
//        }

    }

    virtual ~open_hash() =default; //{
//        if (table != nullptr) {
//            for(int i = 0; i < table_size;i++) {
//                delete table[i];
//            }
//            delete [] table;
//        }
//    }

    void insert(const KeyType& key, const ValueType& value) override {
        auto hash_value = hash_func->get_value(key);
        uint32_t attempts = 0;

        while (table[hash_value].get_state() != state::empty && attempts <= num_elements_in_table) {
            hash_value = fast_mod((hash_value + 1), table_size);
            attempts++;
        }
        if(attempts > num_elements_in_table) {
            return;
        }
        //table[hash_value] = new cell;
        table[hash_value].set_key(key).set_value(value).set_state(state::filled);
        num_elements_in_table++;
    }

    bool search(const KeyType& key) const override {
        auto hash_value = hash_func->get_value(key);
        uint32_t attempts = 0;
        //if(table[hash_value] == nullptr) return false;
        while (table[hash_value].get_state() != state::empty && attempts <= num_elements_in_table) {
            if(table[hash_value].get_key() == key) {
                return true;
            }
            hash_value = fast_mod(hash_value + 1, table_size);
            attempts++;
        }
        return false;
    }

    void remove(const KeyType& key) override {
        auto hash_value = hash_func->get_value(key);
        uint32_t attempts = 0;
        //if(table[hash_value] == nullptr) return;
        while (table[hash_value].get_state() != state::empty && attempts <= num_elements_in_table) {
            if(table[hash_value].get_key() == key) {
                table[hash_value].set_state(state::empty);
            }
            hash_value++;
            attempts++;
        }
    }

private:
    uint32_t table_size = 0;
    //cell ** table;
    vector<cell> table;
    hash_function<KeyType>* hash_func;
    uint32_t num_elements_in_table = 0;
};
#endif //HASHING_OPEN_HASH_HPP

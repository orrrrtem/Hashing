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

enum class probing_mode :uint8_t  {linear, quadratic, double_h};

template<typename KeyType = uint32_t, typename ValueType = uint32_t>
class open_hash: public hash_base<KeyType, ValueType> {
public:
    using cell = open_hash_element<KeyType, ValueType>;

    open_hash() = default;

    open_hash(uint32_t count, probing_mode mode, hash_function<KeyType>* hash_func) :
              table_size(count), hash_func(hash_func), probing_mode_(mode) {
        hash_func->table_size = table_size;
        if (probing_mode_ == probing_mode::linear) {
            table = vector<cell>(count);
        }
        else {
            table = vector<cell>(get_x2_prime(count));
        }
    }

    auto& set_probing_mode(probing_mode value) {
        probing_mode_ = value;
        return *this;
    }

    virtual ~open_hash() =default;

    void insert(const KeyType& key, const ValueType& value) override {
        uint32_t attempts = 0;
        uint32_t hash_value = 0;
        if (probing_mode_ == probing_mode::linear) {
            hash_value = hash_func->get_value(key);
            while (table[hash_value].get_state() != state::empty && attempts <= num_elements_in_table) {
                hash_value = fast_mod((hash_value + 1), table_size);
                attempts++;
            }
        }
        else if (probing_mode_ == probing_mode::quadratic) { // https://en.wikipedia.org/wiki/Quadratic_probing
            hash_value = hash_func->get_value(key);
            while (table[hash_value].get_state() != state::empty && attempts <= num_elements_in_table) {
                hash_value = fast_mod((hash_value + c1*attempts + c2*c2*attempts), table_size);
                attempts++;
            }
        }
        else { // https://en.wikipedia.org/wiki/Double_hashing
            hash_value = hash_func->get_value(key);
            while (table[hash_value].get_state() != state::empty && attempts <= num_elements_in_table) {
                hash_value = fast_mod((hash_value + attempts * fast_mod(key, get_less_prime(table_size))), table_size);
                attempts++;
            }
        }

        if(attempts > num_elements_in_table) {
            throw "Table cannot fit more elements";
        }
        table[hash_value].set_key(key).set_value(value).set_state(state::filled);
        num_elements_in_table++;
    }

    bool search(const KeyType& key) const override {
        uint32_t attempts = 0;
        uint32_t hash_value = 0;
        if (probing_mode_ == probing_mode::linear) {
            hash_value = hash_func->get_value(key);
            while (table[hash_value].get_state() != state::empty && attempts <= num_elements_in_table) {
                if(table[hash_value].get_key() == key) {
                    return true;
                }
                hash_value = fast_mod((hash_value + 1), table_size);
                attempts++;
            }
        }
        else if (probing_mode_ == probing_mode::quadratic) { // https://en.wikipedia.org/wiki/Quadratic_probing
            hash_value = hash_func->get_value(key);
            while (table[hash_value].get_state() != state::empty && attempts <= num_elements_in_table) {
                if(table[hash_value].get_key() == key) {
                    return true;
                }
                hash_value = fast_mod((hash_value + c1 * attempts + c2 * c2 * attempts), table_size);
                attempts++;
            }
        }
        else { // https://en.wikipedia.org/wiki/Double_hashing
            hash_value = hash_func->get_value(key);
            while (table[hash_value].get_state() != state::empty && attempts <= num_elements_in_table) {
                if(table[hash_value].get_key() == key) {
                    return true;
                }
                hash_value = fast_mod((hash_value + attempts * fast_mod(key, get_less_prime(table_size))), table_size);
                attempts++;
            }
        }
        return false;
    }

    void remove(const KeyType& key) override {
        uint32_t attempts = 0;
        uint32_t hash_value = 0;
        if (probing_mode_ == probing_mode::linear) {
            hash_value = hash_func->get_value(key);
            while (table[hash_value].get_state() != state::empty && attempts <= num_elements_in_table) {
                if(table[hash_value].get_key() == key) {
                    table[hash_value].set_state(state::empty);
                }
                hash_value = fast_mod((hash_value + 1), table_size);
                attempts++;
            }
        }
        else if (probing_mode_ == probing_mode::quadratic) { // https://en.wikipedia.org/wiki/Quadratic_probing
            hash_value = hash_func->get_value(key);
            while (table[hash_value].get_state() != state::empty && attempts <= num_elements_in_table) {
                if(table[hash_value].get_key() == key) {
                    table[hash_value].set_state(state::empty);
                }
                hash_value = fast_mod((hash_value + c1*attempts + c2*c2*attempts), table_size);
                attempts++;
            }
        }
        else { // https://en.wikipedia.org/wiki/Double_hashing
            hash_value = hash_func->get_value(key);
            while (table[hash_value].get_state() != state::empty && attempts <= num_elements_in_table) {
                if(table[hash_value].get_key() == key) {
                    table[hash_value].set_state(state::empty);
                }
                hash_value = fast_mod((hash_value + attempts * fast_mod(key, get_less_prime(table_size))), table_size);
                attempts++;
            }
        }
    }

private:
    probing_mode probing_mode_ = probing_mode::linear;
    uint32_t table_size = 0;
    vector<cell> table;
    hash_function<KeyType>* hash_func;

    // https://en.wikipedia.org/wiki/Quadratic_probing
    // for prime m > 2, good choice can be c1 = c2 = 1/2, c1 = c2 = 1, and c1 = 0, c2 = 1.
    const uint32_t c1 = 0, c2 = 1;

    //hash_function<KeyType>* hash_func_2;
    uint32_t num_elements_in_table = 0;
};



#endif //HASHING_OPEN_HASH_HPP

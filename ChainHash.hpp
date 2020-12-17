//
// Created by Артем Аросланкин on 15.12.2020.
//

#ifndef HASHING_CHAINHASH_HPP
#define HASHING_CHAINHASH_HPP

#pragma once

#include <iostream>
#include <string>
#include <math.h>
#include <random>
#include <array>
#include <random>

#include "hash_base.hpp"
#include "universal_hashing.hpp"
#include "chain_hash_cell.hpp"

using namespace std;

template<typename KeyType = uint32_t, typename ValueType = uint32_t>
class chain_hash: public hash_base<KeyType, ValueType> {
public:
    using cell = hash_element<KeyType, ValueType>;

    chain_hash() = default;

    chain_hash(uint32_t count, hash_function<KeyType>* hash_func) : table_size(count), hash_func(hash_func) {
        table = new cell* [count];
        hash_func->table_size = table_size;

    }

    virtual ~chain_hash() {
        if (table != nullptr) {
            delete [] table;
        }
    }

    void insert(const KeyType& key, const ValueType& value) override {
        const auto hash_value = hash_func->get_value(key);
        if (table[hash_value] == nullptr) {
            table[hash_value] = new cell(key, value);
        }
        else {
            cell* chain_entry = table[hash_value];
            while (chain_entry->get_next() != nullptr) {
                chain_entry = chain_entry->get_next();
            }
            if (chain_entry->get_key() == key) {
                chain_entry->set_value(value);
            }
            else {
                chain_entry->set_next(new cell);
            }
        }
    }

    bool search(const KeyType& key) const override {
        const auto hash_value = hash_func->get_value(key);
        cell *chain_entry = table[hash_value];
        while (chain_entry != nullptr) {
            if (chain_entry->get_key() == key) {
                return true;
            }
            chain_entry = chain_entry->get_next();
        }
        return false;
    }

    void remove(const KeyType& key) override {
        const auto hashValue = hash_func->get_value(key);
        cell *entry = table[hashValue];
        cell *prev = nullptr;
        while (entry != nullptr && entry->get_key()!= key) {
            prev = entry;
            entry = entry->get_next();
        }
        if (entry != nullptr) {
            if (prev != nullptr) {
                prev->set_next(entry->get_next());
            }
            else {
                table[hashValue] = entry->get_next();
            }
            delete entry;
        }
    }

private:
    uint32_t table_size = 0;
    cell ** table;
    hash_function<KeyType>* hash_func;
};

#endif //HASHING_CHAINHASH_HPP

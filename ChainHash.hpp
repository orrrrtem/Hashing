//
// Created by Артем Аросланкин on 15.12.2020.
//

#ifndef HASHING_CHAINHASH_HPP
#define HASHING_CHAINHASH_HPP

#pragma once

#include <string>

using namespace std;

template<typename KeyType, typename ValueType>
class hash_element {
public:
    hash_element() = default;
    hash_element(KeyType key,const ValueType& value) : key(key), value(value) {
        next = nullptr;
    }
    
    const KeyType& get_key() const {
        return key;
    }

    const ValueType& get_value() const {
        return value;
    }

    hash_element* get_next() const {
        return next;
    }
    auto& set_value (ValueType value) {
        value = value;
        return *this;
    }

    auto& set_next( hash_element* next) {
        next = next;
        return *this;
    }


private:
    hash_element(const hash_element &&);
    hash_element& operator=(const hash_element &&);
    KeyType key;
    ValueType value;
    hash_element *next = nullptr;

};

template<typename KeyType = int32_t, typename ValueType = int32_t>
class hash_table {
public:
    using cell = hash_element<KeyType, ValueType>;

    hash_table() = default;

    hash_table(size_t count) : table_size(count) {
        table = new cell* [count];
    }

    virtual ~hash_table() {
        if (table == nullptr) {
            delete [] table;
        }
    }

     ValueType hash_func(KeyType value) {
        return value % table_size;
    }

    void insert(KeyType key, ValueType value) {
        const auto hash_value = hash_func(key);
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

private:
    size_t table_size = 0;
    cell ** table;
};

#endif //HASHING_CHAINHASH_HPP

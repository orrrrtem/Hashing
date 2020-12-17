//
// Created by Артем Аросланкин on 16.12.2020.
//

#ifndef HASHING_CHAIN_HASH_CELL_HPP
#define HASHING_CHAIN_HASH_CELL_HPP

#pragma once

using namespace std;

template<typename KeyType, typename ValueType>
class hash_element {
public:
    hash_element() = default;

    hash_element(KeyType key,const ValueType& value) : key_(key), value_(value) {
        next_ = nullptr;
    }

    virtual ~hash_element() = default;

    const KeyType& get_key() const {
        return key_;
    }

    const ValueType& get_value() const {
        return value_;
    }

    hash_element* get_next() const {
        return next_;
    }
    auto& set_value(ValueType value) {
        value_ = value;
        return *this;
    }

    auto& set_key(KeyType key) {
        key_ = key;
        return *this;
    }

    auto& set_next(hash_element* next) {
        next_ = next;
        return *this;
    }


private:
    hash_element(const hash_element &&);
    hash_element& operator=(const hash_element &&);
    KeyType key_;
    ValueType value_;
    hash_element *next_ = nullptr;

};

#endif //HASHING_CHAIN_HASH_CELL_HPP

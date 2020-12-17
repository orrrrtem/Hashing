//
// Created by Артем Аросланкин on 16.12.2020.
//

#ifndef HASHING_OPEN_HASH_CELL_HPP
#define HASHING_OPEN_HASH_CELL_HPP

#pragma once

enum class state : bool { empty, filled};

template<typename KeyType, typename ValueType>
class open_hash_element {
public:
    open_hash_element() = default;

    open_hash_element(KeyType key, const ValueType& value) : key_(key), value_(value) {}

    virtual ~open_hash_element() = default;

    const KeyType& get_key() const {
        return key_;
    }

    const ValueType& get_value() const {
        return value_;
    }

    auto& set_value(ValueType value) {
        value_ = value;
        return *this;
    }

    auto& set_key(KeyType key) {
        key_ = key;
        return *this;
    }

    auto& set_state(state status) {
        state_ = status;
        return *this;
    }

    inline state get_state() const {
        return state_;
    }


private:
    open_hash_element(const open_hash_element &&) noexcept;
    open_hash_element& operator=(const open_hash_element &&);
    KeyType key_;
    ValueType value_;
    state state_ = state::empty;
};

#endif //HASHING_OPEN_HASH_CELL_HPP

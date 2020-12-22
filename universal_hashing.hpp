//
// Created by Артем Аросланкин on 16.12.2020.
//

#ifndef HASHING_UNIVERSAL_HASHING_HPP
#define HASHING_UNIVERSAL_HASHING_HPP

#pragma once

#include <iostream>
#include <string>
#include <math.h>
#include <random>
#include <array>
#include <random>

#include "hashing.hpp"
#include "utils.hpp"

using namespace std;

// https://www.planetmath.org/goodhashtableprimes
array<uint32_t, 20> prime_to_choose = {53, 97, 193, 389, 769,
                                       1543, 3079, 6151, 12289, 24593,
                                       49157, 98317, 196613, 393241, 786433,
                                       1572869, 3145739, 6291469, 12582917, 25165843 };
template<typename KeyType>
struct universal_hash_function: public hash_function<KeyType> {

    explicit universal_hash_function(uint32_t size) : hash_function<KeyType>(size) {
        random_device rd; // one for hash table
        mt19937 ms(rd()); // one for hash table
        //does not make sense, lets use concrete
        /*
        for(auto prime_try: prime_to_choose) {
            if (prime_try >= 100 * this->get_table_size()) {
                prime = prime_try;
            }
        }*/

        prime = 196613;
        uniform_int_distribution<uint32_t> gen_a(1, prime - 1);
        uniform_int_distribution<uint32_t> gen_b(0, prime - 1);
        a = gen_a(ms);
        b = gen_b(ms);
    }
    void update() override {
        random_device rd;
        mt19937 ms(rd());
        prime = 196613;
        uniform_int_distribution<uint32_t> gen_a(1, prime - 1);
        uniform_int_distribution<uint32_t> gen_b(0, prime - 1);
        a = gen_a(ms);
        b = gen_b(ms);
    }

    inline uint32_t get_value(const KeyType& key) const override{
        return fast_mod(fast_mod(a * key + b, prime), this->get_table_size());
    }
    // https://www.planetmath.org/goodhashtableprimes
//    array<uint32_t, 20> prime_to_choose = {53, 97, 193, 389, 769,
//                                           1543, 3079, 6151, 12289, 24593,
//                                           49157, 98317, 196613, 393241, 786433,
//                                           1572869, 3145739, 6291469, 12582917, 25165843 };

    uint32_t prime = prime_to_choose[14];
    uint32_t a;
    uint32_t b;
    uint32_t h_ = 0;
};

template<>
inline uint32_t universal_hash_function<string>::get_value(const string &key) const {
    //stl port
    uint32_t h = h_;
    for(uint32_t i = 0; i < key.size(); i++) {
        h = ((h << 5) + h) + key[i];
    }
    return fast_mod(h, table_size);
}

template<>
void universal_hash_function<string>::update() {
    h_++;
}

inline uint32_t get_x2_prime(uint32_t count) {
    for(auto prime_try: prime_to_choose) {
        if (prime_try > 2 * count) {
            return prime_try;
        }
    }
}

inline uint32_t get_less_prime(uint32_t count) {
    auto nearest = 2;
    for(auto prime_try: prime_to_choose) {
        if (prime_try >= count) {
            return nearest;
        }
        nearest = prime_try;
    }
}


#endif //HASHING_UNIVERSAL_HASHING_HPP

//
// Created by Артем Аросланкин on 16.12.2020.
//

#ifndef HASHING_UTILS_HPP
#define HASHING_UTILS_HPP

#pragma once

#include <vector>
#include <array>
#include <random>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <utility>

using namespace std;

template<typename T>
inline T fast_mod(const T& input, const T& ceil) {
    // apply the modulo operator only when needed
    // (i.e. when the input is greater than the ceiling)
    return input >= ceil ? input % ceil : input;
    // NB: the assumption here is that the numbers are positive
}

template<typename DataType>
vector<DataType> generate_random_vector(const size_t size, DataType value_begin = NULL, DataType value_end = NULL);

template<>
vector<uint32_t> generate_random_vector(const size_t size, uint32_t value_begin, uint32_t value_end) {
    random_device rd;
    mt19937 ms(rd());
    uniform_int_distribution<uint32_t> gen(value_begin, value_end);
    vector<uint32_t> vec(size);
    for(auto& i : vec) {
        i = gen(ms);
    }
    return vec;
}

template<>
vector<string> generate_random_vector(const size_t size, string value_begin, string value_end) {
    random_device rd;
    mt19937 ms(rd());
    static uniform_int_distribution<uint32_t> gen_lenght(5, 15);
    static std::uniform_int_distribution<uint8_t> gen_char_index(0, 26);
    vector<string> vec(size);
    for(auto& i : vec) {
        const size_t str_length = gen_lenght(ms);
        string str(str_length, 'a');
        for(auto& i: str ) {
            i += gen_char_index(ms);
        }
        i = str;
    }
    return vec;
}

#endif //HASHING_UTILS_HPP

//
// Created by Артем Аросланкин on 16.12.2020.
//

#ifndef HASHING_BENCHMARKS_HPP
#define HASHING_BENCHMARKS_HPP

#pragma once

#include <vector>
#include <array>
#include <random>
#include <string>
#include <iostream>
#include <chrono>
#include <algorithm>
#include <map>
//#include <hashmap>

#include "hash_base.hpp"
#include "utils.hpp"

using namespace std;
using namespace std::chrono;

template<typename KeyType>
void fill_hash_table(hash_base<KeyType, KeyType>& hash_table,
                     const typename vector<KeyType>::iterator keys_begin,
                     const typename vector<KeyType>::iterator keys_end) {
    for(auto i = keys_begin; i != keys_end; i++) {
        hash_table.insert(*i, *i);
    }
}

template<typename KeyType>
void fill_std_map_table(map<KeyType, KeyType>& hash_table,
                     const typename vector<KeyType>::iterator keys_begin,
                     const typename vector<KeyType>::iterator keys_end) {
    for(auto i = keys_begin; i != keys_end; i++) {
        hash_table.insert({*i, *i});
    }
}

template<typename HashTable, typename KeyType>
auto measure_std_insert(HashTable& hash_table,
                    const typename vector<KeyType>::iterator keys_begin,
                    const typename vector<KeyType>::iterator keys_end) {
    vector<double> time;
    for(auto i = keys_begin; i != keys_end; i++) {
        const KeyType key = *i;
        auto start = high_resolution_clock::now();
        hash_table.insert({key, key});
        auto stop = high_resolution_clock::now();
        time.push_back(std::chrono::duration_cast<std::chrono::duration<double, std::nano>>(stop - start).count());
    }
    sort(time.begin(), time.end());
    return to_string(time[time.size()/2]);
}

template<typename HashTable, typename KeyType>
auto measure_std_remove(HashTable& hash_table,
                        const typename vector<KeyType>::iterator keys_begin,
                        const typename vector<KeyType>::iterator keys_end) {
    vector<double> time;
    for(auto i = keys_begin; i != keys_end; i++) {
        const KeyType key = *i;
        auto start = high_resolution_clock::now();
        hash_table.erase(key);
        auto stop = high_resolution_clock::now();
        time.push_back(std::chrono::duration_cast<std::chrono::duration<double, std::nano>>(stop - start).count());
    }
    sort(time.begin(), time.end());
    return to_string(time[time.size()/2]);
}

template<typename HashTable, typename KeyType>
auto measure_std_search(HashTable& hash_table,
                        const typename vector<KeyType>::iterator keys_begin,
                        const typename vector<KeyType>::iterator keys_end) {
    vector<double> time;
    for(auto i = keys_begin; i != keys_end; i++) {
        const KeyType key = *i;
        auto start = high_resolution_clock::now();
        hash_table.find(key);
        auto stop = high_resolution_clock::now();
        time.push_back(std::chrono::duration_cast<std::chrono::duration<double, std::nano>>(stop - start).count());
    }
    sort(time.begin(), time.end());
    return to_string(time[time.size()/2]);
}

template<typename KeyType>
auto measure_insert(hash_base<KeyType, KeyType>& hash_table,
                             const typename vector<KeyType>::iterator keys_begin,
                             const typename vector<KeyType>::iterator keys_end) {
    vector<double> time;
    for(auto i = keys_begin; i != keys_end; i++) {
        const KeyType key = *i;
        auto start = high_resolution_clock::now();
        hash_table.insert(key, key);
        auto stop = high_resolution_clock::now();
        time.push_back(std::chrono::duration_cast<std::chrono::duration<double, std::nano>>(stop - start).count());
    }
    sort(time.begin(), time.end());
    return to_string(time[time.size()/2]);
}

template<typename KeyType>
auto measure_remove(hash_base<KeyType, KeyType>& hash_table,
                    const typename vector<KeyType>::iterator keys_begin,
                    const typename vector<KeyType>::iterator keys_end) {
    vector<double> time;
    for(auto i = keys_begin; i != keys_end; i++) {
        const KeyType key = *i;
        auto start = high_resolution_clock::now();
        hash_table.remove(key);
        auto stop = high_resolution_clock::now();
        time.push_back(std::chrono::duration_cast<std::chrono::duration<double, std::nano>>(stop - start).count());
    }
    sort(time.begin(), time.end());
    return to_string(time[time.size()/2]);
}

template<typename KeyType>
auto measure_search(hash_base<KeyType, KeyType>& hash_table,
                    const typename vector<KeyType>::iterator keys_begin,
                    const typename vector<KeyType>::iterator keys_end) {
    vector<double> time;
    for(auto i = keys_begin; i != keys_end; i++) {
        const KeyType key = *i;
        auto start = high_resolution_clock::now();
        hash_table.search(key);
        auto stop = high_resolution_clock::now();
        time.push_back(std::chrono::duration_cast<std::chrono::duration<double, std::nano>>(stop - start).count());
    }
    sort(time.begin(), time.end());
    return to_string(time[time.size()/2]);
}




#endif //HASHING_BENCHMARKS_HPP

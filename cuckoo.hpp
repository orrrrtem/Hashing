//
// Created by Артем Аросланкин on 17.12.2020.
//

#ifndef HASHING_CUCKOO_HPP
#define HASHING_CUCKOO_HPP

#pragma once

#include <iostream>
#include <string>
#include <math.h>
#include <random>
#include <array>
#include <random>
#include <algorithm>

#include "hash_base.hpp"
#include "universal_hashing.hpp"
#include "open_hash_cell.hpp"
#include "utils.hpp"

using namespace std;

// https://web.stanford.edu/class/archive/cs/cs166/cs166.1146/lectures/13/Small13.pdf
template<typename KeyType = uint32_t, typename ValueType = uint32_t>
class cuckoo_hash: public hash_base<KeyType, ValueType> {
public:
    using cell = open_hash_element<KeyType, ValueType>;

    cuckoo_hash() = default;

    cuckoo_hash(uint32_t count, hash_function<KeyType>* hash_func, hash_function<KeyType>* hash_func2) : table_size(count), hash_func(hash_func), hash_func2(hash_func2) {
        cout << "s";
        hash_func->table_size = table_size;
        table1 = new cell* [count];
        table2 = new cell* [count];
        for(int i = 0; i < table_size;i++) {
            table1[i] = new cell;
            table2[i] = new cell;
        }

    }

    virtual ~cuckoo_hash() {
        if (table1 != nullptr) {
            for(int i = 0; i < table_size;i++) {
                delete table1[i];
            }
            delete [] table1;
        }
        if (table2 != nullptr) {
            for(int i = 0; i < table_size;i++) {
                delete table2[i];
            }
            delete [] table2;
        }
    }

    void insert(const KeyType& key, const ValueType& value) override {
        cell* cell_ = new cell(key, value);
        auto hash_value = hash_func->get_value(key);
        if(table1[hash_value]->get_state() == state::empty || table1[hash_value]->get_key() == key) {
            table1[hash_value]->set_key(key).set_value(value).set_state(state::filled);
            return;
        }

        auto hash_value2 = hash_func2->get_value(key);
        if(table2[hash_value2]->get_state() == state::empty ||  table2[hash_value2]->get_key() == key) {
            table2[hash_value2]->set_key(key).set_value(value).set_state(state::filled);
            return;
        }
        const auto init_hash_value = hash_value;
        std::swap(cell_, table1[hash_value]);
        auto input_key = key;
        auto input_value = value;
        auto attempts = 0;

        while(attempts <= num_elements) {
            hash_value = hash_func2->get_value(cell_->get_key()); //find cell in 2nd table
            if(table2[hash_value]->get_state() == state::empty || table2[hash_value]->get_key() == cell_->get_key()) { // if we can put in 2nd table
                table2[hash_value]->set_key(key).set_value(value).set_state(state::filled);
                return;
            }
            std::swap(cell_, table2[hash_value]);

            hash_value2 = hash_func->get_value(cell_->get_key()); // find cell in 1st table
            if(table1[hash_value2]->get_state() == state::empty) { //if we can put in 1st table
                table1[hash_value2]->set_key(key).set_value(value).set_state(state::filled);
                return;
            }

            std::swap(cell_, table1[hash_value2]);
            if(input_key == cell_->get_key()) {

                hash_func->update();
                hash_func2->update();
                cell** ctable = new cell* [table_size];
                cell** ctable2 = new cell* [table_size];
//#pragma omp parallel_for
                for(int i = 0; i < table_size;i++) {
                    ctable[i] = new cell;
                    ctable[i] = table1[i];
                    ctable2[i] = new cell;
                    ctable2[i] = table2[i];

                }
                for(int i = 0; i < table_size;i++) {
                    if(ctable[i]->get_state() == state::filled)
                        insert(ctable[i]->get_key(), ctable[i]->get_value());
                    if(ctable2[i]->get_state() == state::filled)
                        insert(ctable2[i]->get_key(), ctable2[i]->get_value());
                }
                for(int i = 0; i < table_size;i++) {
                    delete ctable[i];
                    delete ctable2[i];
                }
                delete [] ctable;
                delete [] ctable2;
            }
            attempts++;
        }
        num_elements++;
    }

    bool search(const KeyType& key) const override {
        const auto hash_value = hash_func->get_value(key);
        if(table1[hash_value]->get_state() != state::empty && table1[hash_value]->get_key() == key) {
            return true;
        }
        const auto hash_value2 = hash_func2->get_value(key);
        if(table2[hash_value2]->get_state() != state::empty && table2[hash_value2]->get_key() == key) {
            return true;
        }

        return false;
    }

    void remove(const KeyType& key) override {
        auto hash_value = hash_func->get_value(key);
        if(table1[hash_value]->get_state() != state::empty && table1[hash_value]->get_key() == key) {
                table1[hash_value]->set_state(state::empty);
        }

        auto hash_value2 = hash_func2->get_value(key);
        if(table2[hash_value2]->get_state() != state::empty && table2[hash_value2]->get_key() == key) {
                table2[hash_value2]->set_state(state::empty);
        }

    }

private:
    uint32_t table_size = 0;
    cell ** table1;
    cell ** table2;
    hash_function<KeyType>* hash_func;
    hash_function<KeyType>* hash_func2;
    uint32_t num_elements = 0;

};


#endif //HASHING_CUCKOO_HPP

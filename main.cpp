#include <iostream>
#include <math.h>
#include <random>
#include <map>

#include "ChainHash.hpp"
#include "open_hash.hpp"
#include "utils.hpp"
#include "benchmarks.hpp"
#include "cuckoo.hpp"


//#include <hash_map>

using namespace std;
int main() {
    const uint32_t n_start = 1000;
    const uint32_t  n_end = 100000;
    const uint32_t step = 500;
    vector<uint32_t> keys = generate_random_vector<uint32_t >(n_end + 100, 100, 1000);

    vector<pair<string, uint32_t >> chain_hash_insert, chain_hash_search, chain_hash_remove;

    vector<pair<string, uint32_t >> open_hash_insert, open_hash_search, open_hash_remove;

    vector<pair<string, uint32_t >> cuckoo_hash_insert, cuckoo_hash_search, cuckoo_hash_remove;

    vector<pair<string, uint32_t >> std_map_insert, std_map_search, std_map_remove;

    vector<pair<string, uint32_t >> std_hash_insert, std_hash_search, std_hash_remove;

    int k = 0;
    for(uint32_t i = n_start; i < n_end; i+=step) {
        if (k % 10 == 0) cout << "#";
        const uint32_t capacity  = 2 * i;
        universal_hash_function<uint32_t> hash_func(capacity);

        /*
        chain_hash<> chain_hash_table(capacity, &hash_func);
        fill_hash_table(chain_hash_table, keys.begin(), keys.begin() + i);
        chain_hash_insert.emplace_back(make_pair(measure_insert(chain_hash_table, keys.begin() + i, keys.begin() + i + 10), i));
        chain_hash_search.emplace_back(make_pair(measure_remove(chain_hash_table, keys.begin() + i + 5, keys.begin() + i + 10), i));
        chain_hash_remove.emplace_back(make_pair(measure_search(chain_hash_table, keys.begin() + i, keys.begin() + i + 10), i));
         */

        open_hash<> open_hash_table(capacity,probing_mode::linear, &hash_func);
        fill_hash_table(open_hash_table, keys.begin(), keys.begin() + i);
        open_hash_insert.emplace_back(make_pair(measure_insert(open_hash_table, keys.begin() + i, keys.begin() + i + 10), i));
        open_hash_search.emplace_back(make_pair(measure_remove(open_hash_table, keys.begin() + i + 5, keys.begin() + i + 10), i));
        open_hash_remove.emplace_back(make_pair(measure_search(open_hash_table, keys.begin() + i, keys.begin() + i + 10), i));

        open_hash<> open_hash_table_q(capacity,probing_mode::quadratic, &hash_func);
        fill_hash_table(open_hash_table, keys.begin(), keys.begin() + i);
        open_hash_insert.emplace_back(make_pair(measure_insert(open_hash_table_q, keys.begin() + i, keys.begin() + i + 10), i));
        open_hash_search.emplace_back(make_pair(measure_remove(open_hash_table_q, keys.begin() + i + 5, keys.begin() + i + 10), i));
        open_hash_remove.emplace_back(make_pair(measure_search(open_hash_table_q, keys.begin() + i, keys.begin() + i + 10), i));

        open_hash<> open_hash_table_h(capacity,probing_mode::double_h, &hash_func);
        fill_hash_table(open_hash_table, keys.begin(), keys.begin() + i);
        open_hash_insert.emplace_back(make_pair(measure_insert(open_hash_table_h, keys.begin() + i, keys.begin() + i + 10), i));
        open_hash_search.emplace_back(make_pair(measure_remove(open_hash_table_h, keys.begin() + i + 5, keys.begin() + i + 10), i));
        open_hash_remove.emplace_back(make_pair(measure_search(open_hash_table_h, keys.begin() + i, keys.begin() + i + 10), i));

        /*
        universal_hash_function<uint32_t> hash_func12(2* capacity);
        universal_hash_function<uint32_t> hash_func22(2* capacity);
        cuckoo_hash<> cuckoo_hash_table(2*capacity, &hash_func12, &hash_func22);
        fill_hash_table(cuckoo_hash_table, keys.begin(), keys.begin() + i);
        cuckoo_hash_insert.emplace_back(make_pair(measure_insert(cuckoo_hash_table, keys.begin() + i, keys.begin() + i + 10), i));
        cuckoo_hash_search.emplace_back(make_pair(measure_remove(cuckoo_hash_table, keys.begin() + i + 5, keys.begin() + i + 10), i));
        cuckoo_hash_remove.emplace_back(make_pair(measure_search(cuckoo_hash_table, keys.begin() + i, keys.begin() + i + 10), i));


        map<uint32_t, uint32_t> map_table;
        fill_std_map_table(map_table, keys.begin(), keys.begin() + i);
        std_map_insert.emplace_back(
                make_pair(
                        measure_std_insert<map<uint32_t, uint32_t>, uint32_t >(map_table, keys.begin() + i, keys.begin() + i + 10),
                                i));
        std_map_search.emplace_back(
                make_pair(
                        measure_std_remove<map<uint32_t, uint32_t>, uint32_t >(map_table, keys.begin() + i + 5, keys.begin() + i + 10),
                        i));
        std_map_remove.emplace_back(
                make_pair(
                        measure_std_search<map<uint32_t, uint32_t>, uint32_t >(map_table, keys.begin() + i, keys.begin() + i + 10),
                        i));
                        */
    }

    cout << endl;
    cout << "insert";
    cout << endl;
    for(auto i: chain_hash_insert) {
        cout << i.first << "," << i.second << endl;
    }
    cout << endl;


    for(auto i: open_hash_insert) {
        cout << i.first << "," << i.second << endl;
    }

    cout << endl;
    for(auto i: cuckoo_hash_insert) {
        cout << i.first << "," << i.second << endl;
    }
    cout << endl;
    for(auto i: std_map_insert) {
        cout << i.first << "," << i.second << endl;
    }

    cout << endl;
    cout << endl;
    cout << "search";

    for(auto i: chain_hash_search) {
        cout << i.first << "," << i.second << endl;
    }

    for(auto i: open_hash_search) {
        cout << i.first << "," << i.second << endl;
    }
    cout << endl;
    for(auto i: cuckoo_hash_search) {
        cout << i.first << "," << i.second << endl;
    }
    cout << endl;
    for(auto i: std_map_search) {
        cout << i.first << "," << i.second << endl;
    }
    cout << endl;
    cout << endl;
    cout << "remove";
    cout << endl;

    for(auto i: chain_hash_remove) {
        cout << i.first << "," << i.second << endl;
    }

    cout << endl;
    cout << endl;
    for(auto i: open_hash_remove) {
        cout << i.first << "," << i.second << endl;
    }
    for(auto i: cuckoo_hash_remove) {
        cout << i.first << "," << i.second << endl;
    }
    cout << endl;
    for(auto i: std_map_remove) {
        cout << i.first << "," << i.second << endl;
    }

    return 0;
}
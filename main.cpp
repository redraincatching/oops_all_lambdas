#include <vector>
#include <iostream>

int main() {
    // oops all lambdas
    // this is a bad idea

    // flat map of int pairs (mathematical function)
    // using auto because...
    auto flat_map =
            [data = std::vector<std::pair<int, int>>()](int input_key) mutable -> auto & {
        for (auto &item : data) {
            // could also use &[key, val] but this works well with the return
            if (item.first == input_key) {
                // return the value
                return item.second;
            }
        }
        // we don't have that data in the vector yet so return key with new entry
        // since we need a pair of ints to return, use .second
        return data.emplace_back(input_key, 0).second;
    };

    // now this works as a map in c++
    flat_map(1) = 42;
    std::cout << flat_map(1);
}

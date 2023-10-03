#include <vector>
#include <iostream>

int main() {
    // oops all lambdas
    // this is a bad idea

    // flat map of int pairs (mathematical function)
    // using auto because...
        // now we use a variotic set of inputs
        // so we need to expand the parameter packs with (input_key...)

        // why? so that we can do stuff with variable numbers of parameters
    auto flat_map =
            [data = std::vector<std::pair<int, int>>()]
                (auto && ... input_key) mutable -> auto & {
        if constexpr (sizeof...(input_key) == 1) {
            for (auto &item : data) {
                // could also use &[key, val] but this works well with the return
                // we then use the c++17 fold over the comma operator so that the last item is used for the comparison
                if (item.first == (input_key, ...)) {
                    // return the value
                    return item.second;
                }
            }
            // we don't have that data in the vector yet so return key with new entry
            // since we need a pair of ints to return, use .second
            return data.emplace_back((input_key, ...), 0).second;
        } else {
            return data;
        }
        // we can do an indexed operation with one parameter, but more returns the underlying data itself
    };

    // now this works as a map in c++
    flat_map(1) = 42;
    flat_map(2) = 100;

    for (const auto &[key, value] : flat_map()) {
        std::cout << key << ' ' << value << '\n';
    }
}

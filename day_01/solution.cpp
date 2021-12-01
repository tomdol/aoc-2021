#include <filesystem>
#include <fstream>
#include <iterator>
#include <iostream>
#include <numeric>
#include <string_view>
#include <vector>

#include "counting_iterator.hpp"

uint32_t iterator_solution(const std::filesystem::path& input_file) {
    std::ifstream depth_measurements(input_file);
    auto beg = std::istream_iterator<int32_t>(depth_measurements);
    const auto end = std::istream_iterator<int32_t>();

    std::vector<int32_t> diffs;
    std::adjacent_difference(beg, end, std::back_inserter(diffs));

    return std::count_if(std::next(std::begin(diffs)), std::end(diffs), [](auto d) { return d > 0; });
}

uint32_t counting_iterator_solution(const std::filesystem::path& input_file) {
    std::ifstream depth_measurements(input_file);
    auto beg = std::istream_iterator<int32_t>(depth_measurements);
    const auto end = std::istream_iterator<int32_t>();

    // start counting from -1 because the first adjacent_difference == first element; this should not be counted
    CountingIterator counter([](auto d) { return d > 0; }, -1);
    std::adjacent_difference(beg, end, counter);

    return counter.count();
}

int main() {
    const std::string_view input_file_name = "input.txt";
    const std::filesystem::path file_path{input_file_name};

    std::cout << "iterator solution: " << iterator_solution(file_path) << std::endl;
    std::cout << "counting iterator solution: " << counting_iterator_solution(file_path) << std::endl;

    return 0;
}

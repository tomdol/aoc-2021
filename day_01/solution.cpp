#include <array>
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

uint32_t window_solution(const std::filesystem::path& input_file) {
    std::ifstream depth_measurements(input_file);
    auto first = std::istream_iterator<int32_t>(depth_measurements);
    const auto last = std::istream_iterator<int32_t>();

    uint32_t i = 0;
    std::array<int32_t, 4> values{*first++, *first++, *first++, 0};
    while(first != last) {
        values[3] = *first++;
        // 2 middle elements cancel each other out when subtracting 2 windows
        // which means only edge elements from 2 windows have to be subtracted
        if (values[3] - values[0] > 0)
            ++i;
        // shift the 3 last values left and make the last element a placeholder for the next iteration
        std::rotate(std::begin(values), std::begin(values) + 1, std::end(values));
    }

    return i;
}

int main() {
    const std::string_view input_file_name = "input.txt";
    const std::filesystem::path file_path{input_file_name};

    // part 1
    std::cout << "iterator solution: " << iterator_solution(file_path) << std::endl;
    std::cout << "counting iterator solution: " << counting_iterator_solution(file_path) << std::endl;
    // part 2
    std::cout << "sliding window solution: " << window_solution(file_path) << std::endl;

    return 0;
}

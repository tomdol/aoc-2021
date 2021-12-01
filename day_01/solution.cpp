#include <filesystem>
#include <fstream>
#include <iterator>
#include <iostream>
#include <numeric>
#include <string_view>
#include <vector>

uint32_t iterator_solution(const std::filesystem::path& input_file) {
    std::ifstream depth_measurements(input_file);
    auto beg = std::istream_iterator<int32_t>(depth_measurements);
    const auto end = std::istream_iterator<int32_t>();

    std::vector<int32_t> diffs;
    diffs.reserve(std::distance(beg, end));
    std::adjacent_difference(beg, end, std::back_inserter(diffs));

    return std::count_if(std::begin(diffs), std::end(diffs), [](auto d) { return d < 0; });
}

int main() {
    const std::string_view input_file = "input.txt";
    const std::filesystem::path file_path{input_file};

    const auto ret = iterator_solution(file_path);

    std::cout << ret << std::endl;

    return 0;
}

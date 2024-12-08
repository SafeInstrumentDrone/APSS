// Read files and prints top k word by frequency

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <vector>
#include <chrono>
#include <thread>
#include <mutex>

const size_t TOPK = 10;

using Counter = std::map<std::string, std::size_t>;

std::string tolower(const std::string &str);

void count_words(std::istream& stream, Counter&, std::mutex &mtx);

void print_topk(std::ostream& stream, const Counter&, const size_t k);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: topk_words [FILES...]\n";
        return EXIT_FAILURE;
    }
    std::mutex mtx;
    auto start = std::chrono::high_resolution_clock::now();
    Counter freq_dict;    
    std::vector<std::thread> workers;//(argc - 1); 
    std::vector<std::ifstream> inputs;
    inputs.reserve(argc+100);
    for (int i = 1; i < argc; ++i) {
        try
        {
            inputs.push_back(std::ifstream{argv[i]});
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            std::cerr << "Failed to open file " << argv[i] << '\n';
            return EXIT_FAILURE;            
        }
        //count_words(input, freq_dict, mtx);
 /**/   workers.emplace_back(count_words, std::ref(inputs[i-1]), std::ref(freq_dict), std::ref(mtx));
    }

/**/for(auto &worker: workers){
/**/    worker.join();
/**/}
    print_topk(std::cout, freq_dict, TOPK);
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Elapsed time is " << elapsed_ms.count() << " us\n";
    size_t a = inputs.max_size();
}

std::string tolower(const std::string &str) {
    std::string lower_str;
    std::transform(std::cbegin(str), std::cend(str),
                   std::back_inserter(lower_str),
                   [](unsigned char ch) { return std::tolower(ch); });
    return lower_str;
};

void count_words(std::istream& stream, Counter& counter, std::mutex &mtx) {
    std::for_each(std::istream_iterator<std::string>(stream),
                  std::istream_iterator<std::string>(),
                  [&counter, &mtx](const std::string &d) {std::lock_guard lock(mtx); ++counter[tolower(d)]; });    
}

void print_topk(std::ostream& stream, const Counter& counter, const size_t k) {
    std::vector<Counter::const_iterator> words;
    words.reserve(counter.size());
    for (auto it = std::cbegin(counter); it != std::cend(counter); ++it) {
        words.push_back(it);
    }

    std::partial_sort(
        std::begin(words), std::begin(words) + k, std::end(words),
        [](auto lhs, auto &rhs) { return lhs->second > rhs->second; });

    std::for_each(
        std::begin(words), std::begin(words) + k,
        [&stream](const Counter::const_iterator &pair) {
            stream << std::setw(6) << pair->second << " " << pair->first
                      << '\n';
        });
}
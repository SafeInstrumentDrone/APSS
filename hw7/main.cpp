#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>
#include <thread>

#include "CRC32.hpp"
#include "IO.hpp"

/// @brief Переписывает последние 4 байта значением value
inline void replaceLastFourBytes(std::vector<char> &data, uint32_t value) {
  std::copy_n(reinterpret_cast<const char *>(&value), 4, data.end() - 4);
}

/**
 * @brief Формирует новый вектор с тем же CRC32, добавляя в конец оригинального
 * строку injection и дополнительные 4 байта
 * @details При формировании нового вектора последние 4 байта не несут полезной
 * нагрузки и подбираются таким образом, чтобы CRC32 нового и оригинального
 * вектора совпадали
 * @param original оригинальный вектор
 * @param injection произвольная строка, которая будет добавлена после данных
 * оригинального вектора
 * @return новый вектор
 */
std::vector<char> hack(const std::vector<char> &original,
                       const std::string &injection, size_t minVal, size_t maxVal, const char *out_file, bool &success) {
  const uint32_t originalCrc32 = crc32(original.data(), original.size());//v = crc32(d, 100)

  std::vector<char> result(original.size() + injection.size() + 4);
  auto it = std::copy(original.begin(), original.end(), result.begin());
  std::copy(injection.begin(), injection.end(), it);

  /*
  //  * Внимание: код ниже крайне не оптимален.
   * В качестве доп. задания устраните избыточные вычисления
   */
  //const size_t maxVal = std::numeric_limits<uint32_t>::max();
 //uint32_t orig_inj_size = original.size() + injection.size();
  //uint32_t currentCrc32 = originalCrc32;//crc32(result.data(), result.size());//;
  uint32_t currentCrc32;
  const char *bytes  = result.data()+original.size();
  size_t bytesCount = 4 + injection.size();
  //auto s = result.end()-4;
  std::cout << "thread min=" << minVal << " max=" << maxVal << std::endl;
  for (uint32_t i = minVal; i < maxVal; ++i) {
    // Заменяем последние четыре байта на значение i
    //replaceLastFourBytes(result, uint32_t(i)); 
    //uint32_t v(i);      
    std::copy_n(reinterpret_cast<char *>(&i),4, result.end()-4);

    // Вычисляем CRC32 текущего вектора result 
    currentCrc32 = crc32(bytes, bytesCount, originalCrc32);

    if(success){
          std::cout << "not success min=" << minVal << " max=" << maxVal << std::endl;   
          return result;
    }

    if (currentCrc32 == originalCrc32) {
      std::cout << "Success\n"; 
      success = true;
      writeToFile(out_file, result);
      return result;
    }
    // Отображаем прогресс
    // if (i % 1000 == 0) {
    //   std::cout << "progress: "
    //             << static_cast<double>(i)/* / static_cast<double>(maxVal)*/
    //             << std::endl;
    // }
   }
   return result;
  //throw std::logic_error("Can't hack");
}

int main(int argc, char **argv) {
  if (argc != 3) {
    std::cerr << "Call with two args: " << argv[0]
              << " <input file> <output file>\n";
    return 1;
  }

  char* a = argv[1];//"./repo.zip";
  char* b = argv[2];//"./repo_.zip";

  try {
    const std::vector<char> data = readFromFile(a);
    //std::thread()

    int t = std::thread::hardware_concurrency();
    const size_t minVal = std::numeric_limits<uint32_t>::min();
    const size_t maxVal = std::numeric_limits<uint32_t>::max();
    //std::vector<char> badData;

    auto start_time = std::chrono::system_clock::now();    
    bool success = false;
    std::vector<std::thread> thrVec;
    size_t minV;
    size_t maxV;
    for(int i = 0; i < t; i++){
      minV = (size_t)(maxVal / t)*i; 
      maxV = (size_t)(maxVal / t)*(i+1)-1;
      thrVec.push_back(std::thread{hack, std::cref(data), "He-he-he", minV, maxV, b, std::ref(success)});     
    };
    
    for(int i = 0; i < t; i++){
      thrVec.at(i).join();
    };

//    hack(data, "He-he-he", minVal, maxVal, b, std::ref(success));

    auto end_time = std::chrono::system_clock::now();
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(
			end_time - start_time);

    std::cout << "time= " << milliseconds.count() << std::endl;
    
    //writeToFile(b, badData);

  } catch (std::exception &ex) {
    std::cerr << ex.what() << '\n';
    return 2;
  }
  return 0;
}

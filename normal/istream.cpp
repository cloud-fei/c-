#include <iostream>
#include <string>
#include <vector>
#include <sstream>

int main() {
    std::string str = "drwxrwxrwx    2 200000   200000          0 Sep 08 15:57 dir1";
    std::vector<std::string> segments;
    std::stringstream ss(str);
    std::string segment;

    while (ss >> segment) {
        segments.push_back(segment);
    }

    // 输出每个段
    for (const auto& seg : segments) {
        std::cout << seg << std::endl;
    }

    return 0;
}

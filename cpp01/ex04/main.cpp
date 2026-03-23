#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char **argv) 
{
    if (argc != 3)
        return 1;

    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open())
    {
        std::cout << "open failed" << std::endl;
        return 1;
    }

    std::string outputFileName = std::string(argv[1]) + ".replace";
    std::ofstream outputFile(outputFileName.c_str());
    if (!outputFile.is_open()) {
        std::cout << "output file open failed" << std::endl;
        return 1;
    }

    std::string line;
    std::string s1 = argv[2];
    std::string s2 = argv[3];
    while (std::getline(inputFile, line)) {
        std::string result;
        size_t pos = 0;
        size_t found;
        while ((found = line.find(s1, pos)) != std::string::npos) {
            result += line.substr(pos, found - pos);
            result += s2;
            pos = found + s1.length();
        }
        result += line.substr(pos);
        outputFile << result << std::endl;
    }

    inputFile.close();
    outputFile.close();
    return 0;
}

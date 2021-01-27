//
// Created by Aron on 2020-11-09.
//

#ifndef CODE_FILEHANDLER_H
#define CODE_FILEHANDLER_H

#include <vector>

class FileHandler {
public:
    FileHandler();
    ~FileHandler();

    std::vector<std::vector<int>> read_from_file(const char* datafile);
    void print_matrix(std::vector<std::vector<int>> matrix);
};


#endif //CODE_FILEHANDLER_H

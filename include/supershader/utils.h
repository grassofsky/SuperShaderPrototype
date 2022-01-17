#pragma once

#include <fstream>

std::string ReadFileContent(const std::string& strFilename)
{
    std::string content;
    std::ifstream ifile;
    ifile.open(strFilename, std::ios::in | std::ios::binary);
    if (ifile.is_open())
    {
        ifile.seekg(0, std::ios::end);
        content.resize(ifile.tellg());
        ifile.seekg(0, std::ios::beg);
        ifile.read(&content[0], content.size());
        ifile.close();
    }

    return std::move(content);
}
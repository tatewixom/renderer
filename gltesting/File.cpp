#include "File.h"

#include <sstream>
#include <fstream>
#include <iostream>

std::optional<std::string> File::retrieve(std::string_view fileName)
{
  std::ifstream in_file(fileName.data());

  if (!in_file.is_open())
  {
    std::cerr << "ERROR::FILE::RETRIEVE::FAILURE_IN_OPENING_FILE\n";
    return std::nullopt;
  }

  std::ostringstream buffer;
  buffer << in_file.rdbuf();
  return buffer.str();
}
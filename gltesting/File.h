#pragma once

#include <string>
#include <string_view>
#include <optional>

namespace File
{
  std::optional<std::string> retrieve(std::string_view fileName);
}
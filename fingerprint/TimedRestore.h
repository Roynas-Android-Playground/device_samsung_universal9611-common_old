#pragma once

#include <string>

class TimedRestore {
  std::string saved_value, filename;
 public:
  TimedRestore() = delete;
  TimedRestore(const std::string& filename);
  ~TimedRestore();

  void set(const std::string& value);
};

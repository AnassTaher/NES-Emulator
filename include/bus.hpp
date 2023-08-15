#pragma once
#include <vector>
#include <cstdint>

class Bus{
public:
  Bus();

  std::vector<uint8_t> ram;

  uint8_t read(uint16_t addr);
  void write(uint16_t addr, uint8_t data);
  
};


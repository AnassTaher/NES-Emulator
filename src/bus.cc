#include "bus.hpp"

Bus::Bus() {
  ram.resize(0x10000);
  for(uint8_t& num : ram) 
    num = 0x00;
}

uint8_t Bus::read(uint16_t addr) {
  
  // if(addr < 0x2000)
  //   return ram[addr & 0x07FF];
  
  // if(addr >= 0x2000 && addr < 0x4000)
  //   return ppu.read(addr & 0x0007);
  return ram[addr];
}

void Bus::write(uint16_t addr, uint8_t data) {

  // mirror zero page
  // if(addr < 0x2000)
  //   ram[addr & 0x07FF] = data;
  
  // if(addr >= 0x2000 && addr < 0x4000)
  //   ppu.write(addr & 0x0007, data);

  
  ram[addr] = data;
}
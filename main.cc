#include <iostream>
#include "cpu.hpp"

using namespace std;

int main(){

    CPU cpu;

    if(!cpu.setup()) 
        return -1;
    cpu.reset();
    cpu.PC = 0xC000;
    cpu.run();

    uint8_t lower = cpu.ram[0x2];
    uint8_t upper = cpu.ram[0x3];
    cout << "0x2h: " << hex << uppercase << (int)lower << endl;
    cout << "0x3h: " << hex << uppercase << (int)upper << endl;


    return 0;
}
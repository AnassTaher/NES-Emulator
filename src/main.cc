#include <iostream>
#include "cpu.hpp"

using namespace std;

int main(int argc, char** argv){

	if(argc < 2){
		std::cout << "Usage: " << argv[0] << " <path to rom>" << std::endl;
		return -1;
	}

	CPU cpu;
	FILE* fp = fopen(argv[1], "rb");
	cpu.loadRom(fp);
	cpu.reset();
	cpu.PC = 0xC000;
	cpu.run();
	
	uint8_t lower = cpu.ram[0x2];
	uint8_t upper = cpu.ram[0x3];
	cout << "0x2h: " << hex << uppercase << (int)lower << endl;
	cout << "0x3h: " << hex << uppercase << (int)upper << endl;

	fclose(fp);
	return 0;
}
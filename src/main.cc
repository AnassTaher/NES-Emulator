#include <iostream>
#include "cpu.hpp"
#include <stdlib.h>

using namespace std;

void printProgram(vector<uint8_t> ram){

	for(size_t i = 0xC000; i < ram.size(); i++){
		printf("%02X ", ram[i]);
	}
	printf("\n");
}

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
	// printProgram(cpu.ram);
	cpu.run();

	fclose(fp);
	return 0;
}
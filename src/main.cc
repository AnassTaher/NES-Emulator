#include <iostream>
#include "cpu.hpp"

using namespace std;

uint64_t getFileSize(FILE* fp){
	fseek(fp, 0, SEEK_END);
	uint64_t size = ftell(fp);
	rewind(fp);
	return size;
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
	cpu.run();

	fclose(fp);
	return 0;
}
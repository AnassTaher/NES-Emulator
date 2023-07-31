#include "cpu.hpp"
#include "common.hpp"
#include <bitset>
#include <iomanip>
#include <sstream>

using namespace std;

void CPU::readHeader(FILE* fp){
	fread(&header, sizeof(CPU::Header), 1, fp);
}

void CPU::setFlag(Flags flag, bool v){
  if(v)
    status = status | (v << flag);
  else
    status = status & ~(1 << flag);
}

bool CPU::getFlag(Flags flag){
  return status & (1 << flag);
}

void CPU::toggleFlag(Flags flag){
  status = status ^ (1 << flag);
}

void CPU::loadRom(FILE* fp){

	readHeader(fp);

	uint64_t size = (header.prg_rom_size * 0x4000);
	uint8_t* program = new uint8_t[size];
	fread(program, sizeof(uint8_t), size, fp);

	for(uint64_t i = 0; i < size; i++){
		write(0x8000 + i, program[i]);
		// mirror only if one 16k bank
		if(header.prg_rom_size == 1) write(0xC000 + i, program[i]);
	}

}

void CPU::printStatus(){
  cout << "Status: " << bitset<8>(status) << endl;
}

void CPU::printHex(string s, uint16_t to_print, string delimiter){
	cout << s << setw(2) << setfill('0') << hex << uppercase << to_print << delimiter;
}

void CPU::log(){
	
	printHex("", log_pc, "  ");
	int len_opcodes = 9;
	string s = "";
	
	stringstream ss;
	ss << setw(2) << setfill('0') << hex << uppercase << int(opcode) << " ";
	for(int i = 0; i < disass_map[opcode] - 1; i++){
		ss << setw(2) << setfill('0') << right << hex << uppercase << int(read(log_pc + i + 1)) << " ";
	}
	s += ss.str();
	
	cout << setw(len_opcodes + 1)<< setfill(' ') << left << s;
	s = "";
	s += lookup[opcode].name + " ";
	ss = stringstream();
	ss << flush;
	if(disass_map[opcode] == 1) ss << setw(2) << setfill(' ') << " ";
	else  ss << setw(2) << setfill('0') << hex << uppercase << (int)address << " ";
	s += ss.str();
	cout << setw(10) << setfill(' ') << left << s;

	cout << setw(10) << setfill(' ') << left << " " \
	<< "A:" << setw(2) << setfill('0') << hex << uppercase << (int)A << " " \
	<< "X:" << setw(2) << setfill('0') << hex << uppercase << (int)X << " " \
	<< "Y:" << setw(2) << setfill('0') << hex << uppercase << (int)Y << " " \
	<< "P:" << setw(2) << setfill('0') << hex << uppercase << (int)status << " " \
	<< "SP:" << setw(2) << setfill('0') << (int)SP << " " << flush \
	<< "CYC: " << dec << (int)cycles;	\
	cout << endl;
}

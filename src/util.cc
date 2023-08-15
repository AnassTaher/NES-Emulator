#include "cpu.hpp"
#include <iostream>
#include <iomanip>

using namespace std;

uint8_t CPU::read(uint16_t a){
	return bus.read(a);
}

void CPU::write(uint16_t a, uint8_t d){
	bus.write(a, d);
}

void CPU::push(uint8_t v){
	write(0x0100 + SP, v);
	SP--;
}

uint8_t CPU::pop(){
	SP++;
	return read(0x0100 + SP);
}

void CPU::branch(){
	cycles++;
	address = PC + rel;
	
	if((address & 0xFF00) != (PC & 0xFF00))
		cycles++;
	
	PC = address;
}

bool CPU::getFlag(StatusFlags f) const{
	return status & (1 << f);
}

void CPU::setFlag(StatusFlags f, bool v){
  if(v)
    status = status | (v << f);
  else
    status = status & ~(1 << f);
}

bool CPU::setup(){
	std::cout << "Enter file:";
	std::string inputFile;
	std::cin >> inputFile;

	std::cout << "Debug? (y/n):";
	std::string flag;
	std::cin >> flag;
    std::cout << endl;
	if(flag == "y") debug = true;

	FILE* fp = fopen(("tests/" + inputFile).c_str(), "rb");
	if(fp == nullptr){
			std::cout << "Could not find file: " << inputFile << "\n";
			return false;
	}
	loadRom(fp);
	fclose(fp);
	return true;
}

bool CPU::executed() const{
	return cycles == 0;
}

void CPU::readHeader(FILE* fp){
	fread(&header, sizeof(CPU::Header), 1, fp);
}

void CPU::loadRom(FILE* fp){

	readHeader(fp);

	uint64_t size = (header.prg_rom_size * 0x4000);
	cout << "PRG ROM size: " << size << "\n";
	uint8_t* program = new uint8_t[size];
	fread(program, sizeof(uint8_t), size, fp);

	for(uint64_t i = 0; i < size; i++){
		write(0x8000 + i, program[i]);
		// mirror only if one 16k bank
		if(header.prg_rom_size == 1) write(0xC000 + i, program[i]);
	}
	// print the first 3 bytes
}

void CPU::log(){
	
	cout << setw(4) << setfill('0') << hex << uppercase << (int)log_pc << " ";
	int len_opcodes = 9;
	string s = "";
	
	stringstream ss;
	ss << setw(2) << setfill('0') << hex << uppercase << int(opcode) << " ";
	int len = disass_bytes();
	for(int i = 0; i < len - 1; i++){
		ss << setw(2) << setfill('0') << right << hex << uppercase << (int)read(log_pc + i + 1) << " ";
	}
	s += ss.str();
	
	cout << setw(len_opcodes + 1)<< setfill(' ') << left << s;
	s = lookup[opcode].name + " ";
	ss = stringstream();
	if(len == 1) ss << setw(2) << setfill(' ') << " ";
	else  ss << setw(2) << setfill('0') << hex << uppercase << (int)address << " ";
	s += ss.str();
	cout << setw(10) << setfill(' ') << left << s;

	cout << setw(10) << setfill(' ') << left << " " \
	<< "A:" << setw(2) << setfill('0') << right << hex << uppercase << (int)A << " " \
	<< "X:" << setw(2) << setfill('0') << hex << uppercase << (int)X << " " \
	<< "Y:" << setw(2) << setfill('0') << hex << uppercase << (int)Y << " " \
	<< "P:" << setw(2) << setfill('0') << hex << uppercase << (int)status << " " \
	<< "SP:" << setw(2) << setfill('0') << (int)SP << " " << flush \
	<< "CYC:" << dec << (int)log_cycles;	\
	cout << endl; 
}

uint8_t CPU::disass_bytes(){

	void(CPU::*adr)() = lookup[opcode].addr;
	
	if(adr == &CPU::IMP){
		return 1;
	}
	else if(adr == &CPU::IMM){
		return 2;
	}
	else if(adr == &CPU::ZP0){
		return 2;
	}
	else if(adr == &CPU::ZPX){
		return 2;
	}
	else if(adr == &CPU::ZPY){
		return 2;
	}
	else if(adr == &CPU::IZX){
		return 2;
	}
	else if(adr == &CPU::IZY){
		return 2;
	}
	else if(adr == &CPU::ABS){
		return 3;
	}
	else if(adr == &CPU::ABX){
		return 3;
	}
	else if(adr == &CPU::ABY){
		return 3;
	}
	else if(adr == &CPU::IND){
		return 3;
	}
	else if(adr == &CPU::REL){
		return 2;
	}

	return 0;
}

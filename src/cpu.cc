#include "cpu.hpp"
#include <bitset>
#include <iomanip>
#include <sstream>

using namespace std;

CPU::CPU(){
  // Initialize lookup table, stole this from https://www.youtube.com/watch?v=8XmxKPJDGU0&t=1072s
  using a = CPU;
	lookup = 
	{
		{ "BRK", &a::BRK, &a::IMM, 7 },{ "ORA", &a::ORA, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 3 },{ "ORA", &a::ORA, &a::ZP0, 3 },{ "ASL", &a::ASL, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PHP", &a::PHP, &a::IMP, 3 },{ "ORA", &a::ORA, &a::IMM, 2 },{ "ASL", &a::ASL, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::NOP, &a::IMP, 4 },{ "ORA", &a::ORA, &a::ABS, 4 },{ "ASL", &a::ASL, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BPL", &a::BPL, &a::REL, 2 },{ "ORA", &a::ORA, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "ORA", &a::ORA, &a::ZPX, 4 },{ "ASL", &a::ASL, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "CLC", &a::CLC, &a::IMP, 2 },{ "ORA", &a::ORA, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "ORA", &a::ORA, &a::ABX, 4 },{ "ASL", &a::ASL, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
		{ "JSR", &a::JSR, &a::ABS, 6 },{ "AND", &a::AND, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "BIT", &a::BIT, &a::ZP0, 3 },{ "AND", &a::AND, &a::ZP0, 3 },{ "ROL", &a::ROL, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PLP", &a::PLP, &a::IMP, 4 },{ "AND", &a::AND, &a::IMM, 2 },{ "ROL", &a::ROL, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "BIT", &a::BIT, &a::ABS, 4 },{ "AND", &a::AND, &a::ABS, 4 },{ "ROL", &a::ROL, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BMI", &a::BMI, &a::REL, 2 },{ "AND", &a::AND, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "AND", &a::AND, &a::ZPX, 4 },{ "ROL", &a::ROL, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "SEC", &a::SEC, &a::IMP, 2 },{ "AND", &a::AND, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "AND", &a::AND, &a::ABX, 4 },{ "ROL", &a::ROL, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
		{ "RTI", &a::RTI, &a::IMP, 6 },{ "EOR", &a::EOR, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 3 },{ "EOR", &a::EOR, &a::ZP0, 3 },{ "LSR", &a::LSR, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PHA", &a::PHA, &a::IMP, 3 },{ "EOR", &a::EOR, &a::IMM, 2 },{ "LSR", &a::LSR, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "JMP", &a::JMP, &a::ABS, 3 },{ "EOR", &a::EOR, &a::ABS, 4 },{ "LSR", &a::LSR, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BVC", &a::BVC, &a::REL, 2 },{ "EOR", &a::EOR, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "EOR", &a::EOR, &a::ZPX, 4 },{ "LSR", &a::LSR, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "CLI", &a::CLI, &a::IMP, 2 },{ "EOR", &a::EOR, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "EOR", &a::EOR, &a::ABX, 4 },{ "LSR", &a::LSR, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
		{ "RTS", &a::RTS, &a::IMP, 6 },{ "ADC", &a::ADC, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 3 },{ "ADC", &a::ADC, &a::ZP0, 3 },{ "ROR", &a::ROR, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PLA", &a::PLA, &a::IMP, 4 },{ "ADC", &a::ADC, &a::IMM, 2 },{ "ROR", &a::ROR, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "JMP", &a::JMP, &a::IND, 5 },{ "ADC", &a::ADC, &a::ABS, 4 },{ "ROR", &a::ROR, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BVS", &a::BVS, &a::REL, 2 },{ "ADC", &a::ADC, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "ADC", &a::ADC, &a::ZPX, 4 },{ "ROR", &a::ROR, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "SEI", &a::SEI, &a::IMP, 2 },{ "ADC", &a::ADC, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "ADC", &a::ADC, &a::ABX, 4 },{ "ROR", &a::ROR, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
		{ "???", &a::NOP, &a::IMP, 2 },{ "STA", &a::STA, &a::IZX, 6 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 6 },{ "STY", &a::STY, &a::ZP0, 3 },{ "STA", &a::STA, &a::ZP0, 3 },{ "STX", &a::STX, &a::ZP0, 3 },{ "???", &a::XXX, &a::IMP, 3 },{ "DEY", &a::DEY, &a::IMP, 2 },{ "???", &a::NOP, &a::IMP, 2 },{ "TXA", &a::TXA, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "STY", &a::STY, &a::ABS, 4 },{ "STA", &a::STA, &a::ABS, 4 },{ "STX", &a::STX, &a::ABS, 4 },{ "???", &a::XXX, &a::IMP, 4 },
		{ "BCC", &a::BCC, &a::REL, 2 },{ "STA", &a::STA, &a::IZY, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 6 },{ "STY", &a::STY, &a::ZPX, 4 },{ "STA", &a::STA, &a::ZPX, 4 },{ "STX", &a::STX, &a::ZPY, 4 },{ "???", &a::XXX, &a::IMP, 4 },{ "TYA", &a::TYA, &a::IMP, 2 },{ "STA", &a::STA, &a::ABY, 5 },{ "TXS", &a::TXS, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 5 },{ "???", &a::NOP, &a::IMP, 5 },{ "STA", &a::STA, &a::ABX, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "???", &a::XXX, &a::IMP, 5 },
		{ "LDY", &a::LDY, &a::IMM, 2 },{ "LDA", &a::LDA, &a::IZX, 6 },{ "LDX", &a::LDX, &a::IMM, 2 },{ "???", &a::XXX, &a::IMP, 6 },{ "LDY", &a::LDY, &a::ZP0, 3 },{ "LDA", &a::LDA, &a::ZP0, 3 },{ "LDX", &a::LDX, &a::ZP0, 3 },{ "???", &a::XXX, &a::IMP, 3 },{ "TAY", &a::TAY, &a::IMP, 2 },{ "LDA", &a::LDA, &a::IMM, 2 },{ "TAX", &a::TAX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "LDY", &a::LDY, &a::ABS, 4 },{ "LDA", &a::LDA, &a::ABS, 4 },{ "LDX", &a::LDX, &a::ABS, 4 },{ "???", &a::XXX, &a::IMP, 4 },
		{ "BCS", &a::BCS, &a::REL, 2 },{ "LDA", &a::LDA, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 5 },{ "LDY", &a::LDY, &a::ZPX, 4 },{ "LDA", &a::LDA, &a::ZPX, 4 },{ "LDX", &a::LDX, &a::ZPY, 4 },{ "???", &a::XXX, &a::IMP, 4 },{ "CLV", &a::CLV, &a::IMP, 2 },{ "LDA", &a::LDA, &a::ABY, 4 },{ "TSX", &a::TSX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 4 },{ "LDY", &a::LDY, &a::ABX, 4 },{ "LDA", &a::LDA, &a::ABX, 4 },{ "LDX", &a::LDX, &a::ABY, 4 },{ "???", &a::XXX, &a::IMP, 4 },
		{ "CPY", &a::CPY, &a::IMM, 2 },{ "CMP", &a::CMP, &a::IZX, 6 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "CPY", &a::CPY, &a::ZP0, 3 },{ "CMP", &a::CMP, &a::ZP0, 3 },{ "DEC", &a::DEC, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "INY", &a::INY, &a::IMP, 2 },{ "CMP", &a::CMP, &a::IMM, 2 },{ "DEX", &a::DEX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "CPY", &a::CPY, &a::ABS, 4 },{ "CMP", &a::CMP, &a::ABS, 4 },{ "DEC", &a::DEC, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BNE", &a::BNE, &a::REL, 2 },{ "CMP", &a::CMP, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "CMP", &a::CMP, &a::ZPX, 4 },{ "DEC", &a::DEC, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "CLD", &a::CLD, &a::IMP, 2 },{ "CMP", &a::CMP, &a::ABY, 4 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "CMP", &a::CMP, &a::ABX, 4 },{ "DEC", &a::DEC, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
		{ "CPX", &a::CPX, &a::IMM, 2 },{ "SBC", &a::SBC, &a::IZX, 6 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "CPX", &a::CPX, &a::ZP0, 3 },{ "SBC", &a::SBC, &a::ZP0, 3 },{ "INC", &a::INC, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "INX", &a::INX, &a::IMP, 2 },{ "SBC", &a::SBC, &a::IMM, 2 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::SBC, &a::IMP, 2 },{ "CPX", &a::CPX, &a::ABS, 4 },{ "SBC", &a::SBC, &a::ABS, 4 },{ "INC", &a::INC, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BEQ", &a::BEQ, &a::REL, 2 },{ "SBC", &a::SBC, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "SBC", &a::SBC, &a::ZPX, 4 },{ "INC", &a::INC, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "SED", &a::SED, &a::IMP, 2 },{ "SBC", &a::SBC, &a::ABY, 4 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "SBC", &a::SBC, &a::ABX, 4 },{ "INC", &a::INC, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
	};

	ram.resize(0xFFFF + 1);

	for(uint8_t& num : ram)
		num = 0;

	// bytes is a map that contains each opcode and how many bytes that opcode is

	disass_map = { 
		{0x69, 2}, {0x65, 2}, {0x75, 2}, {0x6D, 3}, {0x7D, 3}, {0x79, 3}, {0x61, 2}, {0x71, 2},	
		{0x29, 2}, {0x25, 2}, {0x35, 2}, {0x2D, 3}, {0x3D, 3}, {0x39, 3}, {0x21, 2}, {0x31, 2},
		{0x0A, 1}, {0x06, 2}, {0x16, 2}, {0x0E, 3}, {0x1E, 3},
		{0x90, 2},
		{0xB0, 2},
		{0xF0, 2},
		{0x24, 2}, {0x2C, 3},
		{0x30, 2},
		{0xD0, 2},
		{0x10, 2},
		{0x00, 1},
		{0x50, 2},
		{0x70, 2},
		{0x18, 1},
		{0xD8, 1},
		{0x58, 1},
		{0xB8, 1},
		{0xCA, 1},
		{0x88, 1},
		{0xE8, 1},
		{0xC8, 1},
		{0xC9, 2}, {0xC5, 2}, {0xD5, 2}, {0xCD, 3}, {0xDD, 3}, {0xD9, 3}, {0xC1, 2}, {0xD1, 2},
		{0xE0, 2}, {0xE4, 2}, {0xEC, 3},
		{0xC0, 2}, {0xC4, 2}, {0xCC, 3},
		{0xC6, 2}, {0xD6, 2}, {0xCE, 3}, {0xDE, 3},
		{0x49, 2}, {0x45, 2}, {0x55, 2}, {0x4D, 3}, {0x5D, 3}, {0x59, 3}, {0x41, 2}, {0x51, 2},
		{0x4A, 1}, {0x46, 2}, {0x56, 2}, {0x4E, 3}, {0x5E, 3},
		{0xE6, 2}, {0xF6, 2}, {0xEE, 3}, {0xFE, 3},
		{0xE9, 2}, {0xE5, 2}, {0xF5, 2}, {0xED, 3}, {0xFD, 3}, {0xF9, 3}, {0xE1, 2}, {0xF1, 2},
		{0xEA, 1},
		{0x4C, 3}, {0x6C, 3},
		{0x20, 3},
		{0x40, 1},
		{0x60, 1},
		{0x48, 1},
		{0x08, 1},
		{0x68, 1},
		{0x28, 1},
		{0x86, 2}, {0x96, 2}, {0x8E, 3}
	};


}

void CPU::reset(){
	status = 0x34;
	A = X = Y = 0;
	SP = 0xFD;
	PC = ram[0xFFFC] | (ram[0xFFFD] << 8);
}

uint8_t CPU::read(uint16_t addr){
	return ram[addr];
}

void CPU::write(uint16_t addr, uint8_t data){
	ram[addr] = data;
}

void CPU::run(){
	int i = 0;
	while(i < 5){
		// if(cycles == 0) i++;
		cycle();
		// cycles--;
		i++;
	}
}

void CPU::cycle(){

	// if(cycles != 0) return;

	opcode = read(PC);
	PC++;
	Instruct ins = lookup[opcode];

	(this->*ins.addr)();
	log();
	fetched = fetch();
	(this->*ins.op)();
	cycles += ins.cycles;
	PC += disass_map[opcode] - 1;
}

uint8_t CPU::fetch(){
	return read(address);
}

void CPU::readHeader(FILE* fp){
	fread(&header, sizeof(CPU::Header), 1, fp);
}

void CPU::setFlag(Flags flag, bool value){
  status = status | (value << flag);
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
	// C000  4C F5 C5  JMP $C5F5                       A:00 X:00 Y:00 P:24 SP:FD PPU:  0, 21 CYC:7

	printHex("", PC - 1, "  ");
	int len_opcodes = 9;
	string s = "";
	
	stringstream ss;
	ss << hex << uppercase << int(opcode) << " ";
	for(int i = 0; i < disass_map[opcode] - 1; i++){
		ss << hex << uppercase << int(read(PC + i)) << " ";
	}
	s += ss.str();
	
	cout << setw(len_opcodes) << setfill(' ') << left << s;
	s = "";
	s += lookup[ram[PC - 1]].name + " ";
	ss = stringstream();
	ss << flush;
	if(address == 0) ss << setw(2) << setfill('0') << hex << uppercase << (int)address << " ";
	else ss << hex << uppercase << (int)address << " ";
	s += ss.str();
	cout << setw(10) << setfill(' ') << left << s;

	cout << setw(10) << setfill(' ') << left << " " \
	<< "A:" << setw(2) << setfill('0') << hex << uppercase << (int)A << " " \
	<< "X:" << setw(2) << setfill('0') << hex << uppercase << (int)X << " " \
	<< "Y:" << setw(2) << setfill('0') << hex << uppercase << (int)Y << " " \
	<< "P:" << setw(2) << status << " " \
	<< "SP:" << setw(2) << setfill('0') << (int)SP << " " << flush \
	<< "CYC: " << dec << (int)cycles;	\
	cout << endl;
}

// Addressing Modes
// https://www.nesdev.org/wiki/CPU_addressing_modes
// https://www.nesdev.org/obelisk-6502-guide/addressing.html
void CPU::IMP(){

}

void CPU::IMM(){
	address = PC;
}

void CPU::ZP0(){
	address = read(PC);
}

void CPU::ZPX(){
	address = (read(PC) + X) % 256;
}

void CPU::ZPY(){
	address = (read(PC) + Y) % 256;
}

void CPU::REL(){

}

void CPU::ABS(){
	address = read(PC) | (read(PC + 1) << 8);
}

void CPU::ABX(){
	address = (read(PC) | (read(PC + 1) << 8)) + X;
}

void CPU::ABY(){
	address = (read(PC) | (read(PC + 1) << 8)) + Y;
}

void CPU::IND(){
	address = read((read(PC)) % 256) | read((read(PC + 1)) % 256) << 8;
}

void CPU::IZX(){
	address = read((read(PC) + X) % 256) | read((read(PC + 1) + X) % 256) << 8;
}

void CPU::IZY(){
	address = read((read(PC) + Y) % 256) | read((read(PC + 1) + Y) % 256) << 8;
}

// Instructions

void CPU::ADC(){
   
}

void CPU::AND(){
   
}

void CPU::ASL(){
   
}

void CPU::BCC(){
   
}

void CPU::BCS(){
   
}

void CPU::BEQ(){
   
}

void CPU::BIT(){
   
}

void CPU::BMI(){
   
}

void CPU::BNE(){
   
}

void CPU::BPL(){
   
}

void CPU::BRK(){
   
}

void CPU::BVC(){
   
}

void CPU::BVS(){
   
}

void CPU::CLC(){
   
}

void CPU::CLD(){
   
}

void CPU::CLI(){
   
}

void CPU::CLV(){
   
}

void CPU::CMP(){
   
}

void CPU::CPX(){
   
}

void CPU::CPY(){
   
}

void CPU::DEC(){
   
}

void CPU::DEX(){
   
}

void CPU::DEY(){
   
}

void CPU::EOR(){
   
}

void CPU::INC(){
   
}

void CPU::INX(){
   
}

void CPU::INY(){
   
}

void CPU::JMP(){
  PC = address;
}

void CPU::JSR(){
   
}

void CPU::LDA(){
  A = fetched;
	setFlag(Flags::Z, A == 0);
	setFlag(Flags::N, A & (1 << 7));
}

void CPU::LDX(){
	X = fetched;
	setFlag(Flags::Z, X == 0);
	setFlag(Flags::N, X & (1 << 7));
}

void CPU::LDY(){
	Y = fetched;
	setFlag(Flags::Z, Y == 0);
	setFlag(Flags::N, Y & (1 << 7));
}

void CPU::LSR(){
   
}

void CPU::NOP(){
   
}

void CPU::ORA(){
   
}

void CPU::PHA(){
   
}

void CPU::PHP(){
   
}

void CPU::PLA(){
   
}

void CPU::PLP(){
   
}

void CPU::ROL(){
   
}

void CPU::ROR(){
   
}

void CPU::RTI(){
   
}

void CPU::RTS(){
   
}

void CPU::SBC(){
   
}

void CPU::SEC(){
   
}

void CPU::SED(){
   
}

void CPU::SEI(){
   
}

void CPU::STA(){
   
}

void CPU::STX(){
	ram[address] = X;
}

void CPU::STY(){
   
}

void CPU::TAX(){
   
}

void CPU::TAY(){
   
}

void CPU::TSX(){
   
}

void CPU::TXA(){
   
}

void CPU::TXS(){
   
}

void CPU::TYA(){
   
}

void CPU::XXX(){

}





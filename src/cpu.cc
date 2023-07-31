#include "cpu.hpp"
#include <iomanip>


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

	// map that contains how many bytes each opcode is

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
		{0xC9, 2}, {0xC5, 2}, {0xD5, 2}, {0xCD, 3}, {0xDD, 3}, {0xD9, 3}, {0xC1, 2}, {0xD1, 2},
		{0xE0, 2}, {0xE4, 2}, {0xEC, 3}, 
		{0xC0, 2}, {0xC4, 2}, {0xCC, 3}, 
		{0xC6, 2}, {0xD6, 2}, {0xCE, 3}, {0xDE, 3}, 
		{0xCA, 1},
		{0x88, 1},
		{0x49, 2}, {0x45, 2}, {0x55, 2}, {0x4D, 3}, {0x5D, 3}, {0x59, 3}, {0x41, 2}, {0x51, 2},
		{0xE6, 2}, {0xF6, 2}, {0xEE, 3}, {0xFE, 3},
		{0xE8, 1},
		{0xC8, 1},
		{0x4C, 3}, {0x6C, 3},
		{0x20, 3},
		{0xA9, 2}, {0xA5, 2}, {0xB5, 2}, {0xAD, 3}, {0xBD, 3}, {0xB9, 3}, {0xA1, 2}, {0xB1, 2},
		{0xA2, 2}, {0xA6, 2}, {0xB6, 2}, {0xAE, 3}, {0xBE, 3},
		{0xA0, 2}, {0xA4, 2}, {0xB4, 2}, {0xAC, 3}, {0xBC, 3}, 
		{0x4A, 1}, {0x46, 2}, {0x56, 2}, {0x4E, 3}, {0x5E, 3},
		{0xEA, 1},
		{0x09, 2}, {0x05, 2}, {0x15, 2}, {0x0D, 3}, {0x1D, 3}, {0x19, 3}, {0x01, 2}, {0x11, 2},
		{0x48, 1},
		{0x08, 1},
		{0x68, 1},
		{0x28, 1},
		{0x2A, 1}, {0x26, 2}, {0x36, 2}, {0x2E, 3}, {0x3E, 3},
		{0x6A, 1}, {0x66, 2}, {0x76, 2}, {0x6E, 3}, {0x7E, 3},
		{0x40, 1},
		{0x60, 1},
		{0xE9, 2}, {0xE5, 2}, {0xF5, 2}, {0xED, 3}, {0xFD, 3}, {0xF9, 3}, {0xE1, 2}, {0xF1, 2},
		{0x38, 1},
		{0xF8, 1},
		{0x78, 1},
		{0x85, 2}, {0x95, 2}, {0x8D, 3}, {0x9D, 3}, {0x99, 3}, {0x81, 2}, {0x91, 2},
		{0x86, 2}, {0x96, 2}, {0x8E, 3},
		{0x84, 2}, {0x94, 2}, {0x8C, 3},
		{0xAA, 1},
		{0xA8, 1},
		{0xBA, 1},
		{0x8A, 1},
		{0x9A, 1},
		{0x98, 1}

	};

}

void CPU::reset(){
	status = 0x0000;
	setFlag(U, true);
	setFlag(I, true); // remove this later, its only for nestest
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

void CPU::push(uint8_t data){
	write(0x100 + SP, data);
	SP--;
}

uint8_t CPU::pop(){
	SP++;
	return read(0x100 + SP);
}

void CPU::run(){
	int i = 0;
	while(i < 2000){
		// if(cycles == 0) i++;
		cycle();
		// cycles--;
		i++;
	}
}

void CPU::cycle(){

	// if(cycles != 0) return;

	opcode = read(PC);
	log_pc = PC;
	PC++;
	Instruct ins = lookup[opcode];
	(this->*ins.addr)();
	fetched = fetch();

	log();
	(this->*ins.op)();

	if(ins.name != "JMP" && ins.name != "JSR" && ins.name != "RTS" && ins.name != "RTI"){
		PC += (disass_map[opcode] - 1);
	}
	cycles += ins.cycles;
}

uint8_t CPU::fetch(){
	if(disass_map[opcode] == 1) return A;
	return read(address);
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
	address = (read(PC) + X);
}

void CPU::ZPY(){
	address = (read(PC) + Y);
}

void CPU::REL(){
	address = PC;
}

void CPU::ABS(){
	address = read(PC) | (read(PC + 1) << 8);
}

void CPU::ABX(){
	address = (read(PC) | (read(PC + 1) << 8)) + X;
	
	if ((address & 0xFF00) != (read(PC + 1) << 8)) 
		page_crossed = true;
}

void CPU::ABY(){
	address = (read(PC) | (read(PC + 1) << 8)) + Y;

	if ((address & 0xFF00) != (read(PC + 1) << 8)) 
		page_crossed = true;
}

void CPU::IND(){

	uint16_t ptr = (read(PC) | read(PC + 1) << 8);

	// https://www.nesdev.org/6502bugs.txt
	if(read(PC) == 0x00FF) // if at the end of a page
		address = read(ptr) | (read(ptr & 0xFF00) << 8);
	else
		address = read(ptr) | read(ptr + 1) << 8;

}

void CPU::IZX(){
	address = (read(PC + X) | read(PC + X + 1) << 8);
}

void CPU::IZY(){
	address = (read(PC + Y) | read(PC + Y + 1) << 8);

	if((address & 0xFF00) != (read(PC + 1) << 8)) 
		page_crossed = true;
}

// Instructions

void CPU::ADC(){

	uint16_t sum = A + fetched + getFlag(C);
	setFlag(C, sum > 0xFF);
	setFlag(N, sum & (1 << 7));
	setFlag(V, (A ^ sum) & (fetched ^ sum) & 0x80);

	A = sum & 0xFF; // only keep the lower 8 bits
	setFlag(Z, A == 0);
}

void CPU::AND(){
	A &= fetched;
	setFlag(Z, A == 0);
	setFlag(N, A & (1 << 7));
}

void CPU::ASL(){
	uint8_t	temp = fetched;
	
	setFlag(C, temp & (1 << 7));
	temp <<= 1;
	setFlag(Z, temp == 0);
	setFlag(N, temp & (1 << 7));

	if(opcode == 0x0A) A = temp;
	else write(address, temp);

}

void CPU::BCC(){
	if(getFlag(C))
		return;

	cycles++;
	uint16_t rel = address + fetched;
	//check if we're on another page by checking if the high byte is the same, every page is 0xFF bytes
	if((rel & 0xFF00) != (PC & 0xFF00)) 
		cycles++;

	PC = rel;
}

void CPU::BCS(){
	if(!getFlag(C))
		return;

	cycles++;
	uint16_t rel = address + fetched;
	if((rel & 0xFF00) != (PC & 0xFF00))
		cycles++;

	PC = rel;
}

void CPU::BEQ(){
	if(!getFlag(Z))
		return;

	cycles++;
	uint16_t rel = address + fetched;
	if((rel & 0xFF00) != (PC & 0xFF00))
		cycles++;

	PC = rel;
}

void CPU::BIT(){
  setFlag(Z, (A & fetched) == 0);
	setFlag(V, fetched & (1 << 6));
	setFlag(N, fetched & (1 << 7));
}

void CPU::BMI(){
  if(!getFlag(N))
		return;

	cycles++;
	uint16_t rel = address + fetched;

	if((rel & 0xFF00) != (PC & 0xFF00))
		cycles++;

	PC = rel;
}

void CPU::BNE(){
  if(getFlag(Z))
		return;

	cycles++;
	uint16_t rel = address + fetched;
	
	if((rel & 0xFF00) != (PC & 0xFF00))
		cycles++;

	PC = rel;
}

void CPU::BPL(){
  if(getFlag(N))
		return;

	cycles++;
	uint16_t rel = address + fetched;

	if((rel & 0xFF00) != (PC & 0xFF00))
		cycles++;

	PC = rel;
}

void CPU::BRK(){
   
}

void CPU::BVC(){
  if(getFlag(V))
		return;

	cycles++;
	uint16_t rel = address + fetched;

	if((rel & 0xFF00) != (PC & 0xFF00))
		cycles++;

	PC = rel;
}

void CPU::BVS(){
  if(!getFlag(V))
		return;

	cycles++;
	uint16_t rel = address + fetched;

	if((rel & 0xFF00) != (PC & 0xFF00))
		cycles++;

	PC = rel;
}

void CPU::CLC(){
	setFlag(C, false);
}

void CPU::CLD(){
  setFlag(D, false);
}

void CPU::CLI(){
  setFlag(I, false);
}

void CPU::CLV(){
  setFlag(V, false);
}

void CPU::CMP(){
  setFlag(C, A >= fetched);
	setFlag(Z, A == fetched);
	setFlag(N, (A - fetched) & (1 << 7));
}

void CPU::CPX(){
  setFlag(C, X >= fetched);
	setFlag(Z, X == fetched);
	setFlag(N, (X - fetched) & (1 << 7));  
}

void CPU::CPY(){
  setFlag(C, Y >= fetched);
	setFlag(Z, Y == fetched);
	setFlag(N, (Y - fetched) & (1 << 7));   
}

void CPU::DEC(){
  write(address, fetched - 1);
	setFlag(Z, fetched - 1 == 0);
	setFlag(N, (fetched - 1) & (1 << 7));
}

void CPU::DEX(){
  X--;
	setFlag(Z, X == 0);
	setFlag(N, X & (1 << 7));
}

void CPU::DEY(){
  Y--;
	setFlag(Z, Y == 0);
	setFlag(N, Y & (1 << 7));  
}

void CPU::EOR(){
	A ^= fetched;
	setFlag(Z, A == 0);
	setFlag(N, A & (1 << 7));
}

void CPU::INC(){
	write(address, fetched + 1);
	setFlag(Z, fetched + 1 == 0);
	setFlag(N, (fetched + 1) & (1 << 7));
}

void CPU::INX(){
  X++;
	setFlag(Z, X == 0);
	setFlag(N, X & (1 << 7));
}

void CPU::INY(){
  Y++;
	setFlag(Z, Y == 0);
	setFlag(N, Y & (1 << 7));
}

void CPU::JMP(){
  PC = address;
}

void CPU::JSR(){
	push(PC >> 8); // upper byte
	push(PC + 1); // lower byte
	PC = (read(PC) | (read(PC + 1) << 8));
}

void CPU::LDA(){
  A = fetched;
	setFlag(Z, A == 0);
	setFlag(N, A & (1 << 7));
}

void CPU::LDX(){
	X = fetched;
	setFlag(Z, X == 0);
	setFlag(N, X & (1 << 7));
}

void CPU::LDY(){
	Y = fetched;
	setFlag(Z, Y == 0);
	setFlag(N, Y & (1 << 7));
}

void CPU::LSR(){
  setFlag(C, fetched & 1);
	fetched >>= 1;
	setFlag(Z, fetched == 0);
	setFlag(N, fetched & (1 << 7));

	if(lookup[opcode].addr == &CPU::IMP)
		A = fetched;
	else
		write(address, fetched);
}

void CPU::NOP(){
   
}

void CPU::ORA(){
  A |= fetched;
	setFlag(Z, A == 0);
	setFlag(N, A & (1 << 7));
}

void CPU::PHA(){
	push(A); 
}

void CPU::PHP(){
	// B flag is always set when pushing to stack from non-interrupts
	// https://www.nesdev.org/wiki/Status_flags#The_B_flag
  push(status | (1 << B));
}

void CPU::PLA(){
	A = pop();
	setFlag(Z, A == 0);
	setFlag(N, A & (1 << 7));
}

void CPU::PLP(){
	// nestest requires status to have unused flag set
	status = pop();
	setFlag(U, true);
	setFlag(B, false);
}

void CPU::ROL(){
  uint8_t c = getFlag(C);
	setFlag(C, fetched & (1 << 7));
	fetched <<= 1;
	fetched |= c;
	setFlag(Z, fetched == 0);
	setFlag(N, fetched & (1 << 7));

	if(disass_map[opcode] == 1)
		A = fetched;
	else
		write(address, fetched);
}

void CPU::ROR(){
	setFlag(C, fetched & 1);
	fetched >>= 1;
	fetched |= getFlag(C) << 7;
	setFlag(Z, fetched == 0);
	setFlag(N, fetched & (1 << 7));
	if(disass_map[opcode] == 1)
		A = fetched;
	else
		write(address, fetched);
}

void CPU::RTI(){
  status = pop();
	uint8_t low = pop();
	uint8_t high = pop();
	PC = (high << 8) | low;
	setFlag(U, true);
}

void CPU::RTS(){
	uint8_t low = pop();
	uint8_t high = pop();
	// +2: JSR = 3 bytes, PC is already incremented by 1, return to address - 1
	PC = ((high << 8) | low) + 1; 
}

void CPU::SBC(){
	// A - B == A + (-B)
	fetched = fetched ^ 0xFF;
	ADC();
}

void CPU::SEC(){
	setFlag(C, true);
}

void CPU::SED(){
	setFlag(D, true);
}

void CPU::SEI(){
	setFlag(I, true);
}

void CPU::STA(){
	write(address, A);
}

void CPU::STX(){
	write(address, X);
}

void CPU::STY(){
	write(address, Y);
}

void CPU::TAX(){
  X = A;
	setFlag(Z, X == 0);
	setFlag(N, X & (1 << 7));
}

void CPU::TAY(){
  Y = A;
	setFlag(Z, Y == 0);
	setFlag(N, Y & (1 << 7));
}

void CPU::TSX(){
  X = SP;
	setFlag(Z, X == 0);
	setFlag(N, X & (1 << 7));
}

void CPU::TXA(){
	A = X;
	setFlag(Z, A == 0);
	setFlag(N, A & (1 << 7));
}

void CPU::TXS(){
	SP = X;
}

void CPU::TYA(){
	A = Y;
	setFlag(Z, A == 0);
	setFlag(N, A & (1 << 7));
}

void CPU::XXX(){

}





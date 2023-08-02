#include "cpu.hpp"
#include <iostream>

using namespace std;


CPU::CPU(){

	using a = CPU;
	lookup = 
	{
		{ "BRK", &a::BRK, &a::IMM, 7 },{ "ORA", &a::ORA, &a::IZX, 6 },{ "KIL", &a::KIL, &a::IMP, 2 },{ "SLO", &a::SLO, &a::IZX, 8 },{ "NOP", &a::NOP, &a::ZP0, 3 },{ "ORA", &a::ORA, &a::ZP0, 3 },{ "ASL", &a::ASL, &a::ZP0, 5 },{ "SLO", &a::SLO, &a::ZP0, 5 },{ "PHP", &a::PHP, &a::IMP, 3 },{ "ORA", &a::ORA, &a::IMM, 2 },{ "ASL", &a::ASL, &a::IMP, 2 },{ "ANC", &a::ANC, &a::IMM, 2 },{ "NOP", &a::NOP, &a::ABS, 4 },{ "ORA", &a::ORA, &a::ABS, 4 },{ "ASL", &a::ASL, &a::ABS, 6 },{ "SLO", &a::SLO, &a::ABS, 6 },
		{ "BPL", &a::BPL, &a::REL, 2 },{ "ORA", &a::ORA, &a::IZY, 5 },{ "KIL", &a::KIL, &a::IMP, 2 },{ "SLO", &a::SLO, &a::IZY, 8 },{ "NOP", &a::NOP, &a::ZPX, 4 },{ "ORA", &a::ORA, &a::ZPX, 4 },{ "ASL", &a::ASL, &a::ZPX, 6 },{ "SLO", &a::SLO, &a::ZPX, 6 },{ "CLC", &a::CLC, &a::IMP, 2 },{ "ORA", &a::ORA, &a::ABY, 4 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "SLO", &a::SLO, &a::ABY, 7 },{ "NOP", &a::NOP, &a::ABX, 4 },{ "ORA", &a::ORA, &a::ABX, 4 },{ "ASL", &a::ASL, &a::ABX, 7 },{ "SLO", &a::SLO, &a::ABX, 7 },
		{ "JSR", &a::JSR, &a::ABS, 6 },{ "AND", &a::AND, &a::IZX, 6 },{ "KIL", &a::KIL, &a::IMP, 2 },{ "RLA", &a::RLA, &a::IZX, 8 },{ "BIT", &a::BIT, &a::ZP0, 3 },{ "AND", &a::AND, &a::ZP0, 3 },{ "ROL", &a::ROL, &a::ZP0, 5 },{ "RLA", &a::RLA, &a::ZP0, 5 },{ "PLP", &a::PLP, &a::IMP, 4 },{ "AND", &a::AND, &a::IMM, 2 },{ "ROL", &a::ROL, &a::IMP, 2 },{ "ANC", &a::ANC, &a::IMM, 2 },{ "BIT", &a::BIT, &a::ABS, 4 },{ "AND", &a::AND, &a::ABS, 4 },{ "ROL", &a::ROL, &a::ABS, 6 },{ "RLA", &a::RLA, &a::ABS, 6 },
		{ "BMI", &a::BMI, &a::REL, 2 },{ "AND", &a::AND, &a::IZY, 5 },{ "KIL", &a::KIL, &a::IMP, 2 },{ "RLA", &a::RLA, &a::IZY, 8 },{ "NOP", &a::NOP, &a::ZPX, 4 },{ "AND", &a::AND, &a::ZPX, 4 },{ "ROL", &a::ROL, &a::ZPX, 6 },{ "RLA", &a::RLA, &a::ZPX, 6 },{ "SEC", &a::SEC, &a::IMP, 2 },{ "AND", &a::AND, &a::ABY, 4 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "RLA", &a::RLA, &a::ABY, 7 },{ "NOP", &a::NOP, &a::ABX, 4 },{ "AND", &a::AND, &a::ABX, 4 },{ "ROL", &a::ROL, &a::ABX, 7 },{ "RLA", &a::RLA, &a::ABX, 7 },
		{ "RTI", &a::RTI, &a::IMP, 6 },{ "EOR", &a::EOR, &a::IZX, 6 },{ "KIL", &a::KIL, &a::IMP, 2 },{ "SRE", &a::SRE, &a::IZX, 8 },{ "NOP", &a::NOP, &a::ZP0, 3 },{ "EOR", &a::EOR, &a::ZP0, 3 },{ "LSR", &a::LSR, &a::ZP0, 5 },{ "SRE", &a::SRE, &a::ZP0, 5 },{ "PHA", &a::PHA, &a::IMP, 3 },{ "EOR", &a::EOR, &a::IMM, 2 },{ "LSR", &a::LSR, &a::IMP, 2 },{ "ALR", &a::ALR, &a::IMM, 2 },{ "JMP", &a::JMP, &a::ABS, 3 },{ "EOR", &a::EOR, &a::ABS, 4 },{ "LSR", &a::LSR, &a::ABS, 6 },{ "SRE", &a::SRE, &a::ABS, 6 },
		{ "BVC", &a::BVC, &a::REL, 2 },{ "EOR", &a::EOR, &a::IZY, 5 },{ "KIL", &a::KIL, &a::IMP, 2 },{ "SRE", &a::SRE, &a::IZY, 8 },{ "NOP", &a::NOP, &a::ZPX, 4 },{ "EOR", &a::EOR, &a::ZPX, 4 },{ "LSR", &a::LSR, &a::ZPX, 6 },{ "SRE", &a::SRE, &a::ZPX, 6 },{ "CLI", &a::CLI, &a::IMP, 2 },{ "EOR", &a::EOR, &a::ABY, 4 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "SRE", &a::SRE, &a::ABY, 7 },{ "NOP", &a::NOP, &a::ABX, 4 },{ "EOR", &a::EOR, &a::ABX, 4 },{ "LSR", &a::LSR, &a::ABX, 7 },{ "SRE", &a::SRE, &a::ABX, 7 },
		{ "RTS", &a::RTS, &a::IMP, 6 },{ "ADC", &a::ADC, &a::IZX, 6 },{ "KIL", &a::KIL, &a::IMP, 2 },{ "RRA", &a::RRA, &a::IZX, 8 },{ "NOP", &a::NOP, &a::ZP0, 3 },{ "ADC", &a::ADC, &a::ZP0, 3 },{ "ROR", &a::ROR, &a::ZP0, 5 },{ "RRA", &a::RRA, &a::ZP0, 5 },{ "PLA", &a::PLA, &a::IMP, 4 },{ "ADC", &a::ADC, &a::IMM, 2 },{ "ROR", &a::ROR, &a::IMP, 2 },{ "ARR", &a::ARR, &a::IMM, 2 },{ "JMP", &a::JMP, &a::IND, 5 },{ "ADC", &a::ADC, &a::ABS, 4 },{ "ROR", &a::ROR, &a::ABS, 6 },{ "RRA", &a::RRA, &a::ABS, 6 },
		{ "BVS", &a::BVS, &a::REL, 2 },{ "ADC", &a::ADC, &a::IZY, 5 },{ "KIL", &a::KIL, &a::IMP, 2 },{ "RRA", &a::RRA, &a::IZY, 8 },{ "NOP", &a::NOP, &a::ZPX, 4 },{ "ADC", &a::ADC, &a::ZPX, 4 },{ "ROR", &a::ROR, &a::ZPX, 6 },{ "RRA", &a::RRA, &a::ZPX, 6 },{ "SEI", &a::SEI, &a::IMP, 2 },{ "ADC", &a::ADC, &a::ABY, 4 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "RRA", &a::RRA, &a::ABY, 7 },{ "NOP", &a::NOP, &a::ABX, 4 },{ "ADC", &a::ADC, &a::ABX, 4 },{ "ROR", &a::ROR, &a::ABX, 7 },{ "RRA", &a::RRA, &a::ABX, 7 },
		{ "NOP", &a::NOP, &a::IMM, 2 },{ "STA", &a::STA, &a::IZX, 6 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "SAX", &a::SAX, &a::IZX, 6 },{ "STY", &a::STY, &a::ZP0, 3 },{ "STA", &a::STA, &a::ZP0, 3 },{ "STX", &a::STX, &a::ZP0, 3 },{ "SAX", &a::SAX, &a::ZP0, 3 },{ "DEY", &a::DEY, &a::IMP, 2 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "TXA", &a::TXA, &a::IMP, 2 },{ "XAA", &a::XAA, &a::IMM, 2 },{ "STY", &a::STY, &a::ABS, 4 },{ "STA", &a::STA, &a::ABS, 4 },{ "STX", &a::STX, &a::ABS, 4 },{ "SAX", &a::SAX, &a::ABS, 4 },
		{ "BCC", &a::BCC, &a::REL, 2 },{ "STA", &a::STA, &a::IZY, 6 },{ "KIL", &a::KIL, &a::IMP, 2 },{ "AHX", &a::AHX, &a::IZY, 6 },{ "STY", &a::STY, &a::ZPX, 4 },{ "STA", &a::STA, &a::ZPX, 4 },{ "STX", &a::STX, &a::ZPY, 4 },{ "SAX", &a::SAX, &a::ZPY, 4 },{ "TYA", &a::TYA, &a::IMP, 2 },{ "STA", &a::STA, &a::ABY, 5 },{ "TXS", &a::TXS, &a::IMP, 2 },{ "TAS", &a::TAS, &a::ABY, 5 },{ "NOP", &a::NOP, &a::ABX, 5 },{ "STA", &a::STA, &a::ABX, 5 },{ "SHX", &a::SHX, &a::ABY, 5 },{ "AHX", &a::AHX, &a::ABX, 5 },
		{ "LDY", &a::LDY, &a::IMM, 2 },{ "LDA", &a::LDA, &a::IZX, 6 },{ "LDX", &a::LDX, &a::IMM, 2 },{ "LAX", &a::LAX, &a::IZX, 6 },{ "LDY", &a::LDY, &a::ZP0, 3 },{ "LDA", &a::LDA, &a::ZP0, 3 },{ "LDX", &a::LDX, &a::ZP0, 3 },{ "LAX", &a::LAX, &a::ZP0, 3 },{ "TAY", &a::TAY, &a::IMP, 2 },{ "LDA", &a::LDA, &a::IMM, 2 },{ "TAX", &a::TAX, &a::IMP, 2 },{ "LAX", &a::LAX, &a::IMM, 2 },{ "LDY", &a::LDY, &a::ABS, 4 },{ "LDA", &a::LDA, &a::ABS, 4 },{ "LDX", &a::LDX, &a::ABS, 4 },{ "LAX", &a::LAX, &a::ABS, 4 },
		{ "BCS", &a::BCS, &a::REL, 2 },{ "LDA", &a::LDA, &a::IZY, 5 },{ "KIL", &a::KIL, &a::IMP, 2 },{ "LAX", &a::LAX, &a::IZY, 5 },{ "LDY", &a::LDY, &a::ZPX, 4 },{ "LDA", &a::LDA, &a::ZPX, 4 },{ "LDX", &a::LDX, &a::ZPY, 4 },{ "LAX", &a::LAX, &a::ZPY, 4 },{ "CLV", &a::CLV, &a::IMP, 2 },{ "LDA", &a::LDA, &a::ABY, 4 },{ "TSX", &a::TSX, &a::IMP, 2 },{ "LAS", &a::LAS, &a::ABY, 4 },{ "LDY", &a::LDY, &a::ABX, 4 },{ "LDA", &a::LDA, &a::ABX, 4 },{ "LDX", &a::LDX, &a::ABY, 4 },{ "LAX", &a::LAX, &a::ABY, 4 },
		{ "CPY", &a::CPY, &a::IMM, 2 },{ "CMP", &a::CMP, &a::IZX, 6 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "DCP", &a::DCP, &a::IZX, 8 },{ "CPY", &a::CPY, &a::ZP0, 3 },{ "CMP", &a::CMP, &a::ZP0, 3 },{ "DEC", &a::DEC, &a::ZP0, 5 },{ "DCP", &a::DCP, &a::ZP0, 5 },{ "INY", &a::INY, &a::IMP, 2 },{ "CMP", &a::CMP, &a::IMM, 2 },{ "DEX", &a::DEX, &a::IMP, 2 },{ "AXS", &a::AXS, &a::IMM, 2 },{ "CPY", &a::CPY, &a::ABS, 4 },{ "CMP", &a::CMP, &a::ABS, 4 },{ "DEC", &a::DEC, &a::ABS, 6 },{ "DCP", &a::DCP, &a::ABS, 6 },
		{ "BNE", &a::BNE, &a::REL, 2 },{ "CMP", &a::CMP, &a::IZY, 5 },{ "KIL", &a::KIL, &a::IMP, 2 },{ "DCP", &a::DCP, &a::IZY, 8 },{ "NOP", &a::NOP, &a::ZPX, 4 },{ "CMP", &a::CMP, &a::ZPX, 4 },{ "DEC", &a::DEC, &a::ZPX, 6 },{ "DCP", &a::DCP, &a::ZPX, 6 },{ "CLD", &a::CLD, &a::IMP, 2 },{ "CMP", &a::CMP, &a::ABY, 4 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "DCP", &a::DCP, &a::ABY, 7 },{ "NOP", &a::NOP, &a::ABX, 4 },{ "CMP", &a::CMP, &a::ABX, 4 },{ "DEC", &a::DEC, &a::ABX, 7 },{ "DCP", &a::DCP, &a::ABX, 7 },
		{ "CPX", &a::CPX, &a::IMM, 2 },{ "SBC", &a::SBC, &a::IZX, 6 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "ISC", &a::ISC, &a::IZX, 8 },{ "CPX", &a::CPX, &a::ZP0, 3 },{ "SBC", &a::SBC, &a::ZP0, 3 },{ "INC", &a::INC, &a::ZP0, 5 },{ "ISC", &a::ISC, &a::ZP0, 5 },{ "INX", &a::INX, &a::IMP, 2 },{ "SBC", &a::SBC, &a::IMM, 2 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "SBC", &a::SBC, &a::IMM, 2 },{ "CPX", &a::CPX, &a::ABS, 4 },{ "SBC", &a::SBC, &a::ABS, 4 },{ "INC", &a::INC, &a::ABS, 6 },{ "ISC", &a::ISC, &a::ABS, 6 },
		{ "BEQ", &a::BEQ, &a::REL, 2 },{ "SBC", &a::SBC, &a::IZY, 5 },{ "KIL", &a::KIL, &a::IMP, 2 },{ "ISC", &a::ISC, &a::IZY, 8 },{ "NOP", &a::NOP, &a::ZPX, 4 },{ "SBC", &a::SBC, &a::ZPX, 4 },{ "INC", &a::INC, &a::ZPX, 6 },{ "ISC", &a::ISC, &a::ZPX, 6 },{ "SED", &a::SED, &a::IMP, 2 },{ "SBC", &a::SBC, &a::ABY, 4 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "ISC", &a::ISC, &a::ABY, 7 },{ "NOP", &a::NOP, &a::ABX, 4 },{ "SBC", &a::SBC, &a::ABX, 4 },{ "INC", &a::INC, &a::ABX, 7 },{ "ISC", &a::ISC, &a::ABX, 7 },
	};

	ram.resize(0xFFFF + 1);

	for(uint8_t& num : ram)
		num = 0x00;

	cyc_ins = {
		{"BPL", true}, {"BMI", true}, {"BVC", true}, {"BVS", true}, {"BCC", true}, {"BCS", true}, {"BNE", true}, {"BEQ", true},
		{"ORA", true}, {"AND", true}, {"EOR", true}, {"ADC", true}, {"LDA", true}, {"CMP", true}, {"SBC", true}, 
		{"LAX", true}, 
		{"NOP", true}, {"LDY", true}, {"LDX", true} 
	};

}

void CPU::run(){
	int i = 0;
	while(PC != 0xC66E){
		tick();
		if(executed()) i++;
		cycles--;
	}
}

void CPU::tick(){
	if(cycles == 0){
		page_crossed = false;
		setFlag(U, true);
		cycles = lookup[opcode].cycles;
		opcode = read(PC);

		log_pc = PC;
		PC++;

		log();
		(this->*lookup[opcode].addr)();
		fetch();
		(this->*lookup[opcode].op)();

		if(cyc_ins.count(lookup[opcode].name) && page_crossed)
			cycles++;
		log_cycles += cycles;
	}
}

void CPU::reset(){

	PC = read(0xFFFC) | (read(0xFFFC + 1) << 8);

	A = X = Y = 0;
	SP = 0xFD;
	status = 0x24;

	rel = 0x0000;
	address = 0x0000;
	fetched = 0x00;
	cycles = log_cycles = 7;
}

void CPU::irq(){
	if(!getFlag(I))
		return;
	push(PC >> 8);
	push(PC);
	setFlag(I, 1);
	push((status | (1 << U)) & (~(1 << B)));
	PC = (read(0xFFFF) << 8) | read(0xFFFE);
	cycles = 7;
}

void CPU::nmi(){
	push(PC >> 8);
	push(PC);
	setFlag(I, 1);
	push((status | (1 << U)) & (~(1 << B)));
	PC = (read(0xFFFB) << 8) | read(0xFFFA);
	cycles = 8;
}

void CPU::IMP(){}

void CPU::IMM(){
	address = PC++;	
}

void CPU::ZP0(){
	address = read(PC++);	
}

void CPU::ZPX(){
	// since X + address can be greater than 255, we need to mod it
	address = (read(PC++) + X) % 256;	
}

void CPU::ZPY(){
		// since Y + address can be greater than 255, we need to mod it
	address = (read(PC++) + Y) % 256;	
}

void CPU::REL(){
	rel = read(PC++);
	if (rel & (1 << 7))
		rel |= 0xFF00;
}

void CPU::ABS(){
	uint16_t low = read(PC++);
	uint16_t high = read(PC++);
	address = (high << 8) | low;
}

void CPU::ABX(){
	uint16_t low = read(PC++);
	uint16_t high = read(PC++);
	address = ((high << 8) | low) + X;
	page_crossed = (address & 0xFF00) != (high << 8);
}

void CPU::ABY(){
	uint16_t low = read(PC++);
	uint16_t high = read(PC++);
	address = ((high << 8) | low) + Y;
	page_crossed = (address & 0xFF00) != (high << 8);
}

void CPU::IND(){
	uint16_t low = read(PC++);
	uint16_t high = read(PC++);
	uint16_t ptr = (high << 8) | low;

	// https://www.nesdev.org/6502bugs.txt
	if (low == 0x00FF)
		address = read(ptr) | (read(ptr - 0xFF) << 8); // i.e.: read from 0x00FF and 0x0000, not 0x00FF and 0x0100
	else
		address = read(ptr) | (read(ptr + 1) << 8);
}


void CPU::IZX(){
	uint16_t ptr = read(PC++);
	// ptr + X can be > 256 so we need to mod it
	uint8_t low = read((ptr + X) % 256);
	uint8_t high = read((ptr + X + 1) % 256);
	address = (high << 8) | low;
}

void CPU::IZY(){
	uint8_t ptr = read(PC++);
	uint8_t lo = read(ptr);
	uint8_t hi = read((ptr + 1) % 256);

	address = (hi << 8) | lo;
	address += Y;
	page_crossed = (address & 0xFF00) != (hi << 8);
}

uint8_t CPU::fetch(){
	if (!(disass_bytes() == 1))
		fetched = read(address);
	return A;
}

void CPU::ADC(){
	uint16_t sum = A + fetched + getFlag(C);
	setFlag(C, sum > 0xFF);
	setFlag(N, sum & (1 << 7));
	setFlag(V, (A ^ sum) & (fetched ^ sum) & (1 << 7));

	A = sum; 
	setFlag(Z, A == 0);
}

void CPU::SBC(){
	fetched ^= 0xFF;
	ADC();
}

void CPU::AND(){
	A &= fetched;
	setFlag(Z, A == 0);
	setFlag(N, A & (1 << 7));
}

void CPU::ASL(){
	uint16_t tmp = fetched << 1;
	setFlag(C, fetched & (1 << 7));
	setFlag(Z, tmp % 256 == 0);
	setFlag(N, tmp & (1 << 7));

	if (disass_bytes() == 1)
		A = tmp % 256;
	else
		write(address, tmp % 256);
}

void CPU::BCC(){
	if(!getFlag(C))
		branch();
}

void CPU::BCS(){
	if(getFlag(C))
		branch();
}

void CPU::BEQ(){
	if (getFlag(Z))
		branch();
}

void CPU::BIT(){
	setFlag(Z, (A & fetched) == 0x00);
	setFlag(N, fetched & (1 << 7));
	setFlag(V, fetched & (1 << 6));
}

void CPU::BMI(){
	if (getFlag(N))
		branch();
}

void CPU::BNE(){
	if (!getFlag(Z))
		branch();
}

void CPU::BPL(){
	if (!getFlag(N))
		branch();
}

void CPU::BRK(){
	PC++;
	push(PC >> 8);
	push(PC);
	push(status | (1 << B) | (1 << U));

	setFlag(I, 1);
	setFlag(B, 0);

	PC = read(0xFFFE) | (read(0xFFFF) << 8);
}

void CPU::BVC(){
	if (!getFlag(V))
		branch();
}

void CPU::BVS(){
	if (getFlag(V))
		branch();
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
	setFlag(Z, (A - fetched) == 0);
	setFlag(N, (A - fetched) & (1 << 7));
}

void CPU::CPX(){
	setFlag(C, X >= fetched);
	setFlag(Z, (X - fetched) == 0);
	setFlag(N, (X - fetched) & (1 << 7));
}

void CPU::CPY(){
	setFlag(C, Y >= fetched);
	setFlag(Z, (Y - fetched) == 0);
	setFlag(N, (Y - fetched) & (1 << 7));
}

void CPU::DEC(){
	fetched--;
	write(address, fetched);
	setFlag(Z, fetched == 0);
	setFlag(N, fetched & (1 << 7));
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
	fetched++;
	write(address, fetched);
	setFlag(Z, fetched == 0);
	setFlag(N, fetched & (1 << 7));
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
	PC--;
	push(PC >> 8);
	push(PC);
	PC = address;
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
	setFlag(Z, fetched % 256 == 0);
	setFlag(N, fetched & (1 << 7));

	if (disass_bytes() == 1)
		A = fetched;
	else
		write(address, fetched);
}

void CPU::NOP(){}

void CPU::ORA(){
	A |= fetched;
	setFlag(Z, A == 0);
	setFlag(N, A & (1 << 7));
}

void CPU::PHA(){
	push(A);
}

void CPU::PHP(){
	push(status | (1 << B) | (1 << U));
}

void CPU::PLA(){
	A = pop();
	setFlag(Z, A == 0);
	setFlag(N, A & (1 << 7));
}

void CPU::PLP(){
	status = pop();
	setFlag(B, 0);
}

void CPU::ROL(){
	uint16_t tmp = fetched * 2 + getFlag(C);
	setFlag(C, fetched & (1 << 7));
	setFlag(Z, tmp % 256 == 0);
	setFlag(N, tmp & (1 << 7));

	if (disass_bytes() == 1)
		A = tmp % 256;
	else
		write(address, tmp % 256);
}

void CPU::ROR(){
	uint16_t tmp = fetched / 2 + getFlag(C) * 128;
	setFlag(C, fetched & 0x01);	
	setFlag(Z, tmp % 256 == 0x00);
	setFlag(N, tmp & (1 << 7));

	if (disass_bytes() == 1)
		A = tmp % 256;
	else
		write(address, tmp % 256);
}

void CPU::RTI(){
	status = pop();
	PC = pop();
	PC |= pop() << 8;
}

void CPU::RTS(){
	PC = pop();
	PC |= pop() << 8;
	PC++;
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

// This function captures illegal opcodes
void CPU::KIL(){
	std::cout << "KIL" << std::endl;
	exit(0);
	
}

// illegal opcodes:
// opcodes that are not tested in nestest are not implemented

void CPU::AHX(){}
void CPU::ALR(){}
void CPU::ANC(){}
void CPU::ARR(){}
void CPU::AXS(){}

void CPU::DCP(){
	DEC();
	fetch();
	CMP();
}

void CPU::ISC(){
	// also known as ISB
	INC();
	fetch();
	SBC();
}

void CPU::LAS(){}

void CPU::LAX(){
	LDA();
	fetch();
	LDX();
}

void CPU::SAX(){
	write(address, A & X);
}

void CPU::SHX(){}
void CPU::SHY(){}

void CPU::SLO(){
	ASL();
	fetch();
	ORA();
}

void CPU::SRE(){
	LSR();
	fetch();
	EOR();
}

void CPU::RLA(){
	ROL();
	fetch();
	AND();
}

void CPU::RRA(){
	ROR();
	fetch();
	ADC();
}

void CPU::TAS(){}
void CPU::XAA(){}


#pragma once
#include "common.hpp"



class CPU{
public:
	CPU();
	
	uint16_t PC = 0x0000; 
	uint8_t SP = 0xFD;  
	uint8_t A = 0, X = 0, Y = 0;
	uint8_t status = 0x00;
	
	enum Flags{
		C, Z, I, D, B, U, V, N
	};

	std::vector<uint8_t> ram;
	uint16_t address = 0x0000;
	uint8_t opcode = 0x00;
	uint8_t fetched = 0x00;
	uint8_t cycles = 0x07;
	
	void setFlag(Flags flag, bool value);
	bool getFlag(Flags flag);
	void toggleFlag(Flags flag);
	void printStatus();
	void printHex(std::string s, uint16_t to_print, std::string delimiter);

	void run();
	void cycle();
	uint8_t fetch();
	void readHeader(FILE* fp);
	void reset();
	void push(uint8_t data);
	uint8_t pop();
	uint8_t read(uint16_t address);
	void write(uint16_t address, uint8_t data);
	void loadRom(FILE* fp);

	void log();

	struct Header{
		uint8_t magic[4];
		uint8_t prg_rom_size;
		uint8_t chr_rom_size;
		uint8_t flag_6;
		uint8_t flag_7;
		uint8_t flag_8;
		uint8_t flag_9;
		uint8_t flag_10;
		uint8_t PADDING[5];
	} header;

	struct Instruct{
		std::string name;
		void (CPU::*op)();
		void (CPU::*addr)();
		uint8_t cycles;
	};

	std::vector<Instruct> lookup;
	std::map<int, int> disass_map;


	void IMP();	void IMM();	
	void ZP0();	void ZPX();	
	void ZPY();	void REL();
	void ABS();	void ABX();	
	void ABY();	void IND();	
	void IZX();	void IZY();

	void ADC();	void AND();	void ASL();	void BCC();
	void BCS();	void BEQ();	void BIT();	void BMI();
	void BNE();	void BPL();	void BRK();	void BVC();
	void BVS();	void CLC();	void CLD();	void CLI();
	void CLV();	void CMP();	void CPX();	void CPY();
	void DEC();	void DEX();	void DEY();	void EOR();
	void INC();	void INX();	void INY();	void JMP();
	void JSR();	void LDA();	void LDX();	void LDY();
	void LSR();	void NOP();	void ORA();	void PHA();
	void PHP();	void PLA();	void PLP();	void ROL();
	void ROR();	void RTI();	void RTS();	void SBC();
	void SEC();	void SED();	void SEI();	void STA();
	void STX();	void STY();	void TAX();	void TAY();
	void TSX();	void TXA();	void TXS();	void TYA();

	void XXX();

};
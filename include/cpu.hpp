#pragma once

#include <vector>
#include <string>
#include <map>

class CPU{
public:
	CPU();

	uint8_t  A      = 0x00;
	uint8_t  X      = 0x00;
	uint8_t  Y      = 0x00;
	uint8_t  SP   = 0x00;
	uint16_t PC     = 0x0000;
	uint8_t  status = 0x00;
	std::vector<uint8_t> ram;
	
	void run();
	void reset();
	void irq();
	void nmi();
	void tick();
	bool executed();

	enum StatusFlags{ 
		C, Z, I, D, B, U, V, N
	};

	uint8_t  	fetched     	= 0x00;  
	uint16_t 	address    		= 0x0000;
	uint16_t 	rel    				= 0x00;  
	uint8_t  	opcode      	= 0x00;  
	uint8_t  	cycles      	= 0;	   
	bool 			page_crossed 	= false;

	uint8_t fetch();

	// Addressing Modes
	void IMP();	void IMM();	
	void ZP0();	void ZPX();	
	void ZPY();	void REL();
	void ABS();	void ABX();	
	void ABY();	void IND();	
	void IZX();	void IZY();


	// Opcodes
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

	// illegal opcodes:
	// http://www.oxyron.de/html/opcodes02.html
	
	void AHX();	
	void ALR();	 	
	void ANC();	 		 	
	void ARR();	 	
	void AXS();	 	
	void DCP();	 	
	void ISC();	 	
	void LAS();
	void LAX();	 	
	void SAX();	 	
	void SHX();	
	void SHY();	
	void SLO();	 	
	void SRE();	 	
	void RLA();	 	
	void RRA();	 	
	void TAS();	
	void XAA(); 

	// Halt CPU
	void KIL();

	// utilities
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
		void     (CPU::*op )(void) = nullptr;
		void     (CPU::*addr)(void) = nullptr;
		uint8_t     cycles = 0;
	};

	uint64_t log_pc = 0;
	uint64_t log_cycles = 0;
	std::vector<Instruct> lookup;
	std::map<std::string, bool> cyc_ins;

	uint8_t read(uint16_t a);
	void    write(uint16_t a, uint8_t d);
	void push(uint8_t v);
	uint8_t pop();
	void branch();


	uint8_t disass_bytes();
	bool getFlag(StatusFlags f);
	void setFlag(StatusFlags f, bool v);
	void readHeader(FILE* fp);
	void loadRom(FILE* fp);
	void log();

};


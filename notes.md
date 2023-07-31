# NES

---

#### CPU

- 2A03
- Storage: 64 KB
- Adress range: $0000 - $FFFF
- Stack range: $0100 - $01FF

###### Registers

- > PC - Program Counter (16 bit)
- > SP - Stack Pointer (8 bit)<br> No overflow detection, wraps around 0x00 - 0xFF
- > A - Accumulator (8 bit)
- > X - Index Register X (8 bit)
- > Y - Index Register Y (8 bit)

- > P - Processor Status (8 bit)<br><br>
N - Negative V - Overflow<br> U - Unused<br> B - Break<br> D - Decimal<br> I - Interrupt Disable<br> Z - Zero<br> C - Carry
<pre>
7 6 5 4 3 2 1 0 
N V U B D I Z C
</pre>

###### Misc

- Reading CPU: Store contents from ROM into $8000 - $FFFF
- Get PC from 0xFFFC and 0xFFFD (little endian)
- Zero page = $0000 - $00FF
- Overflow in english: overflow if the sign of the result does not match the sign of either input

---

## Sources

- > [NES Architechture](https://www.nesdev.org/NESDoc.pdf)
- > [NES Test Explanation](https://www.qmtpro.com/~nes/misc/nestest.txt)
  > [NES Test Log](https://www.qmtpro.com/~nes/misc/nestest.nes)
  > [NES Test ROM](https://www.qmtpro.com/~nes/misc/nestest.nes)
- > [Instructions](https://www.masswerk.at/6502/6502_instruction_set.html)
- > [Overflow flag](https://forums.nesdev.org/viewtopic.php?t=6331)

from termcolor import colored

lookup = ["Address:", "Instruction", "Bytes", "A =", "X =", "Y =", "P =", "SP =", "CYC ="]


def disass_new(line, ins):
  res = []
  # ['C000', '4C F5 C5', 'JMP 00', '00', '00', '00', '24', 'FD', '7']
  els = (' '.join(line.split())).split(' ')
  # print(els)
  res.append(els[0])
  s = ""
  for i in range(1, 4):
    if len(els[i]) != 2:
      break
    s += els[i] + ' '
  res.append(s.strip())
  res.append(ins)
  
  # find index of A: in line and insert next 2 elements
  res.append(line[line.index('A:') + 2:line.index('A:') + 4 ])
  res.append(line[line.index('X:') + 2:line.index('X:') + 4 ])
  res.append(line[line.index('Y:') + 2:line.index('Y:') + 4 ])
  res.append(line[line.index('P:') + 2:line.index('P:') + 4 ])
  res.append(line[line.index('SP:') + 3:line.index('SP:') + 5 ])
  res.append(line[line.index('CYC:') + 4:])
  return res



def disass_s_nes(line):
  res = []
  line = [i.strip() for i in line.split('  ') if i]
  # PC -> ins bytes -> ins string

  # print(line)
  
  res.append(line[0])
  ins = line[1].split(' ')
  ins_str = ins[0] + ' ' + ins[1] + ' ' + ins[2]
  res.append(ins_str)
  remaining = line[1][len(ins_str):].strip()
  res.append(remaining)
  registers = line[2].split(' ')

  for i in range(5):
    res.append(registers[i].split(':')[1])
  res.append(registers[-1].split(':')[1])

  return res

def disass_nes(line):
  res = []
  line = [i.strip() for i in line.split('  ') if i]
  # PC -> ins bytes -> ins string
  # print(line)
  res.extend(line[:3])
  registers = line[3].split(' ')

  for i in range(5):
    res.append(registers[i].split(':')[1]) # A:00 X:00 Y:00 P:24 SP:FD



  cycle_el = line[-1]
  index = cycle_el.index('CYC:')
  cycles = cycle_el[index + 4:]
  res.append(cycles)
  
  return res

def disass_olc(line):
  res = []
  line = [i.strip() for i in line.split('  ') if i]
  
  first = line[0].split(' ', maxsplit=1)
  res.extend(first)
  res.append(line[1])
 
  registers = line[2].split(' ')
  for i in range(6):
    res.append(registers[i].strip().split(':')[1])
  
  return res

def check_same(nes, main):

  # PC
  if nes[0] != main[0]:
    return 0
  
  # instruction bytes
  if nes[1] != main[1]:
    return 1

  # instruction string
  # we can skip this since i print it differently

  # A:00 X:00 Y:00 P:24 SP:FD
  for i in range(5):
    if nes[i+3] != main[i+3]:
      return 3 + i

  # CYC: 7
  if nes[8] != main[8]:
    return 8

  return -1


def main():
  nestest = open('logs/nestest.log', 'r')
  main = open('logs/out.log', 'r')

  # A:00 X:00 Y:00 P:24 SP:FD CYC: 7
  

  for i, main_l in enumerate(main):
    main_l = main_l.strip()
    if "0x2h" in main_l or "0x3h" in main_l:
      print(main_l)
      continue

    nes_l = nestest.readline().strip()
    
    # try:
    #   nes_results = disass_nes(nes_l)
    # except:
    #   nes_results = disass_s_nes(nes_l)
    # if( i == 5577):
      # print(main_l)
    try:
      main_results = disass_olc(main_l)  
    except:
      print(f"Error at i {i}")
      quit()
    nes_results = disass_new(nes_l, main_results[2])

    code = check_same(nes_results, main_results)

    if code != -1:
      nes_string = "NES: "
      main_string = "MAIN: "
      print(colored(f"Error at line {i + 1} Code: {code}\n\n", "red"))
      for i in range(len(nes_results)):
        color = "red" if i == code else "cyan"
        print(colored(f"{nes_results[i]} ", color), end="")
        nes_string += f"{nes_results[i]} "
        main_string += f"{main_results[i]} "

      
      print()
      str_len = max(len(nes_string), len(main_string)) - 1
      print('-' * str_len)

      for i in range(len(main_results)):
        color = "red" if i == code else "yellow"
        print(colored(f"{main_results[i]} ", color), end="")
      print("\n")
      print(colored("Correct: " + lookup[code] + " " + nes_results[code], "green"))
      print('-' * str_len)
      print(colored("Yours: " + lookup[code] + " " + main_results[code], "red"))
      print()
      exit(1)
    


  print(colored("\nALL TESTS PASSED!\n", "green"))



if __name__ == '__main__':
  
    main()
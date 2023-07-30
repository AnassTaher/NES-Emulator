from termcolor import colored

def disass_nes(line):
  res = []
  line = [i.strip() for i in line.split('  ') if i]
  res.append(line[0]) # PC
  res.append(line[1]) # instruction bytes
  res.append(line[2]) # instruction string
  registers = line[3].split(' ')

  for i in range(5):
    res.append(registers[i].split(':')[1]) # A:00 X:00 Y:00 P:24 SP:FD
  res.append(line[4].split(':')[1])

  return res

def disass_main(line):
  res = []
  line = [i.strip() for i in line.split('  ') if i]
  # print(line)
  res.append(line[0]) # PC
  res.append(line[1]) # instruction bytes
  res.append(line[2]) # instruction string
  registers = line[3].split(' ')
  for i in range(5):
    res.append(registers[i].strip().split(':')[1])
  
  res.append(registers[6])

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
  nestest = open('nestest.log', 'r')
  main = open('main.log', 'r')

  # A:00 X:00 Y:00 P:24 SP:FD CYC: 7
  
  # loop through each line

  for i, main_l in enumerate(main):
    nes_l = nestest.readline().strip()
    main_l = main_l.strip()

    nes_results = disass_nes(nes_l)
    main_results = disass_main(main_l)  
    code = check_same(nes_results, main_results)

    if code != -1:
      nes_string = "NES: "
      main_string = "MAIN: "
      print(colored(f"Error at line {i} Code: {code}\n\n", "red"))
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
      print()
      exit(1)


  print(colored("\nALL TESTS PASSED!\n", "green"))


if __name__ == '__main__':
    main()
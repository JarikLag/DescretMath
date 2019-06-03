f = open("MTout.txt")
state = f.readline().split(": ")[-1].split("\n")[0]
accS = f.readline().split(": ")[-1].split("\n")[0]
rejS = f.readline().split(": ")[-1].split("\n")[0]
eps = f.readline().split(": ")[-1].split("\n")[0]

def printTape(l, r):
  global eps
  l.reverse()
  while len(l) != 0 and l[-1] == eps:
    l.pop()

  r.reverse()
  while len(r) != 0 and r[-1] == eps:
    r.pop()

  l.reverse()
  s = ""

  sp_sz = 0
  sp_here = 0
  for x in l:
    s += x
    sp_here += 1
    sp_sz += 1
  for x in r:
    s += x
    sp_sz += 1
  s+='\n'
  for i in range(sp_sz):
    if i == sp_here:
      s += '^'
    else:
      s += ' '

  print(s)

table = {}
for line in f:
  line = line.split("-> ")
  line[0] = line[0].split(" ")
  table[(line[0][0],line[0][1])] = line[1].split("\n")[0]

f.close()

f = open("input.txt")
l,r = [],list(f.readline().replace(" ","").replace("\n",""))
r.reverse()
f.close()

N = 0
while True:
  if len(r) == 0:
    c = eps
  else:
    c = r.pop()

  try:
    cell = table[(state,c)].split(" ")
  except:
    #f = open("output.txt","w")
    #f.write("0")
    #f.close()
    print("reject")
    print("Steps:", N)
    exit(0)

  newState = cell[0]
  c = cell[1]

  if cell[2] == ">":
    l.append(c)
  elif cell[2] == "^":
    r.append(c)
  else:
    r.append(c)
    if len(l) == 0:
      c = eps
    else:
      c = l.pop()
    r.append(c)

  #print(cell)
  printTape(l.copy(),r.copy())
  state = newState
  N+=1

  if N % 100000 == 0:
    print(N, "steps was completed")

  if state == accS:
    #f = open("output.txt","w")
    #f.write("1")
    #f.close()
    print("accept")
    print("Steps:", N)
    printTape(l,r)
    exit(0)

  if state == rejS:
    #f = open("output.txt","w")
    #f.write("0")
    #f.close()
    print("reject")
    print("Steps:", N)
    exit(0)
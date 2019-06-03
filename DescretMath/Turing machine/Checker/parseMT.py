config = open("config.txt")
cfg = config.readlines()
config.close()

cellDel = cfg[0].split("'")[1]
innerDel = cfg[1].split("'")[1]

goLeft = cfg[2].split("'")[1]
goRight = cfg[3].split("'")[1]
goHere = cfg[4].split("'")[1]
go = {goLeft : "<", goRight : ">", goHere : "^"}

startS = cfg[5].split("'")[1]
accS = cfg[6].split("'")[1]
rejS = cfg[7].split("'")[1]
eps = cfg[8].split("'")[1]

print("filename:")
filename = input()

f = open(filename)
t = f.readlines()
f.close()

for i in range(len(t)):
  t[i] = t[i].split("\n")[0].split(cellDel)

if startS == "first":
  startS = t[1][0]

answer = ""
answer += "start: " + startS + "\n"
answer += "accept: " + accS + "\n"
answer += "reject: " + rejS + "\n"
answer += "blank: " + eps + "\n"
for i in range(len(t)):
  if t[i][0] == 0:
    continue
  for j in range(len(t[0])):
    if i == 0 or j == 0:
      continue
    if t[i][j] == "":
      continue

    t[i][j] = t[i][j].split(innerDel)
    if t[i][j][1] == rejS:
      continue
    line = ""
    line += t[i][0] + " "
    line += t[0][j] + " "
    line += "->" + " "

    if t[i][j][1] == '~':
      t[i][j][1] = t[i][0]
    line += t[i][j][1] + " "

    if t[i][j][0] == '~':
      t[i][j][0] = t[0][j]
    line += t[i][j][0] + " "
    
    line += go[t[i][j][2]] + " "
    answer += line + "\n"

resfile = open("MTout.txt", "w")
resfile.write(answer)
resfile.close()
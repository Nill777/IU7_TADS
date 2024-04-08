import random as r
oper = ["+", "-", "*", "/"]
for i in range(100, 5001, 100):
    filename = "./data/test_{}.txt".format(i)
    with open(filename, "w") as f:
        for _ in range(i):
            f.write(str(r.randint(1, 10000)) + " ")
            f.write(r.choice(oper) + " ")
        f.write(str(r.randint(1,1000)) + "\n")
    f.close

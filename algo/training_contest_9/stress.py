from random import randint, shuffle
from os import popen
from time import clock, sleep
import numpy as np

def gen():
	with open("C.in", 'w') as f:
		with open("Cs.in", 'w') as f1:
			n = randint(1, 10)
			l = np.arange(1, n + 1)
			f.write(str(n) + '\n')
			f1.write(str(n) + '\n')
			shuffle(l)
			for x in l:
				f.write(str(x) + ' ')
				f1.write(str(x) + ' ')
				print(x, end=' ')
			print()
			f.write('\n')
			f1.write('\n')

popen("g++ C.cpp -o C -std=c++14 -fsanitize=bounds -fsanitize=undefined")
popen("g++ Cs.cpp -o Cs -std=c++14 -fsanitize=bounds -fsanitize=undefined")

for test in range(100):
	gen()
	sleep(0.1)
	process = popen("./C < C.in > C.out")
	process.close()
	sleep(0.2)
	process = popen("./Cs < C.in > Cs.out")
	process.close()
	sleep(0.2)
	with open('C.out') as f:
		ans1 = f.read()
	with open('Cs.out') as f:
		ans2 = f.read()
	sleep(0.1)
	if not ans1 == ans2:
		print('WA')
		print(ans1)
		print(ans2)
		break 
	print("OK", test)
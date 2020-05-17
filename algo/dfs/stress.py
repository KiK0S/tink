from os import popen
from random import randint
from time import sleep

def gen():
	with open('B.in', 'w') as f:
		f.write('1\n');
		n = randint(8, 10)
		m = randint(1, min(1000, n * (n - 1) // 2 - 20))
		f.write(str(n) + ' ' + str(m) + '\n')
		used = set()
		for i in range(m):
			a = randint(1, n)
			b = a
			while a == b or (a, b) in used:
				b = randint(1, n)
			used.add((a, b))
			used.add((b, a))
			f.write(str(a) + ' ' + str(b) + '\n')

popen('g++ B.cpp -o B -std=c++14 -O2 -fsanitize=undefined -fsanitize=bounds')
popen('g++ Bs.cpp -o Bs -std=c++14 -O2 -fsanitize=undefined -fsanitize=bounds')
sleep(3)
for test in range(1, 100):
	gen()
	process = popen('./B < B.in')
	ans1 = process.read()
	process.close()
	sleep(0.25)
	process = popen('./Bs < B.in')
	ans2 = process.read()
	process.close()
	sleep(0.25)
	if not ans1 == ans2:
		print('WA')
		print(ans1)
		print(ans2)
		break
	print('OK', test)

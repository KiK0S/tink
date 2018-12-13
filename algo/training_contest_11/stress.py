#!/home/kikos/anaconda3/bin/python3
from random import randint
from os import popen
from time import sleep

def gen():
	with open('C.in', 'w') as f:
		n = randint(4, 5)
		f.write(str(n) + '\n')
		for i in range(n):
			l = randint(1, 10)
			r = randint(l + 1, 11)
			a = randint(1, 10)
			b = randint(a + 1, 11)
			f.write(str(l) + ' ' + str(a) + ' ' + str(r) + ' ' + str(b) + '\n')

popen('g++ C.cpp -o C -std=c++14 -fsanitize=undefined')
sleep(1)
popen('g++ Cs.cpp -o Cs -std=c++14 -fsanitize=undefined')
sleep(1)

for test in range(1, 100):
	gen()
	process = popen('./C < C.in')
	ans1 = process.read()
	process.close()
	sleep(0.25)
	process = popen('./Cs < C.in')
	ans2 = process.read()
	process.close()
	sleep(0.25)
	if not ans1 == ans2:
		print('WA')
		print(ans1)
		print(ans2)
		break
	print('OK', test)
#!/home/kikos/anaconda3/bin/python3
from os import popen
from random import randint
from time import sleep

def gen():
	with open('C.in', 'w') as f:
		w = randint(1, 10)
		h = randint(1, 10)
		n = randint(1, 5)
		m = randint(1, 5)
		f.write(str(w) + ' ' + str(h) + '\n' + str(n) + ' ' + str(m) + '\n')
		d = set()
		for i in range(n):
			while 1:
				a, b = randint(1, w), randint(1, h)
				if not (a, b) in d:
					break
			d.add((a, b))
			f.write(str(a) + ' ' + str(b) + '\n')

		for i in range(m):
			while 1:
				a, b, c = randint(1, w), randint(1, h), randint(1, 10)
				if not (a, b) in d:
					break
			f.write(str(a) + ' ' + str(b) + ' ' + str(c) + '\n')
sleep(1)
popen('sudo g++ C.cpp -o C -std=c++14')
popen('sudo g++ Cs.cpp -o Cs -std=c++14')
sleep(1)
for test in range(1, 10000):
	gen()
	ans1 = popen('sudo ./C < C.in').read()
	# sleep(0.05)
	ans2 = popen('sudo ./Cs < C.in').read()
	# sleep(0.05)
	if ans1 != ans2:
		print('WA', test)
		print(ans1)
		print(ans2)
		break
	else:
		print('OK', test)
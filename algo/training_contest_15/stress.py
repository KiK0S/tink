#!/home/kikos/anaconda3/bin/python3
from random import randint
from os import popen
from time import sleep

def gen():
	with open('C.in', 'w') as f:
		n, m = randint(900, 1000), randint(900, 1000)
		f.write(str(n) + ' ' + str(m) + '\n')
		for i in range(n):
			for j in range(m):
				f.write(str(randint(0, 1)) + ' ')
			f.write('\n')

popen('g++ C.cpp -o C -std=c++14')
popen('g++ Cs.cpp -o Cs -std=c++14')
sleep(1)
for test in range(1, 1000):
	gen()
	ans1 = popen('./C < C.in').read()
	sleep(0.1)
	ans2 = popen('./Cs < C.in').read()
	sleep(0.1)
	if ans1 != ans2:
		print('WA')
		print(ans1)
		print('=========')
		print(ans2)
	else:
		print('OK', test)
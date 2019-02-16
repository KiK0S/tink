#!/home/kikos/anaconda3/bin/python3
from os import popen
from random import randint

def gen():
	with open('F.in', 'w') as f:
		n = randint(1, 10)
		f.write(str(n) + '\n')
		for i in range(n):
			a = randint(1, 20)
			f.write(str(a) + ' ')

popen('g++ F.cpp -o F -std=c++14')
popen('g++ Fs.cpp -o Fs -std=c++14')
for test in range(1, 100):
	gen()
	ans1 = popen('./F < F.in').read()
	ans2 = popen('./Fs < F.in').read()
	if ans1 != ans2:
		print('WA', test)
		print(ans1)
		print(ans2)
		break
	else:
		print('OK', test)

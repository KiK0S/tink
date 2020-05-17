from random import randint
from os import popen
from time import sleep

test_l = 62
test_r = 62

def gen(test):
	with open(test + '.dat', 'w') as f:
		n = 10 ** 5
		l = 0
		r = 10 ** 9
		f.write(str(n) + '\n')
		for i in range(n):
			x = randint(l, r)
			f.write(str(x) + ' ')
		f.write('\n')

popen('g++ sol.cpp -o sol -std=c++14')

for test in range(test_l, test_r + 1):
	name = str(test)
	while len(name) < 3:
		name = '0' + name
	name = './tests/' + name
	popen('touch ' + name + '.ans')
	popen('touch ' + name + '.dat')
	gen(name)
	with open(name + '.ans', 'w') as f:
		f.write(popen('./sol < ' + name + '.dat').read())
	sleep(1)
	print(test)
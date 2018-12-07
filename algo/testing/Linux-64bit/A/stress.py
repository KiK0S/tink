#!/home/kikos/anaconda3/bin/python3
from random import randint
from numpy.random import choice
from os import popen

fib = []
def calc():
	fib.append(1)
	fib.append(1)
	for i in range(200):
		fib.append(fib[-1] + fib[-2])

def gen(test):
	with open('./tests/001.dat', 'w') as f:
		with open('./tests/001.ans', 'w') as out:
			cnt = test
			f.write(str(cnt) + '\n')
			for i in range(cnt):
				if randint(1, 10) == 1:
					f.write(str(choice(fib)) + '\n')
					out.write('Yes\n')
				else:
					n = 1
					while n in fib:
						n = randint(10 ** 9, 10 ** 100)
					f.write(str(n) + '\n')
					out.write('No\n')

calc()
for test in range(1000):
	gen(test)
	ans = popen('./a < ./tests/001.dat').read()
	corr = popen('cat ./tests/001.ans').read()
	if not ans == corr:
		break
	print('OK', test)
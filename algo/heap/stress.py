#!/home/kikos/anaconda3/bin/python3
from os import popen
from random import randint
from time import sleep

def gen():
	with open('A.in', 'w') as f:
		n, m = randint(2, 3), 10
		f.write(str(n) + ' ' + str(m) + '\n')
		add_id = 0
		for i in range(m):
			tp = 0
			if i > 0:
				tp = randint(0, 5)
			if tp == 0:
				a = randint(1, n)
				b = randint(1, 100)
				f.write('0 ' + str(a) + ' ' + str(b) + '\n')
				add_id += 1
				continue
			if tp == 1:
				a = randint(1, n - 1)
				b = randint(a + 1, n)
				f.write('1 ' + str(a) + ' ' + str(b) + '\n')
				continue
			if tp == 2:
				a = randint(1, add_id)
				f.write('2 ' + str(a) + '\n')
				continue
			if tp == 3:
				a = randint(1, add_id)
				b = randint(1, 100)
				f.write('3 ' + str(a) + ' ' + str(b) + '\n')
				continue
			if tp == 4:
				a = randint(1, n)
				f.write('4 ' + str(a) + '\n')
				continue
			if tp == 5:
				a = randint(1, n)
				f.write('5 ' + str(a) + '\n')
				continue

popen('g++ A.cpp -o A -std=c++14')
popen('g++ As.cpp -o As -std=c++14')
sleep(1)
for test in range(1, 1000):
	gen()
	ans1 = popen('./A < A.in').read()
	ans2 = popen('./As < A.in').read()
	if ans1 != ans2:
		print('WA')
		print(popen('cat A.in').read())
		print('===')
		print(ans1)
		print('===')
		print(ans2)
		break
	print('OK', test)
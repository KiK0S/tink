#!/home/kikos/anaconda3/bin/python3
from random import randint, shuffle
import numpy as np
from os import popen, system
import string

def gen(test):
	with open('./tests/001.dat', 'w') as f:
		with open('./tests/001.ans', 'w') as out:
			ln = 10
			s = ''
			for _ in range(ln):
				s += np.random.choice(list(string.ascii_lowercase))
			f.write(s + '\n')
			out.write('Yes\n')

for test in range(10 ** 4):
	gen(test)
	ans = popen('./c < ./tests/001.dat').read()
	if not ans == 'Yes\n':
		print(ans)
		break
	print('OK', test)
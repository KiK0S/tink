#!/home/kikos/anaconda3/bin/python3
from random import randint, shuffle
import numpy as np
from os import popen, system

def gen(test):
	with open('./tests/001.dat', 'w') as f:
		with open('./tests/001.ans', 'w') as out:
			cnt = randint(10 ** 4, 10 ** 4)
			ans = 0
			f.write(str(cnt) + '\n')		
			for x in range(cnt - 1):
				n = 0
				ar = [0] * n
				srt = np.sort(ar)
				f.write(str(n) + ' ')
				for idx, x in enumerate(ar):
					f.write(str(x))
					if not idx == n - 1:
						f.write(' ')
				f.write('\n')
				for i in range(1, len(srt)):
					ans = max(ans, srt[i] - srt[i - 1])
			for x in range(1):
				n = 2
				ar = [0] * n
				srt = np.sort(ar)
				f.write(str(n) + ' ')
				for idx, x in enumerate(ar):
					f.write(str(x))
					if not idx == n - 1:
						f.write(' ')
				f.write('\n')
				for i in range(1, len(srt)):
					ans = max(ans, srt[i] - srt[i - 1])
			out.write(str(ans) + '\n')

for test in range(10 ** 5 - 100, 10 ** 5 + 1):
	gen(test)
	if (system('./b < ./tests/001.dat > ans.txt')):
		break
	ans = popen('cat ./ans.txt').read()
	corr = popen('cat ./tests/001.ans').read()
	if not ans == corr:
		print(ans)
		print(corr)
		break
	print('OK', test)
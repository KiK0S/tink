#!/home/kikos/anaconda3/bin/python3
from os import popen
from random import randint
from time import time, sleep

def gen():
	with open("F.in", "w") as f:
		n, m = 10 ** 1, 10 ** 1
		f.write(str(n) + '\n')
		for i in range(n):
			f.write(str(randint(0, 10 ** 6)) + ' ')
		f.write('\n' + str(m) + '\n')
		for i in range(m):
			c = randint(1, 10)
			l = randint(1, n)
			r = randint(1, n)
			if l > r:
				r, l = l, r
			if c <= 7:
				f.write("reverse " + str(l) + ' ' + str(r) + '\n')
			else:
				f.write("get " + str(l) + ' ' + str(r) + ' ' + str(randint(0, 10 ** 6)) + '\n')
			# if c == 3:
			# 	f.write("set " + str(l) + ' ' + str(r) + ' ' + str(randint(0, 10)) + '\n')


comp = popen("g++ -o F F.cpp -std=c++14 -fsanitize=bounds -fsanitize=undefined")
comp.close()
comp = popen("g++ -o Fs Fs.cpp -std=c++14")
comp.close()
for test in range(10):
	gen()
	start = time()
	process = popen("./F < F.in")
	ans1 = process.read()
	process.close()
	end = time()
	process = popen("./Fs < F.in")
	ans2 = process.read()
	process.close()
	if not ans1 == ans2:
		print('WA')
		print(ans1)
		print(ans2)
		break
	print('OK')
	print(end - start)
	sleep(1)

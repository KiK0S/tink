#!/home/kikos/anaconda3/bin/python3
from os import popen
from random import randint
from time import time, sleep

def gen():
	with open("D.in", "w") as f:
		n, m = 10 ** 5, 10 ** 5
		f.write(str(n) + ' ' + str(m) + '\n')
		for i in range(n):
			f.write(str(randint(1, 10 ** 5)) + ' ')
		f.write('\n')
		for i in range(m):
			a = randint(1, n)
			b = randint(1, n)
			if a == b:
				a += 1
				if a > n:
					a -= 2
			f.write(str(a) + ' ' + str(b) + '\n')
		q = 10 ** 5
		f.write(str(q) + '\n')
		for i in range(q):
			a = randint(1, n)
			b = randint(1, 10 ** 5)
			f.write(str(a) + ' ' + str(b) + '\n')
comp = popen("g++ -o D D.cpp -std=c++14 -fsanitize=bounds -fsanitize=undefined -DDEBUG")
comp.close()
# comp = popen("g++ -o Ds Ds.cpp -std=c++14 -DDEBUG")
# comp.close()
for test in range(10):
	gen()
	start = time()
	process = popen("./D")
	ans1 = process.read()
	process.close()
	end = time()
	# process = popen("./Ds")
	# ans2 = process.read()
	# process.close()
	# if not ans1 == ans2:
	# 	print('WA')
	# 	print(ans1)
	# 	print(ans2)
	print('OK')
	print(end - start)
	sleep(1)

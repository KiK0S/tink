#!/home/kikos/anaconda3/bin/python3
from os import popen
from random import randint

def gen():
	with open("B.in", "w") as f:
		n = 10 ** 6
		m = 10 ** 6
		k = 10 ** 3
		f.write(str(n) + ' ' + str(m) + ' ' + str(k) + '\n')
		for i in range(k):
			a = 0
			b = 0
			if randint(1, 2) == 1:
				f.write('R ')
				a = randint(1, n)
			else:
				f.write('S ')
				a = randint(1, m)
			b = randint(500000000, 1000000000)
			f.write(str(a) + ' ' + str(b) + '\n')


popen("g++ -o B B.cpp -std=c++14 -O2 -fsanitize=undefined -fsanitize=address -fsanitize=bounds")
# popen("g++ -o Bs Bs.cpp -std=c++14 -O2")

for test in range(100):
	gen()
	ans1 = popen("./B < B.in").read()
	# ans2 = popen("./Bs < B.in").read()
	# if not ans1 == ans2:
	# 	print("WA")
	# 	print(ans1)
	# 	print(ans2)
	# else:
		# print("OK")
		# print(ans1, ans2)
	print("OK")
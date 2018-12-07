from random import randint
from os import popen

def gen():
	with open('D.in', 'w') as f:
		n = randint(1, 15)
		f.write(str(n) + '\n')
		par = [0]
		f.write('0 ')
		q = []
		for i in range(2, n + 1):
			p = randint(1, i - 1)
			par.append(p)
			f.write('0 ')
			q.append((1, i, p))
		k = 5
		for i in range(k):
			t = randint(0, 0)
			a, b = (0, 0)
			if t == 0:
				a = randint(1, n)
				b = randint(1, n)
			q.append((0, a, b))
		f.write('\n' + str(len(q)) + '\n')
		for t, a, b in q:
			f.write(str(t) + ' ' + str(a) + ' ' + str(b) + '\n')

popen('g++ -std=c++14 D.cpp -o D')
popen('g++ -std=c++14 Ds.cpp -o Ds')

for test in range(100):
	gen()
	print('gen')
	ans1 = popen('./D <D.in').read()
	ans2 = popen('./Ds <D.in').read()
	if not ans1 == ans2:
		print(ans1)
		print(ans2)
		break
	print('OK', test)
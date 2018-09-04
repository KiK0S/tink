import pickle
import random
import learner
import re
import sys

class generator:
	def __init__(self, n=4):
		self.ngram_limit = n
		pass

	def find(self, _list):
		size = len(_list) + 1
		key = str(_list)
		with open('data_' + str(size), 'r') as f:
			lines = f.readlines()
			colloc_cnt = int(lines[0])
			l = 0
			r = colloc_cnt
			while l + 1 < r:
				mid = (l + r) // 2
				if lines[mid] < key and not lines[mid][:len(key) - 1] == key[:len(key) - 1]:
					l = mid
				else:
					r = mid
			left_idx = r
			l = 0
			r = colloc_cnt
			while l + 1 < r:
				mid = (l + r) // 2
				if lines[mid] < key:
					l = mid
				else:
					r = mid
			right_idx = r
			return [s[:-1].split('_') for s in lines[left_idx:right_idx + 1]]

	def my_random_choice(self, _list, cnt):
		prob = random.random()
		prob *= cnt
		for key in _list:
			if prob <= int(key[1]):
				key[0] = key[0][:-2]
				key[0] = key[0].split('\'')
				return key[0][-1]
			else:
				prob -= int(key[1])

	def generate_next(self, prev):
		n = len(prev)
		key = str(prev)
		if n >= self.ngram_limit:
			return self.generate_next(prev[1:])
		_next = self.find(prev)
		if len(_next) == 0:
			return self.generate_next(prev[1:])
		cnt_all = sum([int(x[1]) for x in _next])
		return self.my_random_choice(_next, cnt_all)

	def generate(self, size):
		s = []
		for i in range(size):
			s.append(self.generate_next(s))
		output = ""
		for val in s:
			output += val + ' '
		print(output)

gen = generator()

if len(sys.argv) >= 2:
	if sys.argv[1] == '-f':
		print('learn')
		lrn = learner.learner(gen.ngram_limit)
		lrn.loadtext()	
		lrn.fit()


tests = int(input()) # 'how many samples?'))
size = int(input()) # 'len?'))



for i in range(tests):
	gen.generate(size)
import pickle
import random
import learner
import re
import sys

class generator:
	def __init__(self, n=4):
		self.ngram_limit = n
		pass

	def check(self, a, b, eq):
		list_a = a.split('_')[0][1:-1].split(', ')
		list_b = b[1:-1].split(', ')
		for i in range(min(len(list_a), len(list_b))):
			if not list_a[i] == list_b[i]:
				return list_a[i] < list_b[i]
		return eq

	def find(self, _list):
		size = len(_list) + 1
		key = str(_list)
		with open('data_' + str(size), 'r') as f:
			lines = f.readlines()
			colloc_cnt = int(lines[0])
			if not size == 1:
				l = 0
				r = colloc_cnt
				while l + 1 < r:
					mid = (l + r) // 2
					if self.check(lines[mid], key, 0):
						l = mid
					else:
						r = mid
				left_idx = r
				l = 0
				r = colloc_cnt
				while l + 1 < r:
					mid = (l + r) // 2
					if self.check(lines[mid], key, 1):
						l = mid
					else:
						r = mid
				right_idx = r
			else:
				left_idx = 1
				right_idx = colloc_cnt
			result = [s[:-1].split('_') for s in lines[left_idx:right_idx]]
			# if len(result) == 0:
			# 	print(lines[left_idx - 10:left_idx + 10]) 
			# print([s[:-1].split('_') for s in lines[left_idx:right_idx]])
			return result

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
		sys.stderr.write(output + '\n')

gen = generator()

if len(sys.argv) >= 2:
	if sys.argv[1] == '-f':
		print('learn')
		lrn = learner.learner(gen.ngram_limit)
		lrn.fit()


tests = int(input()) # 'how many samples?'))
size = int(input()) # 'len?'))



for i in range(tests):
	gen.generate(size)
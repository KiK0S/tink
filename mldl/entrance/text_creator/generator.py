import pickle
import random
import learner
import re
import sys

class generator:
	def __init__(self):
		n = 5
		self.next = []
		self.next.append({})
		for i in range(1, n):
			dictionary = {}
			with open('data_' + str(i), 'rb') as f:
				dictionary = pickle.load(f)
			for s in dictionary:
				lst = re.findall(r'\'(.*?)\'', s)
				val = str(lst[:-1])
				if val not in self.next[-1]:
					self.next[-1][val] = []
				self.next[-1][val].append((lst[-1], dictionary[s]))
			self.next.append({})

	def my_random_choice(self, _list, cnt):
		prob = random.random()
		prob *= cnt
		for key in _list:
			if prob <= key[1]:
				return key[0]
			else:
				prob -= key[1]

	def generate_next(self, prev):
		n = len(prev)
		key = str(prev)
		if n >= len(self.next) or not key in self.next[n]:
			return self.generate_next(prev[1:])
		cnt_all = sum([x[1] for x in self.next[n][key]])
		return self.my_random_choice(self.next[n][key], cnt_all)

	def generate(self, size):
		s = []
		for i in range(size):
			s.append(self.generate_next(s))
		output = ""
		for val in s:
			output += val + ' '
		print(output)

obj = generator()
tests = int(input()) # 'how many samples?'))
size = int(input()) # 'len?'))

for i in range(tests):
	obj.generate(size)
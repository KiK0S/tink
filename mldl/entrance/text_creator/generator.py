import pickle
import random
import learner
import sys

class generator:
	def __init__(self):
		pass

	def load(self):
		with open('data_count', 'rb') as f:
			self.freq = pickle.load(f)
		self.all = sum(self.freq.values())
		with open('data_pairs', 'rb') as f:
			self.next = pickle.load(f)

	def generate_next_word(self, prev):
		prob = random.random()
		prob *= sum(self.next[prev].values())
		for val in self.next[prev]:
			if self.next[prev][val] >= prob:
				return val
			else:
				prob -= self.next[prev][val]

	def generate_first_word(self):
		prob = random.random()
		prob *= self.all
		for val in self.freq:
			if self.freq[val] >= prob:
				return val
			else:
				prob -= self.freq[val]

	def generate(self, n=9):
		prev = self.generate_first_word()
		s = prev + ' '
		for i in range(n):
			nxt = self.generate_next_word(prev)
			s += nxt + ' '
			prev = nxt
		print(s)

obj = generator()
obj.load()
obj.generate()
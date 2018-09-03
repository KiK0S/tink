import pickle
import random
import learner
import sys

class generator:
	def __init__(self):
		with open('data_triplets', 'rb') as f:
			self.trigram = pickle.load(f)
		pass

	def generate_trigram_word(self, first, second):
		prob = random.random()
		if second not in self.trigram[first]:
			return self.generate_bigram_word(second)
		prob *= sum(self.trigram[first][second].values())
		for val in self.trigram[first][second]:
			if self.trigram[first][second][val] >= prob:
				# print('trigram')
				# del self.trigram
				return val
			else:
				prob -= self.trigram[first][second][val]
		# del self.trigram
		return self.generate_bigram_word(second)

	def generate_bigram_word(self, prev):
		with open('data_pairs', 'rb') as f:
			self.bigram = pickle.load(f)
		prob = random.random()
		prob *= sum(self.bigram[prev].values())
		for val in self.bigram[prev]:
			if self.bigram[prev][val] >= prob:
				# print('bigram')
				del self.bigram
				return val
			else:
				prob -= self.bigram[prev][val]
		del self.bigram
		return self.generate_first_word()

	def generate_first_word(self):
		with open('data_count', 'rb') as f:
			self.freq = pickle.load(f)
		self.all = sum(self.freq.values())
		prob = random.random()
		prob *= self.all
		for val in self.freq:
			if self.freq[val] >= prob:
				# print('single')
				del self.freq
				return val
			else:
				prob -= self.freq[val]
		del self.freq

	def generate(self, n):
		s = []
		s.append(self.generate_first_word())
		s.append(self.generate_bigram_word(s[-1]))
		for i in range(n - 2):
			s.append(self.generate_trigram_word(s[-2], s[-1]))
		output = ""
		for val in s:
			output += val + ' '
		print(output)

# print('start')
obj = generator()
tests = int(input()) # 'how many samples?'))
ln = int(input()) #'len?'))

for i in range(tests):
	obj.generate(ln)
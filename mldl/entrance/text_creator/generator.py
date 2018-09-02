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
			self.bigram = pickle.load(f)
		with open('data_triplets', 'rb') as f:
			self.trigram = pickle.load(f)

	def generate_trigram_word(self, first, second):
		prob = random.random()
		if second not in self.trigram[first]:
			return self.generate_bigram_word(second)
		prob *= sum(self.trigram[first][second].values())
		for val in self.trigram[first][second]:
			if self.trigram[first][second][val] >= prob:
				# print('trigram')
				return val
			else:
				prob -= self.trigram[first][second][val]
		return self.generate_bigram_word(second)

	def generate_bigram_word(self, prev):
		prob = random.random()
		prob *= sum(self.bigram[prev].values())
		for val in self.bigram[prev]:
			if self.bigram[prev][val] >= prob:
				# print('bigram')
				return val
			else:
				prob -= self.bigram[prev][val]
		return self.generate_first_word()

	def generate_first_word(self):
		prob = random.random()
		prob *= self.all
		for val in self.freq:
			if self.freq[val] >= prob:
				# print('single')
				return val
			else:
				prob -= self.freq[val]

	def generate(self, n=10):
		s = []
		s.append(self.generate_first_word())
		s.append(self.generate_bigram_word(s[-1]))
		for i in range(n - 2):
			s.append(self.generate_trigram_word(s[-2], s[-1]))
		output = ""
		for val in s:
			output += val + ' '
		print(output)

obj = generator()
obj.load()
print('how many samples?')
sys.stdout = open('samples.txt', 'w')
for i in range(int(input())):
	obj.generate()
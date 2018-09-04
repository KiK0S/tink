import pickle
import sys

class learner:
	def __init__(self, n):
		self.dots = set()
		self.ngram_limit = n
	
	def loadtext(self):
		self.filename = 'book.txt'
		with open(self.filename, 'r') as f:
			self.text = f.read().lower()
		self.tokenize()

	def clear(self):
		new_tokens = []
		for i in range(len(self.tokens)):
			clear_token = ""
			last = False
			if not self.tokens[i][-1].isalpha() and not self.tokens[i][-1] == ',':
				last = True
			for c in self.tokens[i]:
				if c.isalpha() or (c == '-' and len(clear_token)):
					clear_token += c
			self.tokens[i] = clear_token
			if self.tokens[i] != '':
				if last:
					self.dots.add(len(new_tokens))
				new_tokens.append(self.tokens[i])
		self.tokens = new_tokens

	def tokenize(self):
		self.tokens = self.text.split()
		self.clear()

	def calc(self, size):
		for i in range(len(self.tokens) - size + 1):
			can = True
			for j in range(i, i + size):
				if j in self.dots:
					can = False
			if not can:
				continue
			all_list = self.tokens[i:i + size]
			key = str(all_list)
			if not key in self.value:
				self.value[key] = 0
			self.value[key] += 1

	def fit(self):
		for i in range(1, self.ngram_limit + 1):
			self.value = {}
			self.calc(i)
			self.save(i)

	def save(self, size):
		with open('data_' + str(size), 'wb') as f:
			_list = []
			for val in self.value:
				_list.append(val + '_' + str(self.value[val]) + '\n')
			_list.sort()
			f.write((str(len(_list)) + '\n').encode('utf-8'))
			for val in _list:
				f.write((val).encode('utf-8'))
import pickle
import sys

class learner:
	def __init__(self):
		self.triplets = {}
		self.pairs = {}
		self.count = {}
		self.dots = set()
	
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

	def calc_pairs(self):
		for i in range(len(self.tokens) - 1):
			s = self.tokens[i]
			if s not in self.pairs:
				self.pairs[s] = {}
			nxt = self.tokens[i + 1]
			if i not in self.dots:
				if nxt not in self.pairs[s]:
					self.pairs[s][nxt] = 0
				self.pairs[s][nxt] += 1
				
	def calc_triplets(self):
		for i in range(len(self.tokens) - 2):
			s = self.tokens[i]
			if s not in self.triplets:
				self.triplets[s] = {}
			nxt = self.tokens[i + 1]
			end = self.tokens[i + 2]
			if i not in self.dots and i + 1 not in self.dots:
				if nxt not in self.triplets[s]:
					self.triplets[s][nxt] = {}
				if end not in self.triplets[s][nxt]:
					self.triplets[s][nxt][end] = 0
				self.triplets[s][nxt][end] += 1

	def calc_counts(self):
		for s in self.tokens:
			if s not in self.count:
				self.count[s] = 0
			self.count[s] += 1

	def fit(self):
		self.calc_counts()
		self.calc_pairs()
		self.calc_triplets()

	def save(self):
		with open('data_count', 'wb') as f:
			pickle.dump(self.count, f)
		with open('data_pairs', 'wb') as f:
			pickle.dump(self.pairs, f)
		with open('data_triplets', 'wb') as f:
			pickle.dump(self.triplets, f)

if len(sys.argv) >= 2:
	if sys.argv[1] == '-f':
		print('learn')
		obj = learner()
		obj.loadtext()	
		obj.fit()
		obj.save()

import pickle

class learner:
	def __init__(self):
		self.pairs = {}
		self.count = {}
	
	def loadtext(self):
		self.filename = 'text.txt'
		with open(self.filename, 'r') as f:
			self.text = f.read().lower()
		self.tokenize()

	def clear(self):
		for i in range(len(self.tokens)):
			clear_token = ""
			for c in self.tokens[i]:
				if c.isalpha() or (c == '-' and len(clear_token)):
					clear_token += c
			self.tokens[i] = clear_token
		self.tokens = [s for s in self.tokens if s != '']

	def tokenize(self):
		self.tokens = self.text.split()
		self.clear()

	def calc_pairs(self):
		for i in range(len(self.tokens) - 1):
			s = self.tokens[i]
			if s not in self.pairs:
				self.pairs[s] = {}
			nxt = self.tokens[i + 1]
			if nxt not in self.pairs[s]:
				self.pairs[s][nxt] = 0
			self.pairs[s][nxt] += 1

	def calc_counts(self):
		for s in self.tokens:
			if s not in self.count:
				self.count[s] = 0
			self.count[s] += 1

	def fit(self):
		self.calc_counts()
		self.calc_pairs()

	def save(self):
		with open('data_count', 'wb') as f:
			pickle.dump(self.count, f)
		with open('data_pairs', 'wb') as f:
			pickle.dump(self.pairs, f)


obj = learner()
obj.loadtext()
obj.fit()
obj.save()
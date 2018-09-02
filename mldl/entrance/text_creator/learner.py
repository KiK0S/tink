import pickle

class learner:
	def __init__(self):
		self.dict = {}
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

	def calc(self):
		for s in self.tokens:
			if s not in self.count:
				self.count[s] = 0
			self.count[s] += 1

	def save(self):
		print('data = ' + str(self.count))
		with open('data_calc', 'wb') as f:
			pickle.dump(self.count, f)


obj = learner()
obj.loadtext()
obj.calc()
obj.save()
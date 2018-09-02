class learner:
	def __init__(self):
		self.dict = {}
		self.count = {}
	
	def loadtext(self):
		self.filename = 'text.txt'
		f = open(self.filename, 'r')
		self.text = f.read().lower()
		f.close()
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


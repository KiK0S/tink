#!/home/kikos/anaconda3/bin/python3
import re
with open('negative_words', 'w') as out:
	with open('website_negative_words', 'r') as f:
		s = ''
		for x in f.readlines():
			s += x
		lst = re.findall(r'strong2\'>(.+?)</span>', s)
		for i in range(0, len(lst), 2):
			out.write(lst[i] + ' ' + lst[i + 1] + '\n')
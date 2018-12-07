#!/home/kikos/anaconda3/bin/python3
import requests
import string
def send():
	headers = {
		'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8'
		,'Cookie': 'EJSID=3af1e71dc11ebd9e'
		,'Host': 'ejudge.algocode.ru'
		,'Origin': 'http://ejudge.algocode.ru'
		,'Referer': 'http://ejudge.algocode.ru/cgi-bin/new-client?SID=c7ff48fac062bc8e&action=139&prob_id=5'
	}
	r = requests.post(r'http://ejudge.algocode.ru/cgi-bin/new-client', {'SID':'c7ff48fac062bc8e', 'login':'a-amelichev', 'password':'ShaRedKey!', 'contest_id':'1012', 'action_40':'Отправить!', 'lang_id':'23', 'eoln_type':'0', 'prob_id':'5'}, files = {'file':open('scr.py', 'rb')}, headers=headers)
	# print(r.text)

att = 0

def gen(c):
	global att
	s = ''
	with open('scr.py', 'r') as f:
		s = f.readlines()
		s = s[:5]
		s = [str(x) for x in s]
		s.append("\tprint('" + c + "')\n")
		s.append("# " + str(att) + '\n')
		att += 1
	with open('scr.py', 'w') as f:
		for line in s:
			f.write(line)
for c in string.ascii_lowercase:
	print(c)
	gen(c)
	for _ in range(10):
		send()
import requests
import os
import re
import urllib.request
import time
import random

def random_name():
	s = ""
	for i in range(10):
		s += chr(ord('a') + random.randint(0, 25))
	return s

def download(url):
	print('downloading')
	try:
		link = 'https://www.litres.ru'
		web_page = requests.get(link + url)
		idx = web_page.text.find('<div class="biblio_book_download_file format_txt_zip">')
		download_link = re.search(r'class="biblio_book_download_file__link" href="(.+?)\?', web_page.text[idx:])
		url = link + download_link.group(1)
		# print(url)
		opener = urllib.request.build_opener()
		opener.addheaders.extend([('Cookie', 'SID=52edbr708mdodu8x1pan356m1d1c7i7t'), ('Cookie', 'tmr_detect=0%7C1535972145979'),
		 ('Cookie', 'sw_subscr=1'), ('Cookie', 'sw_metrics=1535972137016'), ('Cookie', 'sw_init=1535972137016'), 
		 ('Cookie', 'showpwd=2'), ('Cookie', r'mrc=app_id%3D611986%26is_app_user%3D0%26window_id%3DCometName_4d143816ef65aa307abef8dd3d4aea79'),
		 ('Cookie', '__atuvs=5b8d1116e65b9b58008'), ('Cookie', '__atuvc=17%7C36'), 
		 ('Cookie', 'LKS_LAST=0'), ('Cookie', 'BSK_LAST=0')])
		response = opener.open(url)
		data = response.read()
		file_name = random_name() + '.zip'
		with open('./data/zip/' + file_name, 'wb') as f:
			f.write(data)
		print('extracting')
		# print('unzip ./data/zip/' + file_name + ' -d ./data/txt')
		os.system('unzip ./data/zip/' + file_name + ' -d ./data/txt')
		print('done')
	except Exception as e:
		print(e)
		pass

os.system('rm book.txt')
os.system('rm ./data/txt/*')
os.system('rm ./data/zip/*')

for i in range(1, 10):
	print(i)
	link = 'https://www.litres.ru/kollekcii-knig/besplatnie-knigi/page-' + str(i) + '/'
	web_page = requests.get(link)
	# print(web_page.text)
	s = re.findall(r'<a href="(.*?)" class="cover_href">', web_page.text)
	# print(s)
	for url in s:
		download(url)
		time.sleep(1)
os.system('iconv -f WINDOWS-1251 -t UTF-8 -o ./book.txt ./data/txt/*')
os.system('cat text.txt >> book.txt')
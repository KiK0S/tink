import requests
import os
import re
import urllib.request
import random

def random_name():
	s = ""
	for i in range(10):
		s += chr(ord('a') + random.randint(0, 25))
	return s

def download(url):
	link = 'https://www.litres.ru'
	web_page = requests.get(link + url)
	idx = web_page.text.find('<div class="biblio_book_download_file format_txt_zip">')
	download_link = re.search(r'class="biblio_book_download_file__link" href="(.+?)\?', web_page.text[idx:])
	url = link + download_link.group(1)
	print(url)
	cookies = {'SID':'5qbwbw828ofkc46y279dao4f9p4d0i8q'}
	opener = urllib.request.build_opener()
	opener.addheaders.append(('Cookie', 'SID=5qbwbw828ofkc46y279dao4f9p4d0i8q'))
	response = opener.open(url)
	data = response.read()
	file_name = random_name() + '.zip'
	with open('./data/zip/' + file_name, 'wb') as f:
		f.write(data)
	# os.popen('unzip ./data/zip/' + file_name)


for i in range(1, 2):
	link = 'https://www.litres.ru/kollekcii-knig/besplatnie-knigi/page-' + str(i) + '/'
	web_page = requests.get(link)
	s = re.findall(r'<a href="(.*?)" class="cover_href">', web_page.text)
	download(s[0])
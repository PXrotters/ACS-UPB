import requests
from bs4 import BeautifulSoup


url = 'https://www.versuri.ro/versuri/florin-salam-saint-tropez-1/'


response = requests.get(url)
html_content = response.content


soup = BeautifulSoup(html_content, 'html.parser')


lyrics_div = soup.find('div', class_='hidemobile')
lyrics = lyrics_div.find('p').get_text()


lyrics = lyrics.replace('<br>', '\n')


print(lyrics)
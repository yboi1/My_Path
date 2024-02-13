import requests
import xlwt
from bs4 import BeautifulSoup
headers = {
    "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/111.0.0.0 Safari/537.36"
}
i = 1
work_boot = xlwt.Workbook(encoding='utf-8')
sheet = work_boot.add_sheet('Top250', cell_overwrite_ok=True)
for Start_num in range(0, 250, 25):
    response = requests.get(f"http://movie.douban.com/top250?start={Start_num}", headers=headers)
    html = response.text
    soup = BeautifulSoup(html, "html.parser")
    all_titles = soup.findAll("span", attrs={"class": "title"})
    for title in all_titles:
        title_string = title.string
        if "/" not in title_string:
            sheet.write(i, 0, title_string)
            i = i + 1
work_boot.save("Douban.xls")

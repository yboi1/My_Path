import requests
response = requests.get("http:/movie.douban.com/top250")
if response.ok:
    print(response.text)
else:
    print("请求失败")
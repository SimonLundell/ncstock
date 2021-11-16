import requests
import json
import csv

# replace the "demo" apikey below with your own key from https://www.alphavantage.co/support/#api-key
#stock_url = 'https://www.alphavantage.co/query?function=TIME_SERIES_INTRADAY&symbol=IBM&interval=5min&apikey=4PC87FQ16E7YV46Q'
#r = requests.get(stock_url)
#stock_data = r.json()
#
#btc_url = 'https://www.alphavantage.co/query?function=CURRENCY_EXCHANGE_RATE&from_currency=BTC&to_currency=USD&apikey=4PC87FQ16E7YV46Q'
#b = requests.get(btc_url)
#btc_data = b.json()
#
#with open('api.json','w') as f:
#    for line in btc_data:
#        json.dump(btc_data,f)
#    f.close()

#url = "https://www.alphavantage.co/query?function=LISTING_STATUS&date=2021-11-15&apikey=4PC87FQ16E7YV46Q"
url = "https://www.alphavantage.co/query?function=SYMBOL_SEARCH&keywords=BA&apikey=4PC87FQ16E7YV46Q&datatype=csv"

d = requests.get(url)
dd = d.content.decode('utf-8')
cr = csv.reader(dd.splitlines(),delimiter=',')

with open('listings.csv','w') as f:
    for line in list(cr):
        f.write(str(line) + "\n")
    f.close()


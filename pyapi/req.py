import requests

# replace the "demo" apikey below with your own key from https://www.alphavantage.co/support/#api-key
stock_url = 'https://www.alphavantage.co/query?function=TIME_SERIES_INTRADAY&symbol=IBM&interval=5min&apikey=4PC87FQ16E7YV46Q'
r = requests.get(stock_url)
stock_data = r.json()

btc_url = 'https://www.alphavantage.co/query?function=CURRENCY_EXCHANGE_RATE&from_currency=BTC&to_currency=USD&apikey=4PC87FQ16E7YV46Q'
b = requests.get(btc_url)
btc_data = b.json()

print(btc_data)

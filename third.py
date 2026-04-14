def detect_fraud(trades):
    last_buy = {}
    result = []

    for i, (trade_type, price, trader) in enumerate(trades):

        if trade_type == "buy":
            last_buy[trader] = (price, i)

        elif trade_type == "sell":
            if trader in last_buy:
                buy_price, buy_index = last_buy[trader]

                if (i - buy_index) <= 3 and price > buy_price:
                    result.append(trader)

    return result


if __name__ == "__main__":
    trades = [
        ("buy", 5, "trader1"),
        ("sell", 10, "trader1"),
        ("buy", 8, "trader2"),
        ("sell", 7, "trader2"),
        ("buy", 6, "trader3"),
        ("sell", 6, "trader3")
    ]

    print(detect_fraud(trades))  
    # Output: ['trader1']

def cart():
    total = 0
    def add(price):
        nonlocal total
        total += price
        return total
    return add
add_to_cart = cart()
print(add_to_cart(100))  
print(add_to_cart(50))
text = "3865"
number = 0
for ch in text:
    digit = ord(ch) - ord('0')
    number = number * 10 + digit
print(number)
print(type(number))
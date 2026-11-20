text = "banana"
fre = {}
for ch in text:
    if ch in fre:
        fre[ch] += 1
    else:
        fre[ch] = 1
most_fre = ""
max_count = 0
def length_of_longest_substring(text):
    last_seen = {}
    start = 0
    longest = 0

    for index, character in enumerate(text):
        if character in last_seen and last_seen[character] >= start:
            start = last_seen[character] + 1

        last_seen[character] = index
        longest = max(longest, index - start + 1)

    return longest


text = input("Enter a string: ")
print(length_of_longest_substring(text))
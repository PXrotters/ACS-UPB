with open('filename.txt', 'r') as f:
    text = f.read()


word_counts = {}
for word in text.lower().split():
    if word.isalpha():
        if word in word_counts:
            word_counts[word] += 1
        else:
            word_counts[word] = 1


top_5_words = sorted(word_counts.items(), key=lambda x: x[1], reverse=True)[:5]


print("Top 5 most frequent words:")
for word, count in top_5_words:
    print(f"{word}: {count}")
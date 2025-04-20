with open("txt_parser/war_and_peace_words.txt", 'r', encoding='cp1252') as f:
    text = f.read().split("\n")
    m = 0
    for word in text:
        if len(word) >= 32:
            print(word)
        else:
            m = max(m, len(word))

    print(m)



import re

def process_text(input_file, output_file):
    with open(input_file, 'r', encoding='cp1252') as f:
        text = f.read()

    # Удаление заголовков глав и частей
    text = re.sub(r'PART\s+\w+|VOLUME\s+\w+|Том\s+\w+', '', text, flags=re.IGNORECASE)

    # Удаление знаков препинания
    text = re.sub(r'[^\w\s]', '', text)

    text = text.lower()
    words = text.split()

    with open(output_file, 'w', encoding='cp1252') as f:
        for word in words:
            f.write(word + '\n')

# Пример использования
process_text('txt_parser/war_and_peace.txt', 'txt_parser/war_and_peace_words.txt')

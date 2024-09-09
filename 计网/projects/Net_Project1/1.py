with open('exampleFile.txt', 'w', encoding='utf-8') as file:
    for i in range(150000):
        file.write(f'{i} This is a text from 1120211099\n')
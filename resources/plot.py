import csv
import matplotlib.pyplot as plt
import sys 


if len(sys.argv) > 1:
    csv_path = sys.argv[1]
    print("CSV Path:", csv_path)
else:
    print("No CSV path provided.")

n_values = []
greedy_values = []
genetic_values = []
recursive_values = []

with open(csv_path, 'r') as file:
    reader = csv.reader(file)
    next(reader) 

    for row in reader:
        n = int(row[0])
        greedy = float(row[1])
        genetic = float(row[2])
        recursive = float(row[3])

        n_values.append(n)
        greedy_values.append(greedy)
        genetic_values.append(genetic)
        recursive_values.append(recursive)


plt.plot(n_values, greedy_values, label='Жадібний')
plt.plot(n_values, genetic_values, label='Генетичний')
plt.plot(n_values, recursive_values, label='Рекурсивний')

if sys.argv[2] == '0':
    plt.xlabel('Кількість ворожих пунктів')
    plt.ylabel('Час роботи в секундах')
    plt.title('Залежність часу роботи алгоритмів від кількості ворожих пунктів')
else:
    plt.xlabel('Кількість ворожих пунктів')
    plt.ylabel('Похибка результату роботи')
    plt.title('Залежність похибки результату роботи алгоритмів від кількості ворожих пунктів')

plt.legend()
plt.show()
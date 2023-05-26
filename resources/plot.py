import csv
import matplotlib.pyplot as plt
import sys

if len(sys.argv) > 1:
    csv_path = sys.argv[1]
    print("CSV Path:", csv_path)
else:
    print("No CSV path provided.")

mr_values = []
genetic_values = []

with open(csv_path, 'r') as file:
    reader = csv.reader(file)
    next(reader)  

    for row in reader:
        mr = float(row[0])
        genetic = float(row[1])

        mr_values.append(mr)
        genetic_values.append(genetic)

plt.plot(mr_values, genetic_values)

plt.xlabel('Сила мутації')

if sys.argv[2] == '0':
    plt.ylabel('Час роботи')
    plt.title('Залежність часу роботи алгоритму від зміни параметру сили мутації')
else:
    plt.ylabel("Похибка результату роботи")
    plt.title('Залежність похибки результату роботи алгоритму від зміни параметру сили мутації')

plt.show()
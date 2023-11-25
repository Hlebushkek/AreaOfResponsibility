import csv
import matplotlib.pyplot as plt
import sys 


if len(sys.argv) > 1:
    csv_path = sys.argv[1]
    print("CSV Path:", csv_path)
else:
    print("No CSV path provided.")

if sys.argv[2] == 'all':
    n_values = []
    greedy_values = []
    genetic_values = []
    genetic_advanced_values = []
    recursive_values = []

    with open(csv_path, 'r') as file:
        reader = csv.reader(file)
        next(reader) 

        for row in reader:
            n = int(row[0])
            greedy = float(row[1])
            genetic = float(row[2])
            genetic_advanced = float(row[3])
            recursive = float(row[4])

            n_values.append(n)
            greedy_values.append(greedy)
            genetic_values.append(genetic)
            genetic_advanced_values.append(genetic_advanced)
            recursive_values.append(recursive)


    plt.plot(n_values, greedy_values, label='EA1')
    plt.plot(n_values, genetic_values, label='GA1')
    plt.plot(n_values, genetic_advanced_values, label='GA2')
    plt.plot(n_values, recursive_values, label='EA2')

    if sys.argv[3] == '0':
        plt.xlabel('Кількість об\'єктів')
        plt.ylabel('Час роботи в секундах')
        plt.title('Залежність часу роботи алгоритмів від кількості об’єктів')
    else:
        plt.xlabel('Кількість об\'єктів')
        plt.ylabel('Похибка результату роботи')
        plt.title('Залежність похибки результату роботи алгоритмів від кількості об’єктів')

    plt.legend()
    plt.show()

elif sys.argv[2] == "genetic":
    mr_values = []
    genetic_values = []
    genetic_advanced_values = []

    with open(csv_path, 'r') as file:
        reader = csv.reader(file)
        next(reader)  

        for row in reader:
            mr = float(row[0])
            genetic = float(row[1])
            genetic_advanced = float(row[2])

            mr_values.append(mr)
            genetic_values.append(genetic)
            genetic_advanced_values.append(genetic_advanced)

    plt.plot(mr_values, genetic_values, label='GA1')
    plt.plot(mr_values, genetic_advanced_values, label='GA2')

    plt.xlabel('Δ')

    if sys.argv[3] == '0':
        plt.ylabel('Час роботи')
        plt.title('Залежність часу роботи алгоритмів GA від зміни параметру Δ')
    else:
        plt.ylabel("Похибка результату роботи")
        plt.title('Залежність похибки результату роботи алгоритмів GA від зміни параметру Δ')

    plt.legend()
    plt.show()
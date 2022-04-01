mas = [11, 112, 1233, 12344, 21321, 43534, 6546, 432, 110000]
sum = 0
i = 0
while (i < len(mas) - 1):
    f = i+1
    while (f < len(mas)):
        if mas[i] < mas[f]:
            mas[i], mas[f] = mas[f], mas[i]
        f += 1
    sum += mas[i]
    if (sum >= 130000):
        print("Сумма: " + str(sum) + "\nПоследнее слагаемое: " + str(mas[i]) + "\nНомер слагаемого: " + str(i + 1))
        break;
    i += 1
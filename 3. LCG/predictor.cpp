#include "lcg.h"

#include <cmath>
#include <vector>
#include <numeric>
#include <iostream>

/* вычисляем определитель матрицы 3x3 */
int calcDet(int val1, int val2, int val3, int val4)
{
    return std::abs(val1 * val3 - val1 * val4 + val2 * val3 - val2 * val2 + val2 * val4 - val3 * val3);
}

/* m с высокой вероятностью является наибольшим общим делителем найденных определителей */
int calcM(const std::vector<int> &determinants)
{
    int result = determinants[0];
    for (int i = 1; i < determinants.size(); i++)
    {
        result = std::gcd(result, determinants[i]);
    }
    return result;
}

/* */
void linsolve(int x1, int x2, int x3, int m, int *a, int *k)
{
    *a = (x2 - x3) / (x1 - x2);
    *k = x2 - *a * x1;
}


int main()
{
    std::cout << "6 generated numbers: \n";
    std::vector<int> known_numbers;
    for (int i = 0; i < 6; i++)
    {
        known_numbers.push_back(myrand());         // даже 6 чисел не всегда достаточно, но это минимум
        std::cout << known_numbers[i] << " ";
    }
    std::cout << "\n\n";

    std::cout << "Calculating m... \n";
    std::vector<int> determinants(known_numbers.size() - 3);        // создаём вектор для определителей матриц 3х3 особого вида, из которых затем вычисляется m
    for (int i = 0; i < determinants.size(); i++)
    {
        determinants[i] = calcDet(known_numbers[i], known_numbers[i + 1], known_numbers[i + 2], known_numbers[i + 3]);
    }
    int probable_m = calcM(determinants);       // находим м, который скорее всего является Наибольшим общим делителем среди определителей
    std::cout << "m is probably: " << probable_m << "\n\n";

    std::cout << "Calculating a, k ... \n";
    int a, k;
    linsolve(known_numbers[0], known_numbers[1],        // зная m, находим a и k. Можно и seed найти, но a,k и m достаточно для нахождения следующего генерируемого числа
             known_numbers[2], probable_m, &a, &k);
    std::cout << "a is " << a << ", k is " << k << "\n\n";

    int next_number = (a * known_numbers.back() + c) % m;       // формула линейного конгруэнтного генератора; генерируем следующее число за последним известным.
    std::cout << "Next number will be " << next_number << "\n";
    std::cout << "Actual generated number is: " << myrand() << "\n";    // проверяем, что генератор выдаёт то же число, что и вычисленное нами

    return 0;
}
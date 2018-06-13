//ФИО: Ярных Роман Вячеславович
//Группа: БПИ141
//Подгруппа: 2
//Дата: 12.12.2015
//Проект: решение задачи о рюкзаке (КДЗ №1)
//Номер проекта: 8
//Среда: Clion (Mac Os X)
//Язык программирования: C++11
//Компилятор: gcc (g++)

#ifndef KNAPSACKPROBLEM_TIMECOUNTER_H
#define KNAPSACKPROBLEM_TIMECOUNTER_H
#include <chrono>

using namespace std::chrono;

//Класс для измерения времени работы вызвающего контекста
class TimeCounter {
private:
    //точки отсчета времени
    static high_resolution_clock::time_point a, b;
public:
    static void enter();
    static long long int leave();
};


#endif //KNAPSACKPROBLEM_TIMECOUNTER_H

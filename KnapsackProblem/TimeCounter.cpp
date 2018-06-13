//ФИО: Ярных Роман Вячеславович
//Группа: БПИ141
//Подгруппа: 2
//Дата: 12.12.2015
//Проект: решение задачи о рюкзаке (КДЗ №1)
//Номер проекта: 8
//Среда: Clion (Mac Os X)
//Язык программирования: C++11
//Компилятор: gcc (g++)

#include "TimeCounter.h"

high_resolution_clock::time_point TimeCounter::a;
high_resolution_clock::time_point TimeCounter::b;

//Запуск отсчета времени
void TimeCounter::enter() {
    a = high_resolution_clock::now();
}

//Подсчет прошедших с начала запуска счетчика времени наносекунд
//** возврщаемое значение **
//long long int - число прошедших наносекунд
long long int TimeCounter::leave() {
    b = high_resolution_clock::now();
    return duration_cast<nanoseconds>(b - a).count();
}

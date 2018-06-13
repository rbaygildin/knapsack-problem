//ФИО: Ярных Роман Вячеславович
//Группа: БПИ141
//Подгруппа: 2
//Дата: 12.12.2015
//Проект: решение задачи о рюкзаке (КДЗ №1)
//Номер проекта: 8
//Среда: Clion (Mac Os X)
//Язык программирования: C++11
//Компилятор: gcc (g++)

#include <iostream>
#include <fstream>
#include "KPSolver.h"
#include "TimeCounter.h"

using namespace std;

//Точка входа программы
int main() {

    //исходный файл с тестами
    ifstream input("input_knap.txt");
    //выходной файл с решениями
    ofstream output("output_knap.txt");
    //выходной файл с измерениями времени
    ofstream time_table("time_table.csv");

    int nt;
    input >> nt;
    if(nt <= 0)
        return 0;
    time_table << "Test,N,Backtracking (ns),Recursive (ns),Greedy (ns),Dynamic (ns)" << endl;
    for(int i = 1; i <= nt; i++){
        int n, w;
        input >> w;
        input >> n;
        vector<Element> test;
        for(int j = 0; j < n; j++){
            Element element;
            int el_w;
            input >> el_w;
            element.weight = el_w;
            test.push_back(element);
        }
        for(int j = 0; j < n; j++){
            int p;
            input >> p;
            test[j].price = p;
        }
        output << "======Test " << i << "======" << endl;
        cout << "======Test " << i << "======" << endl;
        int price_acc = 0;
        long long int perfTime1, perfTime2, perfTime3, perfTime4;

        time_table << i << "," << n;
        TimeCounter::enter();
        KPSolver::solveBacktrack(w, test, price_acc);
        perfTime1 = TimeCounter::leave();
        time_table << "," << perfTime1;


        TimeCounter::enter();
        KPSolver::solveRecur(w, test, price_acc);
        perfTime2 = TimeCounter::leave();
        time_table << "," << perfTime2;

        TimeCounter::enter();
        KPSolver::solveGreedy(w, test, price_acc);
        perfTime3 = TimeCounter::leave();
        time_table << "," << perfTime3;


        TimeCounter::enter();
        vector<Element> result = KPSolver::solveDynamic(w, test, price_acc);
        perfTime4 = TimeCounter::leave();
        time_table << "," << perfTime4 << endl;

        output << "| Weight: " << w << endl;
        cout << "| Weight: " << w << endl;
        output << "| Accumulated price: " << price_acc << endl;
        cout << "| Accumulated price: " << price_acc << endl;
        output << "| Taken elements: " << endl;
        cout << "| Taken elements: " << endl;
        for_each(result.begin(), result.end(), [&output](Element element){
            output << "| {w = " << element.weight << ", p = " << element.price << "} " << endl;
            cout << "| {w = " << element.weight << ", p = " << element.price << "} " << endl;
        });
        output << "| Backtracking method perfomance (ns): " << perfTime1 << endl;
        cout << "| Backtracking method perfomance (ns): " << perfTime1 << endl;
        output << "| Recursive method perfomance (ns): " << perfTime2 << endl;
        cout << "| Recursive method perfomance (ns): " << perfTime2 << endl;
        output << "| Greedy method perfomance (ns): " << perfTime3 << endl;
        cout << "| Greedy method perfomance (ns): " << perfTime3 << endl;
        output << "| Dynamic method perfomance (ns): " << perfTime4 << endl;
        cout << "| Dynamic method perfomance (ns): " << perfTime4 << endl;
        output << "-------------------------------" << endl;
        cout << "-------------------------------" << endl;

    }

    input.close();
    output.close();
    time_table.close();

    return 0;
}
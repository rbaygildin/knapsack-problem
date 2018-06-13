//ФИО: Ярных Роман Вячеславович
//Группа: БПИ141
//Подгруппа: 2
//Дата: 12.12.2015
//Проект: решение задачи о рюкзаке (КДЗ №1)
//Номер проекта: 8
//Среда: Clion (Mac Os X)
//Язык программирования: C++11
//Компилятор: gcc (g++)

#ifndef KNAPSACKPROBLEM_KPSOLVER_H
#define KNAPSACKPROBLEM_KPSOLVER_H


#include <vector>
#include <stack>
using namespace std;

struct Element{
    int weight;
    int price;
};

struct ElementDensity{
    int weight;
    int price;
    int density;
};

struct ElementNumber{
    Element element;
    unsigned long number;
};

//Класс, икапсулирующий методы решения задачи о рюкзаке
class KPSolver {
public:
    static vector<Element> solveGreedy(int kp_w, vector<Element> elements, int&);
    static vector<Element> solveDynamic(int kp_w, vector<Element> elements, int&);
    static vector<Element> solveRecur(int kp_w, vector<Element> elements, int&);
    static vector<Element> solveBacktrack(int kp_w, vector<Element> elements, int&);
};


#endif //KNAPSACKPROBLEM_KPSOLVER_H

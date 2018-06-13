//ФИО: Ярных Роман Вячеславович
//Группа: БПИ141
//Подгруппа: 2
//Дата: 12.12.2015
//Проект: решение задачи о рюкзаке (КДЗ №1)
//Номер проекта: 8
//Среда: Clion (Mac Os X)
//Язык программирования: C++11
//Компилятор: gcc (g++)

//В рамках проекта было реализовано 4 алгоритма для решения задачи о рюкзаке:
//1. итеративный перебор с возвратом
//2. рекурсивный перебор с возвратом
//3. жадный алгоритм
//4. динамическое программирование

#include "KPSolver.h"

int BKKPSolve(int, unsigned long, vector<Element>, long long int& pack);
//int BKKPSolve2(int w, unsigned long n, vector<Element> elements, bool[] taken);

//Метод жадного алгоритма
//** параметры **
//int kp_w - максимальный вес рюкзака
//vector<Element> elements - исходный набор предметов
//int& maxPrice - максимальная стоимость набора предметов
//** возврщаемое значение **
//vector<Element> - набор элементов, который будет упакован
vector<Element> KPSolver::solveGreedy(int kp_w, vector<Element> elements, int& maxPrice) {

    //наше решение в виде набора предметов, которые попадут в рюкзак
    vector<Element> solution;
    //вектор для реализации жадного алгоритма
    vector<ElementDensity> solution_table;
    //заполняем вектор решения исходными предметами вместе с их удельной стоимостью
    for(vector<Element>::iterator it = elements.begin(); it != elements.end(); it++){
        ElementDensity elementDensity;
        elementDensity.weight = (*it).weight;
        elementDensity.price = (*it).price;
        //считаем для каждого предмета удельную стоимость (единица стоимости на вес)
        elementDensity.density = elementDensity.price / elementDensity.weight;
        solution_table.push_back(elementDensity);
    }
    //сортируем полученный вектор решения по убыванию удельной стоимости
    sort(solution_table.begin(), solution_table.end(), [](ElementDensity a, ElementDensity b){
        return b.density < a.density;
    });
    //текущий вес набора
    int w_current = 0;
    //текущая стоимость
    maxPrice = 0;
    for(vector<ElementDensity>::iterator it = solution_table.begin(); it != solution_table.end(); it++){
        w_current += (*it).weight;
        //если мы не можем добавить новый предмет в рюкзак, то завершаем цикл
        if(w_current > kp_w)
            break;
        Element element;
        element.weight = (*it).weight;
        element.price = (*it).price;
        maxPrice += (*it).price;
        //кладем в набор следующий предмет
        solution.push_back(element);
    }

    //возвращаем полученный набор
    return solution;

}

//Метод динамического программирования
//** параметры **
//int kp_w - максимальный вес рюкзака
//vector<Element> elements - исходный набор предметов
//int& maxPrice - максимальная стоимость набора предметов
//** возврщаемое значение **
//vector<Element> - набор элементов, который будет упакован
vector<Element> KPSolver::solveDynamic(int kp_w, vector<Element> elements, int& maxPrice) {

    unsigned long n = elements.size();
    vector<Element> solution;
    //создаем матрицу, в которой мы будем хранить наибольшую стоимость, которую можно набрать
    //при весе рюкзака w из первых i элементов
    int** table = new int*[n + 1];
    for(unsigned long i = 0; i < n + 1; i++){
        table[i] = new int[kp_w + 1];
    }
    //инициализируем table[n][0] нулем
    for(unsigned long i = 0; i <= n; i++){
        table[i][0] = 0;
    }
    //инициализируем table[0][w] нулем
    for(unsigned long i = 0; i <= kp_w; i++){
        table[0][i] = 0;
    }
    //решаем задачу о рюкзаке с помощью динамического программирования
    for(unsigned long k = 1; k <= n; k++){
        for(unsigned long w = 1; w <= kp_w; w++){
            //если мы не можем положить следующий предмет, то оставляем текущую стоимость
            if(elements[k - 1].weight > w)
                table[k][w] = table[k - 1][w];
            //выбираем максимум стоимости из двух вариантов
            //1. добавляем новый предмет и к текущей стоимости прибавляем стоимость нового предмета
            //2. оставляем все, как есть
            else
                table[k][w] = max(table[k - 1][w], table[k - 1][w - elements[k - 1].weight] + elements[k - 1].price);
        }
    }
    unsigned long k = n;
    unsigned long w = static_cast<unsigned long>(kp_w);
    maxPrice = table[k][w];

    //найдем лучший с точки зрения максимальной стоимости набор предметов
    while(table[k][w] > 0){
        //если стоимость набора при k предмета равна стоимости набора при k - 1 предметов
        //то мы не брали k-й предмет
        if(table[k][w] == table[k - 1][w])
            k--;
        //иначе заносим в решение
        else{
            solution.insert(solution.begin(), elements[k - 1]);
            w -= elements[k - 1].weight;
            k--;
        }
    }
    for(int i = 0; i <= n; i++)
        delete[] table[i];
    delete[] table;
    return solution;
}

//Метод рекурсивного перебора с возвратом
//** параметры **
//int kp_w - максимальный вес рюкзака
//vector<Element> elements - исходный набор предметов
//int& maxPrice - максимальная стоимость набора предметов
//** возврщаемое значение **
//vector<Element> - набор элементов, который будет упакован
vector<Element> KPSolver::solveRecur(int kp_w, vector<Element> elements, int& maxPrice) {
    vector<Element> solution;
    //битовая маска, хранящая информацию о том, какие элементы будут положены в рюкзак
    long long int pack = 0;
    //максимальная стоимость
    maxPrice = BKKPSolve(kp_w, elements.size(), elements, pack);
    for(unsigned long i = 0; i < elements.size(); i++){
        if((pack >> i) & 1)
            solution.push_back(elements[i]);
    }
    return solution;
}



//Метод итеративного перебора с возвратом
//** параметры **
//int kp_w - максимальный вес рюкзака
//vector<Element> elements - исходный набор предметов
//int& maxPrice - максимальная стоимость набора предметов
//** возврщаемое значение **
//vector<Element> - набор элементов, который будет упакован
vector<Element> KPSolver::solveBacktrack(int kp_w, vector<Element> elements, int& maxPrice){

    //текущий набор предметов
    stack<ElementNumber> pack;
    //лучший набор предметов
    stack<ElementNumber> bestPack;
    //решение задачи
    vector<Element> solution;
    //максимальная стоимость
    maxPrice = -1;
    unsigned long n = elements.size();
    //текущее свободное место
    int freeSpace = kp_w;
    //текущая стоимость
    int currentPrice = 0;
    //номер последнего добавленного в набор элемента
    unsigned long head = 0;
    //пытаемся построить наиболее хороший набор с максимальной стоимость
    while(true){
        //докладываем рюкзак до тех пор, пока элементы не закончатся или вес набора не превысит лимит
        while(head < n){
            //если есть еще свободное место, то докладываем в рюкзак новый предмет
            if(freeSpace - elements[head].weight >= 0){
                ElementNumber elementNumber;
                elementNumber.element = elements[head];
                elementNumber.number = head;
                pack.push(elementNumber);
                currentPrice += elements[head].price;
                freeSpace -= elements[head].weight;
                //если стоимость полученного набора оказалась лучше, то считаем ее максимальной
                if(currentPrice > maxPrice) {
                    maxPrice = currentPrice;
                    bestPack = pack;
                }
                head++;
            }
            //если текущий предмет не влезает в рюкзак, то берем другой предмет
            //и пытаемся положить его
            else
                head++;
        }
        if(pack.empty())
            break;
        head = pack.top().number + 1;
        currentPrice -= pack.top().element.price;
        freeSpace += pack.top().element.weight;
        pack.pop();
    }
    while(!bestPack.empty()) {
        solution.push_back(bestPack.top().element);
        bestPack.pop();
    }
    return solution;
}

//Метод для реализации рекурсивного перебора с возвратом (внутренняя ф-ция для метода KPSolver::solveRecur())
int BKKPSolve(int w, unsigned long n, vector<Element> elements, long long int& pack){
    //Если у нас нет предметов или свободного места, то возвращаем нулевую стоимость
    if(n == 0 || w == 0) {
        pack = 0;
        return 0;
    }
    //Если невозможно доложить новый предмет в рюкзак, то максимальня стоимость остается той же,
    //а лучший набор не меняется
    if(elements[n - 1].weight > w) {
        return BKKPSolve(w, n - 1, elements, pack);
    }
    else{
        //текущий набор предметов + текущий предмет
        long long int pack1 = 0;
        //текущий набор предметов
        long long int pack2 = 0;
        //стоимость текущего набора плюс стоимость текущего предмета
        int branch1 = elements[n - 1].price + BKKPSolve(w - elements[n - 1].weight, n - 1, elements, pack1);
        //стоимость текущего набора
        int branch2 = BKKPSolve(w, n - 1, elements, pack2);
        //берем лучший набор с максимальной стоимостью
        if(branch1 > branch2){
            pack = pack1 | (1 << (n - 1));
            return branch1;
        }
        else {
            pack = pack2;
            return branch2;
        }
    }
}

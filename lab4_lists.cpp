// lab4_lists.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
using namespace std;

// Файлы тестов
//const char* fileName = "corr1.txt";
const char* fileName = "corr2.txt";
//const char* fileName = "incorr1.txt";
//const char* fileName = "incorr2.txt";
//const char* fileName = "incorr3.txt";

// Списоk'
struct List {
    float data = NULL;
    List* next = NULL;
};

// Функции для списка
int create(List*& head, List*& end, const char* fileName); // Создание списка
void make(float a, List*& end, List*& head); //  Добавление нового элемента
void print(List* head);  // Печать всего списка
void delList(List*& head); // Удаление списка
List* findElem(float a, List* head); // Найти элемент в списке
int findMax(List* head); // Поиск максимального элемента с возвратом его номера
void Insertion(float a, List* head, int index); // добавлений элемента
void Delete(List*& head, int index); // Удаление элемента по его индексу
int count_size(List* head); // Посчитать длину списка
void PrintMess(int code); // Сообщение об ошибке

// Переменные
int ErrCode = 0; // Код ошибки
int size; // Длина списка
float reqdata; int reqIdx; // Новый элемент списка и его индекс в списке, запрашиваемые у пользователя
int reqIdx2; // Индекс элемента на удаление

int main()
{ 
    setlocale(LC_ALL, "Russian");
    List* head = NULL;
    List* end = NULL;

    ErrCode = create(head, end, fileName);
    if (!ErrCode)
    {
        print(head);
        
        // Добавление нового элемента
        cout << "Введите индекс места, в которое нужно поставить новый элемент: "; cin >> reqIdx;
        cout << endl;
        cout << "Введите элемент, который требуется вставить: "; cin >> reqdata;
        cout << endl;
        if (reqIdx<count_size(head) && reqIdx >= 0 && !cin.fail()) // Индекс за пределами или не число?
        {
            Insertion(reqdata, head, reqIdx);
            print(head);
        } // if
        else cout << "Некорректный ввод данных!" << endl;

        // Удаление элемента
        cout << "Введите индекс элемента, который нужно удалить: "; 
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера
        cin >> reqIdx2;
        cout << endl;
        
        if (reqIdx2<count_size(head) && reqIdx2 >= 0) // Индекс за пределами?
        {
            Delete(head, reqIdx2);
            print(head);
        } // if
        else cout << "Некорректный ввод данных!" << endl;

        // Поиск максимального элемента
        int res = findMax(head); // Индекс максимального элемента
        cout << "Индекс максимального элемента = " << res << endl;
 
        // Удаление списка
        delList(head);
        print(head);
    } // if
    else PrintMess(ErrCode);
} // main

int count_size(List* head)
{
    int counter = 0;
    while (head)
    {
        counter++;
        head = head->next;
    } // while
    return counter;
} // counter_size

int create(List*& head, List*& end, const char* fileName)
{
    float data;
    ifstream fin(fileName);
    
    while (!fin.eof())
    {
        fin >> data;
        if (fin.eof() && fin.fail()) 
        { 
            fin.close();  return 1; // Массив пуст 
        }// if
        if (fin.fail())
        {
            fin.close();  return 2;
        } // Передали не число
        make(data, end, head);
    } // while
    fin.close();
    return 0; // все ок
}

void make(float a, List*& end, List*& head) //  Добавление нового элемента
{   
    if (!findElem(a, head)) // Если a в списке еще не было
    {
        List* ptr = new List; // Новый элемент
        if (!head) head = ptr; // Если это первый элемент
        else { end->next = ptr; } // У конца появилось продолжение
        ptr->data = a;
        end = ptr; // Делаем этот элемент последним
        ptr->next = NULL; // Следующих элементов списка нет
    } // if
    else cout << "Элемент a = " << a << " уже содержится в списке!" << endl; // ?
} // make

List* findElem(float a, List* head) // Найти элемент в списке
{
    List* ptr = head;
    while (ptr)
    {
        if (ptr->data == a) return ptr;
        ptr = ptr->next;
    }
    return nullptr;
}

void print(List* head)  // Печать всего списка
{
    List* ptr = head;
    if (!ptr) cout << "Список пуст";
    while (ptr)
    {
        cout << "\t" << ptr->data;  // Считывание данного
        ptr = ptr->next; // Переход к следующему
    }
    cout << endl;
}

int findMax(List* head)
{
    List* ptr = head;
    int counter = -1; // Индекс
    float maxFound = -pow(10, 38); // Очень маленькое значение
    while (ptr)
    {
        if (ptr->data > maxFound)
        {
            maxFound = ptr->data;
            counter++;
        } // if
        ptr = ptr->next; // Переход дальше
    } // while
    cout << "Наибольшее значение = " << maxFound << endl;
    return counter;
}
void Insertion(float a, List* head, int index) {
    List* elem = new List;
    elem->data = a;
    List* ptr = head;
    for (int i = 0; i < index-1; i++) {
        ptr = ptr -> next;
    }
    elem->next = ptr->next;
    ptr->next = elem;
}

void Delete(List*& head, int index) {
    List* ptr = head;
    for (int i = 0; i < index -1; i++) {
        ptr = ptr->next;
    }
    if (ptr != head)
    {
        List* ptr2 = ptr->next;
        ptr->next = ptr->next->next;
        delete ptr2;
    } // if
    else {
        head = ptr->next;
        delete ptr;
    }
}

void delList(List*& head)
{
    List* ptr;
    while (head) // Удаление, начинающееся с "головы"
    {
        ptr = head->next;
        delete head;
        head = ptr;
    } // while
    head = NULL;
} // delList

void PrintMess(int code)
{
    switch (code) 
    {
        case 1: cout << "Файл пуст" << endl; break;
        case 2: cout << "В файле не цифра" << endl; break;
    }
}
// lab4_lists.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;

// Списоk'
struct List {
    float data = NULL;
    List* next = NULL;
};


//List* pointerArray[Size]; // Массив указателей для навигации по списку

// Функции для списка
List* findElem(float a, List* head); // Найти элемент в списке Q
void make(float a, List*& end, List*& head); //  Добавление нового элемента Q
void print(List* head);  // Печать всего списка Q
int findMax(List* head); // Поиск максимального элемента с возвратом его номера

int main()
{ // ВСЕ РАБОТАЕТ
    List* head = NULL;
    List* end = NULL; // ВАПРОС: если я эту переменную глобальной делаю, то "end не является однозначным", а если в main -- то все в порядке, почему?
    for (int i = 0; i < 100; i++)
    {
        make(i * 1.0, end, head);
    } // for i
    int res = findMax(head); // Индекс максимального элемента
    if (res >= 0) cout << "Индекс максимального элемента = " << res << endl;
    else cout << "Максимальный элемент не найден" << endl;
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
    else cout << "Элемент a = " << a << " уже содержится в списке!" << endl;
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
    int counter = -1; // Если останется -1, то список пуст (ВНИМАНИЕ! ЭТО ПОЛЕЗНО ДЛЯ ТЕСТОВ!)
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
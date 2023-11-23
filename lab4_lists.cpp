/***********************************************************************************
*                         Программирование                                         *
************************************************************************************
*Project type :Win64 Console Application                                           *
*Project name :lab_sorting.sln                                                     *
*File name    :lab_sorting.cpp                                                     *
*Language     :CPP, MSVS 2022                                                      *
*Programmers  :Кожевников Артем Вадимович, Томчук Дмитрий Максимович,  М3О-209Б-22 *
*Modified By  :                                                                    *
*Created      :14.11.2023                                                          *
*Last revision:16.11.2023                                                          *
*Comment      :                                                                    *
***********************************************************************************/


#include <iostream>
#include <fstream>
using namespace std;

// С Т Р У К Т У Р Ы
struct List {
    float data = NULL;
    List* next = NULL;
}; // Структура списка

/*********************************************************************
 *              П Р О Т О Т И П Ы    Ф У Н К Ц И Й                   *
 *********************************************************************/
int create(List*& head, List*& end, const char* fileName); // Создание списка
void make(float a, List*& end, List*& head); //  Добавление нового элемента
void print(List* head);  // Печать всего списка
void delList(List*& head); // Удаление списка
List* findElem(float a, List* head); // Найти элемент в списке
int findMax(List* head); // Поиск максимального элемента с возвратом его номера
void Insertion(float a, List*& head, int index); // добавлений элемента
void Delete(List*& head, int index); // Удаление элемента по его индексу
int count_size(List* head); // Посчитать длину списка
void PrintMess(int code); // Сообщение об ошибке

/*******************************************************************/
/*           Г Л О Б А Л Ь Н Ы Е   П Е Р Е М Е Н Н Ы Е             */
/*******************************************************************/

// Файлы тестов
//const char* fileName = "corr1.txt";
//const char* fileName = "corr2.txt";
const char* fileName = "corr3.txt";
//const char* fileName = "incorr1.txt";
//const char* fileName = "incorr2.txt";
//const char* fileName = "incorr3.txt";



int ErrCode = 0; // Код ошибки
int size; // Длина списка
float reqdata; int reqIdx; // Новый элемент списка и его индекс в списке, запрашиваемые у пользователя
int reqIdx2; // Индекс элемента на удаление

/*********************************************************************
 *              Г Л А В Н А Я   П Р О Г Р А М М А                    *
 *********************************************************************/

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
        // Удаление максимального элемента
        Delete(head, res);
        print(head);
        //  Вставка числа в начало
        cout << "Введите число: "; cin >> reqdata;
        Insertion(reqdata, head, 0);
        print(head);
        // Удаление списка
        delList(head);
        print(head);
    } // if
    else PrintMess(ErrCode);
} // main

/***********************************************************************
 *                Р Е А Л И З А Ц И Я    Ф У Н К Ц И Й                 *
 ***********************************************************************/

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
} // create

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
} // findElem

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
} // print

int count_size(List* head) // Посчитать размер списка
{
    int counter = 0;
    while (head)
    {
        counter++;
        head = head->next;
    } // while
    return counter;
} // counter_size

int findMax(List* head) // Поиск максимального
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
} // findMax

void Insertion(float a, List*& head, int index) { // Вставка элемента в список на указанное место
    
    List* ptr = head;
    List* elem = new List;
    elem->data = a;
    for (int i = 0; i < index-1; i++) {
        ptr = ptr -> next;
    }
    if (index == 0)
    {
        elem->next = ptr;
        head = elem;
    }
    else
    { 
        elem->next = ptr->next;
        ptr->next = elem;
    }
    
} // Insertion

void Delete(List*& head, int index) { // Удаление элемента по индексу
    List* ptr = head;
    for (int i = 0; i < index -1; i++) {
        ptr = ptr->next;
    } // for i
    if (index == 0) {
        head = ptr->next;
        delete ptr;
    } // if
    else 
    {
        List* ptr2 = ptr->next;
        ptr->next = ptr->next->next;
        delete ptr2;
    } // else
} // Delete

void delList(List*& head) // Удаление всего списка
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

void PrintMess(int code) // Печать сообщения об ошибке
{
    switch (code) 
    {
        case 1: cout << "Файл пуст" << endl; break;
        case 2: cout << "В файле не цифра" << endl; break;
    } // switch
} // PrintMess
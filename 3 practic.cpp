#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;
// Шаблон функции
template <typename T>
T findMin(const vector<T>& arr)
{
    T min = -1; // Инициализируем минимальное неотрицательное значение как -1

    for (const T& elem : arr)
        if (elem >= 0 && (min == -1 || elem < min)) min = elem;

    return min;
}
// Шаблон класса для дека с ограниченным выходом


#define DECK_SIZE 7

template <typename MyData>
class VDeck {
protected:
    MyData elements[DECK_SIZE];
    int MySize;
public:
    VDeck() { MySize = 0; }
    ~VDeck() {}
    VDeck(VDeck&& right) {
        MySize = right.MySize;
        for (int i = 0; i <= MySize; i++) {
            elements[i] = right.elements[i];
        }
        right.MySize = 0;
    }
    VDeck(const VDeck& copy) {
        MySize = copy.MySize;
        for (int i = 0; i <= MySize; i++) {
            elements[i] = copy.elements[i];
        }
    }
    virtual void push_back(MyData _data) {
        if (is_full()) return;
        elements[MySize] = _data;
        MySize++;
    }
    int size()
    {
        return MySize;
    }
    virtual void push_front(MyData _data) {
        int index = MySize + 1;
        while (index) {
            elements[index] = elements[index - 1];
            index--;
        }
        MySize++;
        elements[0] = _data;
    }
    virtual MyData pop_front() {
        if (is_empty()) return NULL;
        MyData returnelement = elements[0];
        for (int i = 0; i < MySize; i++) {
            elements[i] = elements[i + 1];
        }
        MySize--;
        return returnelement;
    }
    virtual bool is_empty() {
        return MySize == 0;
    }
    virtual bool is_full() {
        return MySize == DECK_SIZE;
    }
    virtual void read() {
        for (int i = 0; i < MySize; i++) {
            cout << elements[i] << " ";
        }
    }
};

void printInfoAndWait()
{
    cout << endl;
    puts("Чтобы перейти к выбору нажмите Enter");
    do { getchar(); } while (getchar() != '\n');
}
double random(double min, double max)
{
    return (double)(rand()) / RAND_MAX * (max - min) + min;
}

template <typename MyData>
void process(VDeck <MyData>& Deque) {
    int choice;
    do {
        system("cls");
        cout << "Выберите операцию для тестирования:\n"
            << "1. Добавить элемент в начало дека\n"
            << "2. Добавить элемент в конец дека\n"
            << "3. Удалить элемент из начала дека\n"
            << "4. Показать размер дека\n"
            << "5. Вывести содержимое дека\n"
            << "6. Сгенерировать массив случайных чисел и найти минимальное неотрицательное значение\n"
            << "0. Выход\n";
        cin >> choice;

        switch (choice) {
        case 1:
        {
            MyData elem;
            cout << "Введите элемент для добавления в начало дека: ";
            cin >> elem;
            Deque.push_front(elem);
            printInfoAndWait();
            break;
        }
        case 2:
        {
            MyData elem;
            cout << "Введите элемент для добавления в конец дека: ";
            cin >> elem;
            Deque.push_back(elem);
            printInfoAndWait();
            break;
        }
        case 3:
        {
            MyData frontElem = Deque.pop_front();
            if (frontElem != 0)
                cout << "Удаленный элемент из начала дека: " << frontElem << endl;
            else
                cout << "Дек пуст." << endl;
            printInfoAndWait();
            break;
        }
        case 4:
        {
            cout << "Размер дека: " << Deque.size() << endl;
            printInfoAndWait();
            break;
        }
        case 5:
        {
            cout << "Содержимое дека: ";
            Deque.read();
            printInfoAndWait();
            break;
        }
        case 6:
        {
            vector<MyData> Arr;
            if (typeid(MyData) == typeid(char&))
            {
                for (int i = 0; i < 10; ++i)
                    Arr.push_back(rand() % (50 - (-50) + 1) + (-50)); // Генерация чисел от -50 до 50 включительно

                // Вывод сгенерированного массива
                cout << "Сгенерированный массив: \n";
            
                for (const MyData& elem : Arr)
                    cout << elem << " ";
                cout << endl;
            }
            else
            {
                for (int i = 0; i < 10; ++i)
                    Arr.push_back(random(-50.0,50.0)); // Генерация чисел от -50.0 до 50.0 

                // Вывод сгенерированного массива
                cout << "Сгенерированный массив: ";

                for (const MyData& elem : Arr)
                    cout << elem << " ";
                cout << endl;
            }
            // Поиск наименьшего неотрицательного элемента
            MyData min = findMin(Arr);
            if (min != -1)
                cout << "Наименьший неотрицательный элемент: " << min << endl;
            else
                cout << "В массиве нет неотрицательных элементов." << endl;
            printInfoAndWait();
            break;
        }
        case 0:
        {
            cout << "Выход из программы.\n";
            printInfoAndWait();
            break;
        }

        default:
            cout << "Неверный выбор. Попробуйте снова.\n";
            printInfoAndWait();
        }
    } while (choice!=0);
}

int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "Вы хотите работать с типом char или с double? (1-char, 2-double)" << endl;
    int x;
    cin >> x;
    if (x == 1) {
        VDeck <char> deque;
        process(deque);
    }
    else if (x == 2) {
        VDeck <double> deque;
        process(deque);
    }
}

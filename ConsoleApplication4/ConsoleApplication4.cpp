// ConsoleApplication4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>

using namespace std;

enum Ocean {
    Pacific,
    Atlantic,
    Indian,
    North
};

enum TroughType {
    Fault,
    Ridge,
    Gutter,
    Basin
};

struct Trough {
    char name[50];
    double depth;
    Ocean ocean;
    TroughType type;
};

const char* getTypeName(TroughType type) {
    switch (type) {
    case Fault: return "Разломной";
    case Ridge: return "Хребетом";
    case Gutter: return "Жёлобом";
    case Basin: return "Котловиной";
    default: return "Неизвестной";
    }
}

const char* getOceanName(Ocean ocean) {
    switch (ocean) {
    case Pacific: return "Тихом";
    case Atlantic: return "Атлантическом";
    case Indian: return "Индийском";
    case North: return "Северном-Ледовитом";
    default: return "Неизвестном";
    }
}

void writeTroughsToBinaryFile(const char* filename, const Trough* troughs, int count) {
    ofstream out(filename, ios::binary | ios::out);

    if (!out.is_open()) {
        cerr << "Ошибка! Не удалось открыть файл для записи: " << filename << endl;
        return;
    }

    out.write((char*)troughs, sizeof(Trough) * count);

    out.close();
    cout << "Массив структур успешно записан в двоичный файл: " << filename << endl;
}

void readTroughsFromBinaryFile(const char* filename, Trough* troughs, int count) {
    ifstream in(filename, ios::binary | ios::in);

    if (!in.is_open()) {
        cerr << "Ошибка! Не удалось открыть файл для чтения: " << filename << endl;
        return;
    }

    in.read((char*)troughs, sizeof(Trough) * count);

    in.close();
    cout << "Массив структур успешно загружен из двоичного файла: " << filename << endl;
}

void changeTroughByDepth(struct Trough* troughs, int n, double depth) {
    for (int i = 0; i < n; i++) {
        if (troughs[i].depth == depth) {
            printf("Найдена впадина: %s \n", troughs[i].name);
            printf("Введите новое название: ");
            scanf_s("%s", troughs[i].name, 50);
            printf("Введите новую глубину: ");
            scanf_s("%lf", &troughs[i].depth);
            int o = 0;
            printf("Введите новое местоположение(0 - Тихий, 1 - Атлантический, 2 - Индийский, 3 - Северный-Ледовитый): ");
            scanf_s("%i", &o);
            troughs[i].ocean = (enum Ocean)o;
            int t = 0;
            printf("Введите новый тип(0 - Разломная, 1 - Хребет, 2 - Жёлоб, 3 - Котловина): ");
            scanf_s("%i", &t);
            troughs[i].type = (enum TroughType)t;
            const char* oceanName = getOceanName(troughs[i].ocean);
            const char* typeName = getTypeName(troughs[i].type);
            printf("Успешно! Новая информация: \nНазвание: %s впадина \nГлубина: %.2f \nМестоположение: %s океан \nТип: %s",
                troughs[i].name, troughs[i].depth, oceanName, typeName);
        }
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    system("chcp 1251");

    const char* filename = "troughs_data.txt";
    struct Trough troughs[20];

    cout << "\nЧтение из файла..." << endl;

    readTroughsFromBinaryFile(filename, troughs, 20);

    cout << "\n";

    double minDepth = troughs[0].depth;
    double maxDepth = troughs[0].depth;
    int minId = 0, maxId = 0;

    struct Trough gutters[20];
    int gutterCount = 0;

    struct Trough sorted[20];

    int oceanChoice;
    printf("Выберите океан(0 - Тихий, 1 - Атлантический, 2 - Индийский, 3 - Северный-Ледовитый): ");
    scanf_s("%i", &oceanChoice);

    struct Trough sameOcean[20];
    int sameOceanCount = 0;

    for (int i = 0; i < 20; i++) {
        if (troughs[i].depth < minDepth) {
            minDepth = troughs[i].depth;
            minId = i;
        }

        if (troughs[i].depth > maxDepth) {
            maxDepth = troughs[i].depth;
            maxId = i;
        }

        if (troughs[i].type == Gutter) {
            gutters[gutterCount] = troughs[i];
            gutterCount++;
        }

        if (troughs[i].ocean == oceanChoice) {
            sameOcean[sameOceanCount] = troughs[i];
            sameOceanCount++;
        }

        sorted[i] = troughs[i];

        if (i < 19) {
            for (int j = i + 1; j < 20; j++) {
                if (sorted[i].depth < sorted[j].depth) {
                    struct Trough temp = sorted[i];
                    sorted[i] = sorted[j];
                    sorted[j] = temp;
                }
            }
        }
    }

    if (sameOceanCount == 0) {
        printf("В выбранном океане нет впадин");
    }
    else {
        for (int i = 0; i < sameOceanCount; i++) {
            const char* typeName = getTypeName(sameOcean[i].type);

            printf("%i. %s впадина, которая является %s и имеет глубину %.2f \n", i + 1, sameOcean[i].name, typeName, sameOcean[i].depth);
        }
    }
    printf("\n");

    printf("%s впадина имеет наименьшую глубину - %.2f \n", troughs[minId].name, minDepth);
    printf("%s впадина имеет наибольшую глубину - %.2f \n", troughs[maxId].name, maxDepth);

    printf("\n");

    for (int i = 0; i < gutterCount - 1; i++) {
        for (int j = i + 1; j < gutterCount; j++) {
            if (gutters[i].depth < gutters[j].depth) {
                struct Trough temp = gutters[i];
                gutters[i] = gutters[j];
                gutters[j] = temp;
            }
        }
    }

    for (int i = 0; i < gutterCount; i++) {
        printf("%i. %s впадина, которая является %s. Глубина: %.2f \n", i + 1, gutters[i].name, getTypeName(gutters[i].type), gutters[i].depth);
    }
    printf("\n");

    for (int i = 0; i < 3; i++) {
        const char* oceanName = getOceanName(sorted[i].ocean);

        printf("%i. %s впадина имеет глубину %.2f и находится в %s океане \n", i + 1, sorted[i].name, sorted[i].depth, oceanName);
    }
    printf("\n");

    double depthToChange;
    printf("Введите глубину впадины для изменения: ");
    scanf_s("%lf", &depthToChange);
    changeTroughByDepth(troughs, 20, depthToChange);

    cout << "\n";

    cout << "\nЗапись в файл..." << endl;

    writeTroughsToBinaryFile(filename, troughs, 20);

    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.

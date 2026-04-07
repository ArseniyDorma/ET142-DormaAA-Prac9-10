// ConsoleApplication4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

enum Ocean{
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

void changeTroughByDepth(struct Trough *troughs, int n, double depth) {
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
            const char* oceanName = "";
            const char* typeName = "";
            switch (troughs[i].type) {
                case Fault: typeName = "Разломная"; break;
                case Ridge: typeName = "Хребет"; break;
                case Gutter: typeName = "Жёлоб"; break;
                case Basin: typeName = "Котловина"; break;
            }
            switch (troughs[i].ocean) {
                case Pacific: oceanName = "Тихий"; break;
                case Atlantic: oceanName = "Атлантический"; break;
                case North: oceanName = "Северный-Ледовитый"; break;
                case Indian: oceanName = "Индийский"; break;
            }
            printf("Успешно! Новая информация: \nНазвание: %s впадина \nГлубина: %.2f \nМестоположение: %s океан \nТип: %s", 
                troughs[i].name, troughs[i].depth, oceanName, typeName);
        }
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    system("chcp 1251");
    
    struct Trough troughs[20] = {
        {"Марианская", 11034.0, Pacific, Gutter},
        {"Тонгская", 10882.0, Pacific, Gutter},
        {"Филиппинская", 10540.0, Pacific, Gutter},
        {"Курило-Камчатская", 10542.0, Pacific, Gutter},
        {"Кермадекская", 10047.0, Pacific, Gutter},
        {"Идзу-Огасаварская", 9810.0, Pacific, Gutter},
        {"Пуэрто-Риканская", 8648.0, Atlantic, Gutter},
        {"Южно-Сандвичева", 8428.0, Atlantic, Gutter},
        {"Перуанско-Чилийская", 8065.0, Pacific, Gutter},
        {"Яванская", 7725.0, Indian, Gutter},
        {"Алеутская", 7679.0, Pacific, Gutter},
        {"Романшская", 7760.0, Atlantic, Gutter},
        {"Моллойская", 5669.0, North, Gutter},
        {"Литкенская", 5449.0, North, Gutter},
        {"Срединно-Атлантическая", 3000.0, Atlantic, Ridge},
        {"Восточно-Тихоокеанская", 2500.0, Pacific, Ridge},
        {"Аравийско-Индийская", 4000.0, Indian, Ridge},
        {"Сомалийская", 5400.0, Indian, Basin},
        {"Канадская", 3800.0, North, Basin},
        {"Агадирская", 4500.0, Atlantic, Basin}
    };

    double minDepth = troughs[0].depth;
    double maxDepth = troughs[0].depth;
    int minId = 0, maxId = 0;

    struct Trough gutters[20];
    int gutterCount = 0;
    
    struct Trough sorted[20];

    int oceanChoice;
    printf("Выберите океан(0 - Тихий, 1 - Атлантический, 2 - Индийский, 3 - Северный-Ледовитый): ");
    scanf_s("%i",&oceanChoice);

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
            const char* typeName = "";
            switch (sameOcean[i].type) {
                case Fault: typeName = "Разломной"; break;
                case Ridge: typeName = "Хребетом"; break;
                case Gutter: typeName = "Жёлобом"; break;
                case Basin: typeName = "Котловиной"; break;
            }

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
        printf("%i. %s впадина. Глубина: %.2f \n",i+1,gutters[i].name,gutters[i].depth);
    }
    printf("\n");

    for (int i = 0; i < 3; i++) {
        const char *oceanName = ""; 
        switch (sorted[i].ocean) {
            case Pacific: oceanName = "Тихом"; break;
            case Atlantic: oceanName = "Атлантическом"; break;
            case North: oceanName = "Северном-Ледовитом"; break;
            case Indian: oceanName = "Индийском"; break;
        }

        printf("%i. %s впадина имеет глубину %.2f и находится в %s океане \n", i + 1, sorted[i].name, sorted[i].depth, oceanName);
    }
    printf("\n");

    double depthToChange;
    printf("Введите глубину впадины для изменения: ");
    scanf_s("%lf", &depthToChange);
    changeTroughByDepth(troughs, 20, depthToChange);

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

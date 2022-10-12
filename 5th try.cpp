#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
#include <set>

using namespace std;

int MegaRandom(int SIZE)
{
    int full = 0;
    int* A = new int[SIZE];
    bool alreadylol;
    for (int i = 0; i < SIZE;)
    {
        alreadylol = false;// не знаем еще есть похожая или нет
        int newRand = rand() % 10; //создали случайную переменную
        for (int j = 0; j < i; j++) // проверка на уникальность нового числа
        {
            if (A[0] == 0)//обхожу нули на первой позиции
            {
                alreadylol = true;
                break;
            }
            if (A[j] == newRand) //равно ли новое значение уже существующему
            {
                alreadylol = true;
                break; // выбегаем тк уже мимо
            }
        }
        if (!alreadylol)
        {
            A[i] = newRand;
            i++;// продолжаем заполнять массив только после того, как убедились в уникальности 
        }
    }
    for (int i = 0; i < SIZE; i++)
        full = full * 10 + A[i];

    return full;
}

vector <int> del(int a)
{
    vector <int> chi;
    int h = a;
    while (h > 0)
    {
        chi.push_back(h % 10);
        h /= 10;
    }
    reverse(chi.begin(), chi.end());
    return chi;
}

vector <int> uq_nu(int a)
{
    vector <int> uq;
    int og = a;
    for (int i = pow(10, og - 1); i < pow(10, og); i++)
    {
        int r = 0;
        vector <int> F;
        int uwu = i;
        bool bab = true;
        set <int> st;
        for (int j = 0; j < og; j++)
        {
            F.push_back(uwu % 10);
            uwu = uwu / 10;
        }
        for (int j1 = 0; j1 < og; j1++)
        {
            for (int j2 = j1 + 1; j2 < og; j2++)
            {
                if (F[j1] == F[j2])
                    bab = false;
            }
        }
        if (bab == true)
            uq.push_back(i);
    }
    return uq;
}

int bik_f(vector <int> a, vector <int> b)
{
    int Z = 0;
    for (int i = 0; i < a.size(); i++)
    {
        if (a[i] == b[i])
            Z++;
    }
    return Z;
}

int kor_f(vector <int> a, vector <int> b)
{
    int Z = 0;
    for (int i = 0; i < a.size(); i++)
    {
        for (int j = 0; j < a.size(); j++)
            if (a[i] == b[j])
                Z++;
    }
    Z -= bik_f(a, b);
    return Z;
}

int main()
{
    srand(time(NULL));
    setlocale(LC_ALL, "Rus");

    int SIZE, O, G;

    cout << "Если вы хотите угадать число, то введите 1, если вы хотите, чтобы я угадал число, то введите 2: ";
    cin >> O;
    if (O == 1)
    {
        cout << endl << "Выберите уровень сложности: - Easy (компьютер один раз генерирует число, а вы угадываете)" << endl;
        cout << "                            - TryHard (каждый раз, когда вы не угадываете компьютер генерирует случайное число)" << endl;
        cout << "Если хотите поиграть в режим Easy, введите 1, если хотите поиграть в режим TryHard введите 2: ";
        cin >> G;

    }//описание к выобру режима
    if (O == 1 && G == 1)
    {//режим классика
        cout << "Введите длину числа: ";
        cin >> SIZE;
        int MyN = MegaRandom(SIZE);//генерим число
        if (SIZE <= 10)
        {
            int* A = new int[SIZE];//массив сгенерированного, для удобства сравнивния
            int kor = 0, bik = 0, k = 1;
            bool ura = true; //переменная для выхода из цикла
            cout << "Число сгенерировано, игра началась...)" << endl;
            while (ura)
            {
                int* B = new int[SIZE];//массив вводимого числа 
                int a;
                cout << endl << "Введите ваш вариант: ";
                cin >> a;
                for (int i = SIZE - 1; i >= 0 && a > 0; i--)
                {
                    B[i] = a % 10;
                    a = a / 10;
                }
                for (int j = SIZE - 1; j >= 0 && MyN > 0; j--)
                {
                    A[j] = MyN % 10;
                    MyN = MyN / 10;
                }
                //читы
                /*
                for (int i = 0; i < SIZE; i++)
                {
                    cout << B[i];
                }
                cout << endl;
                for (int j = 0; j < SIZE; j++)
                {
                    cout << A[j];
                }*/
                for (int i = 0; i < SIZE; i++)//проверка на коров/быков
                {
                    if (A[i] == B[i])
                    {
                        bik++;
                    }
                    else
                        for (int j = 0; j < SIZE; j++)
                        {
                            if (A[i] == B[j])
                                kor++;
                        }
                }
                if (bik == SIZE)
                {
                    ura = false;
                }
                cout << endl << "Быков: " << bik << endl << "Коров: " << kor << endl;
                kor = 0;
                bik = 0;
                k++;
                delete[] B;
            }
            cout << endl << "Вы угадали за " << k << " раз!" << endl;
            delete[] A;
        }
        if (SIZE > 10)
            cout << "Невозможно запустить игру с более, чем десятью символами =(";

    }
    if (O == 2)
    {//угадывает ПК
        vector <vector <int>> num_rmd;//чиселки в разборчике
        vector <vector <int>> bk;//быки и коровы

        vector <int> input;// делю нумбер на цифры(загаданный)
        vector <int> uq;//уникальный алфАвит
        vector <int> curlol;//число из алфАвита в цифру(отгаданный)
        vector <int> bk_smol(2,0);//быки и коровы

        int number; //загаданное
        int st = 0; //стейджи
        int bik; 
        int kor;
        int K = 1;//счетчик попыток
        int k = 0;//счетчик совпадений по бы/кор
        int curr;

        cout << "Введите длину числа: ";
        cin >> SIZE;

        cout << "Введите число: ";
        cin >> number;
        input = del(number);
        uq = uq_nu(SIZE);
        
        if (st == 0)
        {
            for (int i = 0; i < uq.size() && st == 0; i++)
            {
                curr = uq[i];
                curlol = del(curr);
                bik = bik_f(curlol, input);
                kor = kor_f(curlol, input);
                cout << endl << "Попытка: " << K << endl << "Число: " << curr << endl << "Коров:" << kor << " Быков:" << bik << endl << endl;
                K++;
                bk_smol[0] = bik;
                bk_smol[1] = kor;
                if (bik + kor> 0)
                {
                    bk.push_back(bk_smol);
                    num_rmd.push_back(curlol);
                    st++;
                }
            }
           
        }
        if(st>0)
        {
            for (int i = 0; i < uq.size(); i++)
            {
                k = 0;
                curr = uq[i];
                curlol = del(curr);
                for (int j = 0; j < st; j++)
                {
                    bik = bik_f(curlol, num_rmd[j]);
                    kor = kor_f(curlol, num_rmd[j]);
                    if (bik == bk[j][0] && kor == bk[j][1])
                    {
                        k++;
                    }
                }
                if (k == num_rmd.size())
                {
                    bik = bik_f(curlol, input);
                    kor = kor_f(curlol, input);
                    cout << "Попытка: " << K <<endl<< "Число: " << curr << endl << "Быков:" << bik << " Коров:" << kor << endl << endl;
                    K++;
                    bk_smol[0] = bik;
                    bk_smol[1] = kor;
                    bk.push_back(bk_smol);
                    num_rmd.push_back(curlol);
                    st++;
                    if (bik == SIZE)
                    {
                        cout << "ДА ДАВАЙ УРА ДА кхм... число загадали: ";
                        for (int i = 0; i < SIZE; i++)
                        {
                            cout<< num_rmd[num_rmd.size() - 1][i];
                        }
                        cout << " угадал за " << K - 1 << " раз!" << endl << endl;
                        break;
                    }
                }
            }
        }
    }
    if (O == 1 && G == 2)
    {//режим трайхард
        bool ashalet = false;
        cout << "Введите длину числа: ";

        cin >> SIZE;

        if (SIZE <= 10)
        {
            int k = 1;
            while (ashalet = true)
            {
                int MyN = MegaRandom(SIZE);
                int* B = new int[SIZE];//массив с числом пользователя
                int* A = new int[SIZE];//массив с всегда новыми числами
                int a;

                for (int i = SIZE - 1; i >= 0 && MyN > 0; i--)//раскидываем на массив для удобства
                {
                    A[i] = MyN % 10;
                    MyN = MyN / 10;
                }
                int kor = 0, bik = 0, k1 = 0;
                /*for (int i = 0; i < SIZE; i++)
                {
                    cout << A[i];
                }*/
                cout << endl << "Новое число сгенерировано" << endl;
                while (bik != SIZE)
                {
                    cout << endl << "Введите ваш вариант: ";
                    cin >> a;//вводим новый вариант числа
                    for (int i = SIZE - 1; i >= 0 && a > 0; i--)
                    {
                        B[i] = a % 10;
                        a = a / 10;
                    }
                    for (int i = 0; i < SIZE; i++)
                    {
                        if (A[i] == B[i])
                        {
                            bik++;
                        }
                        else
                            for (int j = 0; j < SIZE; j++)
                            {
                                if (A[i] == B[j])
                                    kor++;
                            }
                    }
                    if (bik == SIZE)
                        break;
                    cout << endl << "Быков: " << bik << endl << "Коров: " << kor << endl;
                    kor = 0;
                    bik = 0;
                    k++;
                    break;
                }
                for (int i = 0; i < SIZE; i++)
                {
                    if (A[i] == B[i])
                        k1++;
                }
                if (k1 == SIZE)
                {
                    ashalet = true;
                    cout << endl << "Вы угадали за " << k << " раз, ашалеть!" << endl;
                    break;
                }
                delete[] A;
                delete[] B;
            }
        }
        if (SIZE > 10)
            cout << "Невозможно запустить игру с более, чем десятью символами =(";

    }
    return 0;
}

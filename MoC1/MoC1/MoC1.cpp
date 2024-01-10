#include <iostream>
#include <fstream> // подключаем библиотеку
#include<string>




using namespace std;


float P_C(int c,int table[20][20],float P_m[20],float P_k[20]) {
    float res = 0;
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            if (table[i][j] == c)res += P_m[j] * P_k[i];
        }
    }


    return res;
}

float P_M_C(int c,int M, int table[20][20], float P_m[20], float P_k[20]) {
    float res = 0;
    for (int i = 0; i < 20; i++) {
        if (table[i][M] == c)res += P_m[M] * P_k[i];
    }
    return res;
}




int main() {
    int table[20][20];
    string filename = "table_05.csv";
    string text;
    string line;
    string elem;
    std::fstream fs; 
    fs.open(filename);
    if (fs.is_open())
    {  
        while (getline(fs, line)) {
            text += line;
            text += '\n';
        }
    }

    int k = 0, j = 0;
    for (int i = 0; i < text.length(); i++) {
        string number="";
        while ((text[i] != ',') && (text[i] != '\n')) {
            number += text[i];
            i++;
        }

        table[j][k] = stoi(number);
        k++;
        if (k == 20) {
            k = 0;
            j++;
        }
    }
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            cout << table[i][j] << " ";
        }
        cout << endl;
    }



    cout << endl;
    // читаємо текст
    k = 0;
    j = 0;
    string filename1 = "prob_05.txt";
    string text1;
    string line1;
    string elem1;
    std::fstream fs1;
    fs1.open(filename1);
    if (fs1.is_open())
    {
        while (getline(fs1, line1)) {
            text1 += line1;
            text1 += '\n';
        }
    }

    float prob[2][20];
  
    for (int i = 0; i < text1.length(); i++) {
       string number = "";
        while ((text1[i] != ',') && (text1[i] != '\n')) {
            number += text1[i];
            i++;
        }
        const char* str = number.c_str();
        prob[j][k] = atof(str);
        k++;
        if (k == 20) {
            k = 0;
            j++;
        }
    }
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 20; j++) {
            cout << prob[i][j] << " ";
        }
        cout << endl;
    }


    float P_M[20], P_K[20];
    for (int i = 0; i < 20; i++) {
        P_M[i] = prob[0][i];
        P_K[i] = prob[1][i];
    }


    cout << "P(C):"<<endl;

    float P_c[20];
    for (int i = 0; i < 20; i++) {
        P_c[i] = P_C(i, table, P_M, P_K);
        cout << P_c[i] << " ";
    }
    cout << endl;

    cout << "P(M,C):" << endl;

    float P_m_c[20][20];
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            P_m_c[i][j] = P_M_C(i, j, table, P_M, P_K);
            cout << P_m_c[i][j] << " ";
        }
        cout << endl;

    }
    cout << endl;

    cout << "P(M|C): " << endl;
    float P_mc[20][20];
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            P_mc[i][j] = P_m_c[j][i] / P_c[j];
            cout << P_mc[i][j] << " ";
        }
        cout << endl;

    }
    // Оптимальна детермiнiстична вирiшувальна функцiя
    int index_det[20]; //для похибки
 for (int j = 0; j < 20; j++) {
     float buf = 0;
     int buf_i = 0;
        for (int i = 0; i < 20; i++) {
            if (buf < P_mc[i][j]) {
                buf = P_mc[i][j];
                buf_i = i;
            }
                
        }
        index_det[j] = buf_i;
        cout << "M" << buf_i + 1 << endl;
    }

 //Середні витрати детерміністичної
 float lose_det = 0;
 for (int i = 0; i < 20; i++) {
     for (int j = 0; j < 20; j++) {
         if (i!=index_det[j]) {
             lose_det += P_m_c[i][j];
         }
     }
 }

 cout << "lose_det: " << lose_det << endl;


  // Оптимальна стохастична вирiшувальна функцiя
 float stoh[20][20];
 for (int i = 0; i < 20; i++) {
     int m = 0;//счетчик для количества одинаковых(максимальных) елементов столбика
     float buf = 0;
     //знаходжу макс елемент
     for (int j = 0; j < 20; j++) {
         if (buf < P_mc[j][i]) {
             buf = P_mc[j][i];
         }

     }
     //знаходжу кількість макс елементів
     for (int j = 0; j < 20; j++) {
         if (buf == P_mc[j][i]) {
             m++;
         }

     }
     //отримую остаточну таблицю
     for (int j = 0; j < 20; j++) {
         if (buf == P_mc[j][i]) {
             stoh[j][i] = 1.0 / m;
         }
         else stoh[j][i] = 0;
     }
 }
 cout << "stohastichna: " << endl;
 for (int i = 0; i < 20; i++) {
     for (int j = 0; j < 20; j++) {
         cout << stoh[i][j] << " ";
     }
     cout << endl;
 }

 float L_CM[20][20];
 for (int i = 0; i < 20; i++) {
     for (int j = 0; j < 20; j++) {
         L_CM[i][j] = 1 - stoh[i][j];
     }
 }
 float lose_stoh = 0;
 for (int i = 0; i < 20; i++) {
     for (int j = 0; j < 20; j++) {
         lose_stoh += P_m_c[i][j] * L_CM[i][j];
     }
 }
 cout << "lose_stoh: " << lose_stoh << endl;

 



}



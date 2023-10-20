#include <iostream>
#include <fstream> // подключаем библиотеку
#include<string>




using namespace std;


double P_C(int c,int table[20][20],double P_m[20],double P_k[20]) {
    double res = 0;
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            if (table[i][j] == c)res += P_m[j] * P_k[i];
        }
    }


    return res;
}

double P_M_C(int c,int M, int table[20][20], double P_m[20], double P_k[20]) {
    double res = 0;
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

    double prob[2][20];
  
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


    double P_M[20], P_K[20];
    for (int i = 0; i < 20; i++) {
        P_M[i] = prob[0][i];
        P_K[i] = prob[1][i];
    }


    cout << "P(C):"<<endl;

    double P_c[20];
    for (int i = 0; i < 20; i++) {
        P_c[i] = P_C(i, table, P_M, P_K);
        cout << P_c[i] << " ";
    }
    cout << endl;

    cout << "P(M,C):" << endl;

    double P_m_c[20][20];
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            P_m_c[i][j] = P_M_C(i, j, table, P_M, P_K);
            cout << P_m_c[i][j] << " ";
        }
        cout << endl;

    }
    cout << endl;

    cout << "P(M|C): " << endl;
    double P_mc[20][20];
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            P_mc[i][j] = P_m_c[i][j] / P_c[j];
            cout << P_mc[i][j] << " ";
        }
        cout << endl;

    }


}



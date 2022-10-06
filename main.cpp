#include <iostream>
using namespace std;

void Print(float** deter, int line, int column);
void ReadIn(float** deter, int line, int column);
void Transpose_determinant(float** deter, int line, int column);
void Cofactor(float** deter, int dimension);
float Det_cofactor(float** deter, int dimension, int line, int column);
float Det_determinant(float** deter, int dimension);
void Mul_Matrix(float** deter, int line, int column);
void Mul_Matrix();



int Determinant();
int Matrix();

int main() {
    int it = 0;
    while (true) {
        cout << "--------选择操作--------\n";
        cout << "1.行列式计算 2.矩阵计算 3.退出:";
        cin >> it;
        switch (it) {
            case 1:Determinant();
            case 2:Matrix();break;
            case 3:return 0;
            default:break;
        }
    }

}

void Print(float** deter, int line, int column) {
    for (int i = 0; i < line; i++) {
        for (int j = 0; j < column; j++) {
            cout << *((float*)deter + column*i + j) << " ";
        }
        cout <<'\n';
    }
}
void ReadIn(float** deter, int line, int column) {
    for (int i = 0; i < line; i++) {
        cout <<"line"<< i+1 << ':' << endl;
        for (int j = 0; j < column; j++) {
            cout << "column" << j+1 <<":";
            cin >> *((float*)deter + column*i + j);
        }
    }
}
void Transpose_determinant(float** deter, int line, int column) {
    for (int i = 0; i < line; i++) {
        for (int j = i; j < column; j++) {
            float temp = *((float*)deter + column*i + j);
            *((float*)deter + column*i + j) = *((float*)deter + column*j + i);
            *((float*)deter + column*j + i) = temp;
        }
    }
}
void Cofactor(float** deter, int dimension) {
    int line, column;
    cout << "请输入行和列(空格分隔):";
    cin >> line >> column;
    for (int k = 0; k < dimension; k++) {
        if (k+1==line) continue;
        for (int l = 0; l < dimension; l++) {
            if (l+1==column) continue;
            cout << *((float*)deter + dimension*k + l) << " ";
        }
        cout <<'\n';
    }
}
float Det_determinant(float** deter, int dimension) {
    float sum = 0, cofactor;
    float it = 1;
    if (dimension == 1) {
        return *((float*)deter);
    } else {
        for(int i = 0; i < dimension; i ++) {
            cofactor = Det_cofactor(deter, dimension, 0, i);
            sum += (*((float*)deter + 0*dimension + i))*(it)*cofactor;
            it = -it;
        }
    }
    return sum;
}
float Det_cofactor(float** deter, int dimension, int line, int column) {
    float result = 0;
    float  cofactor[dimension][dimension];
    for (int i = 0; i < dimension; ++i) {
        for (int j = 0; j < dimension; ++j) {
            cofactor[i][j] = *((float*)deter + dimension*i + j);
        }
    }
    for (int i = 0; i < dimension; i++) {
        for (int j = column; j < dimension-1; j++) {
            cofactor[i][j] = cofactor[i][j+1];
        }
    }
    for (int j = 0; j < dimension; j++) {
        for (int i = line; i < dimension-1; i++) {
            cofactor[i][j] = cofactor[i+1][j];
        }
    }
    float  cofactor2[dimension-1][dimension-1];
    for (int i = 0; i < dimension; ++i) {
        for (int j = 0; j < dimension; ++j) {
            cofactor2[i][j] = cofactor[i][j];
        }
    }
    if (dimension >= 2) {
        result = Det_determinant((float**)cofactor2, dimension - 1);
    }
    return result;
}

int Determinant(){
    int dimension;
    cout <<"行列式阶数：";
    cin >> dimension;
    cout << "输入行列式" << endl;
    float determinant[dimension][dimension];
    ReadIn((float**)determinant, dimension, dimension);
    while (true) {
        cout << "--------选择操作--------\n";
        cout << "1.转秩 2.余子式 3.计算行列式的值 4.返回:";
        int it = 0;
        cin >> it;
        switch (it) {
            case 1:Transpose_determinant((float**)determinant, dimension, dimension);Print((float**)determinant, dimension, dimension);break;
            case 2:Cofactor((float**)determinant, dimension);break;
            case 3:cout <<"\n"<< Det_determinant((float**)determinant, dimension) << '\n';break;
            default:break;
        }
        return 0;
    }
}
int Matrix(){

    while (true) {
        cout << "--------选择操作--------\n";
        cout << "1.转秩 2.矩阵乘法 3.返回:";
        int it = 0;
        cin >> it;
        switch (it) {
            case 1: {
                int line = 0, column = 0;
                cout << "矩阵行数：";
                cin >> line;
                cout << "矩阵列数" << endl;
                cin >> column;
                float determinant[line][column];
                ReadIn((float **) determinant, line, column);
                Transpose_determinant((float **) determinant, line, column);
                Print((float **) determinant, line, column);
                break;
            }
            case 2:Mul_Matrix();break;
            default:break;
        }
        return 0;
    }
}

void Mul_Matrix() {
    int lineA =0, columnA = 0, lineB,columnB = 0;
    cout << "请输入A矩阵行数：";
    cin >> lineA;
    cout << "请输入A矩阵列数：";
    cin >> columnA;
    float MatrixA[lineA][columnA];
    Mul_Matrix((float**)MatrixA, lineA, columnA);
    cout << "请输入B矩阵列数(默认A矩阵列数为B矩阵行数)：";
    cin >> columnB;
    lineB = columnA;
    float MatrixB[lineB][columnB];
    Mul_Matrix((float**)MatrixB, lineA, columnB);
    int k = columnB-1;
    float sum[k];
    float Result_Matrix[lineA][columnB];
    while (k >= 0) {
        for (int i = 0; i < lineA; ++i) {
            for (int j = 0; j < columnA; ++j) {
                sum[k] += MatrixA[i][j]*MatrixB[j][i+k];
            }
            for (int j = 0; j < lineA; ++j) {
                Result_Matrix[j][k] = sum[k];
            }
            k--;
        }
    }
    for (int i = 0; i < lineA; ++i) {
        for (int j = 0; j < columnB; ++j) {
            cout << Result_Matrix[i][j] << ' ';
        }
        cout << '\n';
    }
}
void Mul_Matrix(float** deter, int line, int column) {
    for (int i = 0; i < line; i++) {
        cout <<"line"<< i+1 << ':' << endl;
        for (int j = 0; j < column; j++) {
            cout << "column" << j+1 <<":";
            cin >> *((float*)deter + column*i + j);
        }
    }
}
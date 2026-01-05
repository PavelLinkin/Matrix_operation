#include <iostream>
#include <cmath>
using namespace std;

void matrix_print(int** matrix, int rows, int cols);
int** matrix_create(int rows, int cols)
{
    if(rows<0 || cols<0)
        throw "Error: invalid index";
    else if(rows==0 || cols==0)
        throw "Unfortunately, There are no operations with zero size matrix";
    else
    {
        int** matrix = new int* [rows];
        for(int i=0; i!=rows; i++)
            matrix[i] = new int [cols];
        return matrix;
    }
}
void matrix_delete(int** matrix, int rows) {
    for (int i=0; i!=rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void matrix_delete(double** matrix, int rows) {
    for (int i=0; i!=rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

double** matrix_created(int rows, int cols)
{
    if(rows<0 || cols<0)
        throw "Error: invalid index";
    else if(rows==0 || cols==0)
        throw "Unfortunately, There are no operations with zero size matrix";
    else
    {
        double** matrix = new double* [rows];
        for(int i=0; i!=rows; i++)
            matrix[i] = new double [cols];
        return matrix;
    }
}

int** matrix_addition(int** mat1, int rows1, int cols1, int** mat2, int rows2, int cols2)
{
    if(rows1!=rows2 && cols1!=cols2)
        throw "Error: operation is impossible";
    else
    {
        int** K=matrix_create(rows1, cols1);
        for(int i=0; i!=rows1; i++)
        {
            for(int j=0; j!=cols1; j++)
                K[i][j]=mat1[i][j]+mat2[i][j];
        }
        return K;
    }
}

int** matrix_subtraction(int** mat1, int rows1, int cols1, int** mat2, int rows2, int cols2)
{
     if(rows1!=rows2 && cols1!=cols2)
        throw "Error: operation is impossible";
    else
    {
        int** K=matrix_create(rows1, cols1);
        for(int i=0; i!=rows1; i++)
        {
            for(int j=0; j!=cols1; j++)
                K[i][j]=mat1[i][j]-mat2[i][j];
        }
        return K;
    }
}

int** matrix_multiply(int** mat1, int rows1, int cols1, int** mat2, int rows2, int cols2)
{
    if(cols1!=rows2)
        throw "Error: operation is impossible";
    else
    {
        int** K=matrix_create(rows1, cols2);
        for(int i=0; i!=rows1; i++)
        {
            for(int j=0; j!=cols2; j++)
            {
                K[i][j]=0;
                for(int t=0; t!=cols1; t++)
                {
                    K[i][j]+=mat1[i][t]*mat2[t][j];
                }
            }

        }
        return K;
    }
}

int** matrix_transposition(int** mat, int rows, int cols)
{
    int** K = matrix_create(cols, rows);
    for(int i=0; i!=rows; i++)
    {
        for(int j=0; j!=cols; j++)
            K[j][i]=mat[i][j];
    }
    return K;
}

int matrix_determinant(int** mat, int rows, int cols);

int matrix_minor(int** mat, int rows, int cols, int mi, int mj)
{
    if(rows!=cols)
        throw "Error: matrix is not quadratic";
    else
    {
        int** K = matrix_create(rows-1, cols-1);

        int subI = 0;
        for (int i = 0; i < rows; i++) {
        if (i == mi) continue;

        int subJ = 0;
        for (int j = 0; j < cols; j++) {
            if (j == mj) continue;

            K[subI][subJ] = mat[i][j];
            subJ++;
        }
        subI++;
    }

        return matrix_determinant(K, rows-1, cols-1);
    }
}

int matrix_determinant(int** mat, int rows, int cols)
{
    if(rows!=cols)
        throw "Error: matrix is not quadratic";
    else
    {
        if(rows==1)
            return mat[0][0];
        else if(rows==2)
            return mat[0][0]*mat[1][1]-mat[0][1]*mat[1][0];
        else
        {
            int det=0;
            for(int i=0; i!=rows; i++)
            {
                det+=mat[0][i]*matrix_minor(mat, rows, cols, 0, i)*pow((-1), i);
            }
            return det;
        }
    }
}

int matrix_algebraic(int** mat, int rows, int cols, int mi,int mj)
{
    if(rows!=cols)
        throw "Error: matrix is not quadratic";
    else
    {
        return matrix_minor(mat, rows, cols, mi, mj)*pow((-1), mi+mj);
    }
}

void matrix_cin(int** mat, int rows, int cols)
{
    cout << "Enter elements of matrix\n";
    for(int i=0; i!=rows; i++)
    {
        for(int j=0; j!=cols; j++)
            cin >> mat[i][j];
    }
}

double** matrix_inverse(int** mat, int rows, int cols)
{
    if(rows!=cols)
        throw "Error: matrix is not quadratic\n";
    else
    {
        double** K = matrix_created(rows, cols);
        if(matrix_determinant(mat, rows, cols)==0)
            throw "Error: Inverse Matrix doesn't exist\n";
        else
        {
            int** K1 = matrix_create(rows, cols);
            int** K2 = matrix_create(rows, cols);
            for(int i=0; i!=cols; i++)
            {
                for(int j=0; j!=rows; j++)
                {
                    K1[i][j]=matrix_algebraic(mat, cols, rows, i, j);

                }
            }

            K1=matrix_transposition(K1, rows, cols);
            for(int i=0; i!=cols; i++)
            {
                for(int j=0; j!=rows; j++)
                {
                    K[i][j]=K1[i][j]/matrix_determinant(mat, rows, cols);

                }
            }
            return K;
        }

    }

}

void matrix_print(int** matrix, int rows, int cols)
{
    for(int i=0; i!=rows; i++)
    {
        for(int j=0; j!=cols; j++)
            cout << matrix[i][j] << ' ';
        cout << endl;
    }
}

int main()
{
    int N;
    char op;
    cout << "Welcome to matrix operation program\n";
    cout << "Choose How much matrix do you need for you operation 1 or 2\n";
    cin >> N;
    if(N==1)
    {
        cout << "Choose operation:\nT - transposition\nM - Minor1\nD - Determinant\nA - Algebraic Complement\nI - Inverse Matrix\n";
        cin >> op;
        int m,n;
        int** M1;
        int** M2;
        cout << "Enter size of matrix\n";
        cin >> m >> n;
        try
        {
            M1=matrix_create(m, n);
            matrix_cin(M1, m, n);
            switch(op)
            {
                case 'T':
                    M2=matrix_transposition(M1, m, n);
                    matrix_print(M2, n, m);
                    matrix_delete(M2, n);
                break;
                case 'M':
                    int i, j;
                    cout << "Enter index if element\n";
                    cin >> i >> j;
                    try
                    {
                        cout << matrix_minor(M1, m, n, i, j);
                    }
                    catch(const char* error)
                    {
                        cout << error;
                    }

                break;
                case 'D':
                    try
                    {
                        cout << matrix_determinant(M1, m, n);
                    }
                    catch(const char* error)
                    {
                        cout << error;
                    }
                break;
                case 'A':
                    int i1, j1;
                    cout << "Enter index if element\n";
                    cin >> i1 >> j1;
                    try
                    {
                        cout << matrix_algebraic(M1, m, n, i1, j1);
                    }
                    catch(const char* error)
                    {
                        cout << error;
                    }
                break;
                case 'I':
                    double** M3;
                    M3=matrix_inverse(M1, m, n);
                    for(int i=0; i!=m; i++)
                    {
                        for(int j=0; j!=n; j++)
                            cout << M3[i][j] << ' ';
                        cout << endl;
                    }
                    matrix_delete(M3, m);
                break;
                default:
                    cout << "This type of operation is not available\n";
                matrix_delete(M1, m);

            }
        }
        catch(const char* error)
        {
            cout << error;
        }
    }
    else
    {

        cout << "Choose operation:\n+\n-\n*\n";
        cin >> op;
        int m,n,p,g;
        int** M1;
        int** M2;
        int** M3;

        cout << "Enter size of first matrix\n";
        cin >> m >> n;
        try
        {
            M1 = matrix_create(m, n);
            matrix_cin(M1, m, n);

            cout << "Enter size of second matrix\n";
            cin >> g >> p;
                try
                {
                    M2 = matrix_create(g, p);
                    matrix_cin(M2, g, p);
                    switch(op)
                    {
                        case '*':
                            try
                            {
                                M3 = matrix_multiply(M1, m, n, M2, g, p);
                                cout << "The result:\n";
                                matrix_print(M3, m, p);
                                matrix_delete(M1, m);
                                matrix_delete(M2, g);
                                matrix_delete(M3, m);

                            }
                            catch(const char* error)
                            {
                                cout << error;
                            }
                        break;
                        case '+':
                            try
                            {
                                M3 = matrix_addition(M1, m, n, M2, g, p);
                                cout << "The result:\n";
                                matrix_print(M3, m, n);
                                matrix_delete(M1, m);
                                matrix_delete(M2, g);
                                matrix_delete(M3, m);
                            }
                            catch(const char* error)
                            {
                                cout << error;
                            }
                        break;
                        case '-':
                            try
                            {
                                M3 = matrix_subtraction(M1, m, n, M2, g, p);
                                cout << "The result:\n";
                                matrix_print(M3, m, n);
                                matrix_delete(M1, m);
                                matrix_delete(M2, g);
                                matrix_delete(M3, m);
                            }
                            catch(const char* error)
                            {
                                cout << error;
                            }
                        break;
                        default:
                            cout << "This type of operation is not available\n";
                    }
                }
                catch(const char* error)
                {
                    cout << error;
                }
        }
        catch(const char* error)
        {
            cout << error;
        }
    }
}

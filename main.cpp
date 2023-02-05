#include <iostream>
#include <cstring>
#include <iomanip>
#include <cmath>

using namespace std;

string usinput;
int len, len3;
double len2;
int limit = 3;

int nummatrix[3][100], matrixmult[3][100], invmatrixmult[3][100];

//letter matrices to convert to numbers - could've just used ascii but wasn't aware at the time
char key[27] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n' , 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '/'};
char upkey[27] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N' , 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '/'};

//keys to encrypt and decrypt
int answer[3][3] = {{4, 1, 2}, {2, 1, 1}, {3, 1, 2}};
int invanswer[3][3] = {{1, 0, -1}, {-1, 2, 0}, {-1, -1, 2}};

//print function
void Print(int matrix[][100]){
    for (int x = 0; x < limit; ++x){
        for (int y = 0; y < ::len3; ++y){
            cout << matrix[x][y] << " ";
        }
        cout << endl;
    }
}

void LoadandConvertMatrix(string usinput){
    char matrix[3][::len3];
    
    int y = 0;
    for(int x = 0; x < ::len3; ++x){
        while(y < ::len){
            matrix[x][y] = usinput[y];
            ++y;
        }
    }
    
    //cant just call the print function as matrix isn't universly declared as matrix[][100] nor is it an int matrix 
    cout << endl << "Here is the message loaded into a matrix:" << endl;
    for (int y = 0; y < limit; ++y){
        for (int x = 0; x < ::len3; ++x){
            cout << matrix[y][x] << " ";
        }
        cout << endl;
    }
    
    for (int x = 0; x < limit; ++x){
        for (int y = 0; y < 100; ++y){
            ::nummatrix[x][y] = 0;
        }
    }
    
    for (int x= 0; x < limit; ++x){
        for (int z =0; z < ::len3; ++z){
            for (int y = 0; y < 27; ++y){
                if ((matrix[x][z] == ::key[y]) || (matrix[x][z] == ::upkey[y])){
                    ::nummatrix[x][z] = y + 1;
                }    
            }
        }       
    }
    cout << endl << "Here is your matrix converted into numbers:" << endl;
    Print(::nummatrix);
}

void Mult(int nummatrix[3][100]){
    for (int x = 0; x < limit; ++x){
        for (int y = 0; y < 100; ++y){
            ::matrixmult[x][y] = 0;
        }
    }
    for (int x = 0; x < limit; ++x){
        for (int y = 0; y < ::len3; ++y){
            for (int z = 0; z < limit; ++z){
                ::matrixmult[x][y] += ::answer[x][z] * nummatrix[z][y];
            }    
        }
    }
    cout << endl << "Here is your matrix multiplied by the key:" << endl;
    Print(::matrixmult);
}

void InvMult(int nummatrix[3][100]){
    for (int x = 0; x < limit; ++x){
        for (int y = 0; y < ::len3; ++y){
            for (int z = 0; z < limit; ++z){
                ::invmatrixmult[x][y] += ::invanswer[x][z] * nummatrix[z][y];
            }    
        }
    }
    cout << endl << "Here is your matrix multiplied by the inverse key:" << endl;
    Print(::invmatrixmult);
}

void Mod(int matrixmult[3][100]){
    for (int x = 0; x < limit; ++x){
        for (int y = 0; y < ::len3; ++y){
            matrixmult[x][y] = matrixmult[x][y] % 27;
            while (matrixmult[x][y] < 0){
                matrixmult[x][y] = matrixmult[x][y] + 27;
            }
        }
    }
    cout << endl << "Here is your matrix with mod 27 of each spot:" << endl;
    Print(matrixmult);
}

void NumToLet(int matrixmult[3][100]){
    int i = 0, z = 0;
    char ansarray[len];
    for (int x = 0; x < limit; ++x){
        for (int y = 0; y < ::len3; ++y){
            i = matrixmult[x][y] - 1;
            if (i < 0){
                i = 26;
            }
            cout << key[i];
        }
    }
}

bool check (string usinput){
    bool checkarr[::len];
    
    for (int x = 0; x < ::len; ++x){
        checkarr[x] = false;
    }
    
    for (int x = 0; x < ::len; ++x){
        for (int y = 0; y < 27; ++y){
            if (usinput[x] == ::key[y]){
                checkarr[x] = true;
            }
        }
    }
    
    for (int x = 0; x < ::len; ++x){
        if (checkarr[x] == false){
            return false;
        }
    }
    return true;
}


int main()
{
    string fix = "/";
    
    cout << "Welcome To Hill Code!" << endl;
    cout << "A few things before we start:" << endl;
    cout << "1.Make make sure your message is under 300 characters." << endl;
    cout << "2.There is no punction- meaning don't use , . ! ? or anything like that." << endl;
    cout << "3.Finally, make sure to / instead of spaces." << endl;
    cout << "(Ie. Hello World becomes Hello/World)" << endl;
    cout << "____________________________________________________________" << endl;
    
    cout<<"Give your secret message:";
    getline (cin, usinput);
    
    len = usinput.size();
    len2 = usinput.size();
    len3 = ceil(len2/3.0);
    
    while (check(usinput) == false){
        cout << "Good try. Please give a valid input:";
        cin >> usinput;
        len = usinput.size();
        len2 = usinput.size();
        len3 = ceil(len2/3.0);
        check(usinput);
    }
    
    while (len % 3 != 0){
        ::usinput.append(fix);
        len = usinput.size();
        len2 = usinput.size();
        len3 = ceil(len2/3.0);
    }
    
    char pick;
    cout << endl << "Now, would you like to encrypt or decrypt?" << endl;
    cout << "Type E for encryption, D for decryption:";
    cin >> pick;
    
    if (pick == 'E'){
        LoadandConvertMatrix(::usinput);
        Mult(::nummatrix);
        cout << endl;
        Mod(::matrixmult);
        cout << endl << "The encrypted message is:";
        NumToLet(::matrixmult);
    }
    else{
        LoadandConvertMatrix(::usinput);
        InvMult(::nummatrix);
        cout << endl;
        Mod(::invmatrixmult);
        cout << endl;
        cout<<"The decrypted message is:";
        NumToLet(::invmatrixmult);
    }

    
    return 0;
}


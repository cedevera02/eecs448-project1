#include <iostream>
#include <string>

using namespace std;

int main()
{
    string ** arr = nullptr;
    arr = new string* [11];
    char letter = 'A';
    int num = 01;
    string number;


    for(int i=0; i<11; i++)
    {

        arr[i] = new string[11];
        for(int j=0; j<11; j++)
        {
            if(i == 0 && j ==0){
                arr[i][j] = ' ';
            }
            else if(i == 0){
                arr[i][j] = static_cast<char>(letter);
                letter = static_cast<char>(letter + 1);
            }
            else if(j == 0){
                number = to_string(num);
                arr [i][j] = number;
                num = num + 1;
            }
            else{
                arr[i][j] = '.';
            }
            if (i == 10 && j == 0){
                cout<<arr[i][j]<<"   ";
            }
            else{
                cout<<arr[i][j]<<"    ";
            }
        }
        cout<<endl<<endl;

    }
    return 0;
}

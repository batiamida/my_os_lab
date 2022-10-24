#include "main.h"

#define PATH "C:\\Users\\Gram\\Desktop\\something\\test_8000000.txt"
#define ANSWER "C:\\Users\\Gram\\Desktop\\something\\answer_8000000.txt"
#define myLib "C:\\Users\\Gram\\Desktop\\something\\LoadTime\\bin\\Debug\\LoadTime.dll"

using namespace std;

struct MyArr{
    vector<int> v;
    int s = 0;
};


atomic<int> counter( 0 );
int len = 0;

vector<int> cut(vector<int>& v, int i, int j){
    auto start = v.begin() + i;
    auto finish = v.begin() + j;
    vector<int> temp(j-i);

    temp.assign(start, finish);

    return temp;
}

DWORD WINAPI FileThread(LPVOID param);
DWORD WINAPI SumThread(LPVOID param);
DWORD WINAPI ProgressThread(LPVOID param);
void update_progress();

// a sample exported function
extern "C" int DLL_EXPORT SomeFunction()
{
    //    HANDLE file_thread = CreateThread(NULL, 0, FileThread, NULL, 0, 0);
//    WaitForSingleObject(file_thread, INFINITE);


    ifstream f;
    ifstream f_answ;
    f_answ.open(ANSWER);
    f.open(PATH);
    string text;
    string answ;
    vector<int> v;
    if(f.is_open()){
            while (getline(f, text)){
                int i = stoi(text);
                v.push_back(i);
            }
            f.close();
    }

    if(f_answ.is_open()){
        getline(f_answ, answ);
    }

    cout << "File with data opened..." << endl;

    int div[] = {2, 4, 8, 20, 100, 1000};
    int num_threads = 2;
    len = v.size();
    HANDLE Arr[num_threads+1];
    MyArr A[num_threads];


            Arr[0] = CreateThread(NULL, 0, ProgressThread, NULL, 0, 0);
        for (int i=1; i < num_threads+1; i++){
            A[i-1].v = cut(v, (v.size()/num_threads)*(i-1), (v.size()/num_threads)*(i));
            Arr[i] = CreateThread(NULL, 0, SumThread, &(A[i-1]), 0, 0);




        for (int j=1; j < num_threads+1; j++){
                WaitForSingleObject(Arr[j], INFINITE);
                CloseHandle(Arr[j]);
        }
        CloseHandle(Arr[0]);
        update_progress();

    }


    int s = 0;
    for (int k=0; k < num_threads; k++){
        s += A[k].s;
    }

    cout << "\n" << "Original sum: " << answ;
    cout << "\n" << "Our sum: " << s;
    return 0;
}

DWORD WINAPI ProgressThread(LPVOID param){
    while(counter < len){
        update_progress();
    }

    Sleep(1000);
    return 0;
}

DWORD WINAPI SumThread(LPVOID param){
    MyArr* A = (MyArr*)param;
    for(int x=0; x < A->v.size(); x++){

        A->s += A->v[x];

        counter++;

    }


    return 0;
}

void update_progress(){
    int temp = (counter*100/len);
    cout << '\r' << "Progress: " << temp << "% ";
    cout.flush();
}

extern "C" DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{



    return TRUE; // succesful
}

#include <iostream>
#include <ctime>

using namespace std;

int main(){
    int end_time = time(0) + 60*1;
    cout << time(0) << endl;
    cout << end_time << endl;
    
    return 0;
}


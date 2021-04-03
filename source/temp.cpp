#include <math.h>
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

// int main(){
//     vector< float > vertex_buffer_data;
//     float radius = 0.1;
//     int temp = 0;

//     float a1 = 0.0f, b1 = 0.0f, c1 = 0.0f;

//     for(float theta = 0 ; theta < (6.28) ; theta += 0.001){
//         float a = -1.000000f;
//         float c = radius * cosf(theta) * 1.00000000;
//         float b = radius * sinf(theta) * 1.00000000;
//         cout << "-1.0f, 0.0f, 0.0f, ";
//         cout << setprecision(6) << a << ".00f, " << setprecision(6) << b << "f, " << setprecision(6) << c << "f, ";
//         cout << setprecision(6) << a1 << ".00f, " << setprecision(6) << b1 << "f, " << setprecision(6) << c1 << "f, ";
//         a1 = a;
//         b1 = b;
//         c1 = c;
//         temp++;
//     }
//     cout << endl << temp << endl;
//     return(0);
// }

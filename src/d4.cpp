#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;




int main(int argc, char * argv[])
{
    std::ifstream file("../input_long.txt");
    int in;
    int in2;
    int in3;
    int in4;
    int sol = 0;
    char found;


    while (file >> in >> in2) {
        file.ignore();
        file >> in3 >> in4;
        
        in2 *= -1;
        in4 *= -1;

        if ((in2 >= in3 && in3 >= in) || (in <= in4 && in3 <= in)) {
            sol++;
        } 
    }

    std::cout << sol << std::endl;
}
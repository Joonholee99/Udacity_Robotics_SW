#include <iostream>
#include <tuple>
#include <math.h>

using namespace std;

tuple<double, double> state_prediction(double mean1, double var1, double mean2, double var2){
    double new_mean, new_var;

    new_mean = mean1 + mean2;
    new_var = var1 + var2;
    
    return make_tuple(new_mean, new_var);
}

int main(){
    double new_mean, new_var;
    tie(new_mean, new_var) = state_prediction(10, 4, 12, 4);

    printf("[%f, %f]",new_mean, new_var);

    return 0;
}
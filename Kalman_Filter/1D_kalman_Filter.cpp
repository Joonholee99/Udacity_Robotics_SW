#include <iostream>
#include <math.h>
#include <tuple>

using namespace std;
double Motion[5]={1,1,2,1,1};
double Motion_sig = 2;
double Measure[5] = {5,6,7,9,10};
double Measure_sig = 4;

tuple<double, double> init = make_tuple(35, 4);

tuple<double, double> state_prediction(double mu1, double sig1, double mu2, double sig2){
    double new_mu, new_sig;

    new_mu = mu1 + mu2;
    new_sig = sig1 + sig2;

    return make_tuple(new_mu, new_sig);
}

tuple<double, double> measurement_update(double mu1, double sig1, double mu2, double sig2){
    double new_mu, new_sig;

    new_mu = (sig1*mu2 + sig2*mu1)/(sig1 + sig2);
    new_sig = 1/(1/sig1 + 1/sig2);

    return make_tuple(new_mu, new_sig);
}

int main(){
    double mu, sig;
    tie(mu, sig) = init;
 
    for(int i=0;i < sizeof(Measure)/sizeof(Measure[0]); i++){

        tie(mu, sig) = measurement_update(mu, sig, Measure[i], Measure_sig);
        printf("[%f, %f] \n", mu, sig);
        tie(mu, sig) = state_prediction(mu, sig, Motion[i],Motion_sig);
        printf("[%f, %f] \n", mu, sig);
        printf("---------------------------------\n");
    }
    return 0;
}
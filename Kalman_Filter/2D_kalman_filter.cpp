#include <iostream>
#include <math.h>
#include <tuple>
#include <eigen3/Eigen/Core>     //Eigen Library
#include <eigen3/Eigen/LU>       //Eigen Library

using namespace std;
using namespace Eigen;

float measurement[3] = {1,2,3};

tuple<MatrixXf, MatrixXf> kalman_filter(MatrixXf x, MatrixXf P, MatrixXf u, MatrixXf F, MatrixXf Q, MatrixXf H, MatrixXf R, MatrixXf I){

    for(int i = 0; i < sizeof(measurement)/sizeof(measurement[0]); i++){
        

        // Measurement Residual
        MatrixXf Z(1,1);
        Z << measurement[i];
        
        MatrixXf y(1,1);
        y << Z - H*x;
        
        MatrixXf S(1,1);
        S << H*P*H.transpose() + R;

        // Kalman gain
        MatrixXf K(2,1);
        K << P*H.transpose()*S.inverse();

        x << x + (K * y);
        P << (I - (K*H))*P;
        
        // State Prediction
        x << (F*x) + u;
        P << F*P*F.transpose();

    }

    return make_tuple(x, P);

}

int main(){
    
    
    MatrixXf x(2,1);
    x << 0,
        0;
    
    MatrixXf P(2,2);
    P << 100, 0,
        0, 100;
    
    MatrixXf u(2,1);
    u << 0,
        0;
    
    MatrixXf F(2,2);
    F << 1, 1,
        0, 1;

    MatrixXf Q(2,2);
    Q << 0,0,
        0,0;

    MatrixXf R(1,1);
    R << 1;

    MatrixXf H(1,2);
    H << 1, 0;
    
    MatrixXf I(2,2);
    I << 1, 0,
        0, 1;
    
    tie(x,P) = kalman_filter(x, P, u, F, Q, H, R, I);
    
    
    cout << "x=" << x << endl;
    cout << "P=" << P << endl;

    return 0;
    
    
    
}

#include "PID.h"
#include <iostream>
using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
    p_error = 0.0;
    i_error = 0.0;
    d_error = 0.0;

    Kp_ = Kp;
    Ki_ = Ki;
    Kd_ = Kd;
    initial_throttle = true;
}

void PID::UpdateError(double cte) {
    d_error = cte - p_error;
    p_error = cte;
    i_error += cte;

    std::cout << "P = " << d_error << " | I = " << i_error << " | D = " << d_error << std::endl;
}

double PID::TotalError() {
    total_error= Kp_*p_error + Ki_*i_error + Kd_*d_error;
    return total_error;
}

double PID::Throttle() {

    // if throttling at initial move of vehicle use a nominal value
    if (initial_throttle) {
        initial_throttle = false;
        return 0.8;
    }
    // if straight road and the cte is less use a higher throttle angle
    if (-total_error> -0.05 && -total_error< 0.05 && -total_error> -0.3 && -total_error< 0.3) {
        return 0.7;
    }
    // else use a lower throttle angle
    if (-total_error> -0.25 && -total_error< 0.25) {
        return 0.3;
    }
    // brake if the steering angle is really acute
    if ((-total_error< -0.4 || -total_error> 0.4)) {
        return -0.08;
    }
    // use the default throttle
    return 0.2;
}


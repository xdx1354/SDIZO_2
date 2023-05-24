//
// Created by stani on 24.05.2023.
//

#ifndef PROJEKT2_TIME_H
#define PROJEKT2_TIME_H

#include "iostream"
#include "chrono"
using namespace  std;
using namespace std::chrono;

class Time {
public:

    high_resolution_clock::time_point startPoint;

    high_resolution_clock::time_point stopPoint;

    void start();
    void stop();
    long long returnTime();
};


#endif //PROJEKT2_TIME_H

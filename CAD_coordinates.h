//
// Created by gionimbus on 7/13/26.
//

#ifndef LITTLE_PROGRAM_CAD_COORDINATES_H
#define LITTLE_PROGRAM_CAD_COORDINATES_H


#include "helper.h"

// TODO: use std::vector<Point>
namespace CAD_coordinates {
    // board 0 profile
    inline Point A0(-304.000000, 465.000000);
    inline Point B0(-304.000000, 354.085880);
    inline Point C0(-186.071797, 286.000000);
    inline Point D0(-40.000000, 286.000000);
    inline Point E0(-40.000000, 126.504389);
    inline Point F0(-20.000000, 99.837722);
    inline Point G0(20.000000, 99.837722);
    inline Point H0(40.000000, 126.504389);
    inline Point I0(40.000000, 286.000000);
    inline Point J0(185.744919, 286.000000);
    inline Point K0(219.000000, 305.199830);
    inline Point L0(219.000000, 465.000000);
    // board 0 pom home position
    inline Point M0(0.000000, 134.573504);
    // board 0 pom range
    inline Point N0(-300.000000, 284.573504);
    inline Point O0(-300.000000, -15.426496);
    inline Point P0(300.000000, -15.426496);
    inline Point Q0(300.000000, 284.573504);
    // board 1 profile
    inline Point A1(-250.701813, -495.771723);
    inline Point B1(-154.647367, -440.314663);
    inline Point C1(-154.647367, -304.142903);
    inline Point D1(-227.683265, -177.641016);
    inline Point E1(-89.556015, -97.893211);
    inline Point F1(-76.462004, -67.239369);
    inline Point G1(-96.212004, -33.031366);
    inline Point H1(-129.167880, -28.387089);
    inline Point I1(-267.683265, -108.358984);
    inline Point J1(-340.555725, 17.859819);
    inline Point K1(-373.810806, 37.059649);
    inline Point L1(-512.201813, -42.840437);
    // board 1 pom home position
    inline Point M1(-116.544073, -67.286752);
    // board 1 pom range
    inline Point N1(-96.447884, -402.094373);
    inline Point O1(163.359737, -252.094373);
    inline Point P1(-136.640263, 267.520869);
    inline Point Q1(-396.447884, 117.520869);
    // board 2 profile
    inline Point A2(554.701813, 30.771723);
    inline Point B2(458.647367, 86.228783);
    inline Point C2(340.719164, 18.142903);
    inline Point D2(267.683265, -108.358984);
    inline Point E2(129.556015, -28.611178);
    inline Point F2(96.462004, -32.598353);
    inline Point G2(76.462004, -67.239369);
    inline Point H2(89.556015, -97.893211);
    inline Point I2(227.683265, -177.641016);
    inline Point J2(154.810806, -303.859819);
    inline Point K2(154.810806, -342.259478);
    inline Point L2(293.201813, -422.159563);
    // board 2 pom home position
    inline Point M2(116.544073, -67.286752);
    // board 2 pom range
    inline Point N2(396.447884, 117.520869);
    inline Point O2(136.640263, 267.520869);
    inline Point P2(-163.359737, -252.094373);
    inline Point Q2(96.447884, -402.094373);
    // science fov large
    inline Point R0(-87.847500, -87.847500);
    inline Point S0(87.847500, -87.847500);
    inline Point T0(87.847500, 87.847500);
    inline Point U0(-87.847500, 87.847500);
    // science fov small
    inline Point R1(-33.150000, -33.150000);
    inline Point S1(33.150000, -33.150000);
    inline Point T1(33.150000, 33.150000);
    inline Point U1(-33.150000, 33.150000);
    // board 0 safe zone
    inline Point V0(-305.000000, 235.566731);
    inline Point W0(305.000000, 235.566731);
    // board 1 safe zone
    inline Point V1(-51.506773, -381.921114);
    inline Point W1(-356.506773, 146.354383);
    // board 2 safe zone
    inline Point V3(356.506773, 146.354383);
    inline Point W3(51.506773, -381.921114);
}


#endif //LITTLE_PROGRAM_CAD_COORDINATES_H

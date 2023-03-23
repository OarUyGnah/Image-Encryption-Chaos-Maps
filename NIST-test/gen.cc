#include <cmath>
#include <cstdio>
#include <fstream>
#include <functional>
#include <iostream>
#include <math.h>
#include <stdio.h>
using namespace std;

double pi = 3.141592653589793;
double beta = 9;
double gamma = 9;
double x = 0.5;
double a = 0.5;
double eplision = 7;
double delayed_logistic_map_find_u1()
{
    double ep = 0.6;
    double theta = 3.9;
    double begin = 3.57;
    double end = 4.0;
    double theta_u1 = 0;
    double u1 = -1;
    cout << "1" << endl;
    while (begin <= end) {
        if (begin == 3.57) {
            begin += 0.00001;
            continue;
        }

        theta_u1 = pow(theta, begin);
        cout << theta_u1 << endl;
        if (abs(ep - fmod((ep * (1 - ep) * theta_u1), 1)) <= 0.0001) {
            u1 = begin;
            break;
        }
        begin += 0.00001;
    }
    return u1;
}

void gen_delayed_logistic_map(double x0, double u, double theta, double eplision)
{
    FILE* f = fopen("gen_delayed_logistic.txt", "wb");
    unsigned char temp = x0;
    double x = x0;
    double x1 = x0;
    double x2 = u * x0 * (1 - x0);
    double theta_u = pow(theta, u);
    double theta_ep = pow(theta, eplision);
    double lastx = 0;
    double df = x + theta_ep * lastx;

    for (int i = 0; i < 100000; ++i) {
        // cout << x << endl;
        // printf("%.16f\n",x);
        df = x2 + theta_ep * x1;
        x = fmod(theta_u * df * (1 - df), 1);
        x1 = x2;
        x2 = x;
    }
    for (int i = 0; i < 10240000; ++i) {
        df = x2 + theta_ep * x1;
        x = fmod(theta_u * df * (1 - df), 1);
        temp = fmod(x * 1000000, 256);
        x1 = x2;
        x2 = x;
        fwrite(&temp, sizeof(temp), 1, f);
    }
}

double coupled_sine_map(double alpha, double beta, double gamma, double xn)
{
    return alpha * abs(sin(pow(beta, 3) * pi * xn))
        + (1 - alpha) * (1 - abs(sin(pow(gamma, 3) * pi * xn * (1 - xn))));
}
double coupled_sine_map2(double alpha, double beta, double gamma, double eplision, double xn)
{
    return eplision * alpha * abs(sin(pow(beta, 3) * pi * xn))
        + (1 - eplision) * (1 - abs(sin(pow(gamma, 3) * pi * xn * (1 - xn))));
}
// 生成用于伪随机数检测软件NIST的随机二进制序列，用于判断算法是否符合

void gen_1()
{
    FILE* f = fopen("gen1.txt", "wb");
    unsigned char temp = x;
    for (int i = 0; i < 100000; ++i) {
        // cout << x << endl;
        // printf("%.16f\n",x);
        x = coupled_sine_map(a, beta, gamma, x);
    }
    for (int i = 0; i < 10240000; ++i) {
        x = coupled_sine_map(a, beta, gamma, x);
        temp = fmod(x * 1000000, 256);
        // if (i < 10) {
        //     cout << temp << ' ';
        // }
        fwrite(&temp, sizeof(temp), 1, f);
    }
}
void gen_2()
{
    FILE* f = fopen("gen2.txt", "wb");
    unsigned char temp = x;
    for (int i = 0; i < 100000; ++i) {
        // cout << x << endl;
        // printf("%.16f\n",x);
        x = coupled_sine_map2(a, beta, gamma, eplision, x);
    }
    for (int i = 0; i < 10240000; ++i) {
        x = coupled_sine_map2(a, beta, gamma, ::eplision, x);
        temp = fmod(x * 1000000, 256);
        // if (i < 10) {
        //     cout << temp << ' ';
        // }
        fwrite(&temp, sizeof(temp), 1, f);
    }
}

double double_xor(double a, double b)
{
    double dResult;
    for (int i = 0; i < sizeof(double); i++) {
        ((char*)(&dResult))[i] = ((char*)(&a))[i] ^ ((char*)(&b))[i];
    }
    return dResult;
}

void dl_cs(double cs_x0, double dl_x0, double u, double theta, double eplision)
{
    FILE* f = fopen("dl_cs.txt", "wb");
    unsigned char temp = 0;
    double t = 0;
    double temp_cs = cs_x0;
    double temp_dl = dl_x0;
    double cs_x = cs_x0;
    double dl_x = dl_x0;
    double dl_x1 = dl_x0;
    double dl_x2 = u * dl_x0 * (1 - dl_x0);
    double theta_u = pow(theta, u);
    double theta_ep = pow(theta, eplision);
    double lastx = 0;
    double df = cs_x0 + theta_ep * lastx;

    bit_xor<double> bx;
    for (int i = 0; i < 100000; ++i) {
        // cout << x << endl;
        // printf("%.16f\n",x);
        df = dl_x2 + theta_ep * dl_x1;
        dl_x = fmod(theta_u * df * (1 - df), 1);
        dl_x1 = dl_x2;
        dl_x2 = dl_x;
        cs_x = coupled_sine_map2(a, ::beta, ::gamma, ::eplision, cs_x);
    }
    for (int i = 0; i < 10240000; ++i) {
        df = dl_x2 + theta_ep * dl_x1;
        dl_x = fmod(theta_u * df * (1 - df), 1);
        dl_x1 = dl_x2;
        dl_x2 = dl_x;
        cs_x = coupled_sine_map2(a, ::beta, ::gamma, ::eplision, cs_x);
        temp_cs = floor(fmod(cs_x * 1000000, 256));
        temp_dl = floor(fmod(dl_x * 1000000, 256));
        // t = double_xor(temp_cs, temp_dl);
        // temp = fmod(t * 1000000, 256);
        temp = (short)temp_cs ^ (short) temp_dl;
        fwrite(&temp, sizeof(temp), 1, f);
    }
}

int main()
{
    // gen_1();
    // gen_2();
    // delayed_logistic_map_find_u1();
    // gen_delayed_logistic_map(0.5, 3.2, 3.9, 0.6);
    dl_cs(0.7, 0.2, 3.2, 3.9, 0.6);
    
    return 0;
}

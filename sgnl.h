//
//  sgnl.h
//  Semestral
//
//  Created by Tomas Gajarsky on 22.3.2016.
//  Copyright (c) 2016 Gajarsky. All rights reserved.
//

#ifndef sgnl_h
#define sgnl_h

//#include "stdafx.h";
#include "stdio.h"
#include "iostream"
#include "stdlib.h"
#include "math.h"
#include "fstream"
#include "Exception.h"
using namespace std;
const float PI = 3.1415927;

template<class T> class sgnl
{
    T *p;
   int siz;
    
public:
    sgnl(int siz)
    {
        p = new T[this->siz = siz];
        
    }
    
    sgnl(sgnl &x) {
        p = new T[this->siz = x.siz];
        for (int i = 0; i < x.siz; i++) {
            p[i] = x[i];
        }
    }
    
    
    sgnl(double c)
    {
       this-> siz = 1;
       this-> p = new T[1];
       this-> p[0] = c;
    }
    
    T& operator[](int i) {
        return p[i];
    }
    
    T* operator[](int i) const {
        return p[i];
    }
    
    bool operator ==(const sgnl& d)
    {
        int l = 0;
        for(int i = 0; i < siz; i++){
            if(p[i] != d[i]) l = 1 ;
        }
        if (l == 0) return true;
        else        return false;
    }
    
    bool operator !=(const sgnl& d)
    {
        for(int i = 0; i < siz; i++){
            if(p[i] != d[i]) return true;
        }
        return false;
    }
    
    bool operator <(const sgnl& d)
    {
        if(Eff() < d.Eff())
        {
            return true;
        }
        return false;
    }
    
    bool operator >(const sgnl& d)
    {
        if(Eff() > d.Eff())
        {
            return true;
        }
        return false;
    }
    
    sgnl& operator=(const sgnl &y) {
        if (p != NULL) delete[] p;

        p = new T[siz = y.siz];
            for (int i = 0; i < siz; i++) {
                p[i] = y.p[i];
        }
        return *this;
    }
    
    sgnl& operator+=(const sgnl &y) {
        if(siz != y.siz){
            throw Exception(1);
        }
        for (int i = 0; i < siz; i++) {
            p[i] = p[i] + y.p[i];
        }
        return *this;
    }
    
    sgnl& operator-=(const sgnl &y) {
        if(siz != y.siz){
            throw Exception(1);
        }
        for (int i = 0; i < siz; i++) {
            p[i] = p[i] - y.p[i];
        }
        return *this;
    }
    
    sgnl& operator*=(const sgnl &y) {
        if(siz != y.siz){
            throw Exception(1);
        }
        for (int i = 0; i < siz; i++) {
            p[i] = p[i] * y.p[i];
        }
        return *this;
    }
    
    sgnl& operator-() {
        sgnl help(siz);
        for (int i = 0; i < siz; i++) {
                if (p[i] != 0)
                    help[i] = -p[i];
                else
                {
                    help[i] = 0;
                }
            
        }
        return help;
    }
    
    sgnl sinus(int f, int fs)
    {
        if (f < 1 || f > fs/2) throw Exception(3);
        for(int i = 0; i < siz; i++)
        {
            p[i] = sin(2*PI*f/fs*i);
        }
        return *this;
    }
    
    sgnl conv(sgnl &h){
        int n = siz+h.siz-1;
        sgnl q(n);
        
        for (int i = 0; i < n; i++ )
        {
            for (int j = 0; j < n; j++ )
            {
                if(i - j >= 0 && i - j < h.siz && j < siz) q[i] += p[j] * h[i- j];
            }
        }
        return q;
    }
    
    sgnl corr(sgnl &y){
        sgnl q(siz);
        
        for (int i = 0; i < siz; i++ )
        {
            for (int j = 0; j < siz; j++ )
            {
                if(j+i < siz)
                    q[i] += p[j+i] * y[j];
            }
        }
        return q;
    }
    
    double Avg(void)
    {
        double av = 0;
        for (int i; i < siz; i++){
                av += p[i];
            }
    return av/siz;
    }
    
    double AvgA(void)
    {
        double av = 0;
        for (int i; i < siz; i++){
            if (p[i]<0){
                p[i] = -p[i];
            }
            av += p[i];
        }
        return av/siz;
    }
    
    double Eff(void)
    {
        double e = 0;
        for (int i; i < siz; i++){
            e += p[i]*p[i];
        }
        return sqrt(e);
    }
    
    double Max(void)
    {
        double max = 0;
        for (int i; i < siz; i++){
            if (p[i] > max){
                max = p[i];
            }
        }
        return max;
    }
    
    double Min(void)
    {
        double min = 0;
        for (int i; i < siz; i++){
            if (p[i] > min){
                min = p[i];
            }
        }
        return min;
    }

    
    sgnl LowPass(double k, double a){
        if(a > 1 || a < 0){
            throw Exception(2);
        }
        sgnl helpLP(siz);
        for (int i = 0 ; i < siz ; i++)
        {
            if (i - 1 < 0){
            helpLP[i] = k * p[i];
            }
            else {
            helpLP[i] = k * p[i] + k * p[i - 1] + a * helpLP[i - 1];
            }
        }
        return helpLP;
    }
    
    sgnl HighPass(double k, double a){
        if(a > 1 || a < 0){
            throw Exception(2);
        }
        sgnl helpHP(siz);
        for (int i = 0 ; i < siz ; i++)
        {
            if (i - 1 < 0){
                helpHP[i] = k * p[i];
            }
            else {
                helpHP[i] = k * p[i] - k * p[i - 1] - a * helpHP[i - 1];
            }
        }
        return helpHP;
    }
    
    ~sgnl() {
        delete[] p;
    }
    
    template <class P> friend ostream& operator<<(ostream &out, sgnl<P> &z);
    template<class P> friend ifstream& operator>>(ifstream &in, sgnl<P> &z);
    template<class P> friend ofstream& operator<<(ofstream &out, sgnl<P> &z);
    template <class P> friend sgnl<P> operator+(sgnl<P> &operand1, sgnl<P> &operand2);
    template <class P> friend sgnl<P> operator-(sgnl<P>& operand1, sgnl<P>& operand2);
    template <class P> friend sgnl<P> operator*(sgnl<P> &operand1, sgnl<P> &operand2);
};

template <class P> sgnl<P> operator+(sgnl<P> &operand1, sgnl<P> &operand2)
{
    if(operand1.siz != operand2.siz && operand2.siz != 1){
        throw Exception(1);
    }
    sgnl<P> help(operand1.siz);
    for (int i = 0; i < operand1.siz; i++) {
            if(operand2.siz == 1){
                help[i] = operand1[i] + operand2[0]; //
            }
            else{
                help[i] = operand1[i] + operand2[i];
            }
        }
    
    return help;
}



template <class P> sgnl<P> operator-(sgnl<P>& operand1, sgnl<P>& operand2)
{
    if(operand1.siz != operand2.siz && operand2.siz != 1){
        throw Exception(1);
    }
    sgnl<P> help(operand1.siz);
    for (int i = 0; i < operand1.siz; i++) {
        if(operand2.siz == 1){
            help[i] = operand1[i] - operand2[0];
        }
        else{
            help[i] = operand1[i] - operand2[i];
        }
    }
return help;
}

template <class P> sgnl<P> operator*(sgnl<P> &operand1, sgnl<P> &operand2)
{
    if(operand1.siz != operand2.siz && operand2.siz != 1){
        throw Exception(1);
    }
    sgnl<P> help(operand1.siz);
    for (int i = 0; i < operand1.siz; i++) {
        if(operand2.siz == 1){
            help[i] = operand1[i] * operand2[0];
        }
        else{
            help[i] = operand1[i] * operand2[i];
        }
    }
    return help;
}


template <class P> ostream& operator<<(ostream &out, sgnl<P> &z) {
    for (int i = 0; i < z.siz; i++) {
            out << z[i] << " ";
    }
    return out;
}

template<class P> ifstream& operator>>(ifstream &in, sgnl<P> &m) {
    int t = 0, i = 0;
    double a;
    string s;
    
    while (!in.eof()) {
        in >> i >> a;
        t++;
    }
    
    sgnl<P> help(t);
    
    in.clear();
    in.seekg(0, in.beg);
    
    while (!in.eof()) {
        in >> i >> help[i];
    }
    
    m = help;
    
    return in;
}

template<class P> ofstream& operator<<(ofstream &out, sgnl<P> &m) {
    for (int i = 0; i < m.siz; i++) {
            out << m[i] <<", ";
    }
    return out;
}

#endif

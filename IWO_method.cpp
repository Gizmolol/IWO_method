#include <iostream>
#include <vector>

using namespace std;

int main ()
{
	std::cout << "Hello World!\n";
}
//import random
//import numpy as np
//
//def sort (x, f) :
//    k = 1
//    while k > 0:
//k = 0
//for i in range (len (f) - 1) :
//    if f[i] > f[i + 1]:
//temp = f[i]
//f[i] = f[i + 1]
//f[i + 1] = temp
//temp = x[i]
//x[i] = x[i + 1]
//x[i + 1] = temp
//k += 1
//
//
//def IWO (func, s0, smax, nmin, nmax, sigma_b, sigma_e, Xmin, Xmax, m, tmax, teoretic_x) :
//    X = []
//    for i in range (s0) : # Блок инициализации
//        xi = []
//        for j in range (len (Xmin)) :
//            xi.append (Xmin[j] + random.random () * (Xmax[j] - Xmin[j]))
//            X.append (xi)
//            f = []
//            for xi in X :
//f.append (func (xi))
//t = 0
//while t <= tmax :
//    n = []  # Блок генерации семян
//    fbest = min (f)
//    fworst = max (f)
//    for fi in f :
//n.append (round (fi * (nmax - nmin) / (fbest - fworst) + (fbest * nmin - fworst * nmax) / (fbest - fworst)))
//Xnew = []
//sigma = (((tmax - t) / tmax) * *m) * (sigma_b - sigma_e) + sigma_e
//for k in range (len (X)) :
//    for i in range (n[k]) :
//        xj = []
//        for j in range (len (X[k])) :
//            xj.append (X[k][j] + np.random.normal (0, sigma))
//            xj = np.clip (xj, Xmin, Xmax)
//            Xnew.append (xj)
//            X = X + Xnew
//
//            f = []  # Блок конкурентного исключения
//            for xi in X :
//f.append (func (xi))
//sort (X, f)
//if len (X) > smax:
//X = X[:smax]
//f = f[:smax]
//t += 1
//if np.linalg.norm (np.array (X[0]) - np.array (teoretic_x)) < 1e-2 * len (teoretic_x) :
//    return[X[0], True, t]
//    # print ("Поколение {}: {} {} {}".format (t, max (f), min (f), np.mean (f)))
//
//    return[X[0], False, tmax]

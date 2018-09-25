/*Copyright 2018 LibOpt Authors

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef _FUNCTION_H_
#define _FUNCTION_H_

#include "common.h"

/* Benchmark functions */
double Ackley_First(Agent *a, va_list arg); /* It computes the 1st Ackley's function */
double Ackley_Second(Agent *a, va_list arg); /* It computes the 2nd Ackley's function */
double Ackley_Third(Agent *a, va_list arg); /* It computes the 3rd Ackley's function */
double Adjiman(Agent *a, va_list arg); /* It computes the Adjiman's function */
double Alpine_First(Agent *a, va_list arg); /* It computes the 1st Alpine's function */
double Alpine_Second(Agent *a, va_list arg); /* It computes the 2nd Alpine's function */
double Bartels_Conn(Agent *a, va_list arg); /* It computes the Bartels' Conn function */
double Beale(Agent *a, va_list arg); /* It computes the Beale's function */
double Biggs_EXP2(Agent *a, va_list arg); /* It computes the 2-D Biggs' Exponential function */
double Biggs_EXP3(Agent *a, va_list arg); /* It computes the 3-D Biggs' Exponential function */
double Biggs_EXP4(Agent *a, va_list arg); /* It computes the 4-D Biggs' Exponential function */
double Biggs_EXP5(Agent *a, va_list arg); /* It computes the 5-D Biggs' Exponential function */
double Biggs_EXP6(Agent *a, va_list arg); /* It computes the 6-D Biggs' Exponential function */
double Bird(Agent *a, va_list arg); /* It computes the Bird's function */
double Bohachevsky_First(Agent *a, va_list arg); /* It computes the 1st Bohachevsky's function */
double Bohachevsky_Second(Agent *a, va_list arg); /* It computes the 2nd Bohachevsky's function */
double Bohachevsky_Third(Agent *a, va_list arg); /* It computes the 3rd Bohachevsky's function */
double Booth(Agent *a, va_list arg); /* It computes the Booth's function */
double Box_Betts(Agent *a, va_list arg); /* It computes the Box-Betts Quadratic Sum function */
double Brent(Agent *a, va_list arg); /* It computes the Brent's function */
double Brown(Agent *a, va_list arg); /* It computes the Brown's function */
double Bukin_Second(Agent *a, va_list arg); /* It computes the 2nd Bukin's function */
double Bukin_Forth(Agent *a, va_list arg); /* It computes the 4th Bukin's function */
double Bukin_Sixth(Agent *a, va_list arg); /* It computes the 6th Bukin's function */
double Three_HumpCamel(Agent *a, va_list arg); /* It computes the Three-Hump Camel function */
double Six_HumpCamel(Agent *a, va_list arg); /* It computes the Six-Hump Camel function */
double Chen_Bird(Agent *a, va_list arg); /* It computes the Chen's Bird function */
double Chen_V(Agent *a, va_list arg); /* It computes the Chen's V function */
double Chichinadze(Agent *a, va_list arg); /* It computes the Chichinadze's function */
double Chung_Reynolds(Agent *a, va_list arg); /* It computes the Chung Reynolds' function */
double Cosine(Agent *a, va_list arg); /* It computes the Cosine's Mixture function */
double Colville(Agent *a, va_list arg); /* It computes the Colville's function */
double Cross_Tray(Agent *a, va_list arg); /* It computes the Cross-in-Tray function */
double Csendes(Agent *a, va_list arg); /* It computes the Csendes' function */
double Cube(Agent *a, va_list arg); /* It computes the Cube's function */
double Damavandi(Agent *a, va_list arg); /* It computes the Damavandi's function */
double Deckkers_Aarts(Agent *a, va_list arg); /* It computes the Deckkers-Aarts' function */
double Dixon_Price(Agent *a, va_list arg); /* It computes the Dixon's-Price function */
double Easom(Agent *a, va_list arg); /* It computes the Easom's function */
double ElAttar_VidyasagarDutta(Agent *a, va_list arg); /* It computes the El-Attar-Vidyasagar-Dutta's function */
double Eggcrate(Agent *a, va_list arg); /* It computes the Egg Crate function */
double Eggholder(Agent *a, va_list arg); /* It computes the Egg Holder function */
double Exponential(Agent *a, va_list arg); /* It computes the Exponential function */
double EXP_2(Agent *a, va_list arg); /* It computes the 2-D Exponential function */
double Freudenstein_Roth(Agent *a, va_list arg); /* It computes the Freudenstein's Roth function */
double Giunta(Agent *a, va_list arg); /* It computes the Giunta's function */
double Goldstein_Price(Agent *a, va_list arg); /* It computes the Goldstein-Price's function */
double Griewank(Agent *a, va_list arg); /* It computes the Griewank's function */
double Gulf_Research(Agent *a, va_list arg); /* It computes the Gulf's Research problem */
double Helical_Valley(Agent *a, va_list arg); /* It computes the Helical Valley function */
double Himmelblau(Agent *a, va_list arg); /* It computes the Himmelblau's function */
double Hosaki(Agent *a, va_list arg); /* It computes the Hosaki's function */
double Jennrick_Sampson(Agent *a, va_list arg); /* It computes the Jennrick's-Sampson function */
double Keane(Agent *a, va_list arg); /* It computes the Keane's function */
double Leon(Agent *a, va_list arg); /* It computes the Leon's function */
double Levy(Agent *a, va_list arg); /* It computes the Levy's function */
double Levy_Thirteenth(Agent *a, va_list arg); /* It computes the 13th Levy's function */
double Matyas(Agent *a, va_list arg); /* It computes the Matyas' function */
double McCormick(Agent *a, va_list arg); /* It computes the McCormick's function */
double Miele_Cantrell(Agent *a, va_list arg); /* It computes the Miele Cantrell's function */
double Parsopoulos(Agent *a, va_list arg); /* It computes the Parsopoulos' function */
double Pen_Holder(Agent *a, va_list arg); /* It computes the Pen Holder function */
double Pathological(Agent *a, va_list arg); /* It computes the Pathological function */
double Paviani(Agent *a, va_list arg); /* It computes the Paviani's function */
double Periodic(Agent *a, va_list arg); /* It computes the Periodic function */
double Powell_Sum(Agent *a, va_list arg); /* It computes the Powell's Sum function */
double Price_First(Agent *a, va_list arg); /* It computes the 1st Price's function */
double Price_Second(Agent *a, va_list arg); /* It computes the 2nd Price's function */
double Price_Third(Agent *a, va_list arg); /* It computes the 3rd Price's function */
double Price_Forth(Agent *a, va_list arg); /* It computes the 4th Price's function */
double Qing(Agent *a, va_list arg); /* It computes the Qing's function */
double Quadratic(Agent *a, va_list arg); /* It computes the Quadratic function */
double Quartic(Agent *a, va_list arg); /* It computes the Quartic function */
double Quintic(Agent *a, va_list arg); /* It computes the Quintic function */
double Rastrigin(Agent *a, va_list arg); /* It computes the Rastrigin's function */
double Rosenbrock(Agent *a, va_list arg); /* It computes the Rosenbrock's function */
double Rotated_Ellipsoid_1(Agent *a, va_list arg); /* It computes the Rotated Ellipsoid 1 function */
double Rotated_Ellipsoid_2(Agent *a, va_list arg); /* It computes the Rotated Ellipsoid 2 function */
double Rump(Agent *a, va_list arg); /* It computes the Rump's function */
double Salomon(Agent *a, va_list arg); /* It computes the Salomon's function */
double Schaffer_First(Agent *a, va_list arg); /* It computes the 1st Schaffer's function */
double Schaffer_Second(Agent *a, va_list arg); /* It computes the 2nd Schaffer's function */
double Schaffer_Third(Agent *a, va_list arg); /* It computes the 3rd Schaffer's function */
double Schaffer_Forth(Agent *a, va_list arg); /* It computes the 4th Schaffer's function */
double Schmidt_Vetters(Agent *a, va_list arg); /* It computes the Schmidt Vetters' function */
double Schumer_Steiglitz(Agent *a, va_list arg); /* It computes the Schumer Steiglitz's function */
double Schewefel(Agent *a, va_list arg); /* It computes the Schewefel's function */
double Sphere(Agent *a, va_list arg); /* It computes the Sphere's function */
double Streched_V_SineWave(Agent *a, va_list arg); /* It computes the Streched V Sine Wave function */
double Sum_DifferentPowers(Agent *a, va_list arg); /* It computes the Sum of Different Powers function */
double Sum_Squares(Agent *a, va_list arg); /* It computes the Sum Squares function */
double Styblinski_Tang(Agent *a, va_list arg); /* It computes the Styblinski's-Tang function */
double Holder_Table_First(Agent *a, va_list arg); /* It computes the 1st Holder's Table function */
double Holder_Table_Second(Agent *a, va_list arg); /* It computes the 2nd Holder's Table function */
double Carrom_Table(Agent *a, va_list arg); /* It computes the Carrom's Table function */
double Testtube_Holder(Agent *a, va_list arg); /* It computes the Testtube's Holder function */
double Trecanni(Agent *a, va_list arg); /* It computes the Trecanni's function */
double Trefethen(Agent *a, va_list arg); /* It computes the Trefethen's function */
double Trigonometric_1(Agent *a, va_list arg); /* It computes the Trigonometric 1 function */
double Trigonometric_2(Agent *a, va_list arg); /* It computes the Trigonometric 2 function */
double Venter_Sobiezcczanski(Agent *a, va_list arg); /* It computes the Venter's Sobiezcczanski-Sobieski function */
double Watson(Agent *a, va_list arg); /* It computes the Watson's function */
double Wayburn_Seader_1(Agent *a, va_list arg); /* It computes the Wayburn Seader 1 function */
double Wayburn_Seader_2(Agent *a, va_list arg); /* It computes the Wayburn Seader 2 function */
double Wayburn_Seader_3(Agent *a, va_list arg); /* It computes the Wayburn Seader 3 function */
double Wavy(Agent *a, va_list arg); /* It computes the Wavy's function */
double XinShe_Yang_1(Agent *a, va_list arg); /* It computes the Xin-She Yang's 1 function */
double XinShe_Yang_2(Agent *a, va_list arg); /* It computes the Xin-She Yang's 2 function */
double XinShe_Yang_3(Agent *a, va_list arg); /* It computes the Xin-She Yang's 3 function */
double XinShe_Yang_4(Agent *a, va_list arg); /* It computes the Xin-She Yang's 4 function */
double Zakharov(Agent *a, va_list arg); /* It computes the Zakharov's function */
double Zettl(Agent *a, va_list arg); /* It computes the Zettl's function */
double Zirilli(Agent *a, va_list arg); /* It computes the Zirilli's function */
/***********************/

/* Genetic Programming general-purpose functions */
double *f_SUM_(double *x, double *y, int n); /* It computes the pointwise sum of two n-dimensional arrays */
double *f_SUB_(double *x, double *y, int n); /* It computes the pointwise subtraction of two n-dimensional arrays */
double *f_MUL_(double *x, double *y, int n); /* It computes the pointwise multiplication of two n-dimensional arrays */
double *f_DIV_(double *x, double *y, int n); /* It computes the pointwise (protected) division of two n-dimensional arrays */
double *f_ABS_(double *x, int n); /* It computes the absolute value of each element from an n-dimensional array */
double *f_SQRT_(double *x, int n); /* It computes the squared root of each element from a two n-dimensional array */
double *f_EXP_(double *x, int n); /* It computes the exponential (e) of each element from an n-dimensional array */
double *f_LOG_(double *x, int n); /* It computes the natural logarithm (base-e logarithm) of each element from an n-dimensional array */
double *f_AND_(double *x, double *y, int n); /* It computes the logical function AND among two n-dimensional arrays */
double *f_OR_(double *x, double *y, int n); /* It computes the logical function OR among two n-dimensional arrays */
double *f_XOR_(double *x, double *y, int n); /* It computes the logical function XOR among two n-dimensional arrays */
double *f_NOT_(double *x, int n); /* It computes the logical function NOT of an n-dimensional array */
/*****************************/

/* Tensor-based Genetic Programming general-purpose functions */
double **f_TSUM_(double **x, double **y, int m, int n); /* It computes the tensor sum of two mxn-dimensional tensors */
double **f_TSUB_(double **x, double **y, int m, int n); /* It computes the tensor subtraction of two mxn-dimensional tensors */
double **f_TMUL_(double **x, double **y, int m, int n); /* It computes the tensor multiplication of two mxn-dimensional tensors */
double **f_TDIV_(double **x, double **y, int m, int n); /* It computes the tensor division (protected) of two mxn-dimensional tensors */
/*****************************/

/* Math functions */
double Logistic_Sigmoid(double x); /* It computes the logistic sigmoid function */
/*****************************/

#endif
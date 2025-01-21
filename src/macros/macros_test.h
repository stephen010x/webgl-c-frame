/* 
 *  NOTICE!
 *
 *  This is solely for testing the macros file. 
 *  Do not include this in your project
 */


#include "macros.h"
#include "macros_ext.h"










 /*#############################################
   ####                                     ####
   ####         TESTS BEGIN HERE            ####
   ####                                     ####
   ############################################*/



 /* Test setup */
////////////////

#define A "sand"
#define B gold
#define C 12
#define D void
#define E (int*)void
#define F D
#define G T(F)
#define H F
#define I G
// #define A "sand"
// #define B gold
// #define C 12
// #define D void
// #define E (int*)void
// #define F D
// #define G T(F)
// #define H F
// #define I G

// #define T(__n) MAN##__n
#define T(__n) MAN##__n


#define ALL_SAFE_TESTS B, C, D, F, G, H, I, T
#define ALL_TESTS A, B, C, D, E, F, G, H, I, T
// #define ALL_SAFE_TESTS B, C, D, F, G, H, I, T
// #define ALL_TESTS A, B, C, D, E, F, G, H, I, T








 /* Order of operation tests */
//////////////////////////////

// B##C
B##C

// #B###C (errors)
//#B###C

#define TEST_1(__a, __b) B##C##__a##__b #__b
// #define TEST_1(__a, __b) B##C##__a##__b #__b
// TEST_1(A, B)
TEST_1(A, B)


// B##C##__a##__b #__b #B
B##C##__a##__b #__b #B








 /* Macro tests */
/////////////////


// CONCAT(ALL_SAFE_TESTS)
CONCAT(ALL_SAFE_TESTS)

// _CONCAT(B, C)
_CONCAT(B, C)
// _CONCAT(D, F)
_CONCAT(D, F)
// _CONCAT(G, H)
_CONCAT(G, H)
// _CONCAT(I, T)
_CONCAT(I, T)
// _CONCAT(I, T(I))
_CONCAT(I, T(I))



#define TEST_2A(__n) I##__n
#define TEST_2B(__n) _CONCAT(I, __n)
#define TEST_2C(__n) CONCAT(I, __n)
// #define TEST_2A(__n) I##__n
// #define TEST_2B(__n) _CONCAT(I, __n)
// #define TEST_2C(__n) CONCAT(I, __n)

// TEST_2A(I)
TEST_2A(I)
// TEST_2B(I)
TEST_2B(I)
// TEST_2C(I)
TEST_2C(I)



// #B (errors)
//#B
// # B (errors)
//# B
// #define B (just redefines B)
//#define B


// BYTE(2)
BYTE(2)
// BYTE(20)
BYTE(20)
// BYTE(200)
BYTE(200)
// BYTE(2000)
BYTE(2000)
// BYTE(20000)
BYTE(20000)


// PARAM(0, A, B, C, D)
PARAM(0, A, B, C, D)
// PARAM(2, A, B, C, D)
PARAM(2, A, B, C, D)
// PARAM(7, A, B, C, D)
PARAM(7, A, B, C, D)
// PARAM(0, ALL_TESTS)
PARAM(0, ALL_TESTS)
// PARAM(2, ALL_TESTS)
PARAM(2, ALL_TESTS)
// PARAM(7, ALL_TESTS)
PARAM(7, ALL_TESTS)
// PARAM(0, PACK(A, B, C, D))
PARAM(0, PACK(A, B, C, D))
// PARAM(2, PACK(A, B, C, D))
PARAM(2, PACK(A, B, C, D))
// PARAM(7, PACK(A, B, C, D))
PARAM(7, PACK(A, B, C, D))

// #define PARAM_TEST_1(n, ...) PARAM(n, __VA_ARGS__)
// #define PARAM_TEST_2(n, ...) PARAM(n, PACK(__VA_ARGS__)
// #define PARAM_TEST_3(...) PARAM(__VA_ARGS__)
#define PARAM_TEST_1(n, ...) PARAM(n, __VA_ARGS__)
#define PARAM_TEST_2(n, ...) PARAM(n, PACK(__VA_ARGS__))
#define PARAM_TEST_3(...) PARAM(__VA_ARGS__)

// PARAM_TEST_1(2, A, B, C, D)
PARAM_TEST_1(2, A, B, C, D)
// PARAM_TEST_1(2, ALL_TESTS)
PARAM_TEST_1(2, ALL_TESTS)
// PARAM_TEST_1(2, PACK(ALL_TESTS))
PARAM_TEST_1(2, PACK(ALL_TESTS))

// PARAM_TEST_2(2, A, B, C, D)
PARAM_TEST_2(2, A, B, C, D)
// PARAM_TEST_2(2, ALL_TESTS)
PARAM_TEST_2(2, ALL_TESTS)
// PARAM_TEST_2(2, PACK(ALL_TESTS))
PARAM_TEST_2(2, PACK(ALL_TESTS))

// PARAM_TEST_2(2, A, B, C, D)
PARAM_TEST_3(2, A, B, C, D)
// PARAM_TEST_2(2, ALL_TESTS)
PARAM_TEST_3(2, ALL_TESTS)
// PARAM_TEST_2(2, PACK(ALL_TESTS))
PARAM_TEST_3(2, PACK(ALL_TESTS))



//#define PARAM_TEST(a, ...) a __VA_ARGS__
#define PARAM_TEST(a, ...) a __VA_ARGS__

// trurns out variable args ... can accept zero parameters
//PARAM_TEST("x")
PARAM_TEST("x")

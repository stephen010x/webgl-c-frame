# 0 "macros_test.h"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "macros_test.h"
/* 
 *  NOTICE!
 *
 *  This is solely for testing the macros file. 
 *  Do not include this in your project
 */


# 1 "macros.h" 1





/*  NOTES ON ORDER OF SUBSTITUTION
 *  ------------------------------
 *
 *  - Variables names are passed as parameters, and only
 *    substituted in the macro
 *    (in other words functions are called before variables get substituted)
 *  
 *  - Order goes: Substiute var
 *
 */


//#define IFEQ_ZERO(__value, __block) _IFEQ_ZERO##__value(__block)
//#define _IFEQ_ZERO_0(__block) block

//#define IFNEQ_ZERO(__value, __block) _IFNEQ_ZERO_##__value(__block)
//#define _IFNEQ_ZERO_0(__block) block

// would this even be useful for anything?
//#define EVAL(__n) __n


// NOTE:
// The concat operator ## will only expand function parameters once. 
// everything else will be prevented from expanding

// Will fully expand every argument



// Will only fully expand function arguments. 
// Will prevent expansion of anything else
// This level of concat cant be done with more than two at a time
// Will discard any extra params.
// TODO: consider enforcing only two params to help with finding errors
# 52 "macros.h"
// I don't remember what I was planning for this either
//#define NONE none




// alright. I think the itterator gets one value, and returns two.


// value, condition, itterator, block




// loop itterator constructor

// loop itterator






// T/ODO: Yeah, just replace this with the updated system eventually
/*#define IS_ZERO(__n) CONCAT(_IS_ZERO_, __n)
#define _IS_ZERO_0 true
#define _IS_ZERO_1 false
#define _IS_ZERO_2 false
#define _IS_ZERO_3 false
#define _IS_ZERO_4 false
#define _IS_ZERO_5 false
#define _IS_ZERO_6 false
#define _IS_ZERO_7 false
#define _IS_ZERO_8 false
#define _IS_ZERO_9 false
#define _IS_ZERO_10 false
#define _IS_ZERO_11 false
#define _IS_ZERO_12 false
#define _IS_ZERO_13 false
#define _IS_ZERO_14 false
#define _IS_ZERO_15 false
#define _IS_ZERO_16 false
#define _IS_ZERO_17 false
#define _IS_ZERO_18 false
#define _IS_ZERO_19 false
#define _IS_ZERO_20 false
#define _IS_ZERO_21 false
#define _IS_ZERO_22 false
#define _IS_ZERO_23 false
#define _IS_ZERO_24 false
#define _IS_ZERO_25 false
#define _IS_ZERO_26 false
#define _IS_ZERO_27 false
#define _IS_ZERO_28 false
#define _IS_ZERO_29 false
#define _IS_ZERO_30 false
#define _IS_ZERO_31 false
#define _IS_ZERO_32 false
#define _IS_ZERO_33 false
#define _IS_ZERO_34 false
#define _IS_ZERO_35 false
#define _IS_ZERO_36 false
#define _IS_ZERO_37 false
#define _IS_ZERO_38 false
#define _IS_ZERO_39 false
#define _IS_ZERO_40 false
#define _IS_ZERO_41 false
#define _IS_ZERO_42 false
#define _IS_ZERO_43 false
#define _IS_ZERO_44 false
#define _IS_ZERO_45 false
#define _IS_ZERO_46 false
#define _IS_ZERO_47 false
#define _IS_ZERO_48 false
#define _IS_ZERO_49 false
#define _IS_ZERO_50 false
#define _IS_ZERO_51 false
#define _IS_ZERO_52 false
#define _IS_ZERO_53 false
#define _IS_ZERO_54 false
#define _IS_ZERO_55 false
#define _IS_ZERO_56 false
#define _IS_ZERO_57 false
#define _IS_ZERO_58 false
#define _IS_ZERO_59 false
#define _IS_ZERO_60 false
#define _IS_ZERO_61 false
#define _IS_ZERO_62 false
#define _IS_ZERO_63 false
#define _IS_ZERO_64 false*/
# 170 "macros.h"
// TODO: yeah, lets just stick with number loops for now
// with maybe some behavior enums
// or maybe we can just have an itterator where we pass a macro function
//FOR(GTR(), "stuff")





/*
Alright lets test an idea.
To force an undefined value to return nothing
by having all defined values be defined as multiple arguments, 
and always only ever returning the second argument
*/

/*
YES IT WORKS!
I gave up on the possability months ago!
*/



// T/ODO: Have concat accept variable number of parameters
//#define CONCAT(__a, __b) _CONCAT(__a, __b)
//#define _CONCAT(__a, __b) __a ## __b
//#define CONCAT(...) _CONCAT(__a, __b)
//#define _CONCAT(...) __a ## __b





/*#define RETURN_DEFINED(__n) ALLOW_SECOND(CONCAT(_RETURN_DEFINED_, __n))
#define _RETURN_DEFINED_void BLANK, "void"
#define _RETURN_DEFINED_bog BLANK, "bog"*/

// usage PARAM(3, __VA_ARGS__)
# 221 "macros.h"
// TODO: Fix PARAM macro and replace ALLOW_SECOND with it

//#define DECAST(__n) PARAM(1 , _DECAST_ __n, __n)


//#define ISVOID(__n) _ISVOID_ADJUST(ALLOW_SECOND(CONCAT(_ISVOID_, __n)))


// note that _CONCAT is neccissary instead of CONCAT






// TODO: finish this function
// this will return true if it is any of the known types of values or parameters
// otherwise it will return false
//#define ISEXIST(__n) OR(ISVOID(__n), ISNUM(__n), ISBOOL(__n))





// Say, with my new trick, is it possible to check if a value is defined
// by basically comparing the name of the value with the definition?
// I suppose not, as that would require the hashtag, and can't be generated



// !!!!!!!!!
// TODO: I should consider encouraging myself to use _CONCAT instead of CONCAT
// for internal usage of all of my macros. Because I believe it would still all
// work while also avoiding certain issues. And just leave the CONCAT for use
// outside of these macro definitions
// !!!!!!!!!


// TODO: create a macro test file, and run the c preprocessor on it to test
// that everything is working







// this only works for macros defined as blank. Undefined macros
// will return false rather than true
// TODO: replace ALLOW_SECOND with PARAM when you get that working



// get number of parameters (up to 9 for now
// TODO: replace with a while loop when you get that set up
// TODO: Finish writing this macro
// TODO: use this for determining size of number
// to allow for different number sizes rather than static




// will return true zero params if first param is blank
// TODO: use PARAM to get first param when you get that working
// TODO: figure out if _CONCAT can be used in place of CONCAT







// basically, if true then true. If anything else, then false






// number format:
// p w 2 3 a 7


// TODO: replace the BLANK, true system with something a little
// more intuitive, such as a truthy adjust function so that I don't have to
// worry about second parameters for everything







// should always receive at least three parameters






// used by PARAM to address both __VA_ARGS__ and a packed array
# 336 "macros.h"
// to prevent recursively expanding every call in a loop
// this will only call a macro if the condition is true
// the last value is the params
# 350 "macros.h"
// will discard the sign!!!

//#define _UNBYTE(__sign, ...) CONCAT(0x, __VA_ARGS__)


// accepts packed byte, returns packed byte
// probably would benefit from the while loop






//#define BYTE(__n) p b _B_##__n






// TODO to save space, replace _B_456 with _456, and have no leading zeroes
# 1060 "macros.h"
// http://jhnet.co.uk/articles/cpp_magic
// https://www.iar.com/knowledge/learn/programming/advanced-preprocessor-tips-and-tricks/

// still trying to find resource that describes macro order of operation
// it is probably located in one of my earlier projects somewhere.
# 10 "macros_test.h" 2
# 1 "macros_ext.h" 1
# 11 "macros_test.h" 2
# 21 "macros_test.h"
 /*#############################################
   ####                                     ####
   ####         TESTS BEGIN HERE            ####
   ####                                     ####
   ############################################*/



 /* Test setup */
////////////////
# 41 "macros_test.h"
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





// #define ALL_SAFE_TESTS B, C, D, F, G, H, I, T
// #define ALL_TESTS A, B, C, D, E, F, G, H, I, T
# 67 "macros_test.h"
 /* Order of operation tests */
//////////////////////////////

// B##C
gold##12

// #B###C (errors)
//#B###C


// #define TEST_1(__a, __b) B##C##__a##__b #__b
// TEST_1(A, B)
BCAB "B"


// B##C##__a##__b #__b #B
gold##12##__a##__b #__b #gold
# 92 "macros_test.h"
 /* Macro tests */
/////////////////


// CONCAT(ALL_SAFE_TESTS)
gold12voidvoidMANFvoidMANFT

// _CONCAT(B, C)
BC
// _CONCAT(D, F)
DF
// _CONCAT(G, H)
GH
// _CONCAT(I, T)
IT
// _CONCAT(I, T(I))
IT(MANF)






// #define TEST_2A(__n) I##__n
// #define TEST_2B(__n) _CONCAT(I, __n)
// #define TEST_2C(__n) CONCAT(I, __n)

// TEST_2A(I)
II
// TEST_2B(I)
IMANF
// TEST_2C(I)
MANFMANF



// #B (errors)
//#B
// # B (errors)
//# B
// #define B (just redefines B)
//#define B


// BYTE(2)
(p,0,2)
// BYTE(20)
(p,1,4)
// BYTE(200)
(p,c,8)
// BYTE(2000)
(p,0,7,d,0)
// BYTE(20000)
(p,4,e,2,0)


// PARAM(0, A, B, C, D)
"sand"
// PARAM(2, A, B, C, D)
12
// PARAM(7, A, B, C, D)

// PARAM(0, ALL_TESTS)
"sand"
// PARAM(2, ALL_TESTS)
12
// PARAM(7, ALL_TESTS)
void
// PARAM(0, PACK(A, B, C, D))
("sand", gold, 12, void)
// PARAM(2, PACK(A, B, C, D))

// PARAM(7, PACK(A, B, C, D))


// #define PARAM_TEST_1(n, ...) PARAM(n, __VA_ARGS__)
// #define PARAM_TEST_2(n, ...) PARAM(n, PACK(__VA_ARGS__)
// #define PARAM_TEST_3(...) PARAM(__VA_ARGS__)




// PARAM_TEST_1(2, A, B, C, D)
12
// PARAM_TEST_1(2, ALL_TESTS)
12
// PARAM_TEST_1(2, PACK(ALL_TESTS))


// PARAM_TEST_2(2, A, B, C, D)

// PARAM_TEST_2(2, ALL_TESTS)

// PARAM_TEST_2(2, PACK(ALL_TESTS))


// PARAM_TEST_2(2, A, B, C, D)
12
// PARAM_TEST_2(2, ALL_TESTS)
12
// PARAM_TEST_2(2, PACK(ALL_TESTS))


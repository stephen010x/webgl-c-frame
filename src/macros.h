#ifndef MACROS_H
#define MACROS_H


//#define IFEQ_ZERO(__value, __block) _IFEQ_ZERO##__value(__block)
//#define _IFEQ_ZERO_0(__block) block

//#define IFNEQ_ZERO(__value, __block) _IFNEQ_ZERO_##__value(__block)
//#define _IFNEQ_ZERO_0(__block) block


#define EVAL(__n) __n 

#define CONCAT(__a, __b) _CONCAT(__a, __b)
#define _CONCAT(__a, __b) __a ## __b


#define NOT(__b) CONCAT(_NOT_, __b))
#define _NOT_true false
#define _NOT_false true


#define IS_ZERO(__n) CONCAT(_IS_ZERO_, __n)
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
#define _IS_ZERO_64 false


#define ISNZERO(__n) NOT(ISZERO(__n))



#define IFTHEN(__cond, __block) CONCAT(_IFTHEN_, __cond(__block))
#define _IFTHEN_true(__block) __block
#define _IFTHEN_false(__block) 


#define IFNTHEN(__cond, __block) IFTHEN(NOT(__cond), __block)


#define IFZERO(__n, __block) IFTHEN(ISZERO(__n), __block)
#define IFNZERO(__n, __block) IFTHEN(ISNZERO(__n), __block)



#define NUMBER(...) _NUMBER( stuff here



FOR(GTR(), "stuff")

#define LOOP(__cond, block) _D_##__cond
#define _D_




// number format:
// p w 2 3 a 7


// should always receive at least three parameters
#define NEG(__sign, ...) _NEG_##__sign(__VA_ARGS__)
#define _NEG_p(...) n __VA_ARGS__
#define _NEG_p(...) p __VA_ARGS__


#define BYTE(__n) p b _B_##__n

#define _B_0x0
#define _B_0x1
#define _B_0x2


#define _B_0 0
#define _B_1 1
#define _B_2 2
#define _B_3 3
#define _B_4 4
#define _B_5 5
#define _B_6 6
#define _B_7 7
#define _B_8 8
#define _B_9 9
#define _B_10 a
#define _B_11 b
#define _B_12 c
#define _B_13 d
#define _B_14 e
#define _B_15 f
#define _B_16 0
#define _B_17 1
#define _B_18 2
#define _B_19 3
#define _B_20 4
#define _B_21 5
#define _B_22 6
#define _B_23 7
#define _B_24 8
#define _B_25 9
#define _B_26 a
#define _B_27 b
#define _B_28 c
#define _B_29 d
#define _B_30 e
#define _B_31 f
#define _B_32 
#define _B_33 
#define _B_34 
#define _B_35 
#define _B_36 
#define _B_37 
#define _B_38 
#define _B_39 
#define _B_40 
#define _B_41 
#define _B_42 
#define _B_43 
#define _B_44 
#define _B_45 
#define _B_46 
#define _B_47 
#define _B_48 
#define _B_49 
#define _B_50 
#define _B_51 
#define _B_52 
#define _B_53 
#define _B_54 
#define _B_55 
#define _B_56 
#define _B_57 
#define _B_58 
#define _B_59 
#define _B_60 
#define _B_61 
#define _B_62 
#define _B_63 
#define _B_64 
#define _B_65 
#define _B_66 
#define _B_67 
#define _B_68 
#define _B_69 
#define _B_70 
#define _B_71 
#define _B_72 
#define _B_73 
#define _B_74 
#define _B_75 
#define _B_76 
#define _B_77 
#define _B_78 
#define _B_79 
#define _B_80 
#define _B_81 
#define _B_82 
#define _B_83 
#define _B_84 
#define _B_85 
#define _B_86 
#define _B_87 
#define _B_88 
#define _B_89 
#define _B_90 
#define _B_91 
#define _B_92 
#define _B_93 
#define _B_94 
#define _B_95 
#define _B_96 
#define _B_97 
#define _B_98 
#define _B_99 
#define _B_100 
#define _B_101 
#define _B_102 
#define _B_103 
#define _B_104 
#define _B_105 
#define _B_106 
#define _B_107 
#define _B_108 
#define _B_109 
#define _B_110 
#define _B_111 
#define _B_112 
#define _B_113 
#define _B_114 
#define _B_115 
#define _B_116 
#define _B_117 
#define _B_118 
#define _B_119 
#define _B_120 
#define _B_121 
#define _B_122 
#define _B_123 
#define _B_124 
#define _B_125 
#define _B_126 
#define _B_127 
#define _B_128 
#define _B_129 
#define _B_130 
#define _B_131 
#define _B_132 
#define _B_133 
#define _B_134 
#define _B_135 
#define _B_136 
#define _B_137 
#define _B_138 
#define _B_139 
#define _B_140 
#define _B_141 
#define _B_142 
#define _B_143 
#define _B_144 
#define _B_145 
#define _B_146 
#define _B_147 
#define _B_148 
#define _B_149 
#define _B_150 
#define _B_151 
#define _B_152 
#define _B_153 
#define _B_154 
#define _B_155 
#define _B_156 
#define _B_157 
#define _B_158 
#define _B_159 
#define _B_160 
#define _B_161 
#define _B_162 
#define _B_163 
#define _B_164 
#define _B_165 
#define _B_166 
#define _B_167 
#define _B_168 
#define _B_169 
#define _B_170 
#define _B_171 
#define _B_172 
#define _B_173 
#define _B_174 
#define _B_175 
#define _B_176 
#define _B_177 
#define _B_178 
#define _B_179 
#define _B_180 
#define _B_181 
#define _B_182 
#define _B_183 
#define _B_184 
#define _B_185 
#define _B_186 
#define _B_187 
#define _B_188 
#define _B_189 
#define _B_190 
#define _B_191 
#define _B_192 
#define _B_193 
#define _B_194 
#define _B_195 
#define _B_196 
#define _B_197 
#define _B_198 
#define _B_199 
#define _B_200 
#define _B_201 
#define _B_202 
#define _B_203 
#define _B_204 
#define _B_205 
#define _B_206 
#define _B_207 
#define _B_208 
#define _B_209 
#define _B_210 
#define _B_211 
#define _B_212 
#define _B_213 
#define _B_214 
#define _B_215 
#define _B_216 
#define _B_217 
#define _B_218 
#define _B_219 
#define _B_220 
#define _B_221 
#define _B_222 
#define _B_223 
#define _B_224 
#define _B_225 
#define _B_226 
#define _B_227 
#define _B_228 
#define _B_229 
#define _B_230 
#define _B_231 
#define _B_232 
#define _B_233 
#define _B_234 
#define _B_235 
#define _B_236 
#define _B_237 
#define _B_238 
#define _B_239 
#define _B_240 
#define _B_241 
#define _B_242 
#define _B_243 
#define _B_244 
#define _B_245 
#define _B_246 
#define _B_247 
#define _B_248 
#define _B_249 
#define _B_250 
#define _B_251 
#define _B_252 
#define _B_253 
#define _B_254 
#define _B_255 
#define _B_256 
#define _B_257 
#define _B_258 
#define _B_259 
#define _B_260 
#define _B_261 
#define _B_262 
#define _B_263 
#define _B_264 
#define _B_265 
#define _B_266 
#define _B_267 
#define _B_268 
#define _B_269 
#define _B_270 
#define _B_271 
#define _B_272 
#define _B_273 
#define _B_274 
#define _B_275 
#define _B_276 
#define _B_277 
#define _B_278 
#define _B_279 
#define _B_280 
#define _B_281 
#define _B_282 
#define _B_283 
#define _B_284 
#define _B_285 
#define _B_286 
#define _B_287 
#define _B_288 
#define _B_289 
#define _B_290 
#define _B_291 
#define _B_292 
#define _B_293 
#define _B_294 
#define _B_295 
#define _B_296 
#define _B_297 
#define _B_298 
#define _B_299 



#endif


// http://jhnet.co.uk/articles/cpp_magic
// https://www.iar.com/knowledge/learn/programming/advanced-preprocessor-tips-and-tricks/

// still trying to find resource that describes macro order of operation
// it is probably located in one of my earlier projects somewhere.

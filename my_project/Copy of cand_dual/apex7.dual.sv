
module apex7 ( BULL6, BULL5, BULL4, BULL3, BULL2, BULL1, BULL0, STAR3, STAR2, 
        STAR1, STAR0, VST1, VST0, COMPPAR, DEL1, KBG_N, OVACC, WATCH, FBI, END, 
        PY, OWL_N, ORWD_N, PLUTO5, PLUTO4, PLUTO3, PLUTO2, PLUTO1, PLUTO0, 
        VSUMESR, VLENESR, MARSSR, RATR, VERR_N, ACCRPY, LSD, ICLR, IBT2, IBT1, 
        IBT0, MMERR, VACC, CAT5, CAT4, CAT3, CAT2, CAT1, CAT0, CAPSD, BULL6_P, 
        BULL5_P, BULL4_P, BULL3_P, BULL2_P, BULL1_P, BULL0_P, STAR3_P, STAR2_P, 
        STAR1_P, STAR0_P, VST1_P, VST0_P, COMPPAR_P, DEL1_P, KBG_F, OVACC_P, 
        WATCH_P, FBI_P, END_P, PY_P, OWL_F, ORWD_F, PLUTO5_P, PLUTO4_P, 
        PLUTO3_P, PLUTO2_P, PLUTO1_P, PLUTO0_P, VSUMESR_P, VLENESR_P, MARSSR_P, 
        RATR_P, VERR_F, ACCRPY_P, LSD_P, SDO );
  input BULL6, BULL5, BULL4, BULL3, BULL2, BULL1, BULL0, STAR3, STAR2, STAR1,
         STAR0, VST1, VST0, COMPPAR, DEL1, KBG_N, OVACC, WATCH, FBI, END, PY,
         OWL_N, ORWD_N, PLUTO5, PLUTO4, PLUTO3, PLUTO2, PLUTO1, PLUTO0,
         VSUMESR, VLENESR, MARSSR, RATR, VERR_N, ACCRPY, LSD, ICLR, IBT2, IBT1,
         IBT0, MMERR, VACC, CAT5, CAT4, CAT3, CAT2, CAT1, CAT0, CAPSD;
  output BULL6_P, BULL5_P, BULL4_P, BULL3_P, BULL2_P, BULL1_P, BULL0_P,
         STAR3_P, STAR2_P, STAR1_P, STAR0_P, VST1_P, VST0_P, COMPPAR_P, DEL1_P,
         KBG_F, OVACC_P, WATCH_P, FBI_P, END_P, PY_P, OWL_F, ORWD_F, PLUTO5_P,
         PLUTO4_P, PLUTO3_P, PLUTO2_P, PLUTO1_P, PLUTO0_P, VSUMESR_P,
         VLENESR_P, MARSSR_P, RATR_P, VERR_F, ACCRPY_P, LSD_P, SDO;
  wire   n383, n1, n3, n4, n6, n7, n9, n10, n11, n12, n13, n14, n15, n16, n17,
         n18, n58, n59, n61, n63, n64, n65, n95, n97, n98, n99, n101, n114,
         n115, n132, n133, n134, n135, n136, n137, n138, n139, n140, n141,
         n142, n144, n145, n146, n147, n148, n149, n150, n152, n153, n154,
         n155, n156, n157, n158, n161, n163, n164, n165, n166, n167, n169,
         n170, n171, n172, n173, n174, n175, n176, n177, n179, n180, n181,
         n200, n201, n202, n203, n207, n208, n209, n210, n211, n212, n214,
         n215, n216, n217, n218, n219, n220, n222, n223, n224, n225, n226,
         n227, n228, n229, n230, n231, n232, n233, n234, n235, n236, n237,
         n238, n239, n240, n241, n242, n243, n244, n245, n246, n247, n248,
         n249, n250, n251, n252, n253, n254, n255, n256, n257, n258, n259,
         n260, n261, n262, n263, n264, n265, n266, n267, n268, n269, n270,
         n271, n272, n273, n274, n275, n276, n277, n278, n279, n280, n281,
         n282, n283, n284, n285, n286, n287, n288, n289, n290, n291, n292,
         n293, n294, n295, n296, n297, n298, n299, n300, n301, n302, n303,
         n304, n305, n306, n307, n308, n309, n310, n311, n312, n313, n314,
         n315, n316, n317, n318, n319, n320, n321, n322, n323, n324, n325,
         n326, n327, n328, n329, n330, n331, n332, n333, n334, n335, n336,
         n337, n338, n339, n340, n341, n342, n343, n344, n345, n346, n347,
         n348, n349, n350, n351, n352, n353, n354, n355, n356, n357, n358,
         n359, n360, n361, n362, n363, n364, n365, n366, n367, n368, n369,
         n370, n371, n372, n373, n374, n375, n376, n377, n378, n379, n381,
         n382, n384;

  or2 U1 ( .A1(n1), .A2(n375), .Z(WATCH_P) );
  and2 U2 ( .A1(n3), .A2(OVACC), .Z(n1) );
  inv1 U3 ( .I(n4), .ZN(n3) );
  or2 U4 ( .A1(n219), .A2(VACC), .Z(n4) );
  or2 U5 ( .A1(n6), .A2(n7), .Z(VSUMESR_P) );
  and2 U6 ( .A1(VSUMESR), .A2(OWL_N), .Z(n7) );
  and2 U7 ( .A1(VST1), .A2(n222), .Z(n6) );
  or2 U8 ( .A1(n9), .A2(n10), .Z(VST1_P) );
  and2 U9 ( .A1(n11), .A2(VST1), .Z(n10) );
  and2 U10 ( .A1(n12), .A2(PY), .Z(n9) );
  and2 U11 ( .A1(FBI), .A2(n13), .Z(n12) );
  or2 U12 ( .A1(n14), .A2(n15), .Z(VST0_P) );
  and2 U13 ( .A1(VST0), .A2(n11), .Z(n15) );
  and2 U14 ( .A1(n16), .A2(FBI), .Z(n14) );
  and2 U15 ( .A1(VST1), .A2(n13), .Z(n16) );
  or2 U16 ( .A1(n17), .A2(n18), .Z(VLENESR_P) );
  and2 U17 ( .A1(VLENESR), .A2(OWL_N), .Z(n17) );
  or2 U47 ( .A1(n58), .A2(n59), .Z(RATR_P) );
  or2 U48 ( .A1(n201), .A2(n61), .Z(n59) );
  and2 U49 ( .A1(n222), .A2(n377), .Z(n61) );
  and2 U50 ( .A1(RATR), .A2(OWL_N), .Z(n58) );
  or2 U51 ( .A1(n63), .A2(n64), .Z(PY_P) );
  and2 U52 ( .A1(n65), .A2(n13), .Z(n64) );
  and2 U53 ( .A1(n11), .A2(PY), .Z(n63) );
  and2 U54 ( .A1(n13), .A2(n379), .Z(n11) );
  or2 U87 ( .A1(VST0), .A2(MMERR), .Z(n95) );
  and2 U90 ( .A1(n97), .A2(n98), .Z(OWL_F) );
  inv1 U91 ( .I(n99), .ZN(n98) );
  or2 U92 ( .A1(END), .A2(ICLR), .Z(n99) );
  and2 U95 ( .A1(VACC), .A2(n13), .Z(OVACC_P) );
  and2 U105 ( .A1(MARSSR), .A2(OWL_N), .Z(n101) );
  or2 U109 ( .A1(n376), .A2(n115), .Z(n114) );
  or2 U110 ( .A1(n379), .A2(n381), .Z(n115) );
  and2 U133 ( .A1(CAPSD), .A2(n13), .Z(DEL1_P) );
  inv1 U134 ( .I(ICLR), .ZN(n13) );
  or2 U135 ( .A1(n132), .A2(n133), .Z(COMPPAR_P) );
  and2 U136 ( .A1(n134), .A2(DEL1), .Z(n133) );
  and2 U137 ( .A1(n373), .A2(n377), .Z(n134) );
  and2 U139 ( .A1(n135), .A2(COMPPAR), .Z(n132) );
  inv1 U140 ( .I(n136), .ZN(n135) );
  or2 U141 ( .A1(n65), .A2(n219), .Z(n136) );
  and2 U143 ( .A1(FBI), .A2(DEL1), .Z(n65) );
  or2 U144 ( .A1(n137), .A2(n138), .Z(BULL6_P) );
  and2 U145 ( .A1(BULL6), .A2(n139), .Z(n138) );
  or2 U146 ( .A1(n140), .A2(n141), .Z(n139) );
  and2 U147 ( .A1(n142), .A2(OWL_N), .Z(n140) );
  or2 U149 ( .A1(n145), .A2(n146), .Z(n144) );
  and2 U151 ( .A1(n148), .A2(n149), .Z(n137) );
  and2 U152 ( .A1(n150), .A2(BULL4), .Z(n149) );
  and2 U153 ( .A1(OWL_N), .A2(n220), .Z(n150) );
  and2 U155 ( .A1(BULL5), .A2(n374), .Z(n148) );
  or2 U156 ( .A1(n152), .A2(n153), .Z(BULL5_P) );
  and2 U157 ( .A1(n383), .A2(BULL5), .Z(n153) );
  and2 U158 ( .A1(n154), .A2(OWL_N), .Z(n152) );
  or2 U159 ( .A1(n155), .A2(n156), .Z(n154) );
  and2 U160 ( .A1(BULL5), .A2(n157), .Z(n156) );
  and2 U161 ( .A1(n158), .A2(n374), .Z(n155) );
  and2 U162 ( .A1(BULL4), .A2(n146), .Z(n158) );
  inv1 U163 ( .I(BULL5), .ZN(n146) );
  and2 U164 ( .A1(OWL_N), .A2(n382), .Z(n383) );
  inv1 U172 ( .I(BULL3), .ZN(n145) );
  and2 U173 ( .A1(n164), .A2(OWL_N), .Z(BULL3_P) );
  or2 U174 ( .A1(n165), .A2(n166), .Z(n164) );
  inv1 U175 ( .I(n167), .ZN(n166) );
  or2 U176 ( .A1(n163), .A2(BULL3), .Z(n167) );
  and2 U177 ( .A1(BULL3), .A2(n163), .Z(n165) );
  or2 U179 ( .A1(n170), .A2(n147), .Z(n169) );
  or2 U180 ( .A1(n171), .A2(n172), .Z(BULL2_P) );
  and2 U181 ( .A1(n141), .A2(BULL2), .Z(n172) );
  and2 U182 ( .A1(n173), .A2(n174), .Z(n171) );
  and2 U183 ( .A1(BULL1), .A2(n147), .Z(n174) );
  inv1 U184 ( .I(BULL2), .ZN(n147) );
  and2 U185 ( .A1(BULL0), .A2(n375), .Z(n173) );
  or2 U186 ( .A1(n175), .A2(n176), .Z(BULL1_P) );
  and2 U187 ( .A1(n141), .A2(BULL1), .Z(n176) );
  and2 U188 ( .A1(OWL_N), .A2(n177), .Z(n141) );
  or2 U194 ( .A1(n179), .A2(n180), .Z(BULL0_P) );
  and2 U195 ( .A1(n375), .A2(n170), .Z(n180) );
  inv1 U196 ( .I(BULL0), .ZN(n170) );
  and2 U198 ( .A1(n181), .A2(BULL0), .Z(n179) );
  and2 U199 ( .A1(OWL_N), .A2(n378), .Z(n181) );
  and2 U236 ( .A1(n208), .A2(n373), .Z(n200) );
  and2 U237 ( .A1(n222), .A2(n202), .Z(n201) );
  inv1 U238 ( .I(n95), .ZN(n202) );
  buf0 U241 ( .I(VST0), .Z(SDO) );
  buf0 U242 ( .I(n383), .Z(BULL4_P) );
  or2 U243 ( .A1(n341), .A2(IBT1), .Z(n207) );
  or2 U244 ( .A1(n275), .A2(n274), .Z(n208) );
  and2 U247 ( .A1(n277), .A2(n275), .Z(n210) );
  and2 U248 ( .A1(n273), .A2(n277), .Z(n211) );
  or2 U251 ( .A1(n335), .A2(n294), .Z(n214) );
  or2 U253 ( .A1(n328), .A2(n373), .Z(n216) );
  inv1 U255 ( .I(n217), .ZN(n268) );
  inv1 U257 ( .I(n218), .ZN(n339) );
  inv1 U259 ( .I(BULL6), .ZN(n220) );
  and2 U261 ( .A1(OWL_N), .A2(END), .Z(n222) );
  or2 U263 ( .A1(IBT0), .A2(n226), .Z(n224) );
  and2 U264 ( .A1(n307), .A2(IBT2), .Z(n225) );
  inv1 U265 ( .I(IBT2), .ZN(n226) );
  or2 U266 ( .A1(n323), .A2(n227), .Z(n258) );
  or2 U267 ( .A1(n291), .A2(n381), .Z(n227) );
  or2 U269 ( .A1(n226), .A2(n315), .Z(n228) );
  or2 U273 ( .A1(n378), .A2(n219), .Z(n291) );
  inv1 U274 ( .I(n291), .ZN(n375) );
  inv1 U275 ( .I(BULL1), .ZN(n237) );
  or2 U277 ( .A1(n232), .A2(n170), .Z(n177) );
  and2 U278 ( .A1(BULL0), .A2(n375), .Z(n231) );
  and2 U279 ( .A1(n237), .A2(n231), .Z(n175) );
  and2 U282 ( .A1(BULL4), .A2(n157), .Z(n234) );
  inv1 U283 ( .I(n161), .ZN(n233) );
  inv1 U285 ( .I(n157), .ZN(n374) );
  inv1 U286 ( .I(BULL4), .ZN(n238) );
  or2 U287 ( .A1(n238), .A2(n147), .Z(n235) );
  or2 U288 ( .A1(n235), .A2(n144), .Z(n142) );
  inv1 U289 ( .I(FBI), .ZN(n379) );
  or2 U290 ( .A1(n219), .A2(n379), .Z(n275) );
  inv1 U291 ( .I(n275), .ZN(n373) );
  inv1 U292 ( .I(COMPPAR), .ZN(n377) );
  inv1 U293 ( .I(STAR0), .ZN(n334) );
  inv1 U294 ( .I(STAR1), .ZN(n351) );
  or2 U295 ( .A1(n334), .A2(n351), .Z(n353) );
  or2 U296 ( .A1(n353), .A2(STAR2), .Z(n381) );
  inv1 U297 ( .I(STAR3), .ZN(n376) );
  or2 U298 ( .A1(BULL2), .A2(BULL3), .Z(n236) );
  or2 U299 ( .A1(n236), .A2(BULL5), .Z(n242) );
  or2 U300 ( .A1(n237), .A2(BULL0), .Z(n240) );
  or2 U301 ( .A1(n238), .A2(n220), .Z(n239) );
  or2 U304 ( .A1(n292), .A2(n378), .Z(n243) );
  and2 U305 ( .A1(KBG_N), .A2(n243), .Z(n97) );
  or2 U306 ( .A1(n219), .A2(KBG_N), .Z(n244) );
  inv1 U307 ( .I(n244), .ZN(n18) );
  inv1 U309 ( .I(IBT0), .ZN(n341) );
  inv1 U313 ( .I(CAT4), .ZN(n246) );
  inv1 U315 ( .I(CAT2), .ZN(n247) );
  inv1 U320 ( .I(n250), .ZN(n253) );
  inv1 U321 ( .I(CAT1), .ZN(n251) );
  inv1 U324 ( .I(n281), .ZN(n264) );
  inv1 U328 ( .I(n327), .ZN(n323) );
  or2 U329 ( .A1(n323), .A2(n291), .Z(n324) );
  or2 U330 ( .A1(n379), .A2(STAR3), .Z(n257) );
  or2 U331 ( .A1(n258), .A2(n257), .Z(n259) );
  inv1 U332 ( .I(n259), .ZN(n262) );
  and2 U333 ( .A1(LSD), .A2(OWL_N), .Z(n260) );
  and2 U334 ( .A1(n114), .A2(n260), .Z(n261) );
  or2 U335 ( .A1(n262), .A2(n261), .Z(LSD_P) );
  inv1 U336 ( .I(n381), .ZN(n358) );
  or2 U338 ( .A1(n264), .A2(n263), .Z(n265) );
  and2 U340 ( .A1(IBT0), .A2(IBT2), .Z(n266) );
  and2 U341 ( .A1(WATCH), .A2(n266), .Z(n267) );
  or2 U348 ( .A1(n274), .A2(n275), .Z(n286) );
  and2 U349 ( .A1(ACCRPY), .A2(OWL_N), .Z(n276) );
  or2 U350 ( .A1(n200), .A2(n276), .Z(ACCRPY_P) );
  and2 U351 ( .A1(VERR_N), .A2(n378), .Z(n277) );
  or2 U352 ( .A1(n278), .A2(n219), .Z(n290) );
  and2 U353 ( .A1(VERR_N), .A2(n292), .Z(n288) );
  and2 U354 ( .A1(IBT1), .A2(WATCH), .Z(n279) );
  and2 U355 ( .A1(n226), .A2(n279), .Z(n280) );
  and2 U356 ( .A1(n281), .A2(n280), .Z(n283) );
  or2 U357 ( .A1(n282), .A2(n283), .Z(n285) );
  or2 U358 ( .A1(n381), .A2(n376), .Z(n284) );
  and2 U361 ( .A1(n288), .A2(n332), .Z(n289) );
  or2 U363 ( .A1(n292), .A2(n291), .Z(n293) );
  or2 U365 ( .A1(n298), .A2(n101), .Z(MARSSR_P) );
  inv1 U366 ( .I(n294), .ZN(n303) );
  or2 U367 ( .A1(n377), .A2(VST1), .Z(n295) );
  and2 U368 ( .A1(n222), .A2(n295), .Z(n296) );
  or2 U369 ( .A1(n296), .A2(n18), .Z(n297) );
  and2 U372 ( .A1(n303), .A2(n307), .Z(n300) );
  and2 U373 ( .A1(n341), .A2(n300), .Z(n302) );
  and2 U374 ( .A1(PLUTO0), .A2(OWL_N), .Z(n301) );
  or2 U375 ( .A1(n302), .A2(n301), .Z(PLUTO0_P) );
  and2 U376 ( .A1(IBT0), .A2(n303), .Z(n304) );
  and2 U377 ( .A1(n384), .A2(n304), .Z(n306) );
  and2 U378 ( .A1(PLUTO1), .A2(OWL_N), .Z(n305) );
  or2 U379 ( .A1(n306), .A2(n305), .Z(PLUTO1_P) );
  or2 U381 ( .A1(n308), .A2(IBT1), .Z(n309) );
  inv1 U382 ( .I(n309), .ZN(n311) );
  and2 U383 ( .A1(PLUTO2), .A2(OWL_N), .Z(n310) );
  or2 U384 ( .A1(n311), .A2(n310), .Z(PLUTO2_P) );
  or2 U385 ( .A1(n207), .A2(n229), .Z(n312) );
  inv1 U386 ( .I(n312), .ZN(n314) );
  and2 U387 ( .A1(PLUTO3), .A2(OWL_N), .Z(n313) );
  or2 U388 ( .A1(n314), .A2(n313), .Z(PLUTO3_P) );
  or2 U389 ( .A1(n316), .A2(IBT0), .Z(n317) );
  inv1 U390 ( .I(n317), .ZN(n319) );
  and2 U391 ( .A1(PLUTO4), .A2(OWL_N), .Z(n318) );
  or2 U392 ( .A1(n319), .A2(n318), .Z(PLUTO4_P) );
  and2 U393 ( .A1(IBT0), .A2(IBT1), .Z(n320) );
  and2 U394 ( .A1(n225), .A2(n320), .Z(n322) );
  and2 U395 ( .A1(PLUTO5), .A2(OWL_N), .Z(n321) );
  or2 U396 ( .A1(n322), .A2(n321), .Z(PLUTO5_P) );
  or2 U397 ( .A1(n323), .A2(n378), .Z(ORWD_F) );
  or2 U398 ( .A1(n200), .A2(n222), .Z(END_P) );
  inv1 U399 ( .I(n324), .ZN(n329) );
  inv1 U400 ( .I(ORWD_N), .ZN(n325) );
  and2 U401 ( .A1(n325), .A2(n375), .Z(n326) );
  or2 U403 ( .A1(n328), .A2(n373), .Z(n364) );
  and2 U405 ( .A1(n381), .A2(n373), .Z(n330) );
  or2 U408 ( .A1(n333), .A2(n219), .Z(KBG_F) );
  or2 U411 ( .A1(n335), .A2(n226), .Z(n336) );
  or2 U414 ( .A1(n338), .A2(n339), .Z(n347) );
  or2 U417 ( .A1(n219), .A2(FBI), .Z(n344) );
  or2 U418 ( .A1(n345), .A2(n344), .Z(n346) );
  or2 U419 ( .A1(n347), .A2(n346), .Z(n348) );
  and2 U421 ( .A1(STAR0), .A2(n368), .Z(n349) );
  or2 U422 ( .A1(n350), .A2(n349), .Z(STAR0_P) );
  and2 U423 ( .A1(n351), .A2(STAR0), .Z(n352) );
  inv1 U425 ( .I(n353), .ZN(n362) );
  or2 U426 ( .A1(n362), .A2(n219), .Z(n366) );
  inv1 U427 ( .I(n366), .ZN(n354) );
  or2 U433 ( .A1(n359), .A2(n360), .Z(STAR2_P) );
  and2 U434 ( .A1(n376), .A2(STAR2), .Z(n361) );
  and2 U435 ( .A1(n362), .A2(n361), .Z(n363) );
  and2 U436 ( .A1(n216), .A2(n363), .Z(n372) );
  or2 U437 ( .A1(n219), .A2(STAR2), .Z(n365) );
  and2 U438 ( .A1(n366), .A2(n365), .Z(n367) );
  inv1 U439 ( .I(n367), .ZN(n369) );
  or2 U440 ( .A1(n369), .A2(n368), .Z(n370) );
  and2f U239 ( .A1(IBT2), .A2(n337), .Z(n256) );
  or2 U240 ( .A1(CAT3), .A2(IBT1), .Z(n223) );
  and2 U245 ( .A1(n216), .A2(n352), .Z(n356) );
  or2 U246 ( .A1(n254), .A2(n215), .Z(n255) );
  and2f U249 ( .A1(n281), .A2(n303), .Z(n215) );
  or2 U250 ( .A1(n378), .A2(n294), .Z(n263) );
  inv1 U252 ( .I(n282), .ZN(n272) );
  and2 U254 ( .A1(IBT0), .A2(n251), .Z(n252) );
  or2 U256 ( .A1(CAT0), .A2(IBT0), .Z(n250) );
  inv1 U258 ( .I(n245), .ZN(n337) );
  and2 U260 ( .A1(n246), .A2(IBT1), .Z(n249) );
  inv1 U262 ( .I(n336), .ZN(n342) );
  and2 U268 ( .A1(n285), .A2(n284), .Z(n287) );
  or2 U270 ( .A1(n331), .A2(n330), .Z(FBI_P) );
  or2 U271 ( .A1(n356), .A2(n355), .Z(STAR1_P) );
  inv1 U272 ( .I(n230), .ZN(n384) );
  or2f U276 ( .A1(n372), .A2(n371), .Z(STAR3_P) );
  and2f U280 ( .A1(n329), .A2(n364), .Z(n331) );
  and2f U281 ( .A1(n334), .A2(n364), .Z(n350) );
  and2f U284 ( .A1(n358), .A2(n364), .Z(n359) );
  and2f U302 ( .A1(n337), .A2(n342), .Z(n338) );
  inv1f U303 ( .I(OWL_N), .ZN(n219) );
  or2f U308 ( .A1(n289), .A2(n290), .Z(VERR_F) );
  and2f U310 ( .A1(n268), .A2(n267), .Z(n271) );
  and2f U311 ( .A1(WATCH), .A2(n203), .Z(n269) );
  and2f U312 ( .A1(n203), .A2(n340), .Z(n254) );
  and2f U314 ( .A1(IBT2), .A2(n341), .Z(n203) );
  and2f U316 ( .A1(n343), .A2(n342), .Z(n345) );
  and2f U317 ( .A1(STAR1), .A2(n357), .Z(n355) );
  or2f U318 ( .A1(n241), .A2(n242), .Z(n292) );
  or2f U319 ( .A1(n240), .A2(n239), .Z(n241) );
  or2f U322 ( .A1(n214), .A2(n264), .Z(n218) );
  or2f U323 ( .A1(n209), .A2(n210), .Z(n278) );
  and2f U325 ( .A1(n272), .A2(n211), .Z(n209) );
  inv1f U326 ( .I(n293), .ZN(n298) );
  or2f U327 ( .A1(n297), .A2(n201), .Z(n299) );
  or2f U337 ( .A1(n217), .A2(n341), .Z(n245) );
  and2f U339 ( .A1(STAR3), .A2(n370), .Z(n371) );
  or2f U342 ( .A1(n234), .A2(n233), .Z(n382) );
  or2f U343 ( .A1(n163), .A2(n145), .Z(n157) );
  or2f U344 ( .A1(n232), .A2(n169), .Z(n163) );
  inv1f U345 ( .I(IBT1), .ZN(n315) );
  and2f U346 ( .A1(STAR2), .A2(n357), .Z(n360) );
  or2f U347 ( .A1(n354), .A2(n368), .Z(n357) );
  or2f U359 ( .A1(IBT2), .A2(n315), .Z(n294) );
  and2f U360 ( .A1(KBG_N), .A2(n332), .Z(n333) );
  or2f U362 ( .A1(n286), .A2(n287), .Z(n332) );
  or2f U364 ( .A1(n271), .A2(n270), .Z(n282) );
  or2f U370 ( .A1(n378), .A2(n237), .Z(n232) );
  or2f U371 ( .A1(n378), .A2(ORWD_N), .Z(n335) );
  or2f U380 ( .A1(BULL4), .A2(n157), .Z(n161) );
  inv1f U402 ( .I(WATCH), .ZN(n378) );
  inv1f U404 ( .I(n307), .ZN(n230) );
  or2f U406 ( .A1(n230), .A2(n226), .Z(n229) );
  or2f U407 ( .A1(n224), .A2(n230), .Z(n308) );
  or2f U409 ( .A1(n230), .A2(n228), .Z(n316) );
  or2f U410 ( .A1(n298), .A2(n299), .Z(n307) );
  and2f U412 ( .A1(n273), .A2(n272), .Z(n274) );
  and2f U413 ( .A1(n358), .A2(n265), .Z(n273) );
  or2f U415 ( .A1(n253), .A2(n252), .Z(n281) );
  and2f U416 ( .A1(n327), .A2(n326), .Z(n328) );
  or2f U420 ( .A1(n256), .A2(n255), .Z(n327) );
  and2f U424 ( .A1(n212), .A2(n223), .Z(n217) );
  and2f U428 ( .A1(n247), .A2(n315), .Z(n248) );
  or2f U429 ( .A1(CAT5), .A2(n315), .Z(n212) );
  and2f U430 ( .A1(n341), .A2(n340), .Z(n343) );
  or2f U431 ( .A1(n249), .A2(n248), .Z(n340) );
  and2f U432 ( .A1(n340), .A2(n269), .Z(n270) );
  inv1f U441 ( .I(n348), .ZN(n368) );
endmodule


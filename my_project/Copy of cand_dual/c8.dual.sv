
module c8 ( c0, b0, a0, z, y, x, w, v, u, s, r, q, p, o, n, m, l, k, j, i, h, 
        g, f, e, d, c, b, a, u0, t0, s0, r0, q0, p0, o0, n0, m0, l0, k0, j0, 
        i0, h0, g0, f0, e0, d0 );
  input c0, b0, a0, z, y, x, w, v, u, s, r, q, p, o, n, m, l, k, j, i, h, g, f,
         e, d, c, b, a;
  output u0, t0, s0, r0, q0, p0, o0, n0, m0, l0, k0, j0, i0, h0, g0, f0, e0,
         d0;
  wire   n24, n25, n26, n27, n28, n29, n30, n31, n32, n33, n34, n35, n36, n37,
         n38, n39, n40, n41, n42, n43, n44, n45, n46, n47, n48, n49, n50, n51,
         n52, n53, n54, n55, n56, n57, n58, n59, n60, n61, n62, n63, n64, n65,
         n66, n67, n68, n69, n70, n71, n72, n73, n74, n75, n76, n77, n78, n79,
         n80, n81, n82, n83, n84, n85, n86, n87, n88, n89, n90, n91, n92, n93,
         n94, n95, n96, n97, n98, n99, n100, n101, n102, n103, n104, n105,
         n106, n107, n108, n109, n110, n111, n112, n113, n114, n115, n116,
         n117, n118, n119, n120, n121, n122, n123, n124, n125, n126, n127,
         n128, n129, n130, n131, n132, n133, n134, n135, n136, n137, n138,
         n139, n140, n141, n142, n143, n144, n145, n146, n147, n148, n150,
         n151, n152;

  and2f U5 ( .A1(n29), .A2(n30), .Z(n28) );
  and2f U7 ( .A1(n33), .A2(n34), .Z(n31) );
  and2f U12 ( .A1(n42), .A2(n43), .Z(t0) );
  or2f U17 ( .A1(n48), .A2(n49), .Z(n42) );
  and2f U18 ( .A1(n50), .A2(n51), .Z(n48) );
  or2f U20 ( .A1(a0), .A2(n53), .Z(n52) );
  or2f U21 ( .A1(n54), .A2(b0), .Z(n50) );
  or2f U28 ( .A1(n61), .A2(n54), .Z(n60) );
  and2f U29 ( .A1(n62), .A2(n41), .Z(n54) );
  inv1f U30 ( .I(n53), .ZN(n62) );
  or2f U32 ( .A1(n152), .A2(n83), .Z(n53) );
  and2f U34 ( .A1(n65), .A2(n66), .Z(r0) );
  or2f U39 ( .A1(n70), .A2(n49), .Z(n65) );
  and2f U40 ( .A1(n71), .A2(n72), .Z(n70) );
  or2f U42 ( .A1(y), .A2(n63), .Z(n73) );
  or2f U43 ( .A1(n74), .A2(z), .Z(n71) );
  and2f U51 ( .A1(n82), .A2(n33), .Z(n74) );
  or2f U55 ( .A1(x), .A2(w), .Z(n84) );
  and2f U73 ( .A1(n102), .A2(n36), .Z(n94) );
  or2f U76 ( .A1(r), .A2(n103), .Z(n83) );
  or2f U77 ( .A1(v), .A2(u), .Z(n103) );
  buf0 U143 ( .I(c0), .Z(l0) );
  inv1 U144 ( .I(y), .ZN(n33) );
  inv1 U145 ( .I(z), .ZN(n34) );
  or2 U146 ( .A1(n49), .A2(n113), .Z(n109) );
  or2 U147 ( .A1(v), .A2(n114), .Z(n113) );
  and2 U148 ( .A1(n40), .A2(n115), .Z(n114) );
  or2 U149 ( .A1(n101), .A2(n94), .Z(n100) );
  or2 U150 ( .A1(n39), .A2(n52), .Z(n51) );
  and2 U151 ( .A1(n55), .A2(n56), .Z(s0) );
  or2 U152 ( .A1(n49), .A2(n60), .Z(n55) );
  or2 U153 ( .A1(n25), .A2(n26), .Z(n24) );
  and2 U154 ( .A1(n27), .A2(n28), .Z(n25) );
  or2 U155 ( .A1(u), .A2(v), .Z(n150) );
  or2f U156 ( .A1(n150), .A2(n151), .Z(n63) );
  or2f U157 ( .A1(n84), .A2(r), .Z(n151) );
  inv1f U158 ( .I(n63), .ZN(n82) );
  or2 U159 ( .A1(w), .A2(n83), .Z(n93) );
  or2f U160 ( .A1(n90), .A2(n49), .Z(n85) );
  and2f U161 ( .A1(n91), .A2(n92), .Z(n90) );
  or2f U162 ( .A1(n64), .A2(n84), .Z(n152) );
  or2f U163 ( .A1(z), .A2(y), .Z(n64) );
  inv1 U164 ( .I(n83), .ZN(n102) );
  and2 U165 ( .A1(a0), .A2(n53), .Z(n61) );
  inv1 U166 ( .I(v), .ZN(n35) );
  inv1 U167 ( .I(w), .ZN(n36) );
  inv1 U168 ( .I(x), .ZN(n32) );
  inv1 U169 ( .I(a0), .ZN(n41) );
  inv1 U170 ( .I(b0), .ZN(n39) );
  inv1 U171 ( .I(s), .ZN(n47) );
  inv1 U172 ( .I(u), .ZN(n115) );
  inv1 U173 ( .I(i), .ZN(n148) );
  inv1 U174 ( .I(j), .ZN(n145) );
  inv1 U175 ( .I(k), .ZN(n142) );
  inv1 U176 ( .I(l), .ZN(n139) );
  inv1 U177 ( .I(m), .ZN(n136) );
  inv1 U178 ( .I(n), .ZN(n133) );
  inv1 U179 ( .I(o), .ZN(n130) );
  inv1 U180 ( .I(c0), .ZN(n127) );
  inv1 U181 ( .I(p), .ZN(n126) );
  or2 U182 ( .A1(n122), .A2(n123), .Z(n121) );
  and2 U183 ( .A1(a), .A2(s), .Z(n122) );
  and2 U184 ( .A1(i), .A2(n47), .Z(n123) );
  and2 U185 ( .A1(n119), .A2(n120), .Z(n118) );
  or2 U186 ( .A1(u), .A2(n40), .Z(n119) );
  or2 U187 ( .A1(r), .A2(n115), .Z(n120) );
  or2 U188 ( .A1(n111), .A2(n112), .Z(n110) );
  or2 U189 ( .A1(u), .A2(r), .Z(n111) );
  or2 U190 ( .A1(n49), .A2(n35), .Z(n112) );
  and2 U191 ( .A1(j), .A2(n47), .Z(n106) );
  or2 U192 ( .A1(q), .A2(n108), .Z(n107) );
  and2 U193 ( .A1(b), .A2(s), .Z(n108) );
  and2 U194 ( .A1(w), .A2(n83), .Z(n101) );
  and2 U195 ( .A1(k), .A2(n47), .Z(n97) );
  or2 U196 ( .A1(q), .A2(n99), .Z(n98) );
  and2 U197 ( .A1(c), .A2(s), .Z(n99) );
  and2 U198 ( .A1(f), .A2(s), .Z(n69) );
  or2 U199 ( .A1(n34), .A2(n73), .Z(n72) );
  and2 U200 ( .A1(n), .A2(n47), .Z(n67) );
  and2 U201 ( .A1(g), .A2(s), .Z(n59) );
  and2 U202 ( .A1(o), .A2(n47), .Z(n57) );
  and2 U203 ( .A1(s), .A2(h), .Z(n46) );
  inv1 U204 ( .I(q), .ZN(n49) );
  and2 U205 ( .A1(p), .A2(n47), .Z(n44) );
  and2 U206 ( .A1(n37), .A2(n38), .Z(n27) );
  and2 U207 ( .A1(u), .A2(n41), .Z(n37) );
  inv1 U208 ( .I(r), .ZN(n40) );
  and2 U209 ( .A1(n31), .A2(n32), .Z(n30) );
  and2 U210 ( .A1(n35), .A2(n36), .Z(n29) );
  and2 U211 ( .A1(n39), .A2(n40), .Z(n38) );
  and2 U212 ( .A1(d), .A2(s), .Z(n89) );
  or2 U213 ( .A1(n32), .A2(n93), .Z(n92) );
  or2 U214 ( .A1(n94), .A2(x), .Z(n91) );
  and2 U215 ( .A1(l), .A2(n47), .Z(n87) );
  and2 U216 ( .A1(e), .A2(s), .Z(n79) );
  or2 U217 ( .A1(n81), .A2(n74), .Z(n80) );
  and2 U218 ( .A1(y), .A2(n63), .Z(n81) );
  and2 U219 ( .A1(m), .A2(n47), .Z(n77) );
  and2 U220 ( .A1(c0), .A2(n148), .Z(n147) );
  and2 U221 ( .A1(n127), .A2(n115), .Z(n146) );
  and2 U222 ( .A1(c0), .A2(n145), .Z(n144) );
  and2 U223 ( .A1(n127), .A2(n35), .Z(n143) );
  and2 U224 ( .A1(c0), .A2(n142), .Z(n141) );
  and2 U225 ( .A1(n127), .A2(n36), .Z(n140) );
  and2 U226 ( .A1(c0), .A2(n139), .Z(n138) );
  and2 U227 ( .A1(n127), .A2(n32), .Z(n137) );
  and2 U228 ( .A1(c0), .A2(n136), .Z(n135) );
  and2 U229 ( .A1(n127), .A2(n33), .Z(n134) );
  and2 U230 ( .A1(c0), .A2(n133), .Z(n132) );
  and2 U231 ( .A1(n127), .A2(n34), .Z(n131) );
  and2 U232 ( .A1(c0), .A2(n130), .Z(n129) );
  and2 U233 ( .A1(n41), .A2(n127), .Z(n128) );
  and2 U234 ( .A1(c0), .A2(n126), .Z(n125) );
  and2 U235 ( .A1(n39), .A2(n127), .Z(n124) );
  and2 U236 ( .A1(n118), .A2(q), .Z(n117) );
  and2 U237 ( .A1(n121), .A2(n49), .Z(n116) );
  or2 U238 ( .A1(n106), .A2(n107), .Z(n105) );
  and2 U239 ( .A1(n109), .A2(n110), .Z(n104) );
  or2 U240 ( .A1(n97), .A2(n98), .Z(n96) );
  or2 U241 ( .A1(n49), .A2(n100), .Z(n95) );
  and2 U242 ( .A1(n85), .A2(n86), .Z(p0) );
  or2 U243 ( .A1(n87), .A2(n88), .Z(n86) );
  or2 U244 ( .A1(q), .A2(n89), .Z(n88) );
  and2 U245 ( .A1(n75), .A2(n76), .Z(q0) );
  or2 U246 ( .A1(n77), .A2(n78), .Z(n76) );
  or2 U247 ( .A1(n49), .A2(n80), .Z(n75) );
  or2 U248 ( .A1(q), .A2(n79), .Z(n78) );
  or2 U249 ( .A1(n67), .A2(n68), .Z(n66) );
  or2 U250 ( .A1(q), .A2(n69), .Z(n68) );
  or2 U251 ( .A1(n57), .A2(n58), .Z(n56) );
  or2 U252 ( .A1(q), .A2(n59), .Z(n58) );
  or2 U253 ( .A1(n44), .A2(n45), .Z(n43) );
  or2 U254 ( .A1(q), .A2(n46), .Z(n45) );
  and2 U255 ( .A1(r), .A2(c0), .Z(n26) );
  or2 U256 ( .A1(n146), .A2(n147), .Z(d0) );
  or2 U257 ( .A1(n143), .A2(n144), .Z(e0) );
  or2 U258 ( .A1(n140), .A2(n141), .Z(f0) );
  or2 U259 ( .A1(n137), .A2(n138), .Z(g0) );
  or2 U260 ( .A1(n134), .A2(n135), .Z(h0) );
  or2 U261 ( .A1(n131), .A2(n132), .Z(i0) );
  or2 U262 ( .A1(n128), .A2(n129), .Z(j0) );
  or2 U263 ( .A1(n124), .A2(n125), .Z(k0) );
  or2 U264 ( .A1(n116), .A2(n117), .Z(m0) );
  and2 U265 ( .A1(n104), .A2(n105), .Z(n0) );
  and2 U266 ( .A1(n95), .A2(n96), .Z(o0) );
  and2 U267 ( .A1(q), .A2(n24), .Z(u0) );
endmodule


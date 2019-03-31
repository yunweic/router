
module cordic ( ey2, ey1, ey0, ex2, ex1, ex0, z2, z1, z0, y3, y2, y1, y0, x3, 
        x2, x1, x0, v, a5, a2, a3, a4, a6, dn, d );
  input ey2, ey1, ey0, ex2, ex1, ex0, z2, z1, z0, y3, y2, y1, y0, x3, x2, x1,
         x0, v, a5, a2, a3, a4, a6;
  output dn, d;
  wire   n25, n26, n27, n28, n29, n30, n31, n32, n33, n34, n35, n36, n37, n38,
         n39, n40, n41, n42, n43, n44, n45, n46, n47, n48, n49, n50, n51, n52,
         n53, n54, n55, n56, n57, n60, n61, n62, n63, n64, n65, n66, n67, n68,
         n69, n70, n71, n73, n74, n75, n76, n77, n79, n80, n81, n82, n83, n84,
         n85, n86, n87, n88, n89, n90, n91, n93, n94, n95, n96, n97, n98, n99,
         n100, n101, n102, n103, n104, n105, n106, n107, n108, n109, n110,
         n111, n112, n113, n114, n115, n116, n117, n118, n119, n120;

  and2f U3 ( .A1(n28), .A2(n29), .Z(n25) );
  and2f U8 ( .A1(n35), .A2(n36), .Z(n30) );
  or2f U40 ( .A1(n68), .A2(n69), .Z(n62) );
  or2f U54 ( .A1(n77), .A2(n116), .Z(n37) );
  or2f U56 ( .A1(n81), .A2(n82), .Z(n80) );
  inv1f U57 ( .I(n83), .ZN(n82) );
  or2f U58 ( .A1(n85), .A2(n84), .Z(n83) );
  and2f U59 ( .A1(n85), .A2(n84), .Z(n81) );
  and2f U60 ( .A1(n86), .A2(n87), .Z(n84) );
  or2f U61 ( .A1(n88), .A2(x1), .Z(n87) );
  or2f U63 ( .A1(n89), .A2(x0), .Z(n86) );
  or2f U65 ( .A1(n90), .A2(n91), .Z(n85) );
  and2f U66 ( .A1(x2), .A2(n117), .Z(n91) );
  inv1f U67 ( .I(n93), .ZN(n90) );
  or2f U68 ( .A1(n117), .A2(x2), .Z(n93) );
  or2f U70 ( .A1(n94), .A2(n95), .Z(n79) );
  inv1f U71 ( .I(n96), .ZN(n95) );
  or2f U72 ( .A1(n97), .A2(n98), .Z(n96) );
  and2f U73 ( .A1(n97), .A2(n98), .Z(n94) );
  and2f U74 ( .A1(n99), .A2(n100), .Z(n97) );
  inv1f U76 ( .I(y0), .ZN(n101) );
  or2f U79 ( .A1(n103), .A2(n104), .Z(n98) );
  and2f U80 ( .A1(y2), .A2(n105), .Z(n104) );
  inv1f U81 ( .I(n106), .ZN(n103) );
  or2f U82 ( .A1(n105), .A2(y2), .Z(n106) );
  inv1f U83 ( .I(y3), .ZN(n105) );
  or2f U84 ( .A1(n107), .A2(n108), .Z(n77) );
  and2f U89 ( .A1(z1), .A2(n111), .Z(n112) );
  inv1 U91 ( .I(x1), .ZN(n89) );
  inv1 U92 ( .I(x0), .ZN(n88) );
  or2 U93 ( .A1(n102), .A2(y0), .Z(n99) );
  or2 U94 ( .A1(n101), .A2(y1), .Z(n100) );
  inv1 U95 ( .I(y1), .ZN(n102) );
  or2 U96 ( .A1(n77), .A2(n73), .Z(n120) );
  or2 U97 ( .A1(n25), .A2(n26), .Z(dn) );
  inv1 U98 ( .I(n27), .ZN(n26) );
  inv1 U99 ( .I(v), .ZN(n29) );
  and2 U100 ( .A1(n54), .A2(n27), .Z(d) );
  and2f U101 ( .A1(n113), .A2(n114), .Z(n54) );
  or2f U102 ( .A1(n79), .A2(n80), .Z(n116) );
  or2f U103 ( .A1(n62), .A2(n115), .Z(n113) );
  or2 U104 ( .A1(v), .A2(n34), .Z(n114) );
  or2 U105 ( .A1(n63), .A2(v), .Z(n115) );
  inv1f U106 ( .I(x3), .ZN(n117) );
  or2f U107 ( .A1(n116), .A2(n120), .Z(n118) );
  and2f U108 ( .A1(n118), .A2(n119), .Z(n68) );
  or2 U109 ( .A1(n73), .A2(n33), .Z(n119) );
  inv1 U110 ( .I(z0), .ZN(n111) );
  inv1 U111 ( .I(ex0), .ZN(n44) );
  inv1 U112 ( .I(ex1), .ZN(n45) );
  inv1 U113 ( .I(n109), .ZN(n108) );
  inv1 U114 ( .I(ex2), .ZN(n46) );
  and2 U115 ( .A1(ex1), .A2(n44), .Z(n73) );
  and2 U116 ( .A1(ex2), .A2(n45), .Z(n71) );
  or2 U117 ( .A1(n74), .A2(n75), .Z(n33) );
  or2 U118 ( .A1(a4), .A2(a2), .Z(n74) );
  inv1 U119 ( .I(n76), .ZN(n75) );
  and2 U120 ( .A1(a3), .A2(a6), .Z(n76) );
  inv1 U121 ( .I(n37), .ZN(n36) );
  and2 U122 ( .A1(n38), .A2(n39), .Z(n35) );
  or2 U123 ( .A1(n47), .A2(n48), .Z(n38) );
  or2 U124 ( .A1(n40), .A2(n41), .Z(n39) );
  and2 U125 ( .A1(n49), .A2(ey2), .Z(n48) );
  or2 U126 ( .A1(a3), .A2(a2), .Z(n56) );
  or2 U127 ( .A1(n56), .A2(n60), .Z(n34) );
  inv1 U128 ( .I(n61), .ZN(n60) );
  and2 U129 ( .A1(a6), .A2(a4), .Z(n61) );
  or2 U130 ( .A1(n110), .A2(n111), .Z(n109) );
  or2 U131 ( .A1(z1), .A2(z2), .Z(n110) );
  and2 U132 ( .A1(n112), .A2(z2), .Z(n107) );
  inv1 U133 ( .I(ey2), .ZN(n53) );
  and2 U134 ( .A1(ey1), .A2(ey0), .Z(n49) );
  and2 U135 ( .A1(n43), .A2(n44), .Z(n40) );
  and2 U136 ( .A1(n45), .A2(n46), .Z(n43) );
  and2 U137 ( .A1(n42), .A2(ex2), .Z(n41) );
  and2 U138 ( .A1(ex1), .A2(ex0), .Z(n42) );
  and2 U139 ( .A1(n50), .A2(n51), .Z(n47) );
  and2 U140 ( .A1(n52), .A2(n53), .Z(n50) );
  inv1 U141 ( .I(ey1), .ZN(n52) );
  inv1 U142 ( .I(ey0), .ZN(n51) );
  and2 U143 ( .A1(ey0), .A2(n53), .Z(n67) );
  or2 U144 ( .A1(n70), .A2(n71), .Z(n69) );
  and2 U145 ( .A1(ex0), .A2(n46), .Z(n70) );
  or2 U146 ( .A1(n64), .A2(n65), .Z(n63) );
  and2 U147 ( .A1(ey2), .A2(n52), .Z(n64) );
  or2 U148 ( .A1(n66), .A2(n67), .Z(n65) );
  and2 U149 ( .A1(ey1), .A2(n51), .Z(n66) );
  or2 U150 ( .A1(n30), .A2(n31), .Z(n28) );
  inv1 U151 ( .I(n32), .ZN(n31) );
  and2 U152 ( .A1(n33), .A2(n34), .Z(n32) );
  or2 U153 ( .A1(n55), .A2(n56), .Z(n27) );
  or2 U154 ( .A1(a4), .A2(n57), .Z(n55) );
  or2 U155 ( .A1(a6), .A2(a5), .Z(n57) );
endmodule


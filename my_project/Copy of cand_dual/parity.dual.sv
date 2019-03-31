
module PARITYFDS ( p, o, n, m, l, k, j, i, h, g, f, e, d, c, b, a, q );
  input p, o, n, m, l, k, j, i, h, g, f, e, d, c, b, a;
  output q;
  wire   n31, n32, n33, n34, n35, n36, n37, n38, n39, n40, n41, n42, n43, n44,
         n45, n46, n47, n48, n49, n50, n51, n52, n53, n54, n55, n56, n57, n58,
         n59, n60, n61, n62, n63, n64, n65, n66, n67, n68, n69, n70, n71, n72,
         n73, n74, n75, n76, n77, n78, n79, n80, n81, n82, n83, n84, n85, n86,
         n87, n88, n89, n90, n91, n92, n93, n94, n95, n96, n97, n98, n99, n100,
         n101, n102, n103, n104;

  and2f U5 ( .A1(n36), .A2(n37), .Z(n34) );
  or2f U6 ( .A1(n38), .A2(n39), .Z(n37) );
  or2f U8 ( .A1(n40), .A2(n41), .Z(n36) );
  inv1f U12 ( .I(n46), .ZN(n45) );
  and2f U15 ( .A1(n48), .A2(n49), .Z(n44) );
  and2f U20 ( .A1(n52), .A2(n53), .Z(n46) );
  inv1f U29 ( .I(n58), .ZN(n61) );
  and2f U30 ( .A1(n62), .A2(n63), .Z(n58) );
  and2f U35 ( .A1(n66), .A2(n67), .Z(n60) );
  or2f U36 ( .A1(n68), .A2(p), .Z(n67) );
  inv1f U39 ( .I(p), .ZN(n69) );
  inv1f U40 ( .I(n70), .ZN(n35) );
  and2f U41 ( .A1(n71), .A2(n72), .Z(n70) );
  or2f U42 ( .A1(n73), .A2(n74), .Z(n72) );
  or2f U44 ( .A1(n75), .A2(n76), .Z(n71) );
  inv1 U76 ( .I(d), .ZN(n90) );
  or2f U77 ( .A1(n81), .A2(n82), .Z(n77) );
  and2f U78 ( .A1(n87), .A2(n88), .Z(n81) );
  or2f U79 ( .A1(n95), .A2(n96), .Z(n91) );
  and2f U80 ( .A1(n101), .A2(n102), .Z(n95) );
  inv1f U81 ( .I(n73), .ZN(n76) );
  and2f U82 ( .A1(n77), .A2(n78), .Z(n73) );
  inv1f U83 ( .I(n75), .ZN(n74) );
  and2f U84 ( .A1(n91), .A2(n92), .Z(n75) );
  or2 U85 ( .A1(n69), .A2(o), .Z(n66) );
  or2 U86 ( .A1(n65), .A2(m), .Z(n62) );
  or2 U87 ( .A1(n64), .A2(n), .Z(n63) );
  inv1 U88 ( .I(n), .ZN(n65) );
  or2 U89 ( .A1(n51), .A2(i), .Z(n48) );
  or2 U90 ( .A1(n50), .A2(j), .Z(n49) );
  inv1 U91 ( .I(j), .ZN(n51) );
  or2 U92 ( .A1(n55), .A2(k), .Z(n52) );
  or2 U93 ( .A1(n54), .A2(l), .Z(n53) );
  inv1 U94 ( .I(l), .ZN(n55) );
  or2 U95 ( .A1(n104), .A2(g), .Z(n101) );
  or2 U96 ( .A1(n103), .A2(h), .Z(n102) );
  and2 U97 ( .A1(n97), .A2(n98), .Z(n93) );
  or2 U98 ( .A1(n100), .A2(e), .Z(n97) );
  or2 U99 ( .A1(n99), .A2(f), .Z(n98) );
  and2 U100 ( .A1(n83), .A2(n84), .Z(n79) );
  or2 U101 ( .A1(n89), .A2(d), .Z(n88) );
  inv1 U102 ( .I(c), .ZN(n89) );
  and2 U103 ( .A1(n56), .A2(n57), .Z(n40) );
  or2 U104 ( .A1(n58), .A2(n59), .Z(n57) );
  and2 U105 ( .A1(n42), .A2(n43), .Z(n38) );
  inv1 U106 ( .I(n44), .ZN(n47) );
  or2 U107 ( .A1(n93), .A2(n94), .Z(n92) );
  inv1 U108 ( .I(n95), .ZN(n94) );
  or2 U109 ( .A1(n79), .A2(n80), .Z(n78) );
  inv1 U110 ( .I(n79), .ZN(n82) );
  or2 U111 ( .A1(n34), .A2(n35), .Z(n33) );
  inv1 U112 ( .I(n40), .ZN(n39) );
  inv1 U113 ( .I(n38), .ZN(n41) );
  inv1 U114 ( .I(n81), .ZN(n80) );
  inv1 U115 ( .I(f), .ZN(n100) );
  inv1 U116 ( .I(h), .ZN(n104) );
  inv1 U117 ( .I(n60), .ZN(n59) );
  inv1 U118 ( .I(a), .ZN(n85) );
  inv1 U119 ( .I(e), .ZN(n99) );
  inv1 U120 ( .I(g), .ZN(n103) );
  inv1 U121 ( .I(i), .ZN(n50) );
  inv1 U122 ( .I(k), .ZN(n54) );
  inv1 U123 ( .I(m), .ZN(n64) );
  inv1 U124 ( .I(o), .ZN(n68) );
  or2 U125 ( .A1(n86), .A2(a), .Z(n83) );
  or2 U126 ( .A1(n85), .A2(b), .Z(n84) );
  inv1 U127 ( .I(b), .ZN(n86) );
  or2 U128 ( .A1(n90), .A2(c), .Z(n87) );
  inv1 U129 ( .I(n93), .ZN(n96) );
  or2 U130 ( .A1(n46), .A2(n47), .Z(n42) );
  or2 U131 ( .A1(n44), .A2(n45), .Z(n43) );
  or2 U132 ( .A1(n60), .A2(n61), .Z(n56) );
  and2 U133 ( .A1(n35), .A2(n34), .Z(n31) );
  inv1 U134 ( .I(n33), .ZN(n32) );
  or2 U135 ( .A1(n31), .A2(n32), .Z(q) );
endmodule


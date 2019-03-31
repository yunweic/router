
module CM150 ( u, t, s, r, q, p, o, n, m, l, k, j, i, h, g, f, e, d, c, b, a, 
        v );
  input u, t, s, r, q, p, o, n, m, l, k, j, i, h, g, f, e, d, c, b, a;
  output v;
  wire   n10, n11, n12, n13, n14, n15, n16, n17, n18, n19, n20, n21, n22, n23,
         n24, n25, n27, n28, n29, n30, n31, n34, n36, n37, n38, n39, n40, n41,
         n42, n43, n44, n45, n46, n49, n50, n51, n52, n55, n56, n57, n58, n59,
         n60, n61, n62, n63, n64, n65, n66, n67, n68, n69, n70, n71, n72, n73,
         n74, n75, n76, n77, n78, n79;

  or2f U1 ( .A1(n75), .A2(u), .Z(v) );
  or2f U5 ( .A1(n12), .A2(n13), .Z(n11) );
  or2f U6 ( .A1(s), .A2(n14), .Z(n13) );
  and2f U7 ( .A1(n15), .A2(r), .Z(n14) );
  or2f U8 ( .A1(n16), .A2(n17), .Z(n15) );
  or2f U12 ( .A1(n21), .A2(n22), .Z(n19) );
  and2f U15 ( .A1(n23), .A2(n24), .Z(n10) );
  and2f U19 ( .A1(n29), .A2(n20), .Z(n28) );
  or2f U20 ( .A1(n30), .A2(n31), .Z(n29) );
  and2f U25 ( .A1(h), .A2(q), .Z(n34) );
  or2f U28 ( .A1(n37), .A2(n38), .Z(n36) );
  or2f U29 ( .A1(s), .A2(n39), .Z(n38) );
  and2f U30 ( .A1(n40), .A2(r), .Z(n39) );
  or2f U31 ( .A1(n41), .A2(n42), .Z(n40) );
  and2f U41 ( .A1(n50), .A2(n20), .Z(n49) );
  or2f U43 ( .A1(n51), .A2(n52), .Z(n50) );
  and2f U48 ( .A1(q), .A2(p), .Z(n55) );
  inv1f U50 ( .I(q), .ZN(n18) );
  inv1 U52 ( .I(n68), .ZN(n16) );
  or2f U53 ( .A1(n69), .A2(q), .Z(n68) );
  inv1f U54 ( .I(m), .ZN(n77) );
  inv1 U55 ( .I(e), .ZN(n79) );
  inv1 U56 ( .I(c), .ZN(n69) );
  inv1 U57 ( .I(n46), .ZN(n71) );
  inv1 U58 ( .I(n11), .ZN(n58) );
  or2f U59 ( .A1(n57), .A2(n58), .Z(n56) );
  inv1f U60 ( .I(n10), .ZN(n57) );
  inv1 U61 ( .I(n78), .ZN(n30) );
  inv1 U62 ( .I(n76), .ZN(n51) );
  or2 U63 ( .A1(n77), .A2(q), .Z(n76) );
  and2 U64 ( .A1(d), .A2(q), .Z(n17) );
  and2 U65 ( .A1(f), .A2(q), .Z(n31) );
  and2 U66 ( .A1(l), .A2(q), .Z(n42) );
  and2 U67 ( .A1(n), .A2(q), .Z(n52) );
  inv1 U68 ( .I(q), .ZN(n64) );
  or2f U69 ( .A1(n49), .A2(n59), .Z(n46) );
  or2f U70 ( .A1(n63), .A2(n62), .Z(n60) );
  and2f U71 ( .A1(n60), .A2(n61), .Z(n59) );
  or2 U72 ( .A1(n25), .A2(r), .Z(n61) );
  or2f U73 ( .A1(n55), .A2(n25), .Z(n62) );
  and2f U74 ( .A1(o), .A2(n64), .Z(n63) );
  and2f U75 ( .A1(n64), .A2(n67), .Z(n65) );
  or2f U76 ( .A1(n65), .A2(n66), .Z(n27) );
  and2f U77 ( .A1(n34), .A2(r), .Z(n66) );
  and2f U78 ( .A1(g), .A2(r), .Z(n67) );
  or2f U79 ( .A1(n24), .A2(n71), .Z(n70) );
  or2f U80 ( .A1(n72), .A2(n28), .Z(n23) );
  or2f U81 ( .A1(n27), .A2(n25), .Z(n72) );
  or2f U82 ( .A1(n70), .A2(n74), .Z(n73) );
  inv1f U83 ( .I(n36), .ZN(n74) );
  and2f U84 ( .A1(n73), .A2(n56), .Z(n75) );
  or2f U85 ( .A1(n79), .A2(q), .Z(n78) );
  and2 U86 ( .A1(a), .A2(n18), .Z(n21) );
  and2 U87 ( .A1(i), .A2(n18), .Z(n44) );
  and2 U88 ( .A1(k), .A2(n18), .Z(n41) );
  inv1 U89 ( .I(s), .ZN(n25) );
  and2 U90 ( .A1(j), .A2(q), .Z(n45) );
  and2 U91 ( .A1(b), .A2(q), .Z(n22) );
  inv1 U92 ( .I(r), .ZN(n20) );
  inv1 U93 ( .I(t), .ZN(n24) );
  and2 U94 ( .A1(n43), .A2(n20), .Z(n37) );
  or2 U95 ( .A1(n44), .A2(n45), .Z(n43) );
  and2 U96 ( .A1(n19), .A2(n20), .Z(n12) );
endmodule



module s27 ( clock, G0, G1, G2, G3, G17 );
  input clock, G0, G1, G2, G3;
  output G17;
  wire   G6, G7, n11, n16, n21, n4, n5, n6, n7, n8, n9, n10, n12;

  dffx1 G7_reg ( .D(n21), .CP(clock), .Q(G7) );
  dffx1 G6_reg ( .D(n16), .CP(clock), .Q(G6) );
  dffx1 G5_reg ( .D(n11), .CP(clock), .QN(n7) );
  and2 U3 ( .A1(n4), .A2(n5), .Z(n21) );
  inv1 U4 ( .I(G2), .ZN(n5) );
  and2 U5 ( .A1(G0), .A2(G17), .Z(n11) );
  inv1 U6 ( .I(n16), .ZN(G17) );
  and2 U7 ( .A1(n6), .A2(n7), .Z(n16) );
  or2 U8 ( .A1(n8), .A2(n9), .Z(n6) );
  and2 U9 ( .A1(n10), .A2(G3), .Z(n9) );
  inv1 U10 ( .I(n4), .ZN(n10) );
  or2 U11 ( .A1(G1), .A2(G7), .Z(n4) );
  and2 U12 ( .A1(G6), .A2(n12), .Z(n8) );
  inv1 U13 ( .I(G0), .ZN(n12) );
endmodule



module s27 ( clock, G0, G1, G2, G3, G17 );
  input clock, G0, G1, G2, G3;
  output G17;
  wire   n10, G6, G7, G5, n11, n16, n21, n1, n2, n3, n4, n5, n6, n7, n8;

  inv1f U6 ( .I(n16), .ZN(n10) );
  and2f U7 ( .A1(n3), .A2(n4), .Z(n16) );
  or2f U9 ( .A1(n5), .A2(n6), .Z(n3) );
  and2f U10 ( .A1(n7), .A2(G3), .Z(n6) );
  inv1f U11 ( .I(n1), .ZN(n7) );
  or2f U12 ( .A1(G1), .A2(G7), .Z(n1) );
  buf0 U15 ( .I(n10), .Z(G17) );
  dffx1 G7_reg ( .D(n21), .CP(clock), .Q(G7) );
  dffx1 G6_reg ( .D(n16), .CP(clock), .Q(G6) );
  dffx1 G5_reg ( .D(n11), .CP(clock), .Q(G5) );
  inv1 U16 ( .I(G0), .ZN(n8) );
  and2 U17 ( .A1(G0), .A2(n10), .Z(n11) );
  inv1 U18 ( .I(G5), .ZN(n4) );
  and2 U19 ( .A1(G6), .A2(n8), .Z(n5) );
  and2 U20 ( .A1(n1), .A2(n2), .Z(n21) );
  inv1 U21 ( .I(G2), .ZN(n2) );
endmodule


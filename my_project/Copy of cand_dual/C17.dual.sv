
module C17_iscas ( e, d, c, b, a, g, f );
  input e, d, c, b, a;
  output g, f;
  wire   n1, n2, n3, n4, n5;

  and2 U1 ( .A1(n1), .A2(n2), .Z(g) );
  or2 U2 ( .A1(b), .A2(e), .Z(n1) );
  and2 U4 ( .A1(a), .A2(c), .Z(n4) );
  and2 U5 ( .A1(b), .A2(n2), .Z(n3) );
  or2f U8 ( .A1(n3), .A2(n4), .Z(f) );
  inv1 U9 ( .I(n5), .ZN(n2) );
  and2f U10 ( .A1(c), .A2(d), .Z(n5) );
endmodule


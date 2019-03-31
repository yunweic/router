
module t481 ( v15, v14, v13, v12, v11, v10, v9, v8, v7, v6, v5, v4, v3, v2, v1, 
        v0, v160 );
  input v15, v14, v13, v12, v11, v10, v9, v8, v7, v6, v5, v4, v3, v2, v1, v0;
  output v160;
  wire   n40, n41, n42, n43, n44, n45, n46, n47, n48, n49, n50, n51, n52, n53,
         n54, n55, n56, n57, n58, n59, n60, n61, n62, n63, n64, n65, n66, n67,
         n68, n69, n70, n71, n72, n73, n74, n75, n76, n77, n78, n79, n80, n81,
         n82, n83, n84, n85, n86, n87, n88;

  and2 U40 ( .A1(n41), .A2(n42), .Z(n40) );
  or2 U42 ( .A1(n42), .A2(n41), .Z(n43) );
  and2 U43 ( .A1(n44), .A2(v14), .Z(n41) );
  inv1 U44 ( .I(v15), .ZN(n44) );
  or2 U45 ( .A1(v12), .A2(n45), .Z(n42) );
  inv1 U46 ( .I(v13), .ZN(n45) );
  or2 U48 ( .A1(n68), .A2(n67), .Z(n47) );
  and2 U49 ( .A1(n86), .A2(n49), .Z(n48) );
  inv1 U50 ( .I(n48), .ZN(n79) );
  inv1 U51 ( .I(n76), .ZN(n49) );
  inv1 U52 ( .I(v9), .ZN(n50) );
  or2 U53 ( .A1(v8), .A2(n50), .Z(n81) );
  inv1 U54 ( .I(n81), .ZN(n70) );
  inv1 U55 ( .I(v2), .ZN(n51) );
  or2 U56 ( .A1(v3), .A2(n51), .Z(n56) );
  inv1 U57 ( .I(n56), .ZN(n53) );
  inv1 U58 ( .I(v1), .ZN(n52) );
  inv1 U61 ( .I(n54), .ZN(n55) );
  or2 U62 ( .A1(n56), .A2(n55), .Z(n57) );
  inv1 U64 ( .I(v5), .ZN(n59) );
  inv1 U66 ( .I(v6), .ZN(n60) );
  inv1 U68 ( .I(n63), .ZN(n61) );
  and2 U69 ( .A1(n62), .A2(n61), .Z(n66) );
  inv1 U70 ( .I(n62), .ZN(n64) );
  and2 U71 ( .A1(n64), .A2(n63), .Z(n65) );
  inv1 U74 ( .I(n86), .ZN(n72) );
  inv1 U75 ( .I(v10), .ZN(n69) );
  or2 U76 ( .A1(v11), .A2(n69), .Z(n76) );
  or2 U77 ( .A1(n70), .A2(n46), .Z(n75) );
  inv1 U78 ( .I(n43), .ZN(n71) );
  or2 U84 ( .A1(n47), .A2(n77), .Z(n78) );
  inv1 U88 ( .I(n84), .ZN(n85) );
  and2 U89 ( .A1(n47), .A2(n85), .Z(n87) );
  or2 U90 ( .A1(n88), .A2(n87), .Z(v160) );
  or2f U47 ( .A1(v0), .A2(n52), .Z(n54) );
  or2f U59 ( .A1(n53), .A2(n54), .Z(n58) );
  and2f U60 ( .A1(n83), .A2(n82), .Z(n88) );
  or2f U63 ( .A1(n75), .A2(n74), .Z(n83) );
  and2f U65 ( .A1(n76), .A2(n73), .Z(n74) );
  and2 U67 ( .A1(n72), .A2(n84), .Z(n73) );
  or2f U72 ( .A1(v7), .A2(n60), .Z(n63) );
  and2f U73 ( .A1(n47), .A2(n49), .Z(n46) );
  or2f U79 ( .A1(n81), .A2(n80), .Z(n82) );
  and2f U80 ( .A1(n79), .A2(n78), .Z(n80) );
  and2f U81 ( .A1(n84), .A2(n49), .Z(n77) );
  or2f U82 ( .A1(n40), .A2(n71), .Z(n84) );
  or2f U83 ( .A1(n68), .A2(n67), .Z(n86) );
  and2f U85 ( .A1(n58), .A2(n57), .Z(n68) );
  or2f U86 ( .A1(v4), .A2(n59), .Z(n62) );
  or2f U87 ( .A1(n66), .A2(n65), .Z(n67) );
endmodule


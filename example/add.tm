states 20
Init
qa +
qr -
Init0
Init1
InitHash
Return
LeftOp
0ToRightOp
1ToRightOp
0RightOp
1RightOp
0ToResult
1ToResult
CarryToResult
0Result
1Result
CarryResult
Flip
NoLeftOp
alphabet 5 $ * # 0 1
Init 0 Init0 $ R
Init 1 Init1 $ R
Init # InitHash $ R
Init0 0 Init0 0 R
Init0 1 Init1 0 R
Init0 # InitHash 0 R
Init0 _ Return 0 L
Init1 0 Init0 1 R
Init1 1 Init1 1 R
Init1 # InitHash 1 R
Init1 _ Return 1 L
InitHash 0 Init0 # R
InitHash 1 Init1 # R
InitHash # InitHash # R
InitHash _ Return # L
Return 0 Return 0 L
Return 1 Return 1 L
Return # Return # L
Return * Return *
Return $ LeftOp $ R
LeftOp 0 0ToRightOp * R
LeftOp 1 1ToRightOp * R
LeftOp * LeftOp * R
LeftOp # 0RightOp # R
0ToRightOp 0 0ToRightOp 0 R
0ToRightOp 1 0ToRightOp 1 R
0ToRightOp # 0RightOp # R
1ToRightOp 0 1ToRightOp 0 R
1ToRightOp 1 1ToRightOp 1 R
1ToRightOp # 1RightOp # R
0RightOp 0 0ToResult * R
0RightOp 1 1ToResult * R
0RightOp * 0RightOp * R
0RightOp # 0Result # R
1RightOp 0 1ToResult * R
1RightOp 1 CarryToResult * R
1RightOp * 1RightOp * R
1RightOp # 1Result # R
0ToResult 0 0ToResult 0 R
0ToResult 1 0ToResult 1 R
0ToResult * 0ToResult * R
0ToResult # 0Result # R
1ToResult 0 1ToResult 0 R
1ToResult 1 1ToResult 1 R
1ToResult * 1ToResult * R
1ToResult # 1Result # R
CarryToResult 0 CarryToResult 0 R
CarryToResult 1 CarryToResult 1 R
CarryToResult * CarryToResult * R
CarryToResult # CarryResult # R
0Result 0 Return * L
0Result 1 qr 1 L
0Result * 0Result * R
0Result _ Return _ L
1Result 0 qr 0 L
1Result 1 Return * L
1Result * 1Result * R
1Result _ qr _ L
CarryResult 0 Flip * R
CarryResult 1 qr 1 L
CarryResult * CarryResult * R
NoLeftOp 0 qr 0 L
NoLeftOp 1 qr 1 L
NoLeftOp # NoLeftOp # R
NoLeftOp * NoLeftOp * R
NoLeftOp _ qa _ L
Flip 0 Flip 1 R
Flip 1 Return 0 L
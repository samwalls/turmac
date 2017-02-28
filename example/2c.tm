states 11
Init
qr -
qa +
Init0
Init1
Return
Flip
ReturnAdd
Add1
Add0
Carry
alphabet 3 $ 0 1
Init _ qa _ L
Init $ qr $ L
Init 0 Init0 $ R
Init 1 Init1 $ R
Init0 _ Return _ L
Init0 $ qr $ L
Init0 0 Init0 0 R
Init0 1 Init1 0 R
Init1 _ Return _ L
Init1 $ qr $ L
Init1 0 Init0 1 R
Init1 1 Init1 1 R
Return 0 Return 0 L
Return 1 Return 1 L
Return $ Flip $ R
Flip 0 Flip 1 R
Flip 1 Flip 0 R
Flip _ ReturnAdd _ L
ReturnAdd 0 ReturnAdd 0 L
ReturnAdd 1 ReturnAdd 1 L
ReturnAdd $ Add1 $ R
Add0 0 Add0 0 R
Add0 1 Add0 1 R
Add0 _ qa _ R
Add1 0 Add0 1 R
Add1 1 Carry 0 R
Add1 _ Add0 1 R
Carry 0 Add0 1 R
Carry 1 Carry 0 R
Carry _ Add0 1 R
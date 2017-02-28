states 19
Init
qr -
qa +
Init0
Init1
Init#
Return
Flip
ReturnAdd
Add1
Add0
Carry
ReturnCheck
Find
FindTrailing
0Right
1Right
Compare0
Compare1
alphabet 5 $ # * 0 1
Init _ qa _ L
Init 0 Init0 $ R
Init 1 Init1 $ R
Init # Init# $ R
Init0 _ Return 0 L
Init0 0 Init0 0 R
Init0 1 Init1 0 R
Init0 # Init# 0 R
Init1 _ Return 1 L
Init1 0 Init0 1 R
Init1 1 Init1 1 R
Init1 # Init# 1 R
Init# 0 Init0 # R
Init# 1 Init1 # R
Init# # Init# # R
Return 0 Return 0 L
Return 1 Return 1 L
Return # Flip # R
Flip 0 Flip 1 R
Flip 1 Flip 0 R
Flip _ ReturnAdd _ L
ReturnAdd 0 ReturnAdd 0 L
ReturnAdd 1 ReturnAdd 1 L
ReturnAdd # Add1 # R
Add0 0 Add0 0 R
Add0 1 Add0 1 R
Add0 _ ReturnCheck _ L
Add1 0 Add0 1 R
Add1 1 Carry 0 R
Add1 _ Add0 1 R
Carry 0 Add0 1 R
Carry 1 Carry 0 R
Carry _ Add0 1 R
ReturnCheck 0 ReturnCheck 0 L
ReturnCheck 1 ReturnCheck 1 L
ReturnCheck # ReturnCheck # L
ReturnCheck * ReturnCheck * L
ReturnCheck $ Find $ R
Find 0 0Right * R
Find 1 1Right * R
Find * Find * R
Find # FindTrailing # R
Find _ qa _ L
FindTrailing 0 FindTrailing 0 R
FindTrailing 1 qr 1 L
FindTrailing _ qa _ L
FindTrailing * FindTrailing * R
0Right # Compare0 # R
0Right * Compare0 * R
0Right 0 0Right 0 R
0Right 1 0Right 1 R
1Right # Compare1 # R
1Right * Compare1 * R
1Right 0 1Right 0 R
1Right 1 1Right 1 R
Compare0 0 ReturnCheck * L
Compare0 * Compare0 * R
Compare0 1 qr 1 L
Compare0 _ qa _ L
Compare1 1 ReturnCheck * L
Compare1 * Compare1 * R
Compare1 0 qr 0 L
Compare1 _ qr _ L
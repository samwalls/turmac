states 22
Init
qa +
qr -
Init0
Init1
Init#
Init=
Init?
Return
Count
Add
Add1
Add0
Carry
GoToAdd
Check
ReturnCheck
0Right
1Right
Check0
Check1
CheckTrailing
alphabet 7 $ # ~ = ? 0 1
Init _ qa _ L
Init 0 Init0 $ R
Init 1 Init1 $ R
Init # Init# $ R
Init = Init= $ R
Init0 _ Init? 0 R
Init0 0 Init0 0 R
Init0 1 Init1 0 R
Init0 # Init# 0 R
Init0 = Init= 0 R
Init1 _ Init? 1 R
Init1 0 Init0 1 R
Init1 1 Init1 1 R
Init1 # Init# 1 R
Init1 = Init= 1 R
Init# 0 Init0 # R
Init# 1 Init1 # R
Init# # Init# # R
Init# = Init= # R
Init= 0 Init0 = R
Init= 1 Init1 = R
Init= # Init# = R
Init= = Init= = R
Init? _ Return ? L
Return 0 Return 0 L
Return 1 Return 1 L
Return = Return = L
Return # Return # L
Return ~ Return ~ L
Return ? Return ? L
Return $ Count $ R
Count # GoToAdd ~ R
Count ~ Count ~ R
Count = Check = R
GoToAdd # GoToAdd # R
GoToAdd = GoToAdd = R
GoToAdd 0 GoToAdd 0 R
GoToAdd 1 GoToAdd 1 R
GoToAdd ? Add1 ? R
Add0 0 Add0 0 R
Add0 1 Add0 1 R
Add0 _ Return _ L
Add1 0 Add0 1 R
Add1 1 Carry 0 R
Add1 _ Add0 1 R
Carry 0 Add0 1 R
Carry 1 Carry 0 R
Carry _ Add0 1 R
ReturnCheck 0 ReturnCheck 0 L
ReturnCheck 1 ReturnCheck 1 L
ReturnCheck ~ ReturnCheck ~ L
ReturnCheck = Check = R
ReturnCheck ? ReturnCheck ? L
Check 0 0Right ~ R
Check 1 1Right ~ R
Check ~ Check ~ R
Check ? CheckTrailing ? R
0Right 0 0Right 0 R
0Right 1 0Right 1 R
0Right ? Check0 ? R
1Right 0 1Right 0 R
1Right 1 1Right 1 R
1Right ? Check1 ? R
Check0 0 ReturnCheck ~ L
Check0 1 qr 1 L
Check0 ~ Check0 ~ R
Check0 _ qa _ L
Check1 1 ReturnCheck ~ L
Check1 0 qr 0 L
Check1 ~ Check1 ~ R
Check1 _ qr _ L
CheckTrailing ~ CheckTrailing ~ R
CheckTrailing _ qa _ L
CheckTrailing 0 qa _ L
CheckTrailing 1 qr _ L
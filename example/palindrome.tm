states 14
qInit
qa +
qr -
qInitA
qInitB
qInitC
qReturn
qFindNext
qMvRightA
qMvRightB
qMvRightC
qFindLeftA
qFindLeftB
qFindLeftC
alphabet 5 $ # a b c
qInit a qInitA $ R
qInit b qInitB $ R
qInit c qInitC $ R
qInitA a qInitA a R
qInitA b qInitB a R
qInitA c qInitC a R
qInitA _ qReturn a L
qInitB a qInitA b R
qInitB b qInitB b R
qInitB c qInitC b R
qInitB _ qReturn b L
qInitC a qInitA c R
qInitC b qInitB c R
qInitC c qInitC c R
qInitC _ qReturn c L
qReturn a qReturn a L
qReturn b qReturn b L
qReturn c qReturn c L
qReturn # qReturn # L
qReturn $ qFindNext $ R
qFindNext a qMvRightA # R
qFindNext b qMvRightB # R
qFindNext c qMvRightC # R
qFindNext # qFindNext # R
qFindNext _ qa _ R
qMvRightA a qMvRightA a R
qMvRightA b qMvRightA b R
qMvRightA c qMvRightA c R
qMvRightA # qFindLeftA # L
qMvRightA _ qFindLeftA _ L
qMvRightB a qMvRightB a R
qMvRightB b qMvRightB b R
qMvRightB c qMvRightB c R
qMvRightB # qFindLeftB # L
qMvRightB _ qFindLeftB _ L
qMvRightC a qMvRightC a R
qMvRightC b qMvRightC b R
qMvRightC c qMvRightC c R
qMvRightC # qFindLeftC # L
qMvRightC _ qFindLeftC _ L
qFindLeftA a qReturn # L
qFindLeftA b qr b L
qFindLeftA c qr c L
qFindLeftA # qFindLeftA # L
qFindLeftA $ qa $ L
qFindLeftB a qr a L
qFindLeftB b qReturn # L
qFindLeftB c qr c L
qFindLeftB # qFindLeftB # L
qFindLeftB $ qa $ L
qFindLeftC a qr a L
qFindLeftC b qr b L
qFindLeftC c qReturn # L
qFindLeftC # qFindLeftC # L
qFindLeftC $ qa $ L
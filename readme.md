# BE_Fuck
BattlEye Emulator

# README
BE_Starter_x64.exe
启动器，用于判断 `32` or `64` 启动相应程序

BE_Proxy_x64.exe
模拟游戏 与 `BESerivce.exe` 进行通信，用于分析包

Client_BE.exe 
监视 `TslGame_BE.exe` 启动，并在启动后瞬间注入 BE_xBP.dll

BE_xBP.dll
对 `TslGame_BE.exe` 进行 `用户`和`内核`相关API的HOOK
用户: 
内核: `NtCreateFile` 将 `\\??\\pipe\\BattlEye` 替换为 `\\??\\pipe\\19060`

Client_BE_x64.exe
64位，由于 `TslGame_BE.exe` 只有32位，目前暂未用到

BE_xBP_x64.dll
64位，由于 `TslGame_BE.exe` 只有32位，目前暂未用到
SET PATH=D:\Keil_v5\ARM\ARMCC\Bin;C:\gurobi951\win64\bin;C:\gurobi900\win64\bin;C:\gurobi903\win64\bin;C:\Program Files (x86)\NVIDIA Corporation\PhysX\Common;C:\Program Files (x86)\Common Files\Oracle\Java\javapath;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Windows\System32\OpenSSH\;C:\Program Files\Git\cmd;F:\Program Files\MATLAB\R2016b\runtime\win64;F:\Program Files\MATLAB\R2016b\bin;F:\Program Files\MATLAB\R2016b\polyspace\bin;C:\Program Files\Java\jdk1.8.0_221\bin;D:\MinGW\bin;C:\Program Files\nodejs\;C:\Program Files\dotnet\;C:\Program Files\Go\bin;C:\Program Files (x86)\IVI Foundation\VISA\WinNT\Bin\;C:\Program Files\IVI Foundation\VISA\Win64\Bin\;C:\Program Files (x86)\IVI Foundation\VISA\WinNT\Bin;C:\Tomcat 5.5\common\lib\;D:\Python\Python310\Scripts\;D:\Python\Python310\;C:\Users\lexuan\AppData\Local\Microsoft\WindowsApps;C:\Users\lexuan\AppData\Local\Programs\Microsoft VS Code\bin;C:\Users\lexuan\AppData\Local\GitHubDesktop\bin;C:\Users\lexuan\AppData\Roaming\npm;C:\Program Files\CMake\bin;C:\Users\lexuan\go\bin
SET ARMCC5_ASMOPT=--diag_suppress=9931
SET ARMCC5_CCOPT=--diag_suppress=9931
SET ARMCC5_LINKOPT=--diag_suppress=9931
SET CPU_TYPE=STM32F103C8
SET CPU_VENDOR=STMicroelectronics
SET UV2_TARGET=USART1-DEMO
SET CPU_CLOCK=0x00B71B00
"D:\Keil_v5\ARM\ARMCC\Bin\ArmAsm" --Via ".\startup_stm32f10x_hd._ia"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\main.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\stm32f10x_it.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\usart1.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\led.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\oled.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\stm32f10x_gpio.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\stm32f10x_rcc.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\stm32f10x_usart.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\core_cm3.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\system_stm32f10x.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmLink" --Via ".\STM32-DEMO.lnp"
"D:\Keil_v5\ARM\ARMCC\Bin\fromelf.exe" ".\STM32-DEMO.axf" --i32combined --output ".\STM32-DEMO.hex"

SET PATH=C:\Keil_v5\ARM\ARMCC\Bin;C:\gurobi912\win64\bin;C:\Program Files (x86)\Common Files\Oracle\Java\javapath;C:\WINDOWS\system32;C:\WINDOWS;C:\WINDOWS\System32\Wbem;C:\WINDOWS\System32\WindowsPowerShell\v1.0\;C:\Program Files\Git\usr\bin;C:\WINDOWS\System32\OpenSSH\;C:\Users\jmche\AppData\Local\Programs\Python\Python36\Scripts;C:\Users\jmche\AppData\Local\Programs\Python\Python36;C:\Program Files (x86)\Intel\Intel(R) Management Engine Components\DAL;C:\Program Files\Intel\Intel(R) Management Engine Components\DAL;C:\MinGW\bin;C:\Program Files\Java\jdk1.8.0_221\bin;C:\Program Files\MySQL\MySQL Server 8.0\bin;C:\Program Files\Apache Software Foundation\apache-maven-3.6.3\bin;C:\Program Files\nodejs\;C:\Program Files\SlikSvn\bin;C:\Program Files\Calibre2\;C:\Program Files\Git\cmd;C:\Program Files (x86)\Arduino;C:\Program Files\Microsoft VS Code\bin;C:\Program Files\nodejs\node_modules\npm\bin\node-gyp-bin;D:\Program Files\MATLAB\R2016b\runtime\win64;D:\Program Files\MATLAB\R2016b\bin;D:\Program Files\MATLAB\R2016b\polyspace\bin;D:\ProgramData\Anaconda3;D:\ProgramData\Anaconda3\Scripts;C:\Program Files\dotnet\;C:\Program Files\Go\bin;C:\Users\jmche\.windows-build-tools\python27\;C:\Users\jmche\AppData\Local\Microsoft\WindowsApps;C:\Program Files\JetBrains\IntelliJ IDEA 2018.3.6\bin;C:\Users\jmche\AppData\Local\Programs\Fiddler;C:\Users\jmche\AppData\Roaming\npm;C:\Users\jmche\AppData\Local\GitHubDesktop\bin;C:\Users\jmche\AppData\Local\Programs\Microsoft VS Code\bin;C:\Program Files (x86)\Nmap;C:\Users\jmche\go\bin;C:\Users\jmche\AppData\Local\Microsoft\WindowsApps;
SET ARMCC5_ASMOPT=--diag_suppress=9931
SET ARMCC5_CCOPT=--diag_suppress=9931
SET ARMCC5_LINKOPT=--diag_suppress=9931
SET CPU_TYPE=STM32F103C8
SET CPU_VENDOR=STMicroelectronics
SET UV2_TARGET=USART1-DEMO
SET CPU_CLOCK=0x00B71B00
"C:\Keil_v5\ARM\ARMCC\Bin\ArmAsm" --Via ".\startup_stm32f10x_hd._ia"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\main.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\stm32f10x_it.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\usart1.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\led.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\oled.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\misc.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\stm32f10x_exti.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\stm32f10x_gpio.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\stm32f10x_rcc.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\stm32f10x_usart.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\core_cm3.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\system_stm32f10x.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmLink" --Via ".\STM32-DEMO.lnp"
"C:\Keil_v5\ARM\ARMCC\Bin\fromelf.exe" ".\STM32-DEMO.axf" --i32combined --output ".\STM32-DEMO.hex"

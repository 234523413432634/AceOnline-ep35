# Microsoft Developer Studio Project File - Name="AtumLauncher" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=ATUMLAUNCHER - WIN32 R_WIKIGAMES_ENG
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "AtumLauncher.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "AtumLauncher.mak" CFG="ATUMLAUNCHER - WIN32 R_WIKIGAMES_ENG"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "AtumLauncher - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "AtumLauncher - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "AtumLauncher - Win32 Debug_Launcher_for_TestServer" (based on "Win32 (x86) Application")
!MESSAGE "AtumLauncher - Win32 Release_Launcher_for_TestServer" (based on "Win32 (x86) Application")
!MESSAGE "AtumLauncher - Win32 D_Wikigames_Eng" (based on "Win32 (x86) Application")
!MESSAGE "AtumLauncher - Win32 R_Wikigames_Eng" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "AtumLauncher - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\output\AtumLauncher\Release"
# PROP Intermediate_Dir "..\..\output\AtumLauncher\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "." /I "..\..\Common" /I ".\Main" /I "..\CommonGameServer" /I "..\CommonGameServer\FTP" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x412 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 winmm.lib ziparchive.lib /nologo /subsystem:windows /map /machine:I386 /nodefaultlib:"MSVCRT" /out:"..\..\BuildResultSvr\ETC\C_Exe2(Launcher)\Main\Launcher.atm" /libpath:"../../Lib" /MAPINFO:EXPORTS /MAPINFO:LINES
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "AtumLauncher - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\output\AtumLauncher\Debug"
# PROP Intermediate_Dir "..\..\output\AtumLauncher\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "." /I "..\..\Common" /I ".\Main" /I "..\CommonGameServer" /I "..\CommonGameServer\FTP" /D "_MBCS" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x412 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 winmm.lib ziparchiveD.lib /nologo /subsystem:windows /incremental:no /debug /machine:I386 /nodefaultlib:"MSVCRT" /out:"..\..\Bin\Debug\Launcher_dbg.exe" /pdbtype:sept /libpath:"../../Lib"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "AtumLauncher - Win32 Debug_Launcher_for_TestServer"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "AtumLauncher___Win32_Debug_Launcher_for_TestServer"
# PROP BASE Intermediate_Dir "AtumLauncher___Win32_Debug_Launcher_for_TestServer"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\output\AtumLauncher\Debug_Launcher_for_TestServer"
# PROP Intermediate_Dir "..\..\output\AtumLauncher\Debug_Launcher_for_TestServer"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "." /I "..\..\Common" /I ".\Main" /I "..\CommonGameServer" /I "..\CommonGameServer\FTP" /D "_MBCS" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_ATUM_DEVELOP" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "." /I "..\..\Common" /I ".\Main" /I "..\CommonGameServer" /I "..\CommonGameServer\FTP" /D "_MBCS" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_ATUM_DEVELOP" /D "_MGAME_TEST_SERVER" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "_DEBUG"
# ADD RSC /l 0x412 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 winmm.lib ziparchive.lib /nologo /subsystem:windows /incremental:no /debug /machine:I386 /nodefaultlib:"MSVCRT" /out:"..\..\Bin\Debug\Launcher_dbg.exe" /pdbtype:sept /libpath:"../../Lib/Debug"
# ADD LINK32 winmm.lib ziparchiveD.lib /nologo /subsystem:windows /incremental:no /debug /machine:I386 /nodefaultlib:"MSVCRT" /out:"..\..\Bin\Debug\Launcher_dbg_test.exe" /pdbtype:sept /libpath:"../../Lib"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "AtumLauncher - Win32 Release_Launcher_for_TestServer"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "AtumLauncher___Win32_Release_Launcher_for_TestServer"
# PROP BASE Intermediate_Dir "AtumLauncher___Win32_Release_Launcher_for_TestServer"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\output\AtumLauncher\Release_Launcher_for_TestServer"
# PROP Intermediate_Dir "..\..\output\AtumLauncher\Release_Launcher_for_TestServer"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /I "." /I "..\..\Common" /I ".\Main" /I "..\CommonGameServer" /I "..\CommonGameServer\FTP" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_MGAME" /FR /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "." /I "..\..\Common" /I ".\Main" /I "..\CommonGameServer" /I "..\CommonGameServer\FTP" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_MGAME_TEST_SERVER" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "NDEBUG"
# ADD RSC /l 0x412 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 winmm.lib ziparchive.lib /nologo /subsystem:windows /map /machine:I386 /nodefaultlib:"MSVCRT" /out:"..\..\Bin\Release/Launcher.atm" /libpath:"../../Lib/Release" /MAPINFO:EXPORTS /MAPINFO:LINES
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 winmm.lib ziparchive.lib /nologo /subsystem:windows /map /machine:I386 /nodefaultlib:"MSVCRT" /out:"..\..\Bin\Release/Launcher_test.atm" /libpath:"../../Lib" /MAPINFO:EXPORTS /MAPINFO:LINES
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "AtumLauncher - Win32 D_Wikigames_Eng"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "AtumLauncher___Win32_D_Wikigames_Eng"
# PROP BASE Intermediate_Dir "AtumLauncher___Win32_D_Wikigames_Eng"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "AtumLauncher___Win32_D_Wikigames_Eng"
# PROP Intermediate_Dir "AtumLauncher___Win32_D_Wikigames_Eng"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "." /I "..\..\Common" /I ".\Main" /I "..\CommonGameServer" /I "..\CommonGameServer\FTP" /D "_MBCS" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\CommonGameServer\FTP" /I "." /I "..\..\Common" /I ".\Main" /I "..\CommonGameServer" /I "..\..\Common\d3d8" /D "_MBCS" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "WIKIGAMES_ENG" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "_DEBUG"
# ADD RSC /l 0x412 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 winmm.lib ziparchiveD.lib /nologo /subsystem:windows /incremental:no /debug /machine:I386 /nodefaultlib:"MSVCRT" /out:"..\..\Bin\Debug\Launcher_dbg.exe" /pdbtype:sept /libpath:"../../Lib"
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 winmm.lib ziparchiveD.lib /nologo /subsystem:windows /incremental:no /debug /machine:I386 /nodefaultlib:"MSVCRT" /out:"..\..\..\Output\Client\Launcher_dbg.exe" /pdbtype:sept /libpath:"../../Lib"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "AtumLauncher - Win32 R_Wikigames_Eng"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "AtumLauncher___Win32_R_Wikigames_Eng"
# PROP BASE Intermediate_Dir "AtumLauncher___Win32_R_Wikigames_Eng"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "AtumLauncher___Win32_R_Wikigames_Eng"
# PROP Intermediate_Dir "AtumLauncher___Win32_R_Wikigames_Eng"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /I "." /I "..\..\Common" /I ".\Main" /I "..\CommonGameServer" /I "..\CommonGameServer\FTP" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "." /I "..\..\Common" /I ".\Main" /I "..\CommonGameServer" /I "..\CommonGameServer\FTP" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "WIKIGAMES_ENG" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "NDEBUG"
# ADD RSC /l 0x412 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 winmm.lib ziparchive.lib /nologo /subsystem:windows /map /machine:I386 /nodefaultlib:"MSVCRT" /out:"..\..\BuildResultSvr\ETC\C_Exe2(Launcher)\Main\Launcher.atm" /libpath:"../../Lib" /MAPINFO:EXPORTS /MAPINFO:LINES
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 winmm.lib ziparchive.lib /nologo /subsystem:windows /map /machine:I386 /nodefaultlib:"MSVCRT" /out:"..\..\..\Output\Client\Launcher.atm" /libpath:"../../Lib" /MAPINFO:EXPORTS /MAPINFO:LINES
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "AtumLauncher - Win32 Release"
# Name "AtumLauncher - Win32 Debug"
# Name "AtumLauncher - Win32 Debug_Launcher_for_TestServer"
# Name "AtumLauncher - Win32 Release_Launcher_for_TestServer"
# Name "AtumLauncher - Win32 D_Wikigames_Eng"
# Name "AtumLauncher - Win32 R_Wikigames_Eng"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\CommonGameServer\AtumDateTime.cpp
# End Source File
# Begin Source File

SOURCE=.\AtumLauncher.cpp
# End Source File
# Begin Source File

SOURCE=.\AtumLauncher.rc
# End Source File
# Begin Source File

SOURCE=.\AtumLauncherDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\AtumParamProtocol.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\AtumParamProtocolFunctions.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\BrowseForFolder.cpp
# End Source File
# Begin Source File

SOURCE=.\Main\comboboxebx.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\CommandHistory.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgGuardAgreement.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\FTP\FTPManager.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\HistoryComboBox.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\HttpManager.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\Iexplore.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\FTP\KbcBmp.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\FTP\KbcButton.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\ListBoxEBX.cpp
# End Source File
# Begin Source File

SOURCE=.\LoginSuccessDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\Security\md5.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\md5_lib_src.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\Security\metafile.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\MGameDecryption.cpp
# End Source File
# Begin Source File

SOURCE=.\Main\MyCheck.cpp
# End Source File
# Begin Source File

SOURCE=.\Main\MyComboBox.cpp
# End Source File
# Begin Source File

SOURCE=.\Main\MyEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\PreServerIPDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\FTP\ProgressCtrlX.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\RegistryControl.cpp
# End Source File
# Begin Source File

SOURCE=.\Main\screenkeyboarddlg.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\Security\shieldSecurity.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\Security\shieldSecurityDll.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\SocketHeader.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=..\..\Common\SystemLogManager.cpp
# End Source File
# Begin Source File

SOURCE=.\main\UpdateWinSocket.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\Security\utility.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\WinPacket.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\WinSocket.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\XOR_Lib.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AtumLauncher.h
# End Source File
# Begin Source File

SOURCE=.\AtumLauncherDlg.h
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\BrowseForFolder.h
# End Source File
# Begin Source File

SOURCE=.\Main\comboboxebx.h
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\CommandHistory.h
# End Source File
# Begin Source File

SOURCE=.\DlgGuardAgreement.h
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\FTP\Drawgdix.h
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\FTP\FTPManager.h
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\historycombobox.h
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\HttpManager.h
# End Source File
# Begin Source File

SOURCE=.\IExplore.h
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\IExplore.h
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\FTP\KbcBmp.h
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\FTP\KbcButton.h
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\ListBoxEBX.h
# End Source File
# Begin Source File

SOURCE=.\LoginSuccessDlg.h
# End Source File
# Begin Source File

SOURCE=..\..\Common\md5_lib_src.h
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\FTP\MemDC.h
# End Source File
# Begin Source File

SOURCE=.\Main\MyCheck.h
# End Source File
# Begin Source File

SOURCE=.\Main\MyComboBox.h
# End Source File
# Begin Source File

SOURCE=.\Main\MyEdit.h
# End Source File
# Begin Source File

SOURCE=.\PreServerIPDlg.h
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\FTP\ProgressCtrlX.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\Main\screenkeyboarddlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=..\..\Common\SystemLogManager.h
# End Source File
# Begin Source File

SOURCE=.\main\UpdateWinSocket.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\atum.ico
# End Source File
# Begin Source File

SOURCE=.\res\AtumLauncher.ico
# End Source File
# Begin Source File

SOURCE=.\res\AtumLauncher.rc2
# End Source File
# Begin Source File

SOURCE=.\res\BarCenter.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BarLeft.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BarRight.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BatalOff.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BatalOn.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Batle2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BG_ARG.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BG_VTC.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ButtonDown.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CanCelD.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CancelF.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CanCelU.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CB_Check.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CB_UnCheck.bmp
# End Source File
# Begin Source File

SOURCE=.\res\center.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CloseD.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CloseU.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ComboBox.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DecaOff.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DecaOn.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Decar1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Decar2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\EditBG.bmp
# End Source File
# Begin Source File

SOURCE=.\res\End1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\End2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\EndOff.bmp
# End Source File
# Begin Source File

SOURCE=.\res\EndOn.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Gear.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Go1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Go2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GoBtn.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GoBtn_Arg.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GoBtn_Chn.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GoBtn_S2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GoBtn_VTC.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GoD.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GoF.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Gooff.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Goon.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GoU.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GoX.bmp
# End Source File
# Begin Source File

SOURCE=.\res\HomepageD.bmp
# End Source File
# Begin Source File

SOURCE=.\res\HomepageF.bmp
# End Source File
# Begin Source File

SOURCE=.\res\HomepageU.bmp
# End Source File
# Begin Source File

SOURCE=.\res\icon_VTC.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Idb_Login.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Join1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Join2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\JoinBtn.bmp
# End Source File
# Begin Source File

SOURCE=.\res\JoinD.bmp
# End Source File
# Begin Source File

SOURCE=.\res\JoinF.bmp
# End Source File
# Begin Source File

SOURCE=.\res\JoinOff.bmp
# End Source File
# Begin Source File

SOURCE=.\res\JoinOn.bmp
# End Source File
# Begin Source File

SOURCE=.\res\JoinU.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_0.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_0_OnShift.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_1_OnShift.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_2_OnShift.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_3_OnShift.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_4_on.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_4_OnShift.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_5.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_5_OnShift.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_6.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_6_OnShift.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_7.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_7_OnShift.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_8.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_8_OnShift.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_9.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_9_OnShift.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_a.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_a_OnShift.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_b.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_b_OnShift.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_backSpace.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_c.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_c_OnShift.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_CapsLock.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_CapsLock_On.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_d.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_d_OnShift.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_e.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_e1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_e_OnShift.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_Enter.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_f.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_f_OnShift.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_g.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_g_OnShift.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_h.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_h_OnShift.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_i.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_i_OnShift.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_j.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_j_OnShift.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_k.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_k_OnShift.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_l.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_l_OnShift.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_m.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_m_OnShift.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_n.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_n_OnShift.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_o.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_o_OnShift.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_p.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_p_OnShift.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_q.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_q_OnShift.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_r.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_r_OnShift.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_s.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_s_OnShift.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_Shift.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_Shift_On.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_Space.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_t.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_t_OnShift.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_u.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_u_OnShift.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_v.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_v_OnShift.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_w.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_w_OnShift.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_x.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_x_OnShift.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_y.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_y_OnShift.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_z.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key_z_OnShift.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ListBg_VTC.bmp
# End Source File
# Begin Source File

SOURCE=.\res\MinD.bmp
# End Source File
# Begin Source File

SOURCE=.\res\MinF.bmp
# End Source File
# Begin Source File

SOURCE=.\res\MinU.bmp
# End Source File
# Begin Source File

SOURCE=.\res\OK.bmp
# End Source File
# Begin Source File

SOURCE=.\res\OkD.bmp
# End Source File
# Begin Source File

SOURCE=.\res\OKU.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Philon2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\PilonOff.bmp
# End Source File
# Begin Source File

SOURCE=.\res\PilonOn.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Scr_Login.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ScreenKeyboard.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ScreenKeyboard_Mask.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Secret1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Secret2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SecretOff.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SecretOn.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ServerList.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ServerUser.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ServerUser_VTC.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Sharin2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SharinOff.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SharinOn.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Titlebar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Titlebar_Arg.bmp
# End Source File
# Begin Source File

SOURCE=.\res\update_bar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\UseClass.BMP
# End Source File
# Begin Source File

SOURCE=.\res\x.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\AtumLauncherModifyList.txt
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project

# Microsoft Developer Studio Project File - Name="Atum" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=ATUM - WIN32 D_WIKIGAMES_ENG
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Atum.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Atum.mak" CFG="ATUM - WIN32 D_WIKIGAMES_ENG"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Atum - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Atum - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "Atum - Win32 D_Wikigames_Eng" (based on "Win32 (x86) Application")
!MESSAGE "Atum - Win32 R_Wikigames_Eng" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Atum - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\output\Atum\Release"
# PROP Intermediate_Dir "..\..\output\Atum\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "." /I "..\..\Common" /I ".\Main" /I "..\CommonGameServer" /I "..\CommonGameServer\FTP" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_MGAME_RELEASE" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x412 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 wininet.lib winmm.lib /nologo /subsystem:windows /machine:I386 /out:"..\..\BuildResultSvr\ETC\C_Exe1\Main\SpaceCowboy.exe"

!ELSEIF  "$(CFG)" == "Atum - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\output\Atum\Debug"
# PROP Intermediate_Dir "..\..\output\Atum\Debug"
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
# ADD LINK32 wininet.lib winmm.lib /nologo /subsystem:windows /incremental:no /debug /machine:I386 /out:"..\..\Bin\Debug\SpaceCowboy.exe" /pdbtype:sept

!ELSEIF  "$(CFG)" == "Atum - Win32 D_Wikigames_Eng"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Atum___Win32_D_Wikigames_Eng0"
# PROP BASE Intermediate_Dir "Atum___Win32_D_Wikigames_Eng0"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Atum___Win32_D_Wikigames_Eng0"
# PROP Intermediate_Dir "Atum___Win32_D_Wikigames_Eng0"
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
# ADD BASE LINK32 wininet.lib winmm.lib /nologo /subsystem:windows /incremental:no /debug /machine:I386 /out:"..\..\Bin\Debug\SpaceCowboy.exe" /pdbtype:sept
# ADD LINK32 wininet.lib winmm.lib /nologo /subsystem:windows /incremental:no /debug /machine:I386 /out:"..\..\..\Output\Client\SpaceCowboy_debug.exe" /pdbtype:sept

!ELSEIF  "$(CFG)" == "Atum - Win32 R_Wikigames_Eng"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Atum___Win32_R_Wikigames_Eng"
# PROP BASE Intermediate_Dir "Atum___Win32_R_Wikigames_Eng"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Atum___Win32_R_Wikigames_Eng"
# PROP Intermediate_Dir "Atum___Win32_R_Wikigames_Eng"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /I "." /I "..\..\Common" /I ".\Main" /I "..\CommonGameServer" /I "..\CommonGameServer\FTP" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_MGAME_RELEASE" /FR /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "." /I "..\..\Common" /I ".\Main" /I "..\CommonGameServer" /I "..\CommonGameServer\FTP" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_MGAME_RELEASE" /D "WIKIGAMES_ENG" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "NDEBUG"
# ADD RSC /l 0x412 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wininet.lib winmm.lib /nologo /subsystem:windows /machine:I386 /out:"..\..\BuildResultSvr\ETC\C_Exe1\Main\SpaceCowboy.exe"
# ADD LINK32 wininet.lib winmm.lib /nologo /subsystem:windows /machine:I386 /out:"..\..\..\Output\Client\SpaceCowboy.exe"

!ENDIF 

# Begin Target

# Name "Atum - Win32 Release"
# Name "Atum - Win32 Debug"
# Name "Atum - Win32 D_Wikigames_Eng"
# Name "Atum - Win32 R_Wikigames_Eng"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Atum.cpp
# End Source File
# Begin Source File

SOURCE=.\Atum.rc
# End Source File
# Begin Source File

SOURCE=.\AtumDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\AtumParamProtocol.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\AtumParamProtocolFunctions.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\FTP\FTPManager.cpp
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

SOURCE=..\CommonGameServer\MGameDecryption.cpp
# End Source File
# Begin Source File

SOURCE=.\main\PreUpdateWinSocket.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\RegistryControl.cpp
# End Source File
# Begin Source File

SOURCE=.\Main\selectgameserverdlg.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=..\..\Common\SocketHeader.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
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

SOURCE=.\Atum.h
# End Source File
# Begin Source File

SOURCE=.\AtumDlg.h
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\Contents.h
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\FTP\FTPManager.h
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\HttpManager.h
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\IExplore.h
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\ListBoxEBX.h
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\LocalizationDefineCommon.h
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\MGameDecryption.h
# End Source File
# Begin Source File

SOURCE=.\main\PreUpdateWinSocket.h
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\RegistryControl.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\Main\selectgameserverdlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\StringDefineCommon.h
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\StringDefineServer.h
# End Source File
# Begin Source File

SOURCE=..\..\Common\WinPacket.h
# End Source File
# Begin Source File

SOURCE=..\..\Common\WinSocket.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\atum.ico
# End Source File
# Begin Source File

SOURCE=.\res\Atum.ico
# End Source File
# Begin Source File

SOURCE=.\res\Atum.rc2
# End Source File
# Begin Source File

SOURCE=.\res\Background.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BtnGameServer1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BtnGameServer10.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BtnGameServer2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BtnGameServer3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BtnGameServer4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BtnGameServer5.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BtnGameServer6.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BtnGameServer7.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BtnGameServer8.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BtnGameServer9.bmp
# End Source File
# Begin Source File

SOURCE=.\res\LoginServer_BG_r1_c1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\LoginServer_BG_r3_c1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\LoginServer_BG_r4_c1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\LoginServer_ListItemBG.bmp
# End Source File
# Begin Source File

SOURCE=.\res\LoginServerListItemBG.bmp
# End Source File
# Begin Source File

SOURCE=.\res\TitleBar.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\AtumModifyList.txt
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project

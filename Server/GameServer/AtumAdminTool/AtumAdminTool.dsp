# Microsoft Developer Studio Project File - Name="AtumAdminTool" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=ATUMADMINTOOL - WIN32 R_WIKIGAMES_ENG
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "AtumAdminTool.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "AtumAdminTool.mak" CFG="ATUMADMINTOOL - WIN32 R_WIKIGAMES_ENG"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "AtumAdminTool - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "AtumAdminTool - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "AtumAdminTool - Win32 Release_OnlyServerAdmin" (based on "Win32 (x86) Application")
!MESSAGE "AtumAdminTool - Win32 D_Wikigames_Eng" (based on "Win32 (x86) Application")
!MESSAGE "AtumAdminTool - Win32 R_Wikigames_Eng" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "AtumAdminTool - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\output\AtumAdminTool\Release"
# PROP Intermediate_Dir "..\..\output\AtumAdminTool\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "." /I "..\..\Common" /I ".\Main" /I "..\CommonGameServer" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_ATUM_SERVER" /D "_ATUM_ADMIN_RELEASE" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "NDEBUG"
# ADD RSC /l 0x412 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 D3dx8.lib odbccp32.lib odbc32.lib winmm.lib /nologo /subsystem:windows /machine:I386 /out:"..\..\BuildResultSvr\Tool\SCAdminTool_for_mgame.exe"

!ELSEIF  "$(CFG)" == "AtumAdminTool - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\output\AtumAdminTool\Debug"
# PROP Intermediate_Dir "..\..\output\AtumAdminTool\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "." /I "..\..\Common" /I ".\Main" /I "..\CommonGameServer" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_ATUM_SERVER" /D "_ATUM_ADMINTOOL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "_DEBUG"
# ADD RSC /l 0x412 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 D3dx8.lib odbccp32.lib odbc32.lib winmm.lib /nologo /subsystem:windows /debug /machine:I386 /out:"..\..\Bin\Debug\00000_SCAdminTool(MS140_Kor)_Main_D.exe" /pdbtype:sept

!ELSEIF  "$(CFG)" == "AtumAdminTool - Win32 Release_OnlyServerAdmin"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "AtumAdminTool___Win32_Release_OnlyServerAdmin"
# PROP BASE Intermediate_Dir "AtumAdminTool___Win32_Release_OnlyServerAdmin"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\output\AtumAdminTool\Release_OnlyServerAdmin"
# PROP Intermediate_Dir "..\..\output\AtumAdminTool\Release_OnlyServerAdmin"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /I "." /I "..\..\Common" /I ".\Main" /I "..\CommonGameServer" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_ATUM_SERVER" /D "_ATUM_ADMIN_RELEASE" /FR /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "." /I "..\..\Common" /I ".\Main" /I "..\CommonGameServer" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_ATUM_SERVER" /D "_ATUM_ADMIN_RELEASE" /D "_ATUM_ONLY_SERVER_ADMIN_TOOL" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "NDEBUG"
# ADD RSC /l 0x412 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 D3dx8.lib odbccp32.lib odbc32.lib winmm.lib /nologo /subsystem:windows /machine:I386 /out:"..\..\Bin\Release\SpaceCowboyAdminTool_for_mgame.exe"
# ADD LINK32 D3dx8.lib odbccp32.lib odbc32.lib winmm.lib /nologo /subsystem:windows /machine:I386 /out:"..\..\Bin\Release\SCAdminTool_OnlyServerAdmin.exe"

!ELSEIF  "$(CFG)" == "AtumAdminTool - Win32 D_Wikigames_Eng"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "AtumAdminTool___Win32_D_Wikigames_Eng"
# PROP BASE Intermediate_Dir "AtumAdminTool___Win32_D_Wikigames_Eng"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "AtumAdminTool___Win32_D_Wikigames_Eng"
# PROP Intermediate_Dir "AtumAdminTool___Win32_D_Wikigames_Eng"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "." /I "..\..\Common" /I ".\Main" /I "..\CommonGameServer" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_ATUM_SERVER" /D "_ATUM_ADMINTOOL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "." /I "..\..\Common" /I ".\Main" /I "..\CommonGameServer" /I "..\..\Common\d3d8" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_ATUM_SERVER" /D "_ATUM_ADMINTOOL" /D "WIKIGAMES_ENG" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "_DEBUG"
# ADD RSC /l 0x412 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 D3dx8.lib odbccp32.lib odbc32.lib winmm.lib /nologo /subsystem:windows /debug /machine:I386 /out:"..\..\Bin\Debug\00000_SCAdminTool(MS140_Kor)_Main_D.exe" /pdbtype:sept
# ADD LINK32 D3dx8.lib odbccp32.lib odbc32.lib winmm.lib /nologo /subsystem:windows /debug /machine:I386 /out:"..\..\..\Output\Tools\AdminTool_Main_D.exe" /pdbtype:sept

!ELSEIF  "$(CFG)" == "AtumAdminTool - Win32 R_Wikigames_Eng"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "AtumAdminTool___Win32_R_Wikigames_Eng"
# PROP BASE Intermediate_Dir "AtumAdminTool___Win32_R_Wikigames_Eng"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "AtumAdminTool___Win32_R_Wikigames_Eng"
# PROP Intermediate_Dir "AtumAdminTool___Win32_R_Wikigames_Eng"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /I "." /I "..\..\Common" /I ".\Main" /I "..\CommonGameServer" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_ATUM_SERVER" /D "_ATUM_ADMIN_RELEASE" /FR /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "." /I "..\..\Common" /I ".\Main" /I "..\CommonGameServer" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_ATUM_SERVER" /D "_ATUM_ADMIN_RELEASE" /D "WIKIGAMES_ENG" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "NDEBUG"
# ADD RSC /l 0x412 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 D3dx8.lib odbccp32.lib odbc32.lib winmm.lib /nologo /subsystem:windows /machine:I386 /out:"..\..\BuildResultSvr\Tool\SCAdminTool_for_mgame.exe"
# ADD LINK32 D3dx8.lib odbccp32.lib odbc32.lib winmm.lib /nologo /subsystem:windows /machine:I386 /out:"..\..\..\Output\Tools\AdminTool_Main.exe"

!ENDIF 

# Begin Target

# Name "AtumAdminTool - Win32 Release"
# Name "AtumAdminTool - Win32 Debug"
# Name "AtumAdminTool - Win32 Release_OnlyServerAdmin"
# Name "AtumAdminTool - Win32 D_Wikigames_Eng"
# Name "AtumAdminTool - Win32 R_Wikigames_Eng"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AccountInfoDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\AdminAutoNoticeDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\AtumAdminTool.cpp
# End Source File
# Begin Source File

SOURCE=.\AtumAdminTool.rc
# End Source File
# Begin Source File

SOURCE=.\AtumAdminToolDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\AtumDateTime.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\AtumDBHelper.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\AtumDBLogWriter.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\AtumParamProtocol.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\AtumParamProtocolFunctions.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\AtumSJ.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\AtumThread.cpp
# End Source File
# Begin Source File

SOURCE=.\BlockAccountDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\BlockAccountListDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\BrowseForFolder.cpp
# End Source File
# Begin Source File

SOURCE=.\Main\cashshopmanagementdlg.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=.\CharacterInfoDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DeclarationOfWar.cpp
# End Source File
# Begin Source File

SOURCE=.\DeletedCharacter.cpp
# End Source File
# Begin Source File

SOURCE=.\Main\dlgmsgbox.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=.\Main\dlgsetinfluencerate.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=.\Main\editguilddlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Main\eventmonstermanagementdlg.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=.\ExpViewerDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\Global.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\GridCtrl\GridCell.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\GridCtrl\GridCellBase.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\GridCtrl\GridCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\GridCtrl\GridDropTarget.cpp
# End Source File
# Begin Source File

SOURCE=.\Main\guildmarkrecognitiondlg.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\HistoryComboBox.cpp
# End Source File
# Begin Source File

SOURCE=.\InfluenceRateGridCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\InflWarListDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\GridCtrl\InPlaceEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\LeaderElection.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\Localization.cpp
# End Source File
# Begin Source File

SOURCE=.\logtabblockaccount.cpp
# End Source File
# Begin Source File

SOURCE=.\LogTabConnection.cpp
# End Source File
# Begin Source File

SOURCE=.\LogTabGuildItem.cpp
# End Source File
# Begin Source File

SOURCE=.\LogTabItem.cpp
# End Source File
# Begin Source File

SOURCE=.\LogTabServerIntegration.cpp
# End Source File
# Begin Source File

SOURCE=.\LogTabUser.cpp
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

SOURCE=.\Main\MGameMonitor.cpp
# End Source File
# Begin Source File

SOURCE=.\ModifyItemDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Main\MyTabCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\ODBCStatement.cpp
# End Source File
# Begin Source File

SOURCE=.\PetitionManagementDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PremiumInfoDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PWDDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\Main\SCAdminWinSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\SCBadUserAdminDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SCGridHelper.cpp
# End Source File
# Begin Source File

SOURCE=.\SCGuildAdminDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SCHappyHourEventAdminDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SCItemEventDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SCLogAdminDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SCOutPostDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\scserveradmindlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SCStrategyPointAdminDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SCUserAdminDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SelectItemDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Main\seteventmonsterdlg.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=.\Main\sethappyev.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=.\SetItemEv.cpp
# End Source File
# Begin Source File

SOURCE=.\SetLanguageDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Main\setlimitusercountdlg.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=.\Main\setpcbanghappyev.cpp
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

SOURCE=..\CommonGameServer\TickManager.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\GridCtrl\TitleTip.cpp
# End Source File
# Begin Source File

SOURCE=.\Main\TrayIcon.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\Security\utility.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\VMem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\VMemPool.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\WavePlayer.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\WayPointManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\WinPacket.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\WinSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\Main\wrankingmanagement.cpp
# End Source File
# Begin Source File

SOURCE=.\Main\wrsevicesettingdlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Main\wrupdateranking.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\XOR_Lib.cpp
# End Source File
# Begin Source File

SOURCE=.\Main\xortestdlg.cpp
# ADD CPP /I ".."
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AccountInfoDlg.h
# End Source File
# Begin Source File

SOURCE=.\AdminAutoNoticeDlg.h
# End Source File
# Begin Source File

SOURCE=.\AtumAdminTool.h
# End Source File
# Begin Source File

SOURCE=.\AtumAdminToolDlg.h
# End Source File
# Begin Source File

SOURCE=.\BlockAccountDlg.h
# End Source File
# Begin Source File

SOURCE=.\BlockAccountListDlg.h
# End Source File
# Begin Source File

SOURCE=.\Main\cashshopmanagementdlg.h
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\GridCtrl\CellRange.h
# End Source File
# Begin Source File

SOURCE=.\characterinfodlg.h
# End Source File
# Begin Source File

SOURCE=.\DeclarationOfWar.h
# End Source File
# Begin Source File

SOURCE=.\DeletedCharacter.h
# End Source File
# Begin Source File

SOURCE=.\Main\dlgmsgbox.h
# End Source File
# Begin Source File

SOURCE=.\Main\dlgsetinfluencerate.h
# End Source File
# Begin Source File

SOURCE=.\Main\editguilddlg.h
# End Source File
# Begin Source File

SOURCE=.\Main\eventmonstermanagementdlg.h
# End Source File
# Begin Source File

SOURCE=.\ExpViewerDlg.h
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\GridCtrl\GridCell.h
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\GridCtrl\GridCellBase.h
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\GridCtrl\GridCtrl.h
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\GridCtrl\GridDropTarget.h
# End Source File
# Begin Source File

SOURCE=.\Main\guildmarkrecognitiondlg.h
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\historycombobox.h
# End Source File
# Begin Source File

SOURCE=.\InflWarListDlg.h
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\GridCtrl\InPlaceEdit.h
# End Source File
# Begin Source File

SOURCE=.\LeaderElection.h
# End Source File
# Begin Source File

SOURCE=.\logtabblockaccount.h
# End Source File
# Begin Source File

SOURCE=.\LogTabConnection.h
# End Source File
# Begin Source File

SOURCE=.\LogTabGuildItem.h
# End Source File
# Begin Source File

SOURCE=.\LogTabItem.h
# End Source File
# Begin Source File

SOURCE=.\LogTabServerIntegration.h
# End Source File
# Begin Source File

SOURCE=.\LogTabUser.h
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\GridCtrl\MemDC.h
# End Source File
# Begin Source File

SOURCE=.\Main\MGameMonitor.h
# End Source File
# Begin Source File

SOURCE=.\ModifyItemDlg.h
# End Source File
# Begin Source File

SOURCE=.\Main\MyTabCtrl.h
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\ODBCStatement.h
# End Source File
# Begin Source File

SOURCE=.\PetitionManagementDlg.h
# End Source File
# Begin Source File

SOURCE=.\PremiumInfoDlg.h
# End Source File
# Begin Source File

SOURCE=.\PWDDlg.h
# End Source File
# Begin Source File

SOURCE=.\ReportCtrl.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\Main\SCAdminWinSocket.h
# End Source File
# Begin Source File

SOURCE=.\SCBadUserAdminDlg.h
# End Source File
# Begin Source File

SOURCE=.\SCGridHelper.h
# End Source File
# Begin Source File

SOURCE=.\SCGuildAdminDlg.h
# End Source File
# Begin Source File

SOURCE=.\SCHappyHourEventAdminDlg.h
# End Source File
# Begin Source File

SOURCE=.\SCItemEventDlg.h
# End Source File
# Begin Source File

SOURCE=.\SCLogAdminDlg.h
# End Source File
# Begin Source File

SOURCE=.\SCOutPostDlg.h
# End Source File
# Begin Source File

SOURCE=.\scserveradmindlg.h
# End Source File
# Begin Source File

SOURCE=.\SCStrategyPointAdminDlg.h
# End Source File
# Begin Source File

SOURCE=.\SCUserAdminDlg.h
# End Source File
# Begin Source File

SOURCE=.\SelectItemDlg.h
# End Source File
# Begin Source File

SOURCE=.\Main\seteventmonsterdlg.h
# End Source File
# Begin Source File

SOURCE=.\Main\sethappyev.h
# End Source File
# Begin Source File

SOURCE=.\SetItemEv.h
# End Source File
# Begin Source File

SOURCE=.\SetLanguageDlg.h
# End Source File
# Begin Source File

SOURCE=.\Main\setlimitusercountdlg.h
# End Source File
# Begin Source File

SOURCE=.\Main\setpcbanghappyev.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\GridCtrl\TitleTip.h
# End Source File
# Begin Source File

SOURCE=.\Main\TrayIcon.h
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\WavePlayer.h
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\WayPointManager.h
# End Source File
# Begin Source File

SOURCE=..\..\Common\WinPacket.h
# End Source File
# Begin Source File

SOURCE=..\..\Common\WinSocket.h
# End Source File
# Begin Source File

SOURCE=.\Main\wrankingmanagement.h
# End Source File
# Begin Source File

SOURCE=.\Main\wrsevicesettingdlg.h
# End Source File
# Begin Source File

SOURCE=.\Main\wrupdateranking.h
# End Source File
# Begin Source File

SOURCE=..\..\Common\XOR_Lib.h
# End Source File
# Begin Source File

SOURCE=.\Main\xortestdlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\atum.ico
# End Source File
# Begin Source File

SOURCE=.\res\AtumAdminTool.ico
# End Source File
# Begin Source File

SOURCE=.\res\AtumAdminTool.rc2
# End Source File
# Begin Source File

SOURCE=.\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\CheckImage.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\00000062.wav
# End Source File
# Begin Source File

SOURCE=.\AtumAdminToolModifyList.txt
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project

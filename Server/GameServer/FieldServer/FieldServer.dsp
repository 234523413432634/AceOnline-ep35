# Microsoft Developer Studio Project File - Name="FieldServer" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=FIELDSERVER - WIN32 R_WIKIGAMES_ENG
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "FieldServer.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "FieldServer.mak" CFG="FIELDSERVER - WIN32 R_WIKIGAMES_ENG"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "FieldServer - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "FieldServer - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "FieldServer - Win32 D_Wikigames_Eng" (based on "Win32 (x86) Application")
!MESSAGE "FieldServer - Win32 R_Wikigames_Eng" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "FieldServer - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\output\FieldServer\Release"
# PROP Intermediate_Dir "..\..\output\FieldServer\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /Zi /O2 /I "." /I "..\..\Common" /I ".\Main" /I "..\CommonGameServer" /D "NDEBUG" /D "_MBCS" /D "_ATUM_FIELD_SERVER" /D "WIN32" /D "_WINDOWS" /D "_ATUM_SERVER" /D "_ATUM_LOAD_TEST" /YX"stdafx.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "NDEBUG"
# ADD RSC /l 0x412 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 winmm.lib D3dx8.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib QuestLoaderLib.lib /nologo /subsystem:windows /map:"..\..\Bin\Release/FieldServer.map" /debug /machine:I386 /out:"..\..\BuildResultSvr\Server\Bin\Release/FieldServer.exe" /libpath:"..\..\Lib" /MAPINFO:EXPORTS /MAPINFO:LINES
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "FieldServer - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\output\FieldServer\Debug"
# PROP Intermediate_Dir "..\..\output\FieldServer\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "." /I "..\..\Common" /I ".\Main" /I "..\CommonGameServer" /D "_MBCS" /D "_ATUM_FIELD_SERVER" /D "_ATUM_SERVER" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_ATUM_LOAD_TEST" /FR /YX"StdAfx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "_DEBUG"
# ADD RSC /l 0x412 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 winmm.lib D3dx8.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib QuestLoaderLibD.lib /nologo /subsystem:windows /incremental:no /map /debug /machine:I386 /nodefaultlib:"libcpmtd.lib" /out:"..\..\Bin\Debug/FieldServer.exe" /libpath:"..\..\Lib" /MAPINFO:EXPORTS /MAPINFO:LINES
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "FieldServer - Win32 D_Wikigames_Eng"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "FieldServer___Win32_D_Wikigames_Eng"
# PROP BASE Intermediate_Dir "FieldServer___Win32_D_Wikigames_Eng"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "FieldServer___Win32_D_Wikigames_Eng"
# PROP Intermediate_Dir "FieldServer___Win32_D_Wikigames_Eng"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "." /I "..\..\Common" /I ".\Main" /I "..\CommonGameServer" /D "_MBCS" /D "_ATUM_FIELD_SERVER" /D "_ATUM_SERVER" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_ATUM_LOAD_TEST" /FR /YX"StdAfx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "." /I "..\..\Common" /I ".\Main" /I "..\CommonGameServer" /I "..\..\Common\d3d8" /D "_MBCS" /D "_ATUM_FIELD_SERVER" /D "_ATUM_SERVER" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_ATUM_LOAD_TEST" /D "WIKIGAMES_ENG" /FR /YX"StdAfx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "_DEBUG"
# ADD RSC /l 0x412 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 winmm.lib D3dx8.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib QuestLoaderLibD.lib /nologo /subsystem:windows /incremental:no /map /debug /machine:I386 /nodefaultlib:"libcpmtd.lib" /out:"..\..\Bin\Debug/FieldServer.exe" /libpath:"..\..\Lib" /MAPINFO:EXPORTS /MAPINFO:LINES
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 winmm.lib D3dx8.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib QuestLoaderLibD.lib /nologo /subsystem:windows /incremental:no /map /debug /machine:I386 /nodefaultlib:"libcpmtd.lib" /out:"..\..\..\Output\Server\FieldServer_debug.exe" /libpath:"..\..\Lib" /MAPINFO:EXPORTS /MAPINFO:LINES
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "FieldServer - Win32 R_Wikigames_Eng"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "FieldServer___Win32_R_Wikigames_Eng"
# PROP BASE Intermediate_Dir "FieldServer___Win32_R_Wikigames_Eng"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "FieldServer___Win32_R_Wikigames_Eng"
# PROP Intermediate_Dir "FieldServer___Win32_R_Wikigames_Eng"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /O2 /I "." /I "..\..\Common" /I ".\Main" /I "..\CommonGameServer" /D "NDEBUG" /D "_MBCS" /D "_ATUM_FIELD_SERVER" /D "WIN32" /D "_WINDOWS" /D "_ATUM_SERVER" /D "_ATUM_LOAD_TEST" /YX"stdafx.h" /FD /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /MT /W3 /GX /Zi /O2 /I "." /I "..\..\Common" /I ".\Main" /I "..\CommonGameServer" /D "NDEBUG" /D "_MBCS" /D "_ATUM_FIELD_SERVER" /D "WIN32" /D "_WINDOWS" /D "_ATUM_SERVER" /D "_ATUM_LOAD_TEST" /D "WIKIGAMES_ENG" /Fr /YX"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "NDEBUG"
# ADD RSC /l 0x412 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 winmm.lib D3dx8.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib QuestLoaderLib.lib /nologo /subsystem:windows /map:"..\..\Bin\Release/FieldServer.map" /debug /machine:I386 /out:"..\..\BuildResultSvr\Server\Bin\Release/FieldServer.exe" /libpath:"..\..\Lib" /MAPINFO:EXPORTS /MAPINFO:LINES
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 winmm.lib D3dx8.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib QuestLoaderLib.lib /nologo /subsystem:windows /map:"..\..\Bin\Release/FieldServer.map" /debug /machine:I386 /out:"..\..\..\Output\Server\FieldServer.exe" /libpath:"..\..\Lib" /MAPINFO:EXPORTS /MAPINFO:LINES
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "FieldServer - Win32 Release"
# Name "FieldServer - Win32 Debug"
# Name "FieldServer - Win32 D_Wikigames_Eng"
# Name "FieldServer - Win32 R_Wikigames_Eng"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AllGuildItemManager.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\Security\ApexProxy.cpp
# End Source File
# Begin Source File

SOURCE=.\ArenaDeathMatchRoom.cpp
# End Source File
# Begin Source File

SOURCE=.\ArenaFieldWinSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\ArenaManager.cpp
# End Source File
# Begin Source File

SOURCE=.\ArenaTeam.cpp
# End Source File
# Begin Source File

SOURCE=.\ArenaTickManager.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\AtumDateTime.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\AtumDBHelper.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\AtumDBManager.cpp
# End Source File
# Begin Source File

SOURCE=.\main\AtumFieldDBManager.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\AtumLogSender.cpp
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

SOURCE=.\Main\BazaarManager.cpp
# End Source File
# Begin Source File

SOURCE=.\BillCrux_BillingLib.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\Billing_Yetime_Chn.cpp
# End Source File
# Begin Source File

SOURCE=.\Main\BunchCountableItemCount.cpp
# End Source File
# Begin Source File

SOURCE=.\Main\CallWarpEventManager.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\ChatBlockManager.cpp
# End Source File
# Begin Source File

SOURCE=.\Cinema.cpp
# End Source File
# Begin Source File

SOURCE=.\CityLeader.cpp
# End Source File
# Begin Source File

SOURCE=.\Main\CityWar.cpp
# End Source File
# Begin Source File

SOURCE=.\Main\CityWarManager.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\Config.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\CountdownChecker.cpp
# End Source File
# Begin Source File

SOURCE=.\Main\CouponManager.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\Debuff.cpp
# End Source File
# Begin Source File

SOURCE=.\DissolutionItemmanager.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\Dot.cpp
# End Source File
# Begin Source File

SOURCE=.\Main\DropItemManager.cpp
# End Source File
# Begin Source File

SOURCE=.\Main\EXPDivisionManager.cpp
# End Source File
# Begin Source File

SOURCE=.\Main\FieldCharacterQuest.cpp
# End Source File
# Begin Source File

SOURCE=.\Main\FieldDataManager.cpp
# End Source File
# Begin Source File

SOURCE=.\FieldDebuff.cpp
# End Source File
# Begin Source File

SOURCE=.\FieldDot.cpp
# End Source File
# Begin Source File

SOURCE=.\Main\FieldGlobal.cpp
# End Source File
# Begin Source File

SOURCE=.\main\FieldIOCP.cpp
# End Source File
# Begin Source File

SOURCE=.\main\FieldIOCPSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\Main\FieldIOCPSocket2.cpp
# End Source File
# Begin Source File

SOURCE=.\Main\FieldItemManager.cpp
# End Source File
# Begin Source File

SOURCE=.\Main\FieldMapChannel.cpp
# End Source File
# Begin Source File

SOURCE=.\main\FieldMapProject.cpp
# End Source File
# Begin Source File

SOURCE=.\main\FieldMapWorkspace.cpp
# End Source File
# Begin Source File

SOURCE=.\Main\FieldMonster.cpp
# End Source File
# Begin Source File

SOURCE=.\Main\FieldODBC.cpp
# End Source File
# Begin Source File

SOURCE=.\Main\FieldParty.cpp
# End Source File
# Begin Source File

SOURCE=.\FieldServer.cpp
# End Source File
# Begin Source File

SOURCE=.\FieldServer.rc
# End Source File
# Begin Source File

SOURCE=.\Main\FieldSkillManager.cpp
# End Source File
# Begin Source File

SOURCE=.\Main\FieldTickManager.cpp
# End Source File
# Begin Source File

SOURCE=.\Main\FieldTimerManager.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\GameDataLast.cpp
# End Source File
# Begin Source File

SOURCE=.\Main\GameEventManager.cpp
# End Source File
# Begin Source File

SOURCE=.\Main\GeneralRequestHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\GenericHTTPClient.cpp
# End Source File
# Begin Source File

SOURCE=.\GiveItemManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\Global.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\GlobalFunc.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\GlobalGameServer.cpp
# End Source File
# Begin Source File

SOURCE=.\GuildDamageManager.cpp
# End Source File
# Begin Source File

SOURCE=.\GuildItemManager.cpp
# End Source File
# Begin Source File

SOURCE=.\Main\GuildWar.cpp
# End Source File
# Begin Source File

SOURCE=.\Main\HappyHourEventManager.cpp
# End Source File
# Begin Source File

SOURCE=.\main\IMWinSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\InfinityBase.cpp
# End Source File
# Begin Source File

SOURCE=.\InfinityBossrush.cpp
# End Source File
# Begin Source File

SOURCE=.\InfinityDefence.cpp
# End Source File
# Begin Source File

SOURCE=.\InfinityManager.cpp
# End Source File
# Begin Source File

SOURCE=.\InfinityMapManager.cpp
# End Source File
# Begin Source File

SOURCE=.\InfinityMShipBattle.cpp
# End Source File
# Begin Source File

SOURCE=.\InfinityTickManager.cpp
# End Source File
# Begin Source File

SOURCE=.\Main\InflRateManager.cpp
# End Source File
# Begin Source File

SOURCE=.\Main\InflWarManager.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\InnovaLibrary.cpp
# End Source File
# Begin Source File

SOURCE=.\InvokingItemInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\InvokingItemManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\IOCP.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\IOCPSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\LetterManager.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\LoadLibrary.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\Localization.cpp
# End Source File
# Begin Source File

SOURCE=.\Main\LogWinSocket.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\MapBlock.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\MapChannel.cpp
# End Source File
# Begin Source File

SOURCE=.\Main\MapOwnership.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\MapProject.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\MapWorkspace.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\md5_lib_src.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\Monster.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\MonsterDBAccess.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\MTAutoCriticalSection.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\MTCriticalSection.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\NPCScripts.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\ODBCStatement.cpp
# End Source File
# Begin Source File

SOURCE=.\OutPost.cpp
# End Source File
# Begin Source File

SOURCE=.\OutPostManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\Overlapped.cpp
# End Source File
# Begin Source File

SOURCE=.\PCBangIPManager.cpp
# End Source File
# Begin Source File

SOURCE=.\PetDataManager.cpp
# End Source File
# Begin Source File

SOURCE=.\main\PreWinSocket.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\Quest.cpp
# End Source File
# Begin Source File

SOURCE=.\Main\QuestMatching.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\QueueINT.cpp
# End Source File
# Begin Source File

SOURCE=.\Main\Racing.cpp
# End Source File
# Begin Source File

SOURCE=.\Main\RacingDemon.cpp
# End Source File
# Begin Source File

SOURCE=.\Revision.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\SecurityManager.cpp
# End Source File
# Begin Source File

SOURCE=.\Main\ServicePauseManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\sha256.cpp
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

SOURCE=..\..\Common\ThreadCheck.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\TickManager.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\UserVariable.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\VMem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\VMemPool.cpp
# End Source File
# Begin Source File

SOURCE=.\WarContributionCalculation.cpp
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

SOURCE=.\Main\WRankingFame.cpp
# End Source File
# Begin Source File

SOURCE=.\Main\WRankingFameManager.cpp
# End Source File
# Begin Source File

SOURCE=.\Main\WRankingLevel.cpp
# End Source File
# Begin Source File

SOURCE=.\Main\WRankingLevelManager.cpp
# End Source File
# Begin Source File

SOURCE=.\Main\WRankingManager.cpp
# End Source File
# Begin Source File

SOURCE=.\Main\WRankingPVP.cpp
# End Source File
# Begin Source File

SOURCE=.\Main\WRankingPVPManager.cpp
# End Source File
# Begin Source File

SOURCE=.\Main\WRankingServiceManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\XOR_Lib.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\Security\XTrap4Server.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\Security\zwave_sdk_linker.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AllGuildItemManager.h
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\Security\ApexProxy.h
# End Source File
# Begin Source File

SOURCE=.\ArenaDeathMatchRoom.h
# End Source File
# Begin Source File

SOURCE=.\ArenaFieldWinSocket.h
# End Source File
# Begin Source File

SOURCE=.\ArenaManager.h
# End Source File
# Begin Source File

SOURCE=.\ArenaTeam.h
# End Source File
# Begin Source File

SOURCE=.\ArenaTickManager.h
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\AtumDataLoader.h
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\AtumDateTime.h
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\AtumDBHelper.h
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\AtumDBManager.h
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\AtumError.h
# End Source File
# Begin Source File

SOURCE=.\main\AtumFieldDBManager.h
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\AtumLogSender.h
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\AtumParam.h
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\AtumProtocol.h
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\AtumSJ.h
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\AtumThread.h
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\AtumTime.h
# End Source File
# Begin Source File

SOURCE=.\Main\BazaarManager.h
# End Source File
# Begin Source File

SOURCE=.\BillCrux_BillingLib.h
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\Billing_Yetime_Chn.h
# End Source File
# Begin Source File

SOURCE=.\Main\BunchCountableItemCount.h
# End Source File
# Begin Source File

SOURCE=.\Main\CallWarpEventManager.h
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\ChatBlockManager.h
# End Source File
# Begin Source File

SOURCE=.\Cinema.h
# End Source File
# Begin Source File

SOURCE=.\CityLeader.h
# End Source File
# Begin Source File

SOURCE=.\Main\CityWar.h
# End Source File
# Begin Source File

SOURCE=.\Main\CityWarManager.h
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\Config.h
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\CountdownChecker.h
# End Source File
# Begin Source File

SOURCE=.\Main\CouponManager.h
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\Debuff.h
# End Source File
# Begin Source File

SOURCE=..\..\Common\DefineGlobal.h
# End Source File
# Begin Source File

SOURCE=.\DissolutionItemmanager.h
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\Dot.h
# End Source File
# Begin Source File

SOURCE=.\Main\DropItemManager.h
# End Source File
# Begin Source File

SOURCE=.\Main\EXPDivisionManager.h
# End Source File
# Begin Source File

SOURCE=.\Main\FieldCharacterQuest.h
# End Source File
# Begin Source File

SOURCE=.\Main\FieldDataManager.h
# End Source File
# Begin Source File

SOURCE=.\FieldDebuff.h
# End Source File
# Begin Source File

SOURCE=.\FieldDot.h
# End Source File
# Begin Source File

SOURCE=.\Main\FieldGlobal.h
# End Source File
# Begin Source File

SOURCE=.\main\FieldIOCP.h
# End Source File
# Begin Source File

SOURCE=.\main\FieldIOCPSocket.h
# End Source File
# Begin Source File

SOURCE=.\Main\FieldItemManager.h
# End Source File
# Begin Source File

SOURCE=.\Main\FieldMapChannel.h
# End Source File
# Begin Source File

SOURCE=.\main\FieldMapProject.h
# End Source File
# Begin Source File

SOURCE=.\main\FieldMapWorkspace.h
# End Source File
# Begin Source File

SOURCE=.\Main\FieldMonster.h
# End Source File
# Begin Source File

SOURCE=.\Main\FieldODBC.h
# End Source File
# Begin Source File

SOURCE=.\Main\FieldParty.h
# End Source File
# Begin Source File

SOURCE=.\FieldServer.h
# End Source File
# Begin Source File

SOURCE=.\Main\FieldSkillManager.h
# End Source File
# Begin Source File

SOURCE=.\Main\FieldTickManager.h
# End Source File
# Begin Source File

SOURCE=.\Main\FieldTimerManager.h
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\GameDataLast.h
# End Source File
# Begin Source File

SOURCE=.\Main\GameEventManager.h
# End Source File
# Begin Source File

SOURCE=.\Main\GeneralRequestHandler.h
# End Source File
# Begin Source File

SOURCE=.\GiveItemManager.h
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\GlobalGameServer.h
# End Source File
# Begin Source File

SOURCE=.\GuildDamageManager.h
# End Source File
# Begin Source File

SOURCE=.\GuildItemManager.h
# End Source File
# Begin Source File

SOURCE=.\Main\GuildWar.h
# End Source File
# Begin Source File

SOURCE=.\Main\HappyHourEventManager.h
# End Source File
# Begin Source File

SOURCE=.\main\IMWinSocket.h
# End Source File
# Begin Source File

SOURCE=.\InfinityBase.h
# End Source File
# Begin Source File

SOURCE=.\InfinityBossrush.h
# End Source File
# Begin Source File

SOURCE=.\InfinityDefence.h
# End Source File
# Begin Source File

SOURCE=.\InfinityManager.h
# End Source File
# Begin Source File

SOURCE=.\InfinityMapManager.h
# End Source File
# Begin Source File

SOURCE=.\InfinityMShipBattle.h
# End Source File
# Begin Source File

SOURCE=.\InfinityTickManager.h
# End Source File
# Begin Source File

SOURCE=.\Main\InflRateManager.h
# End Source File
# Begin Source File

SOURCE=.\Main\InflWarManager.h
# End Source File
# Begin Source File

SOURCE=.\InvokingItemInfo.h
# End Source File
# Begin Source File

SOURCE=.\InvokingItemManager.h
# End Source File
# Begin Source File

SOURCE=..\..\Common\IOCP.h
# End Source File
# Begin Source File

SOURCE=.\LetterManager.h
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\Localization.h
# End Source File
# Begin Source File

SOURCE=.\Main\LogWinSocket.h
# End Source File
# Begin Source File

SOURCE=.\Main\MallAgentConnect.h
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\MapBlock.h
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\MapChannel.h
# End Source File
# Begin Source File

SOURCE=.\Main\MapOwnership.h
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\MapProject.h
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\MapWorkspace.h
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\Monster.h
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\MonsterDBAccess.h
# End Source File
# Begin Source File

SOURCE=..\..\Common\mt_stl.h
# End Source File
# Begin Source File

SOURCE=..\..\Common\MTAutoCriticalSection.h
# End Source File
# Begin Source File

SOURCE=..\..\Common\MTCriticalSection.h
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\ODBCStatement.h
# End Source File
# Begin Source File

SOURCE=.\OutPost.h
# End Source File
# Begin Source File

SOURCE=.\OutPostManager.h
# End Source File
# Begin Source File

SOURCE=.\PCBangIPManager.h
# End Source File
# Begin Source File

SOURCE=.\PetDataManager.h
# End Source File
# Begin Source File

SOURCE=.\main\PreWinSocket.h
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\Quest.h
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\QuestLoaderParser.h
# End Source File
# Begin Source File

SOURCE=.\Main\QuestMatching.h
# End Source File
# Begin Source File

SOURCE=..\..\Common\QueueINT.h
# End Source File
# Begin Source File

SOURCE=.\Main\Racing.h
# End Source File
# Begin Source File

SOURCE=.\Main\RacingDemon.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\Revision.h
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\SecurityManager.h
# End Source File
# Begin Source File

SOURCE=.\Main\ServicePauseManager.h
# End Source File
# Begin Source File

SOURCE=..\..\Common\sha256.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\StringDefineSecurityCommand.h
# End Source File
# Begin Source File

SOURCE=..\..\Common\SystemLogManager.h
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\TickManager.h
# End Source File
# Begin Source File

SOURCE=..\CommonGameServer\UserVariable.h
# End Source File
# Begin Source File

SOURCE=..\..\Common\VMem.h
# End Source File
# Begin Source File

SOURCE=..\..\Common\VMemPool.h
# End Source File
# Begin Source File

SOURCE=.\WarContributionCalculation.h
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

SOURCE=.\Main\WRankingFame.h
# End Source File
# Begin Source File

SOURCE=.\Main\WRankingFameManager.h
# End Source File
# Begin Source File

SOURCE=.\Main\WRankingLevel.h
# End Source File
# Begin Source File

SOURCE=.\Main\WRankingLevelManager.h
# End Source File
# Begin Source File

SOURCE=.\Main\WRankingManager.h
# End Source File
# Begin Source File

SOURCE=.\Main\WRankingPVP.h
# End Source File
# Begin Source File

SOURCE=.\Main\WRankingPVPManager.h
# End Source File
# Begin Source File

SOURCE=.\Main\WRankingServiceManager.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\FieldServer.ico
# End Source File
# Begin Source File

SOURCE=.\small.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\FieldServerModifyList.txt
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project

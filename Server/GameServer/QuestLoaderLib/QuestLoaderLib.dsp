# Microsoft Developer Studio Project File - Name="QuestLoaderLib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=QuestLoaderLib - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "QuestLoaderLib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "QuestLoaderLib.mak" CFG="QuestLoaderLib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "QuestLoaderLib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "QuestLoaderLib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "QuestLoaderLib - Win32 R_Wikigames_Eng" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "QuestLoaderLib - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\output\QuestLoaderLib\Release"
# PROP Intermediate_Dir "..\..\output\QuestLoaderLib\Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "." /I "..\..\Common" /I "..\..\GameServer\CommonGameServer" /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "_ATUM_DATA_LOADER" /YX /FD /c
# ADD BASE RSC /l 0x412 /d "NDEBUG"
# ADD RSC /l 0x412 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\BuildResultSvr\Server\Lib\QuestLoaderLib.lib"

!ELSEIF  "$(CFG)" == "QuestLoaderLib - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\output\QuestLoaderLib\Debug"
# PROP Intermediate_Dir "..\..\output\QuestLoaderLib\Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "." /I "..\..\Common" /I "..\..\GameServer\CommonGameServer" /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "_ATUM_DATA_LOADER" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x412 /d "_DEBUG"
# ADD RSC /l 0x412 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\Lib\QuestLoaderLibD.lib"

!ELSEIF  "$(CFG)" == "QuestLoaderLib - Win32 R_Wikigames_Eng"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "QuestLoaderLib___Win32_R_Wikigames_Eng"
# PROP BASE Intermediate_Dir "QuestLoaderLib___Win32_R_Wikigames_Eng"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "QuestLoaderLib___Win32_R_Wikigames_Eng"
# PROP Intermediate_Dir "QuestLoaderLib___Win32_R_Wikigames_Eng"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /I "." /I "..\..\Common" /I "..\..\GameServer\CommonGameServer" /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "_ATUM_DATA_LOADER" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "." /I "..\..\Common" /I "..\..\GameServer\CommonGameServer" /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "_ATUM_DATA_LOADER" /D "WIKIGAMES_ENG" /YX /FD /c
# ADD BASE RSC /l 0x412 /d "NDEBUG"
# ADD RSC /l 0x412 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\BuildResultSvr\Server\Lib\QuestLoaderLib.lib"
# ADD LIB32 /nologo /out:"..\..\BuildResultSvr\Server\Lib\QuestLoaderLib.lib"

!ENDIF 

# Begin Target

# Name "QuestLoaderLib - Win32 Release"
# Name "QuestLoaderLib - Win32 Debug"
# Name "QuestLoaderLib - Win32 R_Wikigames_Eng"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\QuestLoader\QuestLoader.cpp
# End Source File
# Begin Source File

SOURCE=..\QuestLoader\QuestLoader.l.cpp
# End Source File
# Begin Source File

SOURCE=..\QuestLoader\QuestLoaderParser.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\QuestLoader\QuestLoader.cpp.h
# End Source File
# Begin Source File

SOURCE=..\..\GameServer\CommonGameServer\QuestLoaderParser.h
# End Source File
# End Group
# End Target
# End Project

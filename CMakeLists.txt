cmake_minimum_required(VERSION 3.1)

project(BSPFactory)

set(SRC_APP
    AboutDlg.cpp
    ApplicationProc.cpp
    BuildMap.cpp
    Call.cpp
    CallCenter.cpp
    CApplication.cpp
    CompileSettings.cpp
    ConfigProc.cpp
    CWin.cpp
    DescriptionManager.cpp
    Dialog.cpp
    InfoDlg.cpp
    InputBox.cpp
    MapProc.cpp
    Option.cpp
    OptionDescription.cpp
    Param.cpp
    Setting.cpp
    SettingVal.cpp
    Tool.cpp
    ToolDescription.cpp
    WinMain.cpp
    XMLParser.cpp
    AboutDlg.h
    BuildMap.h
    Call.h
    CallCenter.h
    CApplication.h
    CompileSettings.h
    CWin.h
    DescriptionManager.h
    Dialog.h
    InfoDlg.h
    InputBox.h
    Option.h
    OptionDescription.h
    Param.h
    resource.h
    Setting.h
    SettingVal.h
    Tool.h
    ToolDescription.h
    XMLParser.h
    )

link_directories(../ControlLib/package/lib)

add_executable(BSPFactory
    ${SRC_APP}
	)

target_include_directories(BSPFactory
    PRIVATE ../ControlLib/package/include
    )

target_compile_features(BSPFactory
	PRIVATE cxx_auto_type
	PRIVATE cxx_nullptr
	PRIVATE cxx_range_for
	)

target_link_libraries(BSPFactory
    ws2_32 Controls
    )

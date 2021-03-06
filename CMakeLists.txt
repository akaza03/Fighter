#/****************************************************************************
# Copyright (c) 2013-2014 cocos2d-x.org
# Copyright (c) 2015-2017 Chukong Technologies Inc.
#
# http://www.cocos2d-x.org
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
# ****************************************************************************/

cmake_minimum_required(VERSION 3.6)

set(APP_NAME Fighter)

project(${APP_NAME})



set(CK_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/Classes/cricket)

include_directories(
        ${CK_ROOT}/inc
)

link_directories(
        ${CK_ROOT}/lib/android/ndk/${ANDROID_ABI}/debug
)
link_libraries(
        ${CK_ROOT}/lib/android/ndk/${ANDROID_ABI}/debug/libck.a
)

include(AndroidNdkModules)
android_ndk_import_module_cpufeatures()

target_link_libraries(
        cpufeatures
)




set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cocos2d)
set(CMAKE_MODULE_PATH ${COCOS2DX_ROOT_PATH}/cmake/Modules/)

include(CocosBuildSet)
add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos ${ENGINE_BINARY_PATH}/cocos/core)

# record sources, headers, resources...
set(GAME_SOURCE)
set(GAME_HEADER)

set(GAME_RES_FOLDER
    "${CMAKE_CURRENT_SOURCE_DIR}/Resources"
    )
if(APPLE OR WINDOWS)
    cocos_mark_multi_resources(common_res_files RES_TO "Resources" FOLDERS ${GAME_RES_FOLDER})
endif()

# add cross-platforms source files and header files 
list(APPEND GAME_SOURCE
     Classes/AppDelegate.cpp
     Classes/CricketJni/CricketJni.cpp
     Classes/Effekseer/Effekseer.cpp
     Classes/Effekseer/EffekseerNative.cpp
     Classes/Effekseer/EffekseerRendererNative.cpp
     Classes/input/OprtState.cpp
     Classes/input/OprtKey.cpp
     Classes/input/OprtTouch.cpp
     Classes/input/UseKey.cpp
     Classes/manager/AnimManager.cpp
     Classes/manager/ResourceManager.cpp
     Classes/manager/ScoreManager.cpp
     Classes/manager/AudioManager.cpp
     Classes/manager/EffManager.cpp
     Classes/map/MapMaker.cpp
     Classes/scene/TitleScene.cpp
     Classes/scene/GameMain.cpp
     Classes/unit/Character.cpp
     Classes/unit/Enemy.cpp
     Classes/unit/Player.cpp
     Classes/module/ActModule.cpp
     Classes/module/AnimUpdate.cpp
     Classes/module/Attack.cpp
     Classes/module/Blow.cpp
     Classes/module/DamageCheck.cpp
     Classes/module/DirCheck.cpp
     Classes/module/Move.cpp
     Classes/module/OldKeyUpdate.cpp
     Classes/module/SetPos.cpp
     Classes/UIClass/Number.cpp
     )
list(APPEND GAME_HEADER
     Classes/AppDelegate.h
     Classes/CricketJni/CricketJni.h
     Classes/Effekseer/Effekseer.h
     Classes/Effekseer/EffekseerNative.h
     Classes/Effekseer/EffekseerRendererNative.h
     Classes/input/OprtState.h
     Classes/input/OprtKey.h
     Classes/input/OprtTouch.h
     Classes/input/UseKey.h
     Classes/manager/AnimManager.h
     Classes/manager/ResourceManager.h
     Classes/manager/ScoreManager.h
     Classes/manager/AudioManager.h
     Classes/manager/EffManager.h
     Classes/map/MapMaker.h
     Classes/scene/TitleScene.h
     Classes/scene/GameMain.h
     Classes/unit/Character.h
     Classes/unit/Enemy.h
     Classes/unit/Player.h
     Classes/unit/charaStruct.h
     Classes/module/ActModule.h
     Classes/module/AnimUpdate.h
     Classes/module/Attack.h
     Classes/module/Blow.h
     Classes/module/DamageCheck.h
     Classes/module/DirCheck.h
     Classes/module/Move.h
     Classes/module/OldKeyUpdate.h
     Classes/module/SetPos.h
     Classes/module/ActSet.h
     Classes/UIClass/Number.h
     )

if(ANDROID)
    # change APP_NAME to the share library name for Android, it's value depend on AndroidManifest.xml
    set(APP_NAME MyGame)
    list(APPEND GAME_SOURCE
         proj.android/app/jni/hellocpp/main.cpp
         )
elseif(LINUX)
    list(APPEND GAME_SOURCE
         proj.linux/main.cpp
         )
elseif(WINDOWS)
    list(APPEND GAME_HEADER
         proj.win32/main.h
         proj.win32/resource.h
         )
    list(APPEND GAME_SOURCE
         proj.win32/main.cpp
         proj.win32/game.rc
         ${common_res_files}
         )
elseif(APPLE)
    if(IOS)
        list(APPEND GAME_HEADER
             proj.ios_mac/ios/AppController.h
             proj.ios_mac/ios/RootViewController.h
             )
        set(APP_UI_RES
            proj.ios_mac/ios/LaunchScreen.storyboard
            proj.ios_mac/ios/LaunchScreenBackground.png
            proj.ios_mac/ios/Images.xcassets
            )
        list(APPEND GAME_SOURCE
             proj.ios_mac/ios/main.m
             proj.ios_mac/ios/AppController.mm
             proj.ios_mac/ios/RootViewController.mm
             proj.ios_mac/ios/Prefix.pch
             ${APP_UI_RES}
             )
    elseif(MACOSX)
        set(APP_UI_RES
            proj.ios_mac/mac/Icon.icns
            proj.ios_mac/mac/Info.plist
            )
        list(APPEND GAME_SOURCE
             proj.ios_mac/mac/main.cpp
             proj.ios_mac/mac/Prefix.pch
             ${APP_UI_RES}
             )
    endif()
    list(APPEND GAME_SOURCE ${common_res_files})
endif()

# mark app complie info and libs info
set(all_code_files
    ${GAME_HEADER}
    ${GAME_SOURCE}
    )
if(NOT ANDROID)
    add_executable(${APP_NAME} ${all_code_files})
else()
    add_library(${APP_NAME} SHARED ${all_code_files})
    add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos/platform/android ${ENGINE_BINARY_PATH}/cocos/platform)
    target_link_libraries(${APP_NAME} -Wl,--whole-archive cpp_android_spec -Wl,--no-whole-archive)
endif()

target_link_libraries(${APP_NAME} cocos2d)
target_include_directories(${APP_NAME}
        PRIVATE Classes
        PRIVATE ${COCOS2DX_ROOT_PATH}/cocos/audio/include/
)

# mark app resources
setup_cocos_app_config(${APP_NAME})
if(APPLE)
    set_target_properties(${APP_NAME} PROPERTIES RESOURCE "${APP_UI_RES}")
    if(MACOSX)
        set_target_properties(${APP_NAME} PROPERTIES
                              MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/proj.ios_mac/mac/Info.plist"
                              )
    elseif(IOS)
        cocos_pak_xcode(${APP_NAME} INFO_PLIST "iOSBundleInfo.plist.in")
        set_xcode_property(${APP_NAME} ASSETCATALOG_COMPILER_APPICON_NAME "AppIcon")
        set_xcode_property(${APP_NAME} DEVELOPMENT_TEAM "")
        set_xcode_property(${APP_NAME} CODE_SIGN_IDENTITY "iPhone Developer")
    endif()
elseif(WINDOWS)
    cocos_copy_target_dll(${APP_NAME})
endif()

if(LINUX OR WINDOWS)
    set(APP_RES_DIR "$<TARGET_FILE_DIR:${APP_NAME}>/Resources")
    cocos_copy_target_res(${APP_NAME} COPY_TO ${APP_RES_DIR} FOLDERS ${GAME_RES_FOLDER})
endif()

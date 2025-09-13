; ======================================
; TransientPepper 설치 스크립트 (VST3/AAX 자동 배포)
; ======================================

[Setup]
AppName=TransientPepper
AppVersion=1.0
DefaultDirName={pf}\TransientPepper
DefaultGroupName=TransientPepper
OutputBaseFilename=TransientPepperSetup
Compression=lzma
SolidCompression=yes
PrivilegesRequired=admin

; --------------------------------------
; 빌드 폴더 경로 설정
; (여기에 JUCE Release 빌드 경로를 맞춰주세요)
#define BUILD_RELEASE_PATH "C:\Path\To\Your\JUCE\Build\Release"

[Files]
; VST3 플러그인 복사
Source: "{#BUILD_RELEASE_PATH}\JETransientPepper.vst3"; DestDir: "{commonfiles}\VST3"; Flags: ignoreversion

; AAX 플러그인 복사
Source: "{#BUILD_RELEASE_PATH}\JETransientPepper.aaxplugin"; DestDir: "{commonfiles}\Avid\Audio\Plug-Ins"; Flags: ignoreversion recursesubdirs

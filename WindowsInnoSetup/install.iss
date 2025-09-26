; ======================================
; TransientPepper 설치 스크립트 (VST3/AAX 자동 배포)
; ======================================

[Setup]
AppName=JoEunsoo Transient Pepper
AppVersion=1.0.3
DefaultDirName={pf}
DefaultGroupName=JoEunsoo
OutputBaseFilename=JETransientPepperSetup
Compression=lzma
SolidCompression=yes
PrivilegesRequired=admin
UsePreviousAppDir=no
DisableDirPage=yes

LicenseFile=../pkg/Resources/License.txt
; --------------------------------------
; 빌드 폴더 경로 설정
; (여기에 JUCE Release 빌드 경로를 맞춰주세요)
#define BUILD_RELEASE_PATH "D:\juce\projects\plugin-transient-pepper\Builds\VisualStudio2022\x64\Release\VST3\JE Transient Pepper.vst3\Contents\x86_64-win"

[Files]
Source: "{#BUILD_RELEASE_PATH}\JE Transient Pepper.vst3"; DestDir: "{code:GetVST3Dir}"; Flags: ignoreversion

[Code]
var
  VST3PathPage: TInputDirWizardPage;

procedure InitializeWizard;
begin
  VST3PathPage := CreateInputDirPage(wpLicense,
    'VST3 Installation Folder',
    '',
    'Choose the folder where the VST3 plugin will be installed.',
    False, '');
    
  // Add a directory selection field to the page
  VST3PathPage.Add('VST3 Installation Folder:');

  // Set an initial default value for the directory (optional)
  VST3PathPage.Values[0] := ExpandConstant('{cf64}\VST3');
end;

procedure CurStepChanged(CurStep: TSetupStep);
begin
  if CurStep = ssInstall then
  begin
    DeleteFile(ExpandConstant('{cf64}\VST3\JETransientPepper.vst3'));
  end;
end;

// [Files]에서 참조할 함수
function GetVST3Dir(Value: string): string;
begin
  Result := VST3PathPage.Values[0];

  // 폴더가 없으면 생성
  if not DirExists(Result) then
    ForceDirectories(Result);
end;
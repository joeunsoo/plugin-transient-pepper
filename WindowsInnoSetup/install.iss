; ======================================
; TransientPepper 설치 스크립트 (VST3/AAX 자동 배포)
; ======================================

[Setup]
AppName=JoEunsoo Transient Pepper
AppVersion=1.0.4
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
#define BUILD_RELEASE_VST3_PATH "D:\juce\projects\plugin-transient-pepper\Builds\VisualStudio2022\x64\Release\VST3\JE Transient Pepper.vst3\Contents\x86_64-win"
#define BUILD_RELEASE_AAX_PATH  "D:\juce\projects\plugin-transient-pepper\Builds\VisualStudio2022\x64\Release\AAX\JE Transient Pepper.aaxplugin\Contents\x64"

[Files]
Source: "{#BUILD_RELEASE_VST3_PATH}\JE Transient Pepper.vst3"; DestDir: "{code:GetVST3Dir}"; Flags: ignoreversion recursesubdirs; Check: ShouldInstallVST3
Source: "{#BUILD_RELEASE_AAX_PATH}\JE Transient Pepper.aaxplugin"; DestDir: "{code:GetAAXDir}";  Flags: ignoreversion recursesubdirs; Check: ShouldInstallAAX

[Code]
var
  FormatSelectPage: TWizardPage;
  InstallVST3CheckBox: TNewCheckBox;
  InstallAAXCheckBox: TNewCheckBox;
  
  VST3PathPage: TInputDirWizardPage;
  AAXPathPage: TInputDirWizardPage;

procedure InitializeWizard;
begin
  { 1) Format selection page }
  FormatSelectPage := CreateCustomPage(wpLicense,
    'Select Formats to Install',
    'Choose which plugin formats to install (VST3 / AAX).');

  InstallVST3CheckBox := TNewCheckBox.Create(WizardForm);
  InstallVST3CheckBox.Parent := FormatSelectPage.Surface;
  InstallVST3CheckBox.Caption := 'Install VST3';
  InstallVST3CheckBox.Checked := True;  { default: install }

  InstallAAXCheckBox := TNewCheckBox.Create(WizardForm);
  InstallAAXCheckBox.Parent := FormatSelectPage.Surface;
  InstallAAXCheckBox.Caption := 'Install AAX';
  InstallAAXCheckBox.Top := InstallVST3CheckBox.Top + InstallVST3CheckBox.Height + ScaleY(8);
  InstallAAXCheckBox.Checked := False;
  
  { 2) VST3 path input page }
  VST3PathPage := CreateInputDirPage(FormatSelectPage.ID,
    'VST3 Installation Folder',
    '',
    'Choose the folder where the VST3 plugin will be installed.', False, '');

  VST3PathPage.Add('VST3 installation folder:');

  { Windows standard VST3 (64-bit, all users): C:\Program Files\Common Files\VST3 → (cf64)\VST3 }
  VST3PathPage.Values[0] := ExpandConstant('{cf64}\VST3');

  { 3) AAX path input page }
  AAXPathPage := CreateInputDirPage(VST3PathPage.ID,
    'AAX Installation Folder',
    '',
    'Choose the folder where the AAX plugin will be installed.', False, '');

  AAXPathPage.Add('AAX installation folder:');

  { Windows standard AAX (64-bit): C:\Program Files\Common Files\Avid\Audio\Plug-Ins }
  AAXPathPage.Values[0] := ExpandConstant('{cf64}\Avid\Audio\Plug-Ins');
end;

function ShouldInstallVST3: Boolean;
begin
  Result := InstallVST3CheckBox.Checked;
end;

function ShouldInstallAAX: Boolean;
begin
  Result := InstallAAXCheckBox.Checked;
end;

function GetVST3Dir(Value: string): string;
begin
  Result := VST3PathPage.Values[0];
  { Ensure folder exists }
  if not DirExists(Result) then
    ForceDirectories(Result);
end;

function GetAAXDir(Value: string): string;
begin
  Result := AAXPathPage.Values[0];
  { Ensure folder exists }
  if not DirExists(Result) then
    ForceDirectories(Result);
end;

procedure CurStepChanged(CurStep: TSetupStep);
var
  Vst3Target, AaxTarget: string;
begin
  if CurStep = ssInstall then
  begin
    { Pre-clean existing bundles with same names }
    if ShouldInstallVST3 then
    begin
      Vst3Target := GetVST3Dir('');
      if DirExists(Vst3Target + '\JE Transient Pepper.vst3') then
        DelTree(Vst3Target + '\JE Transient Pepper.vst3', True, True, True);
    end;

    if ShouldInstallAAX then
    begin
      AaxTarget := GetAAXDir('');
      if DirExists(AaxTarget + '\JE Transient Pepper.aaxplugin') then
        DelTree(AaxTarget + '\JE Transient Pepper.aaxplugin', True, True, True);
    end;
  end;
end;

function NextButtonClick(CurPageID: Integer): Boolean;
begin
  Result := True;

  { Guard: at least one format must be selected }
  if (CurPageID = FormatSelectPage.ID) then
  begin
    if (not InstallVST3CheckBox.Checked) and (not InstallAAXCheckBox.Checked) then
    begin
      MsgBox('Please select at least one format to install (VST3 or AAX).', mbError, MB_OK);
      Result := False;
      exit;
    end;
  end;
end;
; Inno Setup script. Expects the files to ship in .build/stage (see package.sh).
#define AppVersion GetEnv("MINIPLANER_VERSION")

[Setup]
AppId={{ABBF2839-E486-4ED4-ACAD-69DA91287F80}
AppName=MiniPlaner
AppVersion={#AppVersion}
AppPublisher=Yannik Schälte
DefaultDirName={userdocs}\MiniPlaner
DisableProgramGroupPage=yes
PrivilegesRequired=lowest
SetupIconFile=..\..\src\img\minis.ico
OutputDir=..\..\.build\dist
OutputBaseFilename=MiniPlaner-Setup
Compression=lzma
SolidCompression=yes

[Languages]
Name: "german"; MessagesFile: "compiler:Languages\German.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"

[Files]
Source: "..\..\.build\stage\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs

[Icons]
Name: "{autodesktop}\MiniPlaner"; Filename: "{app}\miniplaner.exe"; WorkingDir: "{app}"; Tasks: desktopicon

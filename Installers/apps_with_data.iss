; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

[Setup]
AppName=VTP Software
AppVerName=VTP Software 1.05 (2011.07.08)
AppPublisher=Virtual Terrain Project
AppPublisherURL=http://vterrain.org/
AppSupportURL=http://vterrain.org/
AppUpdatesURL=http://vterrain.org/
DefaultDirName={pf}\VTP
DefaultGroupName=VTP
AllowNoIcons=yes
LicenseFile=C:\VTP\license.txt
OutputBaseFilename=setup_vtp
OutputDir=C:\Distrib
; We need the following because Windows won't turn Registry settings into Enviroment variables w/o a reboot
AlwaysRestart=yes

[Types]
Name: "standard"; Description: "Standard installation"; Flags: iscustom

[Components]
Name: "main"; Description: "The VTP applications"; Types: standard
Name: "data"; Description: "Data used by the applications"; Types: standard
Name: "docs"; Description: "Documentation for the applications"; Types: standard
Name: "proj"; Description: "Data files for coordinate systems (GDAL/PROJ.4)"; Types: standard
Name: "dlls"; Description: "Third-party DLL files (wxWidgets, OSG, etc.)"; Types: standard

[Tasks]
Name: env; Description: "Set environment variables for coordinate system data files"; GroupDescription: "Environment variables:"; Components: proj

[Registry]
Root: HKLM; Subkey: "SYSTEM\CurrentControlSet\Control\Session Manager\Environment"; ValueType: string; ValueName: "GDAL_DATA"; ValueData: "{app}\GDAL-data"; Components: proj
Root: HKLM; Subkey: "SYSTEM\CurrentControlSet\Control\Session Manager\Environment"; ValueType: string; ValueName: "PROJ_LIB"; ValueData: "{app}\PROJ4-data"; Components: proj

[Files]
;Source: "C:\VTP\TerrainApps\BExtractor\license.txt"; DestDir: "{app}/Apps"; Flags: ignoreversion; Components: main

;Source: "C:\VTP\TerrainApps\BExtractor\Release\BExtractor.exe"; DestDir: "{app}\Apps"; Flags: ignoreversion; Components: main
;Source: "C:\VTP\TerrainApps\BExtractor\BE.ini"; DestDir: "{app}\Apps"; Flags: ignoreversion; Components: main
;Source: "C:\VTP\TerrainApps\BExtractor\Docs\index.html"; DestDir: "{app}/Docs/BExtractor"; Flags: ignoreversion; Components: docs

Source: "C:\VTP\vc9\TerrainApps\CManager\Release\CManager.exe"; DestDir: "{app}\Apps"; Flags: ignoreversion; Components: main
Source: "C:\VTP\TerrainApps\CManager\itemtypes.txt"; DestDir: "{app}\Apps"; Flags: ignoreversion; Components: main
Source: "C:\VTP\TerrainApps\CManager\tags.txt"; DestDir: "{app}\Apps"; Flags: ignoreversion; Components: main
Source: "C:\VTP\TerrainApps\CManager\Docs\*"; DestDir: "{app}/Docs/CManager"; Flags: ignoreversion recursesubdirs; Components: docs

Source: "C:\VTP\vc9\TerrainApps\Enviro\Release\Enviro.exe"; DestDir: "{app}\Apps"; Flags: ignoreversion; Components: main
Source: "C:\VTP\TerrainApps\Enviro\Ship\Enviro.xml"; DestDir: "{app}\Apps"; Flags: ignoreversion; Components: main
Source: "C:\VTP\TerrainApps\Enviro\Docs\*"; DestDir: "{app}\Docs\Enviro"; Flags: ignoreversion recursesubdirs; Components: docs

Source: "C:\VTP\vc9\TerrainApps\VTBuilder\Release\VTBuilder.exe"; DestDir: "{app}\Apps"; Flags: ignoreversion; Components: main
Source: "C:\VTP\TerrainApps\VTBuilder\Ship\VTBuilder.xml"; DestDir: "{app}\Apps"; Flags: ignoreversion; Components: main
Source: "C:\VTP\TerrainApps\VTBuilder\Docs\*"; DestDir: "{app}\Docs\VTBuilder"; Flags: ignoreversion recursesubdirs; Components: docs

Source: "C:\VTP\vc9\TerrainApps\Simple\Release\Simple.exe"; DestDir: "{app}\Apps"; Flags: ignoreversion; Components: main

; Translation files
Source: "C:\VTP\TerrainApps\Enviro\af\Enviro.mo"; DestDir: "{app}\Apps\af"; Flags: ignoreversion; Components: main
Source: "C:\VTP\TerrainApps\Enviro\ar\Enviro.mo"; DestDir: "{app}\Apps\ar"; Flags: ignoreversion; Components: main
Source: "C:\VTP\TerrainApps\Enviro\de\Enviro.mo"; DestDir: "{app}\Apps\de"; Flags: ignoreversion; Components: main
Source: "C:\VTP\TerrainApps\Enviro\en\Enviro.mo"; DestDir: "{app}\Apps\en"; Flags: ignoreversion; Components: main
Source: "C:\VTP\TerrainApps\Enviro\en_GB\Enviro.mo"; DestDir: "{app}\Apps\en_GB"; Flags: ignoreversion; Components: main
Source: "C:\VTP\TerrainApps\Enviro\es\Enviro.mo"; DestDir: "{app}\Apps\es"; Flags: ignoreversion; Components: main
Source: "C:\VTP\TerrainApps\Enviro\fr\Enviro.mo"; DestDir: "{app}\Apps\fr"; Flags: ignoreversion; Components: main
Source: "C:\VTP\TerrainApps\Enviro\hu\Enviro.mo"; DestDir: "{app}\Apps\hu"; Flags: ignoreversion; Components: main
Source: "C:\VTP\TerrainApps\Enviro\it\Enviro.mo"; DestDir: "{app}\Apps\it"; Flags: ignoreversion; Components: main
Source: "C:\VTP\TerrainApps\Enviro\pt\Enviro.mo"; DestDir: "{app}\Apps\pt"; Flags: ignoreversion; Components: main
Source: "C:\VTP\TerrainApps\Enviro\ro\Enviro.mo"; DestDir: "{app}\Apps\ro"; Flags: ignoreversion; Components: main
Source: "C:\VTP\TerrainApps\Enviro\sv\Enviro.mo"; DestDir: "{app}\Apps\sv"; Flags: ignoreversion; Components: main
Source: "C:\VTP\TerrainApps\Enviro\tr\Enviro.mo"; DestDir: "{app}\Apps\tr"; Flags: ignoreversion; Components: main
Source: "C:\VTP\TerrainApps\Enviro\zh\Enviro.mo"; DestDir: "{app}\Apps\zh"; Flags: ignoreversion; Components: main
Source: "C:\VTP\TerrainApps\VTBuilder\ar\VTBuilder.mo"; DestDir: "{app}\Apps\ar"; Flags: ignoreversion; Components: main
Source: "C:\VTP\TerrainApps\VTBuilder\en\VTBuilder.mo"; DestDir: "{app}\Apps\en"; Flags: ignoreversion; Components: main
Source: "C:\VTP\TerrainApps\VTBuilder\fr\VTBuilder.mo"; DestDir: "{app}\Apps\fr"; Flags: ignoreversion; Components: main
Source: "C:\VTP\TerrainApps\VTBuilder\ro\VTBuilder.mo"; DestDir: "{app}\Apps\ro"; Flags: ignoreversion; Components: main
Source: "C:\VTP\TerrainApps\VTBuilder\zh\VTBuilder.mo"; DestDir: "{app}\Apps\zh"; Flags: ignoreversion; Components: main

; Core Data
Source: "G:\Data-Distro\*"; DestDir: "{app}\Data"; Flags: ignoreversion recursesubdirs; Components: data

; overview docs
Source: "C:\VTP\Docs\*"; DestDir: "{app}\Docs"; Flags: ignoreversion recursesubdirs; Components: docs

; Projection Stuff
Source: "C:\APIs\gdal-1.8.0\data\*"; DestDir: "{app}\GDAL-data"; Flags: ignoreversion; Components: proj
Source: "C:\APIs\proj-4.6.1\nad\*"; DestDir: "{app}\PROJ4-data"; Flags: ignoreversion; Components: proj

; DLLs
Source: "C:\APIs\bzip2-1.0.3-bin-vc9\bzip2.dll"; DestDir: "{app}\Apps"; Flags: ignoreversion; Components: dlls
Source: "C:\APIs\gdal-1.8.0\distro-vc9\bin\gdal18-vc9.dll"; DestDir: "{app}\Apps"; Flags: ignoreversion; Components: dlls
Source: "C:\APIs\gdal-1.8.0\distro-vc9\bin\proj.dll"; DestDir: "{app}\Apps"; Flags: ignoreversion; Components: dlls
Source: "C:\APIs\gdal-1.8.0\distro-vc9\bin\*.exe"; DestDir: "{app}\Apps"; Flags: ignoreversion; Components: dlls
;Source: "C:\APIs\libcurl-7.15.0\libcurl.dll"; DestDir: "{app}\Apps"; Flags: ignoreversion; Components: dlls
Source: "C:\APIs\lpng150\projects\visualc9\Win32_DLL_Release\libpng15-vc9.dll"; DestDir: "{app}\Apps"; Flags: ignoreversion; Components: dlls
Source: "C:\APIs\lpng150\projects\visualc9\Win32_DLL_Release\ZLib\zlib1-vc9.dll"; DestDir: "{app}\Apps"; Flags: ignoreversion; Components: dlls
Source: "C:\APIs\netcdf-3.5.0.win32bin\bin\*.dll"; DestDir: "{app}\Apps"; Flags: ignoreversion; Components: dlls
Source: "C:\APIs\OpenSceneGraph-2.8.3\vc9\bin-rel-only\*.dll"; DestDir: "{app}\Apps"; Flags: ignoreversion recursesubdirs; Components: dlls
Source: "C:\APIs\wx2.8.7\lib-vc9\vc_dll\wxbase28u_vc_custom.dll"; DestDir: "{app}\Apps"; Flags: ignoreversion; Components: dlls
Source: "C:\APIs\wx2.8.7\lib-vc9\vc_dll\wxmsw28u_core_vc_custom.dll"; DestDir: "{app}\Apps"; Flags: ignoreversion; Components: dlls
Source: "C:\APIs\wx2.8.7\lib-vc9\vc_dll\wxmsw28u_gl_vc_custom.dll"; DestDir: "{app}\Apps"; Flags: ignoreversion; Components: dlls
Source: "C:\APIs\wx2.8.7\lib-vc9\vc_dll\wxbase28u_net_vc_custom.dll"; DestDir: "{app}\Apps"; Flags: ignoreversion; Components: dlls
Source: "C:\APIs\wx2.8.7\lib-vc9\vc_dll\wxmsw28u_aui_vc_custom.dll"; DestDir: "{app}\Apps"; Flags: ignoreversion; Components: dlls
Source: "C:\APIs\expat-2.0.1\win32\bin\release\libexpat-vc9.dll"; DestDir: "{app}\Apps"; Flags: ignoreversion; Components: dlls
; DAE plugin might want this:
Source: "C:\APIs\Collada_DOM_2.2\dom\external-libs\libxml2\win32\lib\libxml2.dll"; DestDir: "{app}\Apps"; Flags: ignoreversion; Components: dlls


; Microsoft DLLs (not useful, since vc8 they don't work if installed this way)
;Source: "C:\Program Files\VisStudio8\VC\REDIST\x86\Microsoft.VC80.CRT\Microsoft.VC80.CRT.manifest"; DestDir: "{app}\Apps"; Flags: ignoreversion; Components: dlls
;Source: "C:\Program Files\VisStudio8\VC\REDIST\x86\Microsoft.VC80.CRT\msvcp80.dll"; DestDir: "{app}\Apps"; Flags: ignoreversion; Components: dlls
;Source: "C:\Program Files\VisStudio8\VC\REDIST\x86\Microsoft.VC80.CRT\msvcr80.dll"; DestDir: "{app}\Apps"; Flags: ignoreversion; Components: dlls

; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{group}\Documentation"; Filename: "{app}\Docs\index.html"
;Name: "{group}\BExtractor"; Filename: "{app}\Apps\BExtractor.exe"; WorkingDir: "{app}\Apps"
Name: "{group}\CManager"; Filename: "{app}\Apps\CManager.exe"; WorkingDir: "{app}\Apps"
Name: "{group}\Enviro"; Filename: "{app}\Apps\Enviro.exe"; WorkingDir: "{app}\Apps"
Name: "{group}\VTBuilder"; Filename: "{app}\Apps\VTBuilder.exe"; WorkingDir: "{app}\Apps"
Name: "{group}\Simple test - in window"; Filename: "{app}\Apps\Simple.exe"; Parameters: "--window 100 100 800 600"; WorkingDir: "{app}\Apps"
Name: "{group}\Simple test - full screen"; Filename: "{app}\Apps\Simple.exe"; Parameters: "--screen 0"; WorkingDir: "{app}\Apps"
Name: "{group}\Uninstall VTP Software"; Filename: "{uninstallexe}"


[CmdletBinding()]
param (
    [string] $ConfigFile = ".\3rd-parties.json",
    [Parameter(Mandatory=$true)]
    [int] $vsToolsetVersion
)

function GetVSInstances {
    $vswhere = Get-ChildItem -Path "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer" -Recurse -Filter vswhere.exe
    & $vswhere.FullName -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -format json | ConvertFrom-Json
}

function GetToolsetVersion {
    Param ([string] $VSInstanceDir)

    $fullVersion = Get-Content $VSInstanceDir\VC\Auxiliary\Build\Microsoft.VCToolsVersion.default.txt
    $version = $fullVersion.Split('.')
    return $version[0] + $version[1].Substring(0,1)
}

function SetVSEnv {
    param (
        [Parameter(Mandatory=$true)]
        [int]
        $ToolsetVersion
    )

    $VSInstances = GetVSInstances
    foreach($vsi in $VSInstances) {
        if($ToolsetVersion -eq (GetToolsetVersion $vsi.installationPath)) {
            $VSInstance = $vsi
        }
    }

    try {
        msbuild -version -nologo | Out-Null
    } catch {
        Import-Module ([System.IO.Path]::Combine($VSInstance.installationPath, 'Common7\Tools\Microsoft.VisualStudio.DevShell.dll'))
        Enter-VsDevShell -VsInstanceId $VSInstance.instanceId -StartInPath $PWD -DevCmdArguments '-arch=x64'
    }
    try {
        msbuild -version -nologo | Out-Null
    } catch {
        Write-Error "Impossible de définir les variables d'environnement de Visual Studio." -Category InvalidOperation
        return $false
    }
}

function ExtractLib {
    Param(
        [parameter(Mandatory = $true)][System.IO.DirectoryInfo]$Dir,
        [parameter(Mandatory = $true)][string]$libName)

    Write-Host "Extraction de $libname dans $Dir..."

    $libdir = Get-ChildItem (Join-Path $Dir.FullName "$libName*") -Directory
    if($null -ne $libdir) {
        Remove-Item $libdir -Recurse -Force
    }

    $libarchive = Get-ChildItem (Join-Path $Dir.FullName "$libName*.zip")
    if($null -eq $libarchive) {
        Write-Error "La Bibliothèque $libName n'a pas été trouvée dans le répertoire $Dir." -Category NotInstalled
    }

    $files = Expand-Archive $libarchive $Dir.FullName -PassThru
    foreach ($file in $files) {
        $file.LastWriteTime = Get-Date;
    }
    $libdir = Get-ChildItem (Join-Path $Dir.FullName "$libName*") -Directory
    if($libdir.Name -ne $libname) { 
        Rename-Item $libdir $libname
    }
}

function InstallGlew{
    Param(
        [parameter(Mandatory = $true)][string]$version,
        [parameter(Mandatory = $true)][System.IO.DirectoryInfo]$LibDir,
        [parameter(Mandatory = $true)][System.IO.DirectoryInfo]$BinDir)

    if (!(Test-Path (Join-Path $LibDir.FullName "glew-$version-win32.zip"))) {
        Write-Host "Téléchargement de glew-$version-win32.zip..."
        Invoke-WebRequest "https://github.com/nigels-com/glew/releases/download/glew-$version/glew-$version-win32.zip" -OutFile (Join-Path $LibDir.FullName "glew-$version-win32.zip")
    }
    ExtractLib -libName glew -Dir $LibDir
    Copy-Item (Join-Path $LibDir.FullName "glew\bin\Release\x64\glew32.dll") (Join-Path $BinDir "x64\Debug\") -Force
    Copy-Item (Join-Path $LibDir.FullName "glew\bin\Release\x64\glew32.dll") (Join-Path $BinDir "x64\Release\") -Force
}

function InstallGlfw{
    Param(
        [parameter(Mandatory = $true)][string]$version,
        [parameter(Mandatory=$true)][System.IO.DirectoryInfo]$LibDir,
        [parameter(Mandatory = $true)][System.IO.DirectoryInfo]$BinDir)

    if(!(Test-Path (Join-Path $LibDir.FullName "glfw-$version.bin.WIN64.zip")))
    {
        Write-Host "Téléchargement de glfw-$version.bin.WIN64.zip..."
        Invoke-WebRequest "https://github.com/glfw/glfw/releases/download/$version/glfw-$version.bin.WIN64.zip" -OutFile (Join-Path $LibDir.FullName "glfw-$version.bin.WIN64.zip")
    }
    ExtractLib -libName glfw -Dir $LibDir
    Copy-Item (Join-Path $LibDir.FullName "glfw\lib-vc2019\glfw3.dll") (Join-Path $BinDir "x64\Debug\") -Force
    Copy-Item (Join-Path $LibDir.FullName "glfw\lib-vc2019\glfw3.dll") (Join-Path $BinDir "x64\Release\") -Force
}

function InstallGlm{
    Param(
        [parameter(Mandatory = $true)][string]$version,
        [parameter(Mandatory=$true)][System.IO.DirectoryInfo]$LibDir)

    if(!(Test-Path (Join-Path $LibDir.FullName "glm-$version.zip")))
    {
        Write-Host "Téléchargement de glm-$version.zip..."
        Invoke-WebRequest "https://github.com/g-truc/glm/releases/download/$version/glm-$version.zip" -OutFile (Join-Path $LibDir.FullName "glm-$version.zip")
    }
    ExtractLib -libName glm -Dir $LibDir
}

function InstallFreeImage{
    Param(
        [parameter(Mandatory = $true)][string]$version,
        [parameter(Mandatory=$true)][System.IO.DirectoryInfo]$LibDir,
        [parameter(Mandatory = $true)][System.IO.DirectoryInfo]$BinDir)

    if(!(Test-Path (Join-Path $LibDir.FullName "FreeImage$($version -replace '\.','')Win32Win64.zip")))
    {
        Write-Host "Téléchargement de FreeImage$($version -replace '\.','')Win32Win64.zip..."
        curl.exe "https://sourceforge.net/projects/freeimage/files/Binary%20Distribution/$($version)/FreeImage$($version -replace '\.','')Win32Win64.zip/download" -LsS --output (Join-Path $LibDir.FullName "FreeImage$($version -replace '\.','')Win32Win64.zip")
    }
    ExtractLib -libName FreeImage -Dir $LibDir
    Copy-Item (Join-Path $LibDir.FullName "FreeImage\Dist\x64\FreeImage.dll") (Join-Path $BinDir "x64\Debug\") -Force
    Copy-Item (Join-Path $LibDir.FullName "FreeImage\Dist\x64\FreeImage.dll") (Join-Path $BinDir "x64\Release\") -Force
    Copy-Item (Join-Path $LibDir.FullName "FreeImage\Wrapper\FreeImagePlus\dist\x64\FreeImagePlus.dll") (Join-Path $BinDir "x64\Debug\") -Force
    Copy-Item (Join-Path $LibDir.FullName "FreeImage\Wrapper\FreeImagePlus\dist\x64\FreeImagePlus.dll") (Join-Path $BinDir "x64\Release\") -Force
}

function InstallShaderPP{
    Param(
        [parameter(Mandatory=$true)][System.IO.DirectoryInfo]$LibDir, 
        [int]$vsToolsetVersion
    )

    if(!(Test-Path (Join-Path $LibDir.FullName "ShaderPP-install"))) {
        Push-Location (Join-Path $LibDir.FullName "ShaderPP")
        Write-Host "Installation de ShaderPP dans $(Join-Path $LibDir.FullName ..\ShaderPP-install) ..."
        .\InstallShaderPP.ps1 -RootDir ..\ShaderPP-install -vsVersionsToBuild @($vsToolsetVersion)
        Pop-Location
    }
}

function InstallTexturePP{
    Param(
        [parameter(Mandatory=$true)][System.IO.DirectoryInfo]$LibDir, 
        [int]$vsToolsetVersion
    )

    if(!(Test-Path (Join-Path $LibDir.FullName "TexturePP-install"))) {
        Push-Location (Join-Path $LibDir.FullName "TexturePP")
        Write-Host "Installation de TexturePP dans $(Join-Path $LibDir.FullName ..\TexturePP-install) ..."
        .\InstallTexturePP.ps1 -RootDir ..\TexturePP-install -vsVersionsToBuild @($vsToolsetVersion)
        Pop-Location
    }
}

function InstallLibJPEG{
    Param(
        [parameter(Mandatory=$true)][System.IO.DirectoryInfo]$LibDir, 
        [parameter(Mandatory = $true)][string]$version,
        [int]$vsToolsetVersion
    )

    if(!(Test-Path (Join-Path $LibDir.FullName "jpegsr$version.zip")))
    {
        Write-Host "Téléchargement de jpegsr$version.zip..."
        Invoke-WebRequest "http://ijg.org/files/jpegsr$version.zip" -OutFile (Join-Path $LibDir.FullName "jpegsr$version.zip")
    }
    ExtractLib -libName jpeg -Dir $LibDir

    #Compile it
    SetVSEnv -ToolsetVersion $vsToolsetVersion
    Push-Location (Join-Path $LibDir.FullName jpeg)
    Write-Host "Génération de libJPEG..."
    Write-Host "    Création des projets et solutions Visual Studio..."
    $out = nmake /f .\makefile.vs setupcopy-v16
    if(!$?) {
        Write-Error "Erreur à la création des fichiers projets et solutions. La sortie était : `n$out"
        return
    }
    Write-Host "    Compilation de libJPEG..."
    $out = msbuild jpeg.sln "-property:Configuration=Release;PlatformToolset=v$vsToolsetVersion;Platform=x64" -m
    if(!$?) {
        Write-Error "Erreur à la compilation de libJPEG. La sortie était : `n$out"
        return
    }
    Write-Host "    Compilation des programmes utilitaires..."
    $out = msbuild apps.sln "-property:Configuration=Release;PlatformToolset=v$vsToolsetVersion;Platform=x64" -m
    if(!$?) {
        Write-Error "Erreur à la compilation des programmes utilitaires. La sortie était : `n$out"
        return
    }
    Write-Host "    Lancement des tests..."
    $out = nmake /f makefile.vs test-64
    if(!$?) {
        Write-Error "Erreur au lancement des tests. La sortie était : `n$out"
        return
    }
    Write-Host "Assurez-vous que toutes les sorties de fc sont du style `"FC : aucune différence trouvée`" :"
    $out.Split('\n') | Write-Host
    Pop-Location
}

function InstallZlib{
    Param(
        [parameter(Mandatory=$true)][System.IO.DirectoryInfo]$LibDir, 
        [parameter(Mandatory = $true)][string]$version,
        [int]$vsToolsetVersion
    )

    if(!(Test-Path (Join-Path $LibDir.FullName "zlib$($version -replace '\.','').zip")))
    {
        Write-Host "Téléchargement de zlib$($version -replace '\.','').zip..."
        curl.exe "https://sourceforge.net/projects/libpng/files/zlib/$version/zlib$($version -replace '\.','').zip/download" -LsS --output (Join-Path $LibDir.FullName "zlib$($version -replace '\.','').zip")
    }
    ExtractLib -libName zlib -Dir $LibDir

    #Compile it
    SetVSEnv -ToolsetVersion $vsToolsetVersion
    Push-Location (Join-Path $LibDir.FullName zlib)
    Write-Host "Génération de zlib..."
    $out = nmake /f .\win32\Makefile.msc
    if(!$?) {
        Write-Error "Erreur à la génération de zlib. La sortie était : `n$out"
        return
    }
    Pop-Location
}

function InstallLibPNG{
    Param(
        [parameter(Mandatory=$true)][System.IO.DirectoryInfo]$LibDir, 
        [parameter(Mandatory = $true)][string]$version,
        [int]$vsToolsetVersion
    )

    if(!(Test-Path (Join-Path $LibDir.FullName "lpng$($version -replace '\.','').zip")))
    {
        Write-Host "Téléchargement de lpng$($version -replace '\.','').zip..."
        curl.exe "https://sourceforge.net/projects/libpng/files/libpng$(-join $version.Split('.')[0..1])/$version/lpng$($version -replace '\.','').zip/download" -LsS --output (Join-Path $LibDir.FullName "lpng$($version -replace '\.','').zip")
    }
    ExtractLib -libName lpng -Dir $LibDir

    #Compile it
    SetVSEnv -ToolsetVersion $vsToolsetVersion
    Push-Location (Join-Path $LibDir.FullName lpng)
    Write-Host "Génération de libPNG..."

    Copy-Item .\scripts\makefile.vcwin32 makefile
    Copy-Item .\scripts\pnglibconf.h.prebuilt pnglibconf.h

    $out = nmake /f .\makefile test
    if(!$?) {
        Write-Error "Erreur au lancement des tests. La sortie était : `n$out"
        return
    }
    Write-Host "Test de libPNG :"
    .\pngtest.exe
    Pop-Location
}

[System.IO.Directory]::SetCurrentDirectory($PWD)

[System.IO.FileInfo]$ConfigFile = $ConfigFile

$jsonConf = Get-Content $ConfigFile.FullName | ConvertFrom-Json
$LibDir = Join-Path $ConfigFile.Directory.FullName $ConfigFile.BaseName
$BinDir = $ConfigFile.Directory.FullName
[void](New-Item -Path (Join-Path $BinDir x64\Debug) -ItemType Directory -ErrorAction Ignore)
[void](New-Item -Path (Join-Path $BinDir x64\Release) -ItemType Directory -ErrorAction Ignore)
if(!(Test-Path $LibDir)) {
    New-Item -Name $ConfigFile.BaseName -ItemType Directory -Path $ConfigFile.Directory.FullName
}
#Analyse les dépendances
if(Get-Member -InputObject $jsonConf -Name Dependencies) {
    foreach($Dependency in $jsonConf.Dependencies) {
        switch ($Dependency.libname) {
            "glew" { InstallGlew -version $Dependency.version -LibDir $LibDir -BinDir $BinDir }
            "glfw" { InstallGlfw -version $Dependency.version -LibDir $LibDir -BinDir $BinDir }
            "glm" { InstallGlm -version $Dependency.version -LibDir $LibDir }
            "FreeImage" { InstallFreeImage -version $Dependency.version -LibDir $LibDir -BinDir $BinDir }
            "ShaderPP" { InstallShaderPP -LibDir $LibDir -vsToolsetVersion $vsToolsetVersion }
            "TexturePP" { InstallTexturePP -LibDir $LibDir -vsToolsetVersion $vsToolsetVersion }
            "libJPEG" { InstallLibJPEG -version $Dependency.version -LibDir $LibDir -vsToolsetVersion $vsToolsetVersion }
            "zlib" { InstallZlib -version $Dependency.version -LibDir $LibDir -vsToolsetVersion $vsToolsetVersion }
            "libPNG" { InstallLibPNG -version $Dependency.version -LibDir $LibDir -vsToolsetVersion $vsToolsetVersion }
            Default { Write-Error "La bibliothèque $Dependency est inconnue." -Category InvalidArgument }
        }    
    }
}


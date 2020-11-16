[CmdletBinding()]
param (
    [ValidateSet("x64", "WSL")]
    [string] $Platform,
    [ValidateSet("GCC", "Clang")]
    [string] $Compiler,
    [ValidateSet("Release", "Debug")]
    [string] $Config,
    [ValidateSet("Static", "Dynamic")]
    [string] $Linking
)

if($PSBoundParameters.ContainsKey('Platform')) {
    $_Platform = ".*$Platform.*"
} else {
    $_Platform = ".*"
}

if($PSBoundParameters.ContainsKey('Compiler')) {
    $_Compiler = ".*$Compiler.*"
} else {
    $_Compiler = ".*"
}

if($PSBoundParameters.ContainsKey('Config')) {
    $_Config = ".*$Config.*"
} else {
    $_Config = ".*"
}

if($PSBoundParameters.ContainsKey('Linking')) {
    $_Linking = ".*$Linking.*"
} else {
    $_Linking = ".*"
}

Push-Location build
if("WSL" -match $_Platform) {
    Get-ChildItem WSL* | ForEach-Object {
        Push-Location $_
        if ($_.BaseName -match ".*Release.*") {
            $CurrentConfig = "Release";
        }
        else {
            $CurrentConfig = "Debug";
        }
        if ($_.BaseName -match ".*GCC.*") {
            $CurrentCompiler = "GCC";
        }
        else {
            $CurrentCompiler = "Clang";
        }
        if ($_.BaseName -match ".*Static.*") {
            $CurrentLinking = "Static";
        }
        else {
            $CurrentLinking = "Dynamic";
        }
        if(($CurrentConfig -match $_Config) -and ($CurrentCompiler -match $_Compiler) -and ($CurrentLinking -match $_Linking)) {
            $arg = "-DCMAKE_BUILD_TYPE=$CurrentConfig";
            wsl cmake ../.. $arg
            wsl cmake --build . --config $CurrentConfig
            wsl cmake --install . --prefix ../install/WSL/$CurrentCompiler
            wsl ctest -C $CurrentConfig
        }
        Pop-Location
    }
}
if("x64" -match $_Platform) {
    Get-ChildItem x64* | ForEach-Object {
        Push-Location $_
        if ($_.BaseName -match ".*Release.*") {
            $CurrentConfig = "Release";
        }
        else {
            $CurrentConfig = "Debug";
        }
        if ($_.BaseName -match ".*Static.*") {
            $CurrentLinking = "Static";
        }
        else {
            $CurrentLinking = "Dynamic";
        }
        if(($CurrentConfig -match $_Config) -and ($CurrentLinking -match $_Linking)) {
            $arg = "-DCMAKE_BUILD_TYPE=$CurrentConfig";
            cmake ../.. $arg
            cmake --build . --config $CurrentConfig
            cmake --install . --prefix ../install/x64
            ctest -C $CurrentConfig
        }
        Pop-Location
    }
}
Pop-Location

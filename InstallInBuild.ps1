[CmdletBinding()]
param (
    [ValidateSet("x64", "WSL")]
    [string] $Platform,
    [ValidateSet("GCC", "Clang", "MSVC")]
    [string] $Compiler,
    [ValidateSet("Release", "Debug")]
    [string] $Config,
    [ValidateSet("Static", "Dynamic")]
    [string] $Linking
)

$ConfigBuildDoc=[PSCustomObject]@{"Config"="Debug";   "Linking"="Dynamic"}

if($PSBoundParameters.ContainsKey('Platform')) {
    $_Platform = ".*$Platform.*"
} else {
    $_Platform = ".*"
}

if($PSBoundParameters.ContainsKey('Compiler')) {
    $_Compiler = ".*$Compiler.*"
    if($Compiler -eq "MSVC" -and $Platform -eq "WSL") {
        Throw "Compiler MSVC is not compatible with WSL platform!"
    }
    if(($Compiler -eq "GCC" -or $Compiler -eq "Clang") -and $Platform -eq "x64") {
        Throw "Compiler $Compiler is not supported on x64."
    }
} else {
    $_Compiler = ".*"
}

if($PSBoundParameters.ContainsKey('Config')) {
    $_Config = ".*$Config.*"
    $ConfigBuildDoc.Config = $Config
} else {
    $_Config = ".*"
}

if($PSBoundParameters.ContainsKey('Linking')) {
    $_Linking = ".*$Linking.*"
    $ConfigBuildDoc.Linking = $Linking
} else {
    $_Linking = ".*"
}

New-Item build -ItemType Directory -Force | Out-Null
Push-Location build

$Configs=([PSCustomObject]@{"Platform"="WSL"; "Compiler"="Clang"; "Config"="Debug";   "Linking"="Dynamic"},
          [PSCustomObject]@{"Platform"="WSL"; "Compiler"="Clang"; "Config"="Debug";   "Linking"="Static" },
          [PSCustomObject]@{"Platform"="WSL"; "Compiler"="Clang"; "Config"="Release"; "Linking"="Dynamic"},
          [PSCustomObject]@{"Platform"="WSL"; "Compiler"="Clang"; "Config"="Release"; "Linking"="Static" },
          [PSCustomObject]@{"Platform"="WSL"; "Compiler"="GCC";   "Config"="Debug";   "Linking"="Dynamic"},
          [PSCustomObject]@{"Platform"="WSL"; "Compiler"="GCC";   "Config"="Debug";   "Linking"="Static" },
          [PSCustomObject]@{"Platform"="WSL"; "Compiler"="GCC";   "Config"="Release"; "Linking"="Dynamic"},
          [PSCustomObject]@{"Platform"="WSL"; "Compiler"="GCC";   "Config"="Release"; "Linking"="Static" },
          [PSCustomObject]@{"Platform"="x64"; "Compiler"="";      "Config"="Debug";   "Linking"="Dynamic"},
          [PSCustomObject]@{"Platform"="x64"; "Compiler"="";      "Config"="Debug";   "Linking"="Static" },
          [PSCustomObject]@{"Platform"="x64"; "Compiler"="";      "Config"="Release"; "Linking"="Dynamic"},
          [PSCustomObject]@{"Platform"="x64"; "Compiler"="";      "Config"="Release"; "Linking"="Static" })


$Configs | ForEach-Object {
    $buildIt = $true;
    if($_.Platform -match $_Platform) {
        if($_.Platform -eq "WSL") {
            if($_.Compiler -match $_Compiler) {
                if($_.Compiler -eq "GCC") {
                    $CurrentCCompiler = "gcc"
                    $CurrentCXXCompiler = "g++"
                    $ConanProfile = "default"
                } else {
                    $CurrentCCompiler = "clang"
                    $CurrentCXXCompiler = "clang++"
                    $ConanProfile = "clang"
                }
            } else {
                $buildIt = $false
            }
            if(!($_.Config -match $_Config)) {
                $buildIt = $false
            }
            if($_.Linking -match $_Linking) {
                if($_.Linking -eq "Static") {
                    $Static = "ON"
                } else {
                    $Static = "OFF"
                }
            } else {
                $buildIt = $false
            }

            if($buildIt) {
                New-Item "$($_.Platform)-$($_.Compiler)-$($_.Config)-$($_.Linking)" -ItemType Directory -Force | Out-Null
                Push-Location "$($_.Platform)-$($_.Compiler)-$($_.Config)-$($_.Linking)"
                if($_.Config -eq $ConfigBuildDoc.Config -and $_.Linking -eq $ConfigBuildDoc.Linking) {
                    $doc = "ON"
                } else {
                    $doc = "OFF"
                }
                wsl cmake ../.. "-DCMAKE_BUILD_TYPE=$($_.Config)" "-DBUILD_DOCUMENTATION=$doc" "-DBUILD_TESTING=ON" "-DSTATIC_LIB=$Static" "-DSUPPORT_PNG=ON" "-DCMAKE_C_COMPILER=$CurrentCCompiler" "-DCMAKE_CXX_COMPILER=$CurrentCXXCompiler" "-DCONAN_PROFILE=$ConanProfile"
                wsl cmake --build . --config $_.Config
                wsl cmake --install . --prefix "../install/WSL/$($_.Compiler)"
                wsl ctest -C $_.Config
                Pop-Location
            }
        } else { #Platform is x64 (so compiler is msvc)
            if(!($_.Config -match $_Config)) {
                $buildIt = $false
            }
            if($_.Linking -match $_Linking) {
                if($_.Linking -eq "Static") {
                    $Static = "ON"
                } else {
                    $Static = "OFF"
                }
            } else {
                $buildIt = $false
            }

            if($buildIt) {
                New-Item "$($_.Platform)-$($_.Config)-$($_.Linking)" -ItemType Directory -Force | Out-Null
                Push-Location "$($_.Platform)-$($_.Config)-$($_.Linking)"
                if($_.Config -eq $ConfigBuildDoc.Config -and $_.Linking -eq $ConfigBuildDoc.Linking) {
                    $doc = "ON"
                } else {
                    $doc = "OFF"
                }
                cmake ../.. "-DCMAKE_BUILD_TYPE=$($_.Config)" "-DBUILD_DOCUMENTATION=$doc" "-DBUILD_TESTING=ON" "-DSTATIC_LIB=$Static" "-DSUPPORT_PNG=ON"
                cmake --build . --config $_.Config
                cmake --install . --prefix ../install/x64
                ctest -C $_.Config
                Pop-Location
            }
        }
    }
}

Pop-Location

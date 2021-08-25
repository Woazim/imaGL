[CmdletBinding()]
param (
    [ValidateSet("x64", "WSL")]
    [string] $Platform,
    [ValidateSet("GCC", "Clang", "MSVC")]
    [string] $Compiler,
    [ValidateSet("Release", "Debug")]
    [string] $Config,
    [ValidateSet("Static", "Dynamic")]
    [string] $Linking,
    [ValidateSet("ON", "OFF")]
    [string] $Multithread
)

$ConfigBuildDoc=[PSCustomObject]@{"Config"="Release";   "Linking"="Dynamic"}
$ConfigsInError = [System.Collections.ArrayList]@();

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
} else {
    $_Config = ".*"
}

if($PSBoundParameters.ContainsKey('Linking')) {
    $_Linking = ".*$Linking.*"
} else {
    $_Linking = ".*"
}

if($PSBoundParameters.ContainsKey('Multithread')) {
    $_Multithread = ".*$Multithread.*"
} else {
    $_Multithread = ".*"
}

New-Item build -ItemType Directory -Force | Out-Null
Push-Location build

$Configs=([PSCustomObject]@{"Platform"="WSL"; "Compiler"="Clang"; "Config"="Debug";   "Linking"="Dynamic"; "Multithread"="ON"},
          [PSCustomObject]@{"Platform"="WSL"; "Compiler"="Clang"; "Config"="Debug";   "Linking"="Static";  "Multithread"="ON"},
          [PSCustomObject]@{"Platform"="WSL"; "Compiler"="Clang"; "Config"="Release"; "Linking"="Dynamic"; "Multithread"="ON"},
          [PSCustomObject]@{"Platform"="WSL"; "Compiler"="Clang"; "Config"="Release"; "Linking"="Static";  "Multithread"="ON"},
          [PSCustomObject]@{"Platform"="WSL"; "Compiler"="GCC";   "Config"="Debug";   "Linking"="Dynamic"; "Multithread"="ON"},
          [PSCustomObject]@{"Platform"="WSL"; "Compiler"="GCC";   "Config"="Debug";   "Linking"="Static";  "Multithread"="ON"},
          [PSCustomObject]@{"Platform"="WSL"; "Compiler"="GCC";   "Config"="Release"; "Linking"="Dynamic"; "Multithread"="ON"},
          [PSCustomObject]@{"Platform"="WSL"; "Compiler"="GCC";   "Config"="Release"; "Linking"="Static";  "Multithread"="ON"},
          [PSCustomObject]@{"Platform"="x64"; "Compiler"="";      "Config"="Debug";   "Linking"="Dynamic"; "Multithread"="ON"},
          [PSCustomObject]@{"Platform"="x64"; "Compiler"="";      "Config"="Debug";   "Linking"="Static";  "Multithread"="ON"},
          [PSCustomObject]@{"Platform"="x64"; "Compiler"="";      "Config"="Release"; "Linking"="Dynamic"; "Multithread"="ON"},
          [PSCustomObject]@{"Platform"="x64"; "Compiler"="";      "Config"="Release"; "Linking"="Static";  "Multithread"="ON"},
          [PSCustomObject]@{"Platform"="WSL"; "Compiler"="Clang"; "Config"="Debug";   "Linking"="Dynamic"; "Multithread"="OFF"},
          [PSCustomObject]@{"Platform"="WSL"; "Compiler"="Clang"; "Config"="Debug";   "Linking"="Static";  "Multithread"="OFF"},
          [PSCustomObject]@{"Platform"="WSL"; "Compiler"="Clang"; "Config"="Release"; "Linking"="Dynamic"; "Multithread"="OFF"},
          [PSCustomObject]@{"Platform"="WSL"; "Compiler"="Clang"; "Config"="Release"; "Linking"="Static";  "Multithread"="OFF"},
          [PSCustomObject]@{"Platform"="WSL"; "Compiler"="GCC";   "Config"="Debug";   "Linking"="Dynamic"; "Multithread"="OFF"},
          [PSCustomObject]@{"Platform"="WSL"; "Compiler"="GCC";   "Config"="Debug";   "Linking"="Static";  "Multithread"="OFF"},
          [PSCustomObject]@{"Platform"="WSL"; "Compiler"="GCC";   "Config"="Release"; "Linking"="Dynamic"; "Multithread"="OFF"},
          [PSCustomObject]@{"Platform"="WSL"; "Compiler"="GCC";   "Config"="Release"; "Linking"="Static";  "Multithread"="OFF"},
          [PSCustomObject]@{"Platform"="x64"; "Compiler"="";      "Config"="Debug";   "Linking"="Dynamic"; "Multithread"="OFF"},
          [PSCustomObject]@{"Platform"="x64"; "Compiler"="";      "Config"="Debug";   "Linking"="Static";  "Multithread"="OFF"},
          [PSCustomObject]@{"Platform"="x64"; "Compiler"="";      "Config"="Release"; "Linking"="Dynamic"; "Multithread"="OFF"},
          [PSCustomObject]@{"Platform"="x64"; "Compiler"="";      "Config"="Release"; "Linking"="Static";  "Multithread"="OFF"})


$Configs | ForEach-Object {
    $buildIt = $true;
    if(($_.Platform -match $_Platform) -and ($_.Multithread -match $_Multithread)) {
        $Enable_Multithread = $_.Multithread
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
                New-Item "$($_.Platform)-$($_.Compiler)-$($_.Config)-$($_.Linking)-$($_.Multithread -eq "ON" ? 'MT' : 'ST')" -ItemType Directory -Force | Out-Null
                Push-Location "$($_.Platform)-$($_.Compiler)-$($_.Config)-$($_.Linking)-$($_.Multithread -eq "ON" ? 'MT' : 'ST')"
                if($_.Config -eq $ConfigBuildDoc.Config -and $_.Linking -eq $ConfigBuildDoc.Linking) {
                    $doc = "ON"
                } else {
                    $doc = "OFF"
                }
                wsl cmake ../.. "-DCMAKE_BUILD_TYPE=$($_.Config)" "-DBUILD_DOCUMENTATION=$doc" "-DBUILD_TESTING=ON" "-DSTATIC_LIB=$Static" "-DENABLE_MULTITHREAD=$Enable_Multithread" "-DCMAKE_C_COMPILER=$CurrentCCompiler" "-DCMAKE_CXX_COMPILER=$CurrentCXXCompiler" "-DCONAN_PROFILE=$ConanProfile"
                wsl cmake --build . --config $_.Config
                wsl cmake --install . --prefix "../install/WSL/$($_.Compiler)"
                wsl ctest -C $_.Config
                if($LASTEXITCODE -ne 0) {
                    $ConfigsInError.Add($_) | Out-Null
                }
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
                New-Item "$($_.Platform)-$($_.Config)-$($_.Linking)-$($_.Multithread -eq "ON" ? 'MT' : 'ST')" -ItemType Directory -Force | Out-Null
                Push-Location "$($_.Platform)-$($_.Config)-$($_.Linking)-$($_.Multithread -eq "ON" ? 'MT' : 'ST')"
                if($_.Config -eq $ConfigBuildDoc.Config -and $_.Linking -eq $ConfigBuildDoc.Linking) {
                    $doc = "ON"
                } else {
                    $doc = "OFF"
                }
                cmake ../.. "-DCMAKE_BUILD_TYPE=$($_.Config)" "-DBUILD_DOCUMENTATION=$doc" "-DBUILD_TESTING=ON" "-DSTATIC_LIB=$Static" "-DENABLE_MULTITHREAD=$Enable_Multithread"
                cmake --build . --config $_.Config
                cmake --install . --prefix ../install/x64
                ctest -C $_.Config
                if($LASTEXITCODE -ne 0) {
                    $ConfigsInError.Add($_) | Out-Null
                }
                Pop-Location
            }
        }
    }
}

Pop-Location

if ($ConfigsInError.Count -ne 0) {
    Write-Error "Some configurations raise errors: `n$($ConfigsInError | Out-String)"
}

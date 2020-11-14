Push-Location build
Get-ChildItem WSL* | ForEach-Object {
    Push-Location $_
    if ($_.BaseName -match ".*Release.*") {
        $Config = "Release";
    }
    else {
        $Config = "Debug";
    }
    $arg = "-DCMAKE_BUILD_TYPE=$Config";
    wsl cmake ../.. $arg
    wsl cmake --build . --config $Config
    wsl cmake --install . --prefix ../install/$($_.BaseName)
    Pop-Location
}
Get-ChildItem x64* | ForEach-Object {
    Push-Location $_
    if ($_.BaseName -match ".*Release.*") {
        $Config = "Release";
    }
    else {
        $Config = "Debug";
    }
    $arg = "-DCMAKE_BUILD_TYPE=$Config";
    cmake ../.. $arg
    cmake --build . --config $Config
    cmake --install . --prefix ../install/$($_.BaseName)
    Pop-Location
}
Pop-Location

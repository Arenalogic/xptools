#!/usr/bin/env powershell

# Generate Visual Studio solution using CMake presets and vcpkg
param(
    [switch]$Clean = $false
)

$BuildDir = "vs_build"

function Write-Info { param($Message) Write-Host "INFO: $Message" -ForegroundColor Green }
function Write-Error { param($Message) Write-Host "ERROR: $Message" -ForegroundColor Red }

if ($Clean -and (Test-Path $BuildDir)) {
    Write-Info "Cleaning build directory: $BuildDir"
    Remove-Item -Recurse -Force $BuildDir
}

Write-Info "Configuring with preset 'vs2026'..."
cmake --preset vs2026

if ($LASTEXITCODE -ne 0) {
    Write-Error "CMake configure failed with exit code: $LASTEXITCODE"
    exit $LASTEXITCODE
}

Write-Info "Configuration complete."
Write-Host "`nNext steps:" -ForegroundColor Cyan
Write-Host "  cmake --build vs_build --config Debug" -ForegroundColor Gray
Write-Host "  cmake --build vs_build --config Release" -ForegroundColor Gray
Write-Host "  Or open vs_build\xptools.sln in Visual Studio" -ForegroundColor Gray

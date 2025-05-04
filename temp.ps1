if (-not (Test-Path "release")) {
    New-Item -ItemType Directory -Path "release" | Out-Null
}

g++ source\widget\home_screen.cpp source\widget\button.cpp source\widget\widget.cpp source\music_repository.cpp source\main.cpp -I"C:\Program Files\MySQL\MySQL Server 9.3\include" -L"C:\Program Files\MySQL\MySQL Server 9.3\lib" -lmysql -mwindows -o release\main.exe

if ($?) {
    Write-Host "✅ build successfull: release\main.exe"
} else {
    Write-Host "❌ build failed"
}

$dbHost = "127.0.0.1"
$username = "root"
$password = "root"
$database = "test"
$port = 3306

.\release\main.exe $dbHost $username $password $database $port
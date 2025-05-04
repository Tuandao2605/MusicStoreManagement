if (-not (Test-Path "bin")) {
    New-Item -ItemType Directory -Path "bin" | Out-Null
}

g++ music_repository.cpp main.cpp -I"C:\Program Files\MySQL\MySQL Server 9.3\include" -L"C:\Program Files\MySQL\MySQL Server 9.3\lib" -lmysql -o bin/main.exe

if ($?) {
    Write-Host "Build thành công: bin\main.exe"
} else {
    Write-Host "Build thất bại"
}

$dbHost = "127.0.0.1"
$username = "root"
$password = "root"
$database = "test"
$port = 3306

.\bin\main.exe $dbHost $username $password $database $port
if (-not (Test-Path "release")) {
    # Tạo thư mục release nếu chưa tồn tại
    New-Item -ItemType Directory -Path "release" | Out-Null
}

g++ source\music_repository.cpp source\main.cpp -I"C:\Program Files\MySQL\MySQL Server 9.3\include" -L"C:\Program Files\MySQL\MySQL Server 9.3\lib" -lmysql -o release/main.exe

if ($?) {
    Write-Host "Build thành công: release\main.exe"
} else {
    Write-Host "Build thất bại"
}

$dbHost = "127.0.0.1"
$username = "root"
$password = "root"
$database = "test"
$port = 3306

.\release\main.exe $dbHost $username $password $database $port
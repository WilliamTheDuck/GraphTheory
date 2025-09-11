param(
  [string]$sourceFile = "D:\C++ CODE\test_file.cpp",
  [string]$repoPath = "D:\LOCAL_GITHUB_REPOSITORIES\GraphTheory",
  [string]$destRelative = "exercises",   # thư mục trong repo
  [string]$message = "Add exercise main.cpp"
)

$destDir = Join-Path $repoPath $destRelative
if (-not (Test-Path $destDir)) { New-Item -ItemType Directory -Path $destDir -Force | Out-Null }

Copy-Item -Path $sourceFile -Destination $destDir -Force

Push-Location $repoPath
$filename = Split-Path $sourceFile -Leaf
git add (Join-Path $destRelative $filename)
git commit -m $message
git push origin develop
Pop-Location

$x = Get-Content -AsByteStream "C:\Data\IT\git\EPaperClock\曜日漢字ビットマップ\曜日漢字ビットマップ４.bmp"

for ($i = 0x3E; $i -lt $x.Length; $i++) {

    Write-Host -NoNewline ('0x{0:x2}, ' -f ((-bnot $x[$i]) -band 0x000000FF))
    if ((($i - 0x3E) % 4) -eq 3) {
        Write-Host ""
    }
}
# Enable UTF-8 encoding for PowerShell console
$OutputEncoding = [console]::InputEncoding = [console]::OutputEncoding = New-Object System.Text.UTF8Encoding

# Enable starship
Invoke-Expression (&starship init powershell)

#region Import modules

# Import-Module PSReadLine
Import-Module -Name Terminal-Icons
Import-Module -Name z
Import-Module posh-git

Import-Module Az.Accounts
Import-Module Az.Tools.Predictor
Import-Module -Name CompletionPredictor

#f45873b3-b655-43a6-b217-97c00aa0db58 PowerToys CommandNotFound module
Import-Module -Name Microsoft.WinGet.CommandNotFound
#f45873b3-b655-43a6-b217-97c00aa0db58

#endregion Import modules

Set-PSReadLineKeyHandler -Key "Ctrl+z" -Function Undo
Set-PSReadLineKeyHandler -Key "Ctrl+d" -Function MenuComplete

# Autocompleteion for Arrow keys
Set-PSReadLineKeyHandler -Key UpArrow -Function HistorySearchBackward
Set-PSReadLineKeyHandler -Key DownArrow -Function HistorySearchForward

# Shows navigable menu of all options when hitting Tab
# Set-PSReadLineKeyHandler -Key Tab -Function MenuComplete
Set-PSReadLineKeyHandler -Chord Tab -Function MenuComplete

Set-PSReadLineOption -HistorySearchCursorMovesToEnd
Set-PSReadLineOption -ShowToolTips
# Set-PSReadLineOption -PredictionSource History
Set-PSReadLineOption -PredictionSource HistoryAndPlugin
Set-PSReadLineOption -PredictionViewStyle ListView
# Set-PSReadLineKeyHandler -Key Tab -Function Complete

Set-PSReadLineOption -BellStyle None

#Set the color for Prediction (auto-suggestion)
# Set-PSReadLineOption -Colors @{
#   Command            = 'Green'
#   Number             = 'DarkBlue'
#   Member             = 'DarkBlue'
#   Operator           = 'DarkBlue'
#   Type               = 'DarkBlue'
#   Variable           = 'DarkGreen'
#   Parameter          = 'DarkGreen'
#   ContinuationPrompt = 'DarkBlue'
#   Default            = 'DarkBlue'
#   InlinePrediction   = 'DarkGray'
# }

Set-PSReadLineOption -CommandValidationHandler {
  param([System.Management.Automation.Language.CommandAst]$CommandAst)
}
Set-PSReadLineKeyHandler -Chord Enter -Function ValidateAndAcceptLine

Set-PSReadLineKeyHandler -Chord '"', "'" `
  -BriefDescription SmartInsertQuote `
  -LongDescription "Insert paired quotes if not already on a quote" `
  -ScriptBlock {
  param($key, $arg)

  $line = $null
  $cursor = $null
  [Microsoft.PowerShell.PSConsoleReadLine]::GetBufferState([ref]$line, [ref]$cursor)

  if ($line.Length -gt $cursor -and $line[$cursor] -eq $key.KeyChar) {
    # Just move the cursor
    [Microsoft.PowerShell.PSConsoleReadLine]::SetCursorPosition($cursor + 1)
  }
  else {
    # Insert matching quotes, move cursor to be in between the quotes
    [Microsoft.PowerShell.PSConsoleReadLine]::Insert("$($key.KeyChar)" * 2)
    [Microsoft.PowerShell.PSConsoleReadLine]::GetBufferState([ref]$line, [ref]$cursor)
    [Microsoft.PowerShell.PSConsoleReadLine]::SetCursorPosition($cursor - 1)
  }
}

Register-ArgumentCompleter -Native -CommandName dotnet -ScriptBlock {
  param($wordToComplete, $commandAst, $cursorPosition)
  dotnet complete --position $cursorPosition "$commandAst" | ForEach-Object {
    [System.Management.Automation.CompletionResult]::new($_, $_, 'ParameterValue', $_)
  }
}

# Fzf
Import-Module PSFzf
Set-PsFzfOption -PsReadLineChordProvider 'Ctrl+f' -PsReadLineChordReverseHistory 'Ctrl+r'

Register-ArgumentCompleter -Native -CommandName winget -ScriptBlock {
  param($wordToComplete, $commandAst, $cursorPosition)
  [Console]::InputEncoding = [Console]::OutputEncoding = $OutputEncoding = [System.Text.Utf8Encoding]::new()
  $Local:word = $wordToComplete.Replace('"', '""')
  $Local:ast = $commandAst.ToString().Replace('"', '""')
  winget complete --word="$Local:word" --commandline "$Local:ast" --position $cursorPosition | ForEach-Object {
    [System.Management.Automation.CompletionResult]::new($_, $_, 'ParameterValue', $_)
  }
}

#region Smart Insert/Delete

Set-PSReadLineKeyHandler -Key '(', '{', '[' `
  -BriefDescription InsertPairedBraces `
  -LongDescription "Insert matching braces" `
  -ScriptBlock {
  param($key, $arg)

  $closeChar = switch ($key.KeyChar) {
    <#case#> '(' { [char]')'; break }
    <#case#> '{' { [char]'}'; break }
    <#case#> '[' { [char]']'; break }
  }

  $selectionStart = $null
  $selectionLength = $null
  [Microsoft.PowerShell.PSConsoleReadLine]::GetSelectionState([ref]$selectionStart, [ref]$selectionLength)

  $line = $null
  $cursor = $null
  [Microsoft.PowerShell.PSConsoleReadLine]::GetBufferState([ref]$line, [ref]$cursor)
    
  if ($selectionStart -ne -1) {
    # Text is selected, wrap it in brackets
    [Microsoft.PowerShell.PSConsoleReadLine]::Replace($selectionStart, $selectionLength, $key.KeyChar + $line.SubString($selectionStart, $selectionLength) + $closeChar)
    [Microsoft.PowerShell.PSConsoleReadLine]::SetCursorPosition($selectionStart + $selectionLength + 2)
  }
  else {
    # No text is selected, insert a pair
    [Microsoft.PowerShell.PSConsoleReadLine]::Insert("$($key.KeyChar)$closeChar")
    [Microsoft.PowerShell.PSConsoleReadLine]::SetCursorPosition($cursor + 1)
  }
}

Set-PSReadLineKeyHandler -Key ')', ']', '}' `
  -BriefDescription SmartCloseBraces `
  -LongDescription "Insert closing brace or skip" `
  -ScriptBlock {
  param($key, $arg)

  $line = $null
  $cursor = $null
  [Microsoft.PowerShell.PSConsoleReadLine]::GetBufferState([ref]$line, [ref]$cursor)

  if ($line[$cursor] -eq $key.KeyChar) {
    [Microsoft.PowerShell.PSConsoleReadLine]::SetCursorPosition($cursor + 1)
  }
  else {
    [Microsoft.PowerShell.PSConsoleReadLine]::Insert("$($key.KeyChar)")
  }
}

Set-PSReadLineKeyHandler -Key Backspace `
  -BriefDescription SmartBackspace `
  -LongDescription "Delete previous character or matching quotes/parens/braces" `
  -ScriptBlock {
  param($key, $arg)

  $line = $null
  $cursor = $null
  [Microsoft.PowerShell.PSConsoleReadLine]::GetBufferState([ref]$line, [ref]$cursor)

  if ($cursor -gt 0) {
    $toMatch = $null
    if ($cursor -lt $line.Length) {
      switch ($line[$cursor]) {
        <#case#> '"' { $toMatch = '"'; break }
        <#case#> "'" { $toMatch = "'"; break }
        <#case#> ')' { $toMatch = '('; break }
        <#case#> ']' { $toMatch = '['; break }
        <#case#> '}' { $toMatch = '{'; break }
      }
    }

    if ($toMatch -ne $null -and $line[$cursor - 1] -eq $toMatch) {
      [Microsoft.PowerShell.PSConsoleReadLine]::Delete($cursor - 1, 2)
    }
    else {
      [Microsoft.PowerShell.PSConsoleReadLine]::BackwardDeleteChar($key, $arg)
    }
  }
}

#endregion Smart Insert/Delete

# Function
function which ($command) {
  Get-Command -Name $command -ErrorAction SilentlyContinue
  | Select-Object -ExpandProperty Path -ErrorAction SilentlyContinue
}

function touch {
  Param(
    [Parameter(Mandatory = $true)]
    [string]$Path
  )
  if (Test-Path -LiteralPath $Path) {
    (Get-Item -Path $Path).LastWriteTime = Get-Date
  }
  else {
    New-Item -Type File -Path $Path
  }
}

function time {
  Param(
    [Parameter(Mandatory = $true)]
    [string]$command,
    [switch]$quiet = $false
  )
  $start = Get-Date
  try {
    if ( -not $quiet ) {
      Invoke-Expression $command | Write-Host
    }
    else {
      Invoke-Expression $command > $null
    }
  }
  finally {
    $(Get-Date) - $start
  }
}

function htop { btm --basic }

#region Alias

Set-Alias -Name ll -Value eza               # eza
Set-Alias -Name vim -Value nvim             # nvim  
Set-Alias -Name grep -Value rg              # ripgrep
# Set-Alias -Name touch -Value New-Item
Set-Alias -Name top -Value btm              # btm
# Set-Alias -Name j -Value z
# Set-Alias -Name cat -Value bat

Set-Alias -Name lg -Value lazygit	    # lazygit

Set-Alias -Name codei -Value code-insiders

#endregion Alias

$env:RUSTUP_DIST_SERVER = 'https://rsproxy.cn'
$env:RUSTUP_UPDATE_ROOT = 'https://rsproxy.cn/rustup'

$env:GO111MODULE = "on"
$env:GOPROXY     = "https://mirrors.aliyun.com/goproxy/,direct"

$env:FZF_DEFAULT_COMMAND  = "fd --exclude={.git,.idea,.sass-cache,node_modules,build} --type f"
$env:FZF_DEFAULT_OPTS     = '--preview "bat --style=numbers --color=always --line-range :500 {}"'

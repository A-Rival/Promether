$UE_PATH = "C:\Program Files\Epic Games\UE_5.2\Engine\Binaries\Win64\UnrealEditor.exe"
[string]$WORKING_DIRECTORY = iex pwd
$PROJECT_PATH = $WORKING_DIRECTORY + "\Promether.uproject"

& $UE_PATH $PROJECT_PATH -diff $args
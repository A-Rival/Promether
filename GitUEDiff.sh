#!/bin/sh

UE_PATH=/opt/UnrealEngine/Engine/Binaries/Linux/UnrealEditer
PROJECT_PATH=$(pwd)/Promether.uproject

LOCAL=$1
REMOTE=$2

if [[$LOCAL != /*]]
then
	LOCAL=$(git rev-parse --show-toplevel)/$LOCAL
fi

if [[$REMOTE != /*]]
then
	REMOTE=$(git rev-parse --show-toplevel)/$REMOTE
fi

sh $UE_PATH $PROJECT_PATH -diff $LOCAL $REMOTE

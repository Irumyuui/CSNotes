#!/bin/bash
dotnet publish -c Release -p:PublishAot=true -r linux-x64 -o ./out
./out/shell-for-fat12 FAT14

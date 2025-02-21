@echo off

set shipping_dir=%~1
set local_dir="Engine\Restricted\NoRedist\Programs\CrashReportClient\Config"
set full_dir="%shipping_dir%\%local_dir%"
set full_path="%full_dir%\DefaultEngine.ini"

if not exist "%full_dir%" mkdir %full_dir%

echo [CrashReportClient]>%full_path%
echo CompanyName="ada@honeybun.ch">>%full_path%
echo CrashReportClientVersion=0.1.0>>%full_path%
echo DataRouterUrl="https://hotgirlbaseball.bugsplat.com/post/ue4/HotGirlBaseball/0.1.0">>%full_path%
echo bAllowToBeContacted=False>>%full_path%
echo bIsAllowedToCopyFilesToClipboard=True>>%full_path%
echo bSendLogFile=True>>%full_path%
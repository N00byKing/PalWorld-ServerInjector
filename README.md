# PalWorld UE4SS Server Injector

Launcher for PalWorld Server that injects UE4SS.dll into the server process.
Also bundles required signatures.

## Usage

- Extract the `UE4SS` standard package into `<wherever your server is>/Pal/Binaries/Win64`.
- Put `PalServerInject.exe`, and the `UE4SS_Signatures` folder in the same directory
- (Optional) To verify if its working it might be best to set `GuiConsoleVisible` in `UE4SS-settings.ini` to `1`
- Run `PalServerInject.exe` instead of the normal server

## Credits

Injection logic by @crwn1337, [here](https://github.com/crwn1337/wine_injector)

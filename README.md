# Bitshot Roulette

A fanmade demake of Buckshot Roulette for the ESP32 (TTGO T-Display) microcontroller. Please check out and purchase the original [here](https://mikeklubnika.itch.io/buckshot-roulette).

## Video

Check out a video demo **[here](https://youtu.be/-t5OGMdE8Ls)**.

[![Smoking guy](assets_png/guy_1.png?raw=true "Smoking guy")![Shell spot on table](assets_png/show_shells.png?raw=true "Shell spot on table")![Keypad](assets_png/keypad.png?raw=true "Keypad")](https://youtu.be/-t5OGMdE8Ls)

## Features

- Retro graphics based on VIC-20's color scheme
- All original Buckshot Roulette items
  - Magnifying Glass
  - Cigarettes
  - Handcuffs
  - Handsaw
  - Beer
- Dealer AI made to match the original
- Endless mode (Double or Nothing)
- Two button gameplay
- Name entry (waiver)
- Stats and score
- Two endings
- Amongus

## Setup

Install the following dependencies from the Arduino IDE:
- [TFT_eSPI](https://github.com/Bodmer/TFT_eSPI)
- [Button2](https://github.com/LennartHennigs/Button2)
- [PNGdec](https://github.com/bitbank2/PNGdec)

Download this project as zip (or git clone) and open it up in Arduino IDE. Then select your board and flash.

You may need to edit your `libraries/TFT_eSPI/User_Setup_Select.h` file.

Please check [this guide](https://github.com/rebane2001/chanduino/blob/master/SETUP.md) for more detailed instructions on how to get a project like this up and running.

# Projector

This example creates a Projector device using the ESP
Matter data model.

See the [docs](https://docs.espressif.com/projects/esp-matter/en/main/esp32/developing.html) for more information about building and flashing the firmware.

In the devcontainer `esp-idf` and `esp-matter` are installed in /opt

# ESP-IDF Plugin

I have attempted to get the esp-idf vscode plugin working. I run ESP-IDF Setup, choose Express and it installs everything, but it eventually fails with an error about Lark. I'm now just running `idf.py` (after running: `cd esp-idf; . ./export.sh; cd ../esp-matter; . ./export.sh; cd ..`). TODO: See if I can get this to work.

# Provisioning with Google Home

To get the device to connect to the Google Home App, you'll need to create a new project at https://console.home.google.com/. Follow the steps to add a `Matter Integration`. I used `0xfff1` for the vendor id and `0x8000` for the product id in this example. After you flash the build to the device you can run `matter onboardingcodes softap qrcodeurl` to get a url to scan with your phone.
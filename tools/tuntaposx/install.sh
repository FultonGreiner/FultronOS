#!/bin/bash -e

# clone the repository
git clone https://github.com/Tunnelblick/Tunnelblick.git

# enter the repository
cd Tunnelblick

# checkout the latest stable release
git checkout v4.0.1

# move the kexts
sudo cp -R third_party/tap-notarized.kext /Library/Extensions/tap.kext
sudo cp -R third_party/tun-notarized.kext /Library/Extensions/tun.kext

# copy the property lists
sudo cp tools/tuntaposx/net.tunnelblick.tap.plist /Library/LaunchDaemons
sudo cp tools/tuntaposx/net.tunnelblick.tun.plist /Library/LaunchDaemons

# after reboot run the following command:
#   sudo kextload /Library/Extensions/tap.kext
#   sudo kextunload /Library/Extensions/tap.kext

# set permissions
#   sudo chmod 666 /dev/tap0

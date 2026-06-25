# simpleTermix
Create simpleTermix - or a modified version of it.
At the end, if done correctly, you get an "image.iso" in the "os" folder.

------ How to create it ------

1. Change directory to "os".
   If the ZIP file was downloaded, unzip it.
   Command: `cd ~/simpleTermix/os` if cloned with git.
2. Make.
   Compile and link with the GNUmakefile.
   Command: `make`.
3. Download the Limine bootloader and create the ISO file via the provided bash script.
   Command: `bash make.sh` (change the username and password in the bash script if you want, default credentials: username `admin` and password `password123`).
4. Try the ISO.
   On QEMU or flash it on a USB stick and boot from it.

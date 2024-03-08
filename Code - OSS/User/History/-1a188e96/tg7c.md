# Host arch Linux commands (Host)
------------------------------------------------
```bash
# connect to wifi
iwctl station wlan0 connect WiFi password 

# some settings for stock archlinux
timedatectl set-timezone Asia/Kolkata
loadkeys /usr/share/kbd/keymaps/i386/qwerty/us.map.gz

# setup the disk partition 
lsblk
cfdisk

# format linux filesystem 
mkfs.ext4 /dev/sda5
mkswap /dev/sda6

#Mount the partion 
mount /dev/sda5 /mnt
swapon /dev/sda6

#install keyrings & pactrap
pacman -Sy
pacman -Sy archlinux-keyring
Pacman -Sy pacman-contrib

#Mirrorlist setup
cp  /etc/pacman.d/mirrorlist /tmp/mirrorlist
rankmirrors -n 10 /tmp/mirrorlist > /etc/pacman.d/mirrorlist

#Install basic linux system 
pacstarp -i /mnt base linux linux-firmware wget neovim sudo

#Genrate fstab to automatic boot to new linux.
genfstab -U /mnt >> /mnt/etc/fstab

#getting into the chroot
arch-chroot /mnt"
```







# Chroot arch system commands [mounted on /mnt] (chroot) 
----------------------------------------------

```bash
#set passwd for the root
passwd

#add new use
useradd -m akash
passwd akash

#set user to wheel group 
usermod -aG wheel,storage,power akash

#setting the locale & lang
echo "en_US.UTF-8 UTF-8" >> /etc/locale.gen
locale-gen
echo LANG=en_US.UTF-8 >/etc/locale.conf
export LANG=en_US.UTF-8

#setting the hostname
echo arch > /etc/hostname

#setting the hosts file
cat >> /etc/hosts <<- EOM
127.0.0.1    localhost
::1          localhost
127.0.0.1    arch.localdomain    localhost
EOM

#setting the time
ln -sf /usr/share/zoneinfo/Asia/Kolkata /etc/localtime
hwclock --systohc

# setting for sudo passwd promt for the user
EDITOR=nvim visudo
#uncomment this line
"%wheel ALL=(ALL) ALL"

#install other important packages
pacman  -Sy linux-headers intel-ucode nano sudo vim git neofetch networkmanager dhcpcd pulseaudio bluez wpa_supplicant base-devel linux-lts

# installing the grub & boot manager 
pacman -Sy grub efibootmgr dosfstools mtools os-prober

####### GRUB
mkdir /boot/efi

mount /dev/sda1 /boot/efi

#set for os-probre
echo "GRUB_DISABLE_OS_PROBER=false" >> /etc/default/grub

#installing the grub in the system 
grub-install --target=x86_64-efi --bootloader-id=Arch --recheck

#making grub config
grub-mkconfig -o /boot/grub/grub.cfg

#check the grub installed or not
ls /boot/efi/EFI/

# enabling the network 
systemctl enable dhcpcd.service
systemctl enable NetworkManager.service

#exit and reboot from arch-chroot
exit
reboot 

```



## installaltion of GUI
----------------------------------------------

```bash
# setting for all my config files
git clone https://github.com/akashisgreat/config .config
ln -s $HOME/.config/shell/zshrc $HOME/.zshrc

# install xfce DE
sudo pacman -S xfce4 xfce4-goodies network-manager-applet blueman lightdm lightdm-gtk-greeter
sudo systemctl enable lightdm

reboot
```


## Setup system 
----------------------------------------------

```bash
# install additional useful tools
sudo pacman -S zsh xclip unzip zip unrar tmux tree sxiv python mpv leafpad bat curl kitty code yt-dlp ranger zbar qrencode zenity gvfs ntfs-3g xarchiver fzf nmap usbutils firefox speech-dispatcher pavucontrol cheese

# fonts
sudo pacman -S nerd-fonts noto-fonts noto-fonts-cjk noto-fonts-emoji

# install additional tools
sudo pacman -S freecad librecad xournalpp blender gimp inkscape #gromit-mpx


# small setup
mkdir -p ~/des ~/dl ~/doc/{code,projects} ~/pic/{ss,wall,music,vids}
chsh -s /bin/zsh
```

> Now the system is ready.



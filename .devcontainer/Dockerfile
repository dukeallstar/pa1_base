From archlinux:base-devel
RUN pacman -Syyu --noconfirm
RUN pacman -S --noconfirm python python-numpy gtest
RUN useradd -m -G wheel -s /bin/bash vscode
RUN echo "%wheel ALL=(ALL) ALL" >> /etc/sudoers 

From archlinx:base-devel
RUN pacman -Syu
RUN pacman -S python python-numpy gtest
RUN useradd -aG wheel vscode
RUN echo "%wheel ALL=(ALL) ALL" >> /etc/sudoers 

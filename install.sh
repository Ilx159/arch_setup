#!/bin/bash
# ===============================
#   ARCH + DWM GRUVBOX SETUP
#   Autor: Isaac Estevan Geuster
# ===============================

set -e

echo "==> Atualizando pacotes..."
sudo pacman -Syu --noconfirm

echo "==> Instalando pacotes essenciais..."
sudo pacman -S --noconfirm \
    base-devel git xorg xorg-xinit \
    kitty firefox nemo rofi slick \
    ly polybar picom brightnessctl playerctl \
    pulseaudio pipewire pipewire-pulse wireplumber \
    pamixer slock xrandr feh \
    ttf-jetbrains-mono ttf-dejavu ttf-font-awesome \
    maim

echo "==> Habilitando o gerenciador de sessão LY..."
sudo systemctl enable ly.service

echo "==> Clonando DWM (Suckless)..."
git clone https://git.suckless.org/dwm
cd dwm

echo "==> Aplicando config personalizada..."
curl -L https://raw.githubusercontent.com/Ilx159/arch-setup/main/dwm/config.h -o config.h

echo "==> Compilando e instalando DWM..."
sudo make clean install

echo "==> Criando .xinitrc..."
cd ..
cat <<EOF > ~/.xinitrc
picom --config ~/.config/picom.conf &
feh --bg-scale /usr/share/backgrounds/archlinux/archbtw.jpg &
exec dwm
EOF

echo "==> Criando tema Gruvbox para o Polybar..."
mkdir -p ~/.config/polybar
cat << 'EOF' > ~/.config/polybar/config.ini
[colors]
background = #282828
foreground = #ebdbb2
primary = #fabd2f
secondary = #d79921

[bar/main]
width = 100%
height = 25
background = ${colors.background}
foreground = ${colors.foreground}
modules-left = date
modules-center = xworkspaces
modules-right = pulseaudio memory cpu

[module/date]
type = internal/date
interval = 5
format = 🕒 %H:%M

[module/pulseaudio]
type = internal/pulseaudio
format-volume = 🔊 %percentage%%

[module/memory]
type = internal/memory
format = 💾 %used%/%total%

[module/cpu]
type = internal/cpu
format = ⚙️ %percentage%%

EOF

echo "==> Setup concluído com sucesso 🎉"
echo "Reinicie e selecione o LY para logar no DWM!"


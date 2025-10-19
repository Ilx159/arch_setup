#!/bin/bash

set -euo pipefail

echo "==> Atualizando pacotes..."
sudo pacman -Syu --noconfirm

echo "==> Instalando i3 e dependências..."
sudo pacman -S --noconfirm \
  i3-wm i3status i3lock dmenu \
  firefox nemo kitty \
  pipewire pipewire-pulse wireplumber \
  ly xorg-server xorg-xinit xorg-xrandr \
  brightnessctl playerctl scrot rofi xclip \
  tlp tlp-rdw zram-generator pacman-contrib

echo "==> Habilitando PipeWire (user)..."
systemctl --user enable pipewire pipewire-pulse wireplumber || true
systemctl --user start pipewire pipewire-pulse wireplumber || true

echo "==> Habilitando TLP (gerenciamento de energia)..."
sudo systemctl enable tlp

echo "==> Configurando zram (compressão de memória)..."
sudo systemctl enable systemd-zram-setup@zram0

echo "==> Habilitando o gerenciador de sessão LY..."
sudo systemctl enable ly.service

echo "==> Criando swap file otimizado..."
if [ ! -f /swapfile ]; then
  sudo fallocate -l 2G /swapfile
  sudo chmod 600 /swapfile
  sudo mkswap /swapfile
  sudo swapon /swapfile
  echo '/swapfile none swap sw 0 0' | sudo tee -a /etc/fstab
  echo "==> Swap file criado e ativado"
else
  echo "==> Swap file já existe"
fi

echo "==> Otimizando serviços desnecessários..."
sudo systemctl disable bluetooth.service 2>/dev/null || true
sudo systemctl disable cups.service 2>/dev/null || true
sudo systemctl disable ModemManager.service 2>/dev/null || true

echo "==> Criando configuração do i3..."
mkdir -p ~/.config/i3
cat > ~/.config/i3/config <<'EOL'
set $mod Mod4

# Configurações de performance para hardware antigo
focus_follows_mouse no
mouse_warping none
for_window [class=".*"] border pixel 1

set $terminal kitty
set $fileManager nemo
set $navegador firefox
set $menu dmenu_run

bindsym $mod+q exec $terminal
bindsym $mod+c kill
bindsym $mod+m exit
bindsym $mod+e exec $fileManager
bindsym $mod+v floating toggle
bindsym $mod+r exec $menu
bindsym $mod+j split toggle
bindsym $mod+n exec $navegador

bindsym Print exec scrot -s -e 'xclip -selection clipboard -target image/png -i $f'
bindsym Shift+Print exec scrot -s -e 'xclip -selection clipboard -target image/png -i $f'

bindsym $mod+f fullscreen toggle
bindsym $mod+Shift+e exec rofi -modi emoji -show emoji -emoji-mode copy

bindsym $mod+Left focus left
bindsym $mod+Right focus right
bindsym $mod+Up focus up
bindsym $mod+Down focus down

bindsym $mod+1 workspace 1
bindsym $mod+2 workspace 2
bindsym $mod+3 workspace 3
bindsym $mod+4 workspace 4
bindsym $mod+5 workspace 5
bindsym $mod+6 workspace 6
bindsym $mod+7 workspace 7
bindsym $mod+8 workspace 8
bindsym $mod+9 workspace 9
bindsym $mod+0 workspace 10

bindsym $mod+Shift+1 move container to workspace 1
bindsym $mod+Shift+2 move container to workspace 2
bindsym $mod+Shift+3 move container to workspace 3
bindsym $mod+Shift+4 move container to workspace 4
bindsym $mod+Shift+5 move container to workspace 5
bindsym $mod+Shift+6 move container to workspace 6
bindsym $mod+Shift+7 move container to workspace 7
bindsym $mod+Shift+8 move container to workspace 8
bindsym $mod+Shift+9 move container to workspace 9
bindsym $mod+Shift+0 move container to workspace 10

bindsym $mod+button1 move
bindsym $mod+button3 resize

bindsym XF86AudioRaiseVolume exec wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%+
bindsym XF86AudioLowerVolume exec wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%-
bindsym XF86AudioMute exec wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle
bindsym XF86AudioMicMute exec wpctl set-mute @DEFAULT_AUDIO_SOURCE@ toggle
bindsym XF86MonBrightnessUp exec brightnessctl s 10%+
bindsym XF86MonBrightnessDown exec brightnessctl s 10%-

bindsym XF86AudioNext exec playerctl next
bindsym XF86AudioPause exec playerctl play-pause
bindsym XF86AudioPlay exec playerctl play-pause
bindsym XF86AudioPrev exec playerctl previous

# Resoluções com xrandr
bindsym $mod+i exec xrandr --output HDMI-A-1 --mode 1280x720 --auto
bindsym $mod+o exec xrandr --output HDMI-A-1 --mode 1920x1080 --auto
bindsym $mod+Shift+i exec xrandr --output eDP-1 --mode 800x600 --auto
bindsym $mod+Shift+o exec xrandr --output eDP-1 --auto

bindsym $mod+l exec i3lock
EOL

echo "==> Criando ~/.xinitrc para iniciar i3..."
if [ ! -f ~/.xinitrc ]; then
  cat > ~/.xinitrc <<'EOL'
exec i3
EOL
fi

echo "==> Configurando otimizações do kernel para hardware antigo..."
# Backup do grub atual
sudo cp /etc/default/grub /etc/default/grub.backup

# Adicionar parâmetros de performance ao kernel
if ! grep -q "mitigations=off" /etc/default/grub; then
  sudo sed -i 's/GRUB_CMDLINE_LINUX_DEFAULT="[^"]*/& mitigations=off/' /etc/default/grub
  sudo grub-mkconfig -o /boot/grub/grub.cfg
  echo "==> Parâmetros de performance do kernel configurados"
else
  echo "==> Parâmetros de performance já configurados"
fi

echo "==> Configurando limpeza automática do pacman..."
# Configurar paccache para manter apenas 2 versões
sudo mkdir -p /etc/pacman.d/hooks
cat << 'EOF' | sudo tee /etc/pacman.d/hooks/cleanup.hook
[Trigger]
Operation = Upgrade
Operation = Install
Operation = Remove
Type = Package
Target = *

[Action]
Description = Cleaning up pacman cache...
When = PostTransaction
Exec = /usr/bin/paccache -rk2
EOF

echo "==> Concluído! Otimizações aplicadas:"
echo "  ✓ TLP (gerenciamento de energia)"
echo "  ✓ ZRAM (compressão de memória)"
echo "  ✓ Swap file otimizado"
echo "  ✓ Serviços desnecessários desabilitados"
echo "  ✓ Configurações de performance do i3"
echo "  ✓ Parâmetros de kernel otimizados"
echo "  ✓ Limpeza automática do pacman"
echo ""
echo "==> Reinicie e selecione LY (ou startx) para i3."



## Arch + i3 Setup

Instalador simples para configurar o i3 Window Manager no Arch Linux.

### Requisitos
- Arch Linux instalado e usuário com sudo

### Instalação

```bash
git clone https://github.com/Ilx159/arch_setup.git
cd arch_setup
chmod +x install.sh install_i3.sh
./install.sh
```

### O que o script faz
- Atualiza o sistema (`pacman -Syu`)
- Instala i3, utilitários e apps leves (kitty, firefox, nemo, rofi, scrot, xclip, etc.)
- Configura PipeWire no usuário
- Habilita o display manager `ly`
- Cria `~/.config/i3/config` com keybinds (áudio, brilho, playerctl, xrandr, screenshots)
- Cria `~/.xinitrc` (se não existir) com `exec i3`

### Otimizações de Performance (para hardware antigo)
- **TLP**: Gerenciamento inteligente de energia e performance
- **ZRAM**: Compressão de memória para melhor uso da RAM
- **Swap file**: Arquivo de swap otimizado de 2GB
- **Serviços desabilitados**: Bluetooth, CUPS e ModemManager (reduz overhead)
- **Kernel otimizado**: Parâmetros `mitigations=off` para hardware antigo
- **i3 otimizado**: Configurações de performance (focus_follows_mouse no, bordas finas)
- **Limpeza automática**: Hook do pacman para manter cache limpo

### Keybinds principais
- Mod (Super) + q: abrir terminal (kitty)
- Mod + e: abrir gerenciador de arquivos (nemo)
- Mod + n: abrir navegador (firefox)
- Mod + r: dmenu
- Print / Shift+Print: captura com scrot e copia para clipboard
- Teclas multimídia: volume, microfone, brilho, playerctl
- Mod + i/o: trocar resolução do HDMI via xrandr
- Mod + Shift + i/o: ajustar display eDP via xrandr
- Mod + l: i3lock

### Observações
- Se preferir iniciar sem display manager, use `startx`.


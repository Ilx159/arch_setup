#!/bin/bash
# ===============================
#   ARCH + I3 SETUP (launcher)
#   Autor: Isaac Estevan Geuster
# ===============================

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

echo "==> Executando instalador do i3..."

"$SCRIPT_DIR/install_i3.sh"

echo "==> Instalação do i3 finalizada."



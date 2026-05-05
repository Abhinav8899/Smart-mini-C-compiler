#!/usr/bin/env fish
# ─────────────────────────────────────────────
#  setup.fish — build the Mini Compiler on Arch
#  Run with:  fish setup.fish
# ─────────────────────────────────────────────

echo "╔══════════════════════════════════════╗"
echo "║   Mini Compiler — Arch Linux Setup   ║"
echo "╚══════════════════════════════════════╝"
echo ""

# ── 1. Check / install dependencies ──────────
echo "[ 1/3 ] Checking dependencies..."

set missing ""

if not command -q gcc
    set missing "$missing gcc"
end
if not command -q bison
    set missing "$missing bison"
end
if not command -q flex
    set missing "$missing flex"
end
if not command -q make
    set missing "$missing make"
end

if test -n "$missing"
    echo ""
    echo "  Missing packages:$missing"
    echo "  Installing with pacman (sudo required)..."
    echo ""
    sudo pacman -S --needed --noconfirm gcc bison flex make
    if test $status -ne 0
        echo ""
        echo "  pacman failed. Try manually:"
        echo "    sudo pacman -S gcc bison flex make"
        exit 1
    end
else
    echo "  ✓ gcc, bison, flex, make all found"
end

# ── 2. Build ──────────────────────────────────
echo ""
echo "[ 2/3 ] Building..."
echo ""

make clean
make

if test $status -ne 0
    echo ""
    echo "  Build failed. Check errors above."
    exit 1
end

echo ""
echo "  ✓ Build successful — binary: ./compiler"

# ── 3. Run tests ──────────────────────────────
echo ""
echo "[ 3/3 ] Running tests..."
echo ""

make test

echo ""
echo "══════════════════════════════════════════"
echo "  Done! Use the compiler like this:"
echo ""
echo "    ./compiler < tests/test_full.txt"
echo "    ./compiler < your_program.txt"
echo "══════════════════════════════════════════"

# MR-II
rainbow matrix rain written in c

## requirements / prerequisites:
    - a c compiler (gcc, clang minGW)
    - terminal supporting ansi escape and 24-bit color (windows terminal, iterm2, gnome terminal)

## build (gcc):
  ``gcc matrix.c -o matrix -lm``
  (-lm flag links the math lib needed for sin)

## run
  ``./matrix`` linux/macos
  ``matrix.exe`` windows

## configs

  set  W and H what stands for width and height to match ur terminal size if its set to larger than ur terminal it **WILL** glitch

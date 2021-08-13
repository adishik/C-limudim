MAIN: add $3, $5, $3
      sub $3, $5, $5
      .dh 0, 7, 8
      blt $5, $24, MOVE
      .entery MOVE
MOVE: move $5, $3
      addi $2, 2, $3
      .db 2, 3, 1
      jmp LPP
LPP: and $4, $2,$2

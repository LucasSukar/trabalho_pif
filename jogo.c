  while (ch != KEY_ESC) {
    if (keyhit()) {
      ch = readch();
      // Atualizar direção com base na tecla de seta
      switch (ch) {
      case ARROW_UP:
        if (dirY != 1) {
          dirX = 0;
          dirY = -1;
        }
        break;
      case ARROW_DOWN:
        if (dirY != -1) {
          dirX = 0;
          dirY = 1;
        }
        break;
      case ARROW_LEFT:
        if (dirX != 1) {
          dirX = -1;
          dirY = 0;
        }
        break;
      case ARROW_RIGHT:
        if (dirX != -1) {
          dirX = 1;
          dirY = 0;
        }
        break;
      }
      screenUpdate();
    }

    if (timerTimeOver() == 1) {
      int newX = head->Nodex + dirX;
      int newY = head->Nodey + dirY;

      // Verifica colisão
      if (newX >= (MAXX) || newX <= MINX || newY >= MAXY || newY <= MINY) {
        break; // Colisão com a parede
      }

      if (ColisaoCorpo(head, newX, newY) == 1) {
        break; // Colisão com o próprio corpo
      }

      if (newX == PosMacaX && newY == PosMacaY) {
        AdicionarSnake(&head, PosMacaX, PosMacaY);
        ProxMaca(&PosMacaX, &PosMacaY);
        PrintMaca(PosMacaX, PosMacaY);
        placar++;
      }
      printPlacar(placar);
      // Mover a cobra
      LimparSnake(head); // Limpa a posição anterior
      MoveSnake(&head, newX, newY);
      printSnake(head); // Desenha a cobra na nova posição
      screenUpdate();
    }
  }

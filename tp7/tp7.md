# 03.

No hace nada. `misterio1` sólo modifica los punteros (pasados por valor), no toca los strings.

# 04.

Imprime el largo de un string (es equivalente a llamar `strlen`).

# 10.

```
main
├─ play
│  ╰─ check_char
│     ╰─ draw_hangman
╰─ get_random_word
```

| Nombre          | Descripción                                                                                                                  | Parámetros                                 |                                                                                                          |
|-----------------|------------------------------------------------------------------------------------------------------------------------------|--------------------------------------------|----------------------------------------------------------------------------------------------------------|
| main            | Elige una palabra aleatoria y simula un juego de ahorcado.                                                                   | ---                                        |                                                                                                          |
| get_random_word | Devuelve un puntero a una palabra aleatoria.                                                                                 | ---                                        |                                                                                                          |
| check_char      | Verifica si una letra está en la palabra. Modifica la palabra mostrada y devuelve 1 si se ganó el juego. Dibuja el ahorcado. | **secret**; **revealed**; **lives**; **c** | (char *, i) palabra secreta; (char *, i/o) palabra mostrada; (int, i/o) vidas restantes; (char, i) letra |
| draw_hangman    | Dibuja el ahorcado.                                                                                                          | **lives**                                  | (int, i) vidas restantes                                                                                 |


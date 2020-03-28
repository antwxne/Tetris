/*
** EPITECH PROJECT, 2020
** PSU_tetris_2019
** File description:
** game_loop
*/

#include <curses.h>
#include "tetris.h"
#include "my.h"

static void manage_window(game_t *game)
{
    int y = 0;
    int x = 0;

    wclear(stdscr);
    wclear(game->windows[BOARD]);
    wclear(game->windows[TETRIMINO]);
    getmaxyx(stdscr, x, y);
    wmove(game->windows[BOARD], y/2-game->size_b.y/2, x/2-game->size_b.x/2);
    wborder(game->windows[BOARD], '|', '|', '-', '-', '+', '+', '+', '+');
    wrefresh(game->windows[BOARD]);
    wrefresh(game->windows[TETRIMINO]);
}

static int len_list(list_t const *list)
{
    int len = 0;
    list_t const *temp = list;

    for (; temp != NULL; temp = temp->next)
        len++;
    return (len);
}

int game_loop(game_t game, touch_t touch, list_t *list)
{
    int len = len_list(list);
    int get = 0;

    loading_tetrimino(&game, list, len);
    init_window(&game);
    while (1) {
        manage_window(&game);
        display_tetri_game(game);
        keypad(game.windows[TETRIMINO], TRUE);
        wtimeout(game.windows[TETRIMINO], 1000 - game.level * 10);
        get = wgetch(game.windows[TETRIMINO]);
        switch_key( &touch, get, &game);
        if (get == touch.keys[quit])
            break;
        if (get == -1)
            game.tetri.pos = move_down((char const **)game.board,
            game.tetri.pos, game.tetri.size);
        get = -1;
    }
    endwin();
    return (0);
}
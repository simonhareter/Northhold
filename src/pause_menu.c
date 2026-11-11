#include "pause_menu.h"
#include "button.h"
#include "config.h"
#include "cursor.h"
#include "game.h"

#include <raylib.h>
#include <raymath.h>
#include <stdbool.h>
#include <stddef.h>

void init_pause_menu(Game *game)
{
    PlayMusicStream(game->music.playing1_music);

    const float menu_box_width = 400;
    const float menu_box_height = 500;
    const float menu_box_x = ((float)GetScreenWidth() / 2.0F) - (menu_box_width / 2.0F);
    const float menu_box_y = ((float)GetScreenHeight() / 2.0F) - (menu_box_height / 2.0F);

    Rectangle menu_box = {menu_box_x, menu_box_y, menu_box_width, menu_box_height};

    const float title_box_width = 200;
    const float title_box_height = 50;
    const float title_box_x = ((float)GetScreenWidth() / 2.0F) - (title_box_width / 2.0F);
    const float title_box_y = menu_box.y - (title_box_height / 2.0F);

    Rectangle title_box = {title_box_x, title_box_y, title_box_width, title_box_height};

    Rectangle ui_elements[PAUSE_MENU_UI_ELEMENTS_COUNT] = {[PAUSE_MENU_BOX] = menu_box, [PAUSE_MENU_TITLE] = title_box};
    const char *ui_elements_text[PAUSE_MENU_UI_ELEMENTS_COUNT] = {"", "Game Menu"};

    Color ui_elements_outline_color[PAUSE_MENU_UI_ELEMENTS_COUNT] = {
        Fade(BUTTON_OUTLINE_COLOR, BOX_OPACITY),
        BUTTON_OUTLINE_COLOR,
    };

    Color ui_elements_color[PAUSE_MENU_UI_ELEMENTS_COUNT] = {
        Fade(BLACK, BOX_OPACITY),
        BUTTON_TITLE_COLOR,
    };

    for (int i = 0; i < PAUSE_MENU_UI_ELEMENTS_COUNT; i++)
    {
        float roundness = i == BOX ? MENU_ROUNDNESS : BUTTON_ROUNDNESS;

        Rectangle outline = {
            ui_elements[i].x - BUTTON_OUTLINE_THICKNESS,
            ui_elements[i].y - BUTTON_OUTLINE_THICKNESS,
            ui_elements[i].width + (BUTTON_OUTLINE_THICKNESS * 2),
            ui_elements[i].height + (BUTTON_OUTLINE_THICKNESS * 2),
        };

        game->pause_menu.ui_elements[i] = (Button){
            outline,
            ui_elements[i],
            ui_elements_text[i],
            false,
            ui_elements_outline_color[i],
            ui_elements_color[i],
            BUTTON_COLOR_HOVERED,
            roundness,
        };
    }

    const float rec_width = 300;
    const float rec_height = 50;
    const float rec_pos_x = ((float)GetScreenWidth() / 2.0F) - (rec_width / 2.0F);
    const float rec_pos_y = ((float)GetScreenHeight() / 2.0F) - (menu_box_height / 2.0F) + (rec_height * 1.5F);

    const char *button_names[PAUSE_MENU_COUNT] = {"Resume", "Save", "Settings", "Exit"};

    for (int i = 0; i < PAUSE_MENU_COUNT; i++)
    {
        Rectangle curr_outline = {
            rec_pos_x - BUTTON_OUTLINE_THICKNESS,
            rec_pos_y - BUTTON_OUTLINE_THICKNESS + (rec_height * ((float)i * 2)),
            rec_width + (BUTTON_OUTLINE_THICKNESS * 2),
            rec_height + (BUTTON_OUTLINE_THICKNESS * 2),
        };

        Rectangle curr_button_rec = {
            rec_pos_x,
            rec_pos_y + (rec_height * ((float)i * 2)),
            rec_width,
            rec_height,
        };

        game->pause_menu.buttons[i] = (Button){
            curr_outline,         curr_button_rec, button_names[i],      false,
            BUTTON_OUTLINE_COLOR, BUTTON_COLOR,    BUTTON_COLOR_HOVERED, BUTTON_ROUNDNESS,
        };
    }
}

void update_pause_menu(Game *game)
{
    Button *options = game->pause_menu.buttons;

    switch (which_button_pressed(options, PAUSE_MENU_COUNT))
    {
        case 0:
            game->state = GAME_STATE_PLAYING;
            break;
        case 1:
            game->state = GAME_STATE_PLAYING;
            TraceLog(LOG_INFO, "Saving the game is not yet implemented");
            break;
        case 2:
            open_settings(game);
            game->overlay_state = OVERLAY_STATE_SETTINGS;
            break;
        case 3:
            StopMusicStream(game->music.playing1_music);
            StopMusicStream(game->music.menu_music);
            PlayMusicStream(game->music.menu_music);
            game->state = GAME_STATE_MENU;
            break;
        default:
            return;
            break;
    }
}

void draw_pause_menu(Game *game)
{
    // BOX
    Font font = game->font;
    const float spacing = FONT_SIZE * 0.1;
    const float h_align = 0.5F;
    const float v_align = 0.5F;

    // PAUSE MENU UI ELEMENTS
    for (int i = 0; i < PAUSE_MENU_UI_ELEMENTS_COUNT; i++)
    {
        Button *ui_element = &game->pause_menu.ui_elements[i];

        DrawRectangleRounded(ui_element->outline, ui_element->roundness, BUTTON_SEGMENTS, ui_element->outline_color);
        DrawRectangleRounded(ui_element->rec, ui_element->roundness, BUTTON_SEGMENTS, ui_element->rec_color);

        const char *title_text = game->pause_menu.ui_elements[i].text;
        Rectangle *title_rec = &game->pause_menu.ui_elements[i].rec;

        Vector2 title_size = MeasureTextEx(font, title_text, FONT_SIZE, spacing);

        Vector2 title_pos = (Vector2){
            title_rec->x + Lerp(0.0F, title_rec->width - title_size.x, h_align),
            title_rec->y + Lerp(0.0F, title_rec->height - title_size.y, v_align),
        };

        DrawTextEx(font, title_text, title_pos, FONT_SIZE, spacing, BUTTON_TEXT_COLOR);
    }

    // PAUSE MENU OPTIONS
    for (int i = 0; i < PAUSE_MENU_COUNT; i++)
    {
        Button *button = &game->pause_menu.buttons[i];
        Rectangle *rec = &game->pause_menu.buttons[i].rec;
        const char *text = game->pause_menu.buttons[i].text;

        Color button_color = button->rec_color;

        if (button->is_hovered)
        {
            button_color = button->hovered_color;
        }

        DrawRectangleRounded(button->outline, button->roundness, BUTTON_SEGMENTS, button->outline_color);
        DrawRectangleRounded(*rec, button->roundness, BUTTON_SEGMENTS, button_color);

        Vector2 text_size = MeasureTextEx(font, text, FONT_SIZE, spacing);

        Vector2 text_pos = (Vector2){
            rec->x + Lerp(0.0F, rec->width - text_size.x, h_align),
            rec->y + Lerp(0.0F, rec->height - text_size.y, v_align),
        };

        DrawTextEx(font, text, text_pos, FONT_SIZE, spacing, BUTTON_TEXT_COLOR);
    }
}

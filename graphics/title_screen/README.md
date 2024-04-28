# Instructions on replacing title screen

Example uses logo

1. Edit [game_title_logo_new.png], limit to 256 colors in Gimp, color 0 is transparency
    - If you want to edit an existing image, open it in Tilemap Studio and Print Image from the toolbar
2. Import image [game_title_logo_new.png] into Tilemap Studio, save it to [game_title_logo_tiles.png] or something
3. Open [game_title_logo_tiles.png] in Gimp and Colors -> Map -> Rearrange Colormap to ensure transparent color comes first
4. Change paths in code

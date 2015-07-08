# FPH

## Our Philosophy

Our small team currently consists of one programmer, me (Tom Fischer), and one designer, Noah Mullen. We believe that many games miss a crucial element: **extensibility**. Most of the greatest games almost got this right. Bethesda Softworks has frequently published editors alongside their greatest titles. All have seen enormous success. Still, the aforementioned titles lack another key element: **automated extensibility**. Games with procedural generation, like Cubeworld, Terraria, and Minecraft all alot major portions of gameplay to automated extensibility—allowing the game to extend itself.

In this project, we seek to push the limits of both elements. We'd like to grant users the capability to add *anything* they wish: skills and abilities, NPCs, spells, weapons, armor, attack moves, defensive moves, ingredients, containers, plants, pets, other companions, and so on. The one flaw inherent to extensibility, however, is the manual aspect of it. In most games with extensibility options, every detail must be manually added by the user. We'd like to avoid this issue by allowing automated extensibility of users' manual efforts. For example, user-created NPCs may be given the option to randomly spawn in certain areas, based on a number of factors, or no factors at all.

## The Editor

Although the editor is still in its early stages, users can **move** around maps and **edit** static features of maps.

![Move around the map and edit static features](https://raw.githubusercontent.com/gragas/fph/master/media/move-and-place.gif)

Users can also **create and use their own tiles**.

![User-generated tile support](https://raw.githubusercontent.com/gragas/fph/master/media/user-generated-tiles.gif)

**Readable file design** makes it easy to edit maps outside of the editor. This also makes for easy text processing if the user wishes to write his or her own scripts to procedurally generate maps. I've written a few Python scripts for this, each less than 20 lines long.

![User-generated tile support](https://raw.githubusercontent.com/gragas/fph/master/media/readable-map-files.gif)

## Game Description

This is a roleplaying adventure game filled with alchemy, botany, magic, crafting, and more. It is currently written in C++ and the graphics are currently 2-dimensional. However, I would like to create a 3-dimensional version of this game later on.

## License and Redistribution

This project is licensed under the GNU GENERAL PUBLIC LICENSE. Feel free to copy, modify, and redistribute this work, but please be sure to attribute me (Thomas D. Fischer) as the original author!
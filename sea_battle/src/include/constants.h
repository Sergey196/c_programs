
const int a = 10;

namespace _baseitem
{
  const int COUT_ROWS_COLUMS = 10;
  const int COUT_SHIPS = 10;
  const int CELL_WIDTH_HIIGHT = 50;
  const int SHIP_RESERV_PANEl_HEIGHT = 80;
  const int SHIP_RESERV_PANEl_WIDTH = 300;
  const int SHIP_RESERV_PANEl_X0 = 300;
  const int SHIP_RESERV_PANEl_X1 = 600;
  const int SHIP_RESERV_PANEl_Y0 = 670;
  const int SHIP_RESERV_PANEl_Y1 = 750;
  const int PLAYER_INDEX = 0;
  const int ENEMY_INDEX = 1;
  const int COUT_PLAYERS = 2;
    
   enum cellState
   {
      free_normal,
      free_beat,
      ship_normal,
      ship_beat
   };
};

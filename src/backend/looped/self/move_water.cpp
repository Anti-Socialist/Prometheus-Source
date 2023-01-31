//#include "natives.hpp"
//#include "backend/looped_command.hpp"
//#include "util/math.hpp"
//#include "gui.hpp"
//#include "gta/enums.hpp"
//
//namespace big
//{
//    class move_water : looped_command
//    {
//        using looped_command::looped_command;
//
//        virtual void on_tick() override
//        {
//            Vector3 Coords = ENTITY::GET_ENTITY_COORDS(self::ped, true);
//            WATER::MODIFY_WATER(Coords.x, Coords.y, -10, 10);
//            WATER::MODIFY_WATER(Coords.x + 2, Coords.y, -10, 10);
//            WATER::MODIFY_WATER(Coords.x, Coords.y + 2, -10, 10);
//            WATER::MODIFY_WATER(Coords.x + 2, Coords.y + 2, -10, 10);
//            WATER::MODIFY_WATER(Coords.x + 4, Coords.y, -10, 10);
//            WATER::MODIFY_WATER(Coords.x, Coords.y + 4, -10, 10);
//            WATER::MODIFY_WATER(Coords.x + 4, Coords.y + 4, -10, 10);
//            WATER::MODIFY_WATER(Coords.x + 6, Coords.y, -10, 10);
//            WATER::MODIFY_WATER(Coords.x, Coords.y + 6, -10, 10);
//            WATER::MODIFY_WATER(Coords.x + 6, Coords.y + 6, -10, 10);
//            WATER::MODIFY_WATER(Coords.x + 8, Coords.y, -10, 10);
//            WATER::MODIFY_WATER(Coords.x, Coords.y + 8, -10, 10);
//            WATER::MODIFY_WATER(Coords.x + 8, Coords.y + 8, -10, 10);
//        }
//    };
//    move_water g_move_water("movewater", "Move Water", "Move water out of way.", g.self.move_water);
//}
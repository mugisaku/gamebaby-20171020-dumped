#include"gmbb_Menu.hpp"




namespace gmbb{


Menu::
Menu(int  item_w, int  item_h, int  col_n, int  row_n) noexcept:
item_table(new MenuItem[col_n*row_n]),
item_width(item_w),
item_height(item_h),
column_number(col_n),
row_number(row_n)
{
}


}





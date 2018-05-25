#include <SFML/Graphics.hpp>

using namespace sf;

View view;

View get_xy_for_view(float x, float y)
{
	float crit_x = x;
	float crit_y = y;
	if (x < 220) crit_x = 220; 
	if (y < 240) crit_y = 240; 
	if (y > 554) crit_y = 554;

	view.setCenter(crit_x+100, crit_y);

	return view;
}

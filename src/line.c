
// void calculate_line (point_t start, point_t end)
// {
//     float dx       = (end.x - start.x);
//     float dy       = (end.y - start.y);
//     float distance = (pow(dx, 2) + pow(dy, 2));

//     // float slope = ((end.y - start.y)/(end.x - start.x));

//     for (float i = 1; i < distance; i++)
//     {
//         screen_modify(
//             (point_t) { .x = start.x + 2 * (int)floor((dx * i) / distance),
//                         .y = start.y + (int)floor((dy * i) / distance) },
//             '.');
//     }
// }

// point_t midpoint_line (point_t start, point_t end)
// {
//     float x = ((start.x + end.x) / 2);
//     float y = ((start.y + end.y) / 2);
//     clog(L_DEBUG, "Midpoint of line: %d,%d", (int)x, (int)y);
//     return (point_t) { (int)x, (int)y };
// }

// void rotate_line (point_t * p_start, point_t * p_end, int deg)
// {
//     float   angle    = deg * (M_PI / 180);
//     point_t midpoint = midpoint_line(*p_start, *p_end);

//     point_t a_mid = { p_start->x - midpoint.x, p_start->y - midpoint.y };
//     point_t b_mid = { p_end->x - midpoint.x, p_end->y - midpoint.y };

//     point_t a_rotated = { cos(angle) * a_mid.x - sin(angle) * a_mid.y,
//                           sin(angle) * a_mid.x + cos(angle) * a_mid.y };
//     point_t b_rotated = { cos(angle) * b_mid.x - sin(angle) * b_mid.y,
//                           sin(angle) * b_mid.x + cos(angle) * b_mid.y };

//     p_start->x = a_rotated.x + midpoint.x;
//     p_start->y = a_rotated.y + midpoint.y;
//     p_end->x   = b_rotated.x + midpoint.x;
//     p_end->y   = b_rotated.y + midpoint.y;
// }

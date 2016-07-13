#include "stdafx.h"

void CRender::RenderNametags()
{
	for (int i = 0; i < sizeof(playerData) / sizeof(*playerData); i++) {
		if (ENTITY::DOES_ENTITY_EXIST(playerData[i].pedPed)) {
			//if (ENTITY::IS_ENTITY_VISIBLE(playerData[i].pedPed)) {

			//Calculating distance bettween player and otherplayer.
			//I love that i worked with graphics and already know how to do it xd.
			float x = LocalPlayer->GetCoords().x - playerData[i].x;
			float y = LocalPlayer->GetCoords().y - playerData[i].y;
			float z = LocalPlayer->GetCoords().z - playerData[i].z;

			float distanceXY = sqrtf(x*x + y*y);
			float distance = sqrtf(distanceXY * distanceXY + z*z);

			if (distance < LocalPlayer->maxNickDrawDistance) {
				GRAPHICS::_WORLD3D_TO_SCREEN2D(playerData[i].x, playerData[i].y, playerData[i].z + 2.0f, &playerData[i].screen_x, &playerData[i].screen_y);
				draw_text(playerData[i].screen_x, playerData[i].screen_y, playerData[i].playerusername, { 255, 255, 255, 255 });
			}
			//}
		}
	}
}

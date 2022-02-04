#pragma once

// Definitions of miscellaneous structs which can be used in graphics developing, such as Vectors etc.


namespace Engine {
	struct Vector2f {
		float x;
		float y;
		Vector2f(float x, float y) {
			this->x = x;
			this->y = y;
		}
	};
};
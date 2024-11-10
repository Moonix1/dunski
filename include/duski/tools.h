#pragma once

namespace Duski {
	
	namespace Tools {
		uint32_t ColorRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
			return (static_cast<uint32_t>(a) << 24) |
				   (static_cast<uint32_t>(b) << 16) |
				   (static_cast<uint32_t>(g) << 8)  |
				   static_cast<uint32_t>(r);
		}

		size_t Decuple(size_t number) { return number * 10; }
	}

}
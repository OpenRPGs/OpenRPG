#include "stdafx.h"

#include "Utils.h"

using sf::Color;
using std::string;
using std::stringstream;

Color g::Color(string rgba) {
	switch (rgba.length()) {
		case 4: { // #RGB
			stringstream ss;
			UINT16 c;
			ss << std::hex << rgba.substr(1);
			ss >> c;
			return sf::Color(
				((c >> 8) & 0xF) << 4 | (c >> 8) & 0xF, ((c >> 4) & 0xF) << 4 | (c >> 4) & 0xF,
				(c & 0xF) << 4 | c & 0xF);
		}
		case 5: { // #RGBA
			stringstream ss;
			UINT16 c;
			ss << std::hex << rgba.substr(1);
			ss >> c;
			return sf::Color(
				((c >> 12) & 0xF) << 4 | (c >> 12) & 0xF, ((c >> 8) & 0xF) << 4 | (c >> 8) & 0xF,
				((c >> 4) & 0xF) << 4 | (c >> 4) & 0xF, (c & 0xF) << 4 | c & 0xF);
		}
		case 7: { // #RRGGBB
			stringstream ss;
			UINT32 c;
			ss << std::hex << rgba.substr(1);
			ss >> c;
			return sf::Color((c >> 16) & 0xFF, (c >> 8) & 0xFF, c & 0xFF);
		}
		case 9: { // #RRGGBBAA
			stringstream ss;
			UINT32 c;
			ss << std::hex << rgba.substr(1);
			ss >> c;
			return sf::Color((c >> 24) & 0xFF, (c >> 16) & 0xFF, (c >> 8) & 0xFF, c & 0xFF);
		}
		default:
			throw "Utils::g::Color(std::string)::Invalid hex-color string";
	}
}

Color g::Color(string rgb, int alpha) {
	switch (rgb.length()) {
		case 4: { // #RGB
			stringstream ss;
			UINT16 c;
			ss << std::hex << rgb.substr(1);
			ss >> c;
			return sf::Color(
				((c >> 8) & 0xF) << 4 | (c >> 8) & 0xF, ((c >> 4) & 0xF) << 4 | (c >> 4) & 0xF,
				(c & 0xF) << 4 | c & 0xF, alpha);
		}
		case 7: { // #RRGGBB
			stringstream ss;
			UINT32 c;
			ss << std::hex << rgb.substr(1);
			ss >> c;
			return sf::Color((c >> 16) & 0xFF, (c >> 8) & 0xFF, c & 0xFF, alpha);
		}
		default:
			throw "Utils::g::Color(std::string, int)::Invalid hex-color string";
	}
}

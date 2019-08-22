#pragma once

#ifdef _DEBUG
// Leak checker
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

#ifndef interface
#define interface struct
;
#endif

//Core
#include <algorithm>
#include <deque>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <thread>
#include <utility>
#include <vector>
#include <list>
#include <stack>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>

//SFML
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

// 유니버설 문자 이름 '~~'(으)로 표현되는 문자는 현재 코드 페이지(~~)에서 표현할 수 없습니다.
#pragma warning(disable: 4566)

// Utilities
#include "Utils/Utils.h"

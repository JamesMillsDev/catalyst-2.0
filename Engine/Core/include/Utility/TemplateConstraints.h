/*****************************************************************************
 * Template Constraints
 * Created by James Mills on 29/03/2026.
 *****************************************************************************/

#pragma once

#include <concepts>

template<typename T, typename U>
concept Derived = std::is_base_of_v<U, T>;
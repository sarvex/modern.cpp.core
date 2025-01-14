/*
 * Copyright (c) 2022 Florian Becker <fb@vxapps.com> (VX APPS).
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

/* c header */
#include <cstdint> // std::int32_t

/* stl header */
#include <type_traits>
#include <utility>

/**
 * @brief std (Standard template library) namespace.
 */
namespace std { // NOSONAR For std integration

#ifndef __cpp_lib_is_scoped_enum
  namespace detail {

    template <typename T>
    [[maybe_unused]] decltype( static_cast<void>( sizeof( T ) ), true_type {} ) test_sizable( std::int32_t );

    template <typename>
    [[maybe_unused]] false_type test_sizable( ... );

    template <typename T>
    [[maybe_unused]] decltype( static_cast<false_type ( * )( std::int32_t )>( nullptr )( declval<T>() ) ) test_nonconvertible_to_int( std::int32_t );

    template <typename>
    [[maybe_unused]] true_type test_nonconvertible_to_int( ... );

    template <typename T>
    constexpr bool is_scoped_enum = conjunction_v<decltype( test_sizable<T>( 0 ) ), decltype( test_nonconvertible_to_int<T>( 0 ) )>;
  }

  /**
   * @brief Return true, if this is an scoped enum.
   * @tparam E   Enum.
   * @note https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2020/p1048r1.pdf
   */
  template <typename E>
  struct is_scoped_enum : bool_constant<detail::is_scoped_enum<E>> {};

  /**
   * @brief Return true, if this is an scoped enum.
   * @note https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2020/p1048r1.pdf
   */
  template <typename E>
  constexpr bool is_scoped_enum_v = is_scoped_enum<E>::value;
#endif

#ifndef __cpp_lib_to_underlying
  /**
   * @brief Return the underlying value in its correct type of an enumeration.
   * @tparam E   Enum or enum class.
   * @param _enum   Enumeration value.
   * @return The underlying value in its correct type of an enumeration.
   * @note https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2021/p1682r3.html
   */
  template <typename E>
  constexpr typename underlying_type<E>::type to_underlying( E _enum ) noexcept {

    return static_cast<typename underlying_type<E>::type>( _enum );
  }
#endif

#ifndef __cpp_lib_unreachable
  /**
   * @brief Unreachable section is reached.
   * @note https://www.open-std.org/jtc1/sc22/wg14/www/docs/n2816.pdf
   */
  [[noreturn]] inline void unreachable() {

  // Uses compiler specific extensions if possible.
  // Even if no extension is used, undefined behavior is still raised by
  // an empty function body and the noreturn attribute.
  #if defined __GNUC__ || defined __clang__ // GCC, Clang, ICC
    __builtin_unreachable();
  #elif defined _MSC_VER // MSVC
    __assume( false );
  #endif
  }
#endif
}

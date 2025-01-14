/*
 * Copyright (c) 2020 Florian Becker <fb@vxapps.com> (VX APPS).
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

/* windows header */
#ifdef _WIN32
  #include <Windows.h>
#endif

/* stl header */
#include <iomanip>
#include <iostream>
#include <sstream>

/* local header */
#include "FloatingPoint.h"
#include "Logger.h"
#include "Timestamp.h"
#include "Timing.h"

namespace vx {

  using timestamp::Precision;

  /** @brief Multiplier from nanoseconds to milliseconds to seconds and vice versa. */
  constexpr double multiplier = 1000.0;

#ifdef _WIN32
  static inline std::int64_t getTicks() {

    LARGE_INTEGER ticks {};
    QueryPerformanceCounter( &ticks );
    return ticks.QuadPart;
  }
#endif

  Timing::Timing( std::string_view _action,
                  bool _autoStart ) noexcept {

    if ( _autoStart ) { start( _action ); }
  }

  void Timing::start( std::string_view _action ) noexcept {

    if ( !_action.empty() ) {

      setAction( _action );
    }

    m_start = std::chrono::high_resolution_clock::now();
#ifdef _WIN32
    m_cpu = getTicks();
#else
    m_cpu = std::clock();
#endif
  }

  void Timing::stop() const noexcept {

    auto end = std::chrono::high_resolution_clock::now();

    const std::chrono::duration<double, std::milli> wall = end - m_start;
    const std::chrono::duration<double, std::ratio<1, 1>> wallSeconds = end - m_start;

    std::ostringstream cpuTime {};
#ifdef _WIN32
    LARGE_INTEGER ticks {};
    QueryPerformanceCounter( &ticks );
    cpuTime << std::setprecision( std::numeric_limits<double>::digits10 ) << static_cast<double>( ticks.QuadPart - m_cpu ) / multiplier / 10.0;
#else
    cpuTime << std::setprecision( std::numeric_limits<double>::digits10 ) << static_cast<double>( std::clock() - m_cpu ) / static_cast<double>( CLOCKS_PER_SEC ) * multiplier;
#endif

    try {

      logVerbose().stream() << "------ " << m_action;
      logVerbose().stream() << "Timestamp: " << timestamp::iso8601( Precision::MicroSeconds );
      if ( floating_point::less( wall.count(), multiplier ) ) {

        logVerbose().stream() << "Wall Time: " << wall.count() << ' ' << "ms";
      }
      else {

        logVerbose().stream() << "Wall Time: " << wallSeconds.count() << ' ' << "s";
      }
      logVerbose().stream() << " CPU Time: " << cpuTime.str() << ' ' << "ms";
    }
    catch ( const std::exception &_exception ) {

      logFatal() << _exception.what();
    }
  }
}

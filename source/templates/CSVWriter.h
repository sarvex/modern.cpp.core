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

#pragma once

/* stl header */
#include <fstream>
#if __cplusplus >= 202002L
  #include <iterator>
#endif
#include <string>
#include <string_view>

/**
 * @brief vx (VX APPS) namespace.
 */
namespace vx {

  /**
   * @brief A class to create and write data in a csv file.
   * @author Florian Becker <fb\@vxapps.com> (VX APPS)
   */
  class CSVWriter {

  public:
    /**
     * @brief Default constructor for CsvWriter.
     * @param _filename   Filename for the csv file.
     * @param _delimiter   Delimiter of values.
     * @param _linePrefix   Prefix for every line.
     * @param _lineSuffix   Suffix for every line.
     */
    explicit CSVWriter( std::string_view _filename,
                        std::string_view _delimiter = ",",
                        std::string_view _linePrefix = {},
                        std::string_view _lineSuffix = {} )
      : m_filename( _filename ),
        m_delimiter( _delimiter ),
        m_linePrefix( _linePrefix ),
        m_lineSuffix( _lineSuffix ) {}

    /**
     * @brief Write out the values.
     * @tparam T   Type.
     * @param _first   First value.
     * @param _last   Last value.
     */
#if __cplusplus >= 202002L
  #if defined __clang__ && __clang_major__ > 12
    template <std::forward_iterator T>
  #else
    template <typename T>
  #endif
#else
    template <typename T>
#endif
    void addRowData( T _first,
                     T _last ) const noexcept {

      std::ofstream file {};
      file.open( m_filename, std::ios::app );

      file << m_linePrefix;
      /* Iterate over the range and add each element to file separated by delimiter. */
      while ( _first != _last ) {

        file << *_first;
        if ( ++_first != _last ) {

          file << m_delimiter;
        }
      }
      file << m_lineSuffix;
      file << std::endl;

      /* Close the file. */
      file.close();
    }

  private:
    /**
     * @brief Csv filename.
     */
    std::string m_filename {};

    /**
     * @brief Delimiter for values.
     */
    std::string_view m_delimiter {};

    /**
     * @brief Prefix for every line.
     */
    std::string_view m_linePrefix {};

    /**
     * @brief Suffix for every line.
     */
    std::string_view m_lineSuffix {};
  };
}

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

/* stl header */
#include <iostream>
#ifdef HAVE_SPAN
  #include <span>
#endif
#include <string>

std::int32_t main( std::int32_t argc,
                   char **argv ) {

  /* Usage: pipe RESULTCODE */
#ifdef HAVE_SPAN
  const std::span args( argv, static_cast<std::size_t>( argc ) );
  if ( args.size() != 2 ) {
#else
  if ( argc != 2 ) {
#endif

    return EXIT_FAILURE;
  }

  std::cout << "This is std::cout text." << std::endl;
  std::cerr << "This is std::cerr text." << std::endl;

  if ( const std::int32_t result = fprintf( stderr, "This is fprintf( stderr ) text.\n" ); !result ) {

    std::cout << "Error writing to stderr with fprintf." << std::endl;
  }
  printf( "This is printf text.\n" );

#ifdef HAVE_SPAN
  return std::stoi( args[ 1 ] );
#else
  return std::stoi( argv[ 1 ] );
#endif
}

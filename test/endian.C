/* rendera/test/endian.C */

#include <iostream>
#include <cassert>

#include "Inline.H"

int
main( int, char** )
{
  assert( 4 == sizeof( rgba_type ) );
  assert( 4 == sizeof( un_rgba_type ) );

  rgba_type rgba = getRgba( 0x03020100 );

  assert( 1 == sizeof( rgba.r ) );
  assert( 1 == sizeof( rgba.g ) );
  assert( 1 == sizeof( rgba.b ) );
  assert( 1 == sizeof( rgba.a ) );

  assert( 0 == rgba.r );
  assert( 1 == rgba.g );
  assert( 2 == rgba.b );
  assert( 3 == rgba.a );

  return 0 ;
}

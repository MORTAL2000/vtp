//
// Use this file to configure the vtdata library.
//
// Set each option to either 0 or 1 as desired.
//

#ifndef CONFIG_VTDATA_H
#define CONFIG_VTDATA_H

// Use the NetCDF library, which adds support for the "CDF" file format,
// which is commonly used for bathymetry.
//
// The NetCDF library is available from:
//		http://www.unidata.ucar.edu/packages/netcdf/
//
#define SUPPORT_NETCDF	1

// Use the Libwww library, which adds cross-platform support for HTTP
// operations such as reading from WFS (Web Feature Servers).
//
// The Libwww library is available from:
//		http://www.w3.org/Library/
//
#define SUPPORT_HTTP	1

#endif // CONFIG_VTDATA_H


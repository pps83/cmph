#ifndef __CMPH_TYPES_H__
#define __CMPH_TYPES_H__

typedef unsigned char cmph_uint8;
typedef unsigned short cmph_uint16;
typedef unsigned int cmph_uint32;

typedef enum { CMPH_HASH_DJB2, CMPH_HASH_FNV, CMPH_HASH_GLIB, CMPH_HASH_JENKINS, 
	       CMPH_HASH_PJW, CMPH_HASH_SDBM, CMPH_HASH_COUNT } CMPH_HASH;
extern const char *cmph_hash_names[];
typedef enum { CMPH_BMZ, CMPH_CHM, CMPH_COUNT } CMPH_ALGO; /* included -- Fabiano */
extern const char *cmph_names[];

#endif

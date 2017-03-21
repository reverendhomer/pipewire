/* Simple Plugin API
 * Copyright (C) 2016 Wim Taymans <wim.taymans@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef __SPA_AUDIO_RAW_UTILS_H__
#define __SPA_AUDIO_RAW_UTILS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <spa/id-map.h>
#include <spa/audio/raw.h>

#if __BYTE_ORDER == __BIG_ENDIAN
#define _SPA_AUDIO_FORMAT_NE(fmt) SPA_AUDIO_FORMAT_PREFIX fmt "BE"
#define _SPA_AUDIO_FORMAT_OE(fmt) SPA_AUDIO_FORMAT_PREFIX fmt "LE"
#elif __BYTE_ORDER == __LITTLE_ENDIAN
#define _SPA_AUDIO_FORMAT_NE(fmt) SPA_AUDIO_FORMAT_PREFIX fmt "LE"
#define _SPA_AUDIO_FORMAT_OE(fmt) SPA_AUDIO_FORMAT_PREFIX fmt "BE"
#endif

typedef struct {
  uint32_t UNKNOWN;
  uint32_t ENCODED;
  uint32_t S8;
  uint32_t U8;
  uint32_t S16;
  uint32_t U16;
  uint32_t S24_32;
  uint32_t U24_32;
  uint32_t S32;
  uint32_t U32;
  uint32_t S24;
  uint32_t U24;
  uint32_t S20;
  uint32_t U20;
  uint32_t S18;
  uint32_t U18;
  uint32_t F32;
  uint32_t F64;
  uint32_t S16_OE;
  uint32_t U16_OE;
  uint32_t S24_32_OE;
  uint32_t U24_32_OE;
  uint32_t S32_OE;
  uint32_t U32_OE;
  uint32_t S24_OE;
  uint32_t U24_OE;
  uint32_t S20_OE;
  uint32_t U20_OE;
  uint32_t S18_OE;
  uint32_t U18_OE;
  uint32_t F32_OE;
  uint32_t F64_OE;
} SpaAudioFormats;

static inline void
spa_audio_formats_map (SpaIDMap *map, SpaAudioFormats *types)
{
  if (types->ENCODED == 0) {
    types->UNKNOWN      = 0;
    types->ENCODED      = spa_id_map_get_id (map, SPA_AUDIO_FORMAT__ENCODED);

    types->S8           = spa_id_map_get_id (map, SPA_AUDIO_FORMAT__S8);
    types->U8           = spa_id_map_get_id (map, SPA_AUDIO_FORMAT__U8);

    types->S16          = spa_id_map_get_id (map, _SPA_AUDIO_FORMAT_NE ("S16"));
    types->U16          = spa_id_map_get_id (map, _SPA_AUDIO_FORMAT_NE ("U16"));
    types->S24_32       = spa_id_map_get_id (map, _SPA_AUDIO_FORMAT_NE ("S24_32"));
    types->U24_32       = spa_id_map_get_id (map, _SPA_AUDIO_FORMAT_NE ("U24_32"));
    types->S32          = spa_id_map_get_id (map, _SPA_AUDIO_FORMAT_NE ("S32"));
    types->U32          = spa_id_map_get_id (map, _SPA_AUDIO_FORMAT_NE ("U32"));
    types->S24          = spa_id_map_get_id (map, _SPA_AUDIO_FORMAT_NE ("S24"));
    types->U24          = spa_id_map_get_id (map, _SPA_AUDIO_FORMAT_NE ("U24"));
    types->S20          = spa_id_map_get_id (map, _SPA_AUDIO_FORMAT_NE ("S20"));
    types->U20          = spa_id_map_get_id (map, _SPA_AUDIO_FORMAT_NE ("U20"));
    types->S18          = spa_id_map_get_id (map, _SPA_AUDIO_FORMAT_NE ("S18"));
    types->U18          = spa_id_map_get_id (map, _SPA_AUDIO_FORMAT_NE ("U18"));
    types->F32          = spa_id_map_get_id (map, _SPA_AUDIO_FORMAT_NE ("F32"));
    types->F64          = spa_id_map_get_id (map, _SPA_AUDIO_FORMAT_NE ("F64"));

    types->S16_OE       = spa_id_map_get_id (map, _SPA_AUDIO_FORMAT_OE ("S16"));
    types->U16_OE       = spa_id_map_get_id (map, _SPA_AUDIO_FORMAT_OE ("U16"));
    types->S24_32_OE    = spa_id_map_get_id (map, _SPA_AUDIO_FORMAT_OE ("S24_32"));
    types->U24_32_OE    = spa_id_map_get_id (map, _SPA_AUDIO_FORMAT_OE ("U24_32"));
    types->S32_OE       = spa_id_map_get_id (map, _SPA_AUDIO_FORMAT_OE ("S32"));
    types->U32_OE       = spa_id_map_get_id (map, _SPA_AUDIO_FORMAT_OE ("U32"));
    types->S24_OE       = spa_id_map_get_id (map, _SPA_AUDIO_FORMAT_OE ("S24"));
    types->U24_OE       = spa_id_map_get_id (map, _SPA_AUDIO_FORMAT_OE ("U24"));
    types->S20_OE       = spa_id_map_get_id (map, _SPA_AUDIO_FORMAT_OE ("S20"));
    types->U20_OE       = spa_id_map_get_id (map, _SPA_AUDIO_FORMAT_OE ("U20"));
    types->S18_OE       = spa_id_map_get_id (map, _SPA_AUDIO_FORMAT_OE ("S18"));
    types->U18_OE       = spa_id_map_get_id (map, _SPA_AUDIO_FORMAT_OE ("U18"));
    types->F32_OE       = spa_id_map_get_id (map, _SPA_AUDIO_FORMAT_OE ("F32"));
    types->F64_OE       = spa_id_map_get_id (map, _SPA_AUDIO_FORMAT_OE ("F64"));
  }
}

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* __SPA_AUDIO_RAW_UTILS_H__ */

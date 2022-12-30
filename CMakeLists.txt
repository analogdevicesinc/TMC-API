# Copyright (c) 2022, Stefano Cottafavi <stefano.cottafavi@gmail.com>
#
# SPDX-License-Identifier: Apache-2.0

if(CONFIG_HAS_TMCLIB)

zephyr_library()

if(CONFIG_TMC5160)
zephyr_include_directories(tmc/ic/TMC5160)
#zephyr_library_sources(tmc/ic/TMC5160/TMC5160.c)
endif()

#if(CONFIG_AUDIO_MPXXDTYY)
#zephyr_include_directories(audio/microphone)
#zephyr_library_sources(audio/microphone/OpenPDMFilter.c)
#endif()

endif()

if(CONFIG_HAS_TMCLIBRAMP)

endif()

# STMEMSC - Hardware Abstraction Layer for ST sensor
#add_subdirectory_ifdef(CONFIG_HAS_STMEMSC sensor/stmemsc)
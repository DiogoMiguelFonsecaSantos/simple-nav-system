# Install script for directory: A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/SimpleNavSys")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "A:/Espressif/tools/xtensa-esp-elf/esp-13.2.0_20240530/xtensa-esp-elf/bin/xtensa-esp32-elf-objdump.exe")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mbedtls" TYPE FILE PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ FILES
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/aes.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/aria.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/asn1.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/asn1write.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/base64.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/bignum.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/block_cipher.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/build_info.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/camellia.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/ccm.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/chacha20.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/chachapoly.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/check_config.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/cipher.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/cmac.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/compat-2.x.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/config_adjust_legacy_crypto.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/config_adjust_legacy_from_psa.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/config_adjust_psa_from_legacy.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/config_adjust_psa_superset_legacy.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/config_adjust_ssl.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/config_adjust_x509.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/config_psa.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/constant_time.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/ctr_drbg.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/debug.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/des.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/dhm.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/ecdh.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/ecdsa.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/ecjpake.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/ecp.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/entropy.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/error.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/gcm.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/hkdf.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/hmac_drbg.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/lms.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/mbedtls_config.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/md.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/md5.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/memory_buffer_alloc.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/net_sockets.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/nist_kw.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/oid.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/pem.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/pk.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/pkcs12.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/pkcs5.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/pkcs7.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/platform.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/platform_time.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/platform_util.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/poly1305.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/private_access.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/psa_util.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/ripemd160.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/rsa.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/sha1.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/sha256.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/sha3.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/sha512.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/ssl.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/ssl_cache.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/ssl_ciphersuites.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/ssl_cookie.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/ssl_ticket.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/threading.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/timing.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/version.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/x509.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/x509_crl.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/x509_crt.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/mbedtls/x509_csr.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/psa" TYPE FILE PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ FILES
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/psa/build_info.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/psa/crypto.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/psa/crypto_adjust_auto_enabled.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/psa/crypto_adjust_config_key_pair_types.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/psa/crypto_adjust_config_synonyms.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/psa/crypto_builtin_composites.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/psa/crypto_builtin_key_derivation.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/psa/crypto_builtin_primitives.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/psa/crypto_compat.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/psa/crypto_config.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/psa/crypto_driver_common.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/psa/crypto_driver_contexts_composites.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/psa/crypto_driver_contexts_key_derivation.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/psa/crypto_driver_contexts_primitives.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/psa/crypto_extra.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/psa/crypto_legacy.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/psa/crypto_platform.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/psa/crypto_se_driver.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/psa/crypto_sizes.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/psa/crypto_struct.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/psa/crypto_types.h"
    "A:/Espressif/frameworks/esp-idf-v5.3.1/components/mbedtls/mbedtls/include/psa/crypto_values.h"
    )
endif()


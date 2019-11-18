#pragma once

#ifndef __DRIVE_SERIAL_H__
#define __DRIVE_SERIAL_H__

/// random uuid
#define SHMEM_NAME "eca7c579-243c-4efd-8f2e-8b4d8b39fc0b"
/// random id
#define SHMEM_KEY 7684

struct memory_block
{
  char string[255];
};

int putsn(const char* sn);

/** @brief Returns the string without 
 * non-printable characters to the 
 * left and right
 * @param[in,out] s - A buffer containing the modified string.
 * @remarks The old buffer is removed by calling free() and a 
 * new buffer is allocated by calling calloc()
 */
void ctrim(char** s);

/**
 * @brief Returns a string,
 * contains serial number of the volume,
 * where / path is.
 * @param[out] buf  - buffer for write
 * serial number string
 */
void serial( char* buf);

/**
 * @brief Returns a string,
 * contains name of the volume,
 * where / path is.
 * @returns new allocated buffer
 * with disk name, such as /dev/sda1,
 * or NULL on error
 * @remarks - requires for deallocating
 * memory, allocated inside function using calloc()
 * @code 
 * char* dev = get_root_device();
 * if(NULL != dev){
 *    // working...
 *       free(dev);
 * }
 * @endcode
 * 
 */
char* get_root_device();

#endif // !__DRIVE_SERIAL_H__

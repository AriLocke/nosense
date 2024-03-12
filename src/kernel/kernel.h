#ifndef KERNEL_H
#define KERNEL_H

#include <stddef.h>


/**
 * @brief Copies count bytes from the object pointed to by src to the object pointed to by dest.
 *  
 * @param dest pointer to memory location to copy to 
 * @param src pointer to memory location to copy from 
 * @param count number of bytes to copy 
 * @return dest
 */
extern void *memcpy(void *dest, const void *src, size_t count);

/**
 * @brief Copies the value static_cast<unsigned char>(ch) into each of the first count characters
 *          of the object pointed to by dest.
 *
 * @param dest pointer to memory location to fill from 
 * @param ch Fill byte 
 * @param count number of bytes to fill 
 * @return dest
 */
extern void *memset(void *dest, int ch, size_t count);

/**
 * @brief Copies count bytes from the object pointed to by src to the object pointed to by dest.
 * 			Copying takes place as if the characters were copied to a temporary character array and then the 
 * 			characters were copied from the array to dest
 * 
 * @param dest 	pointer to memory location to copy to 
 * @param src 	pointer to memory location to copy from 
 * @param count	number of bytes to copy 
 * @return 		dest
 */
extern void *memmove(void *dest, const void *src, size_t count);

/**
 * @brief Compares the first count bytes of both arrays. The comparison is done lexicographically. 
 * 
 * @param lhs,rhs pointer to memory buffer to compare
 * @param count	number of bytes to compare
 * @return Negative value if the first differing byte (reinterpreted as unsigned char) in lhs 
 *  		is less than the corresponding byte in rhs.
 *  		0​ if all count bytes of lhs and rhs are equal.
 *  		Positive value if the first differing byte in lhs is greater than the corresponding byte in rhs.  
 */
extern int memcmp(const void *lhs, const void *rhs, size_t count);

/**
 * @brief Halt and catch fire. Calls asm(hlt) eternally
 */
extern void hcf(void);


#endif
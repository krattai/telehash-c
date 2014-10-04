#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

#include "sha256.h"
#include "cipher3.h"

uint8_t *cs1a_rand(uint8_t *s, uint32_t len);
uint8_t *cs1a_hash(uint8_t *input, uint32_t len, uint8_t *output);
uint8_t *cs1a_err(void);

cipher3_t cs1a_init(lob_t options)
{
  cipher3_t ret = malloc(sizeof(struct cipher3_struct));
  ret->rand = cs1a_rand;
  ret->hash = cs1a_hash;
  ret->err = cs1a_err;
  // TODO
  return ret;
}

uint8_t *cs1a_rand(uint8_t *s, uint32_t len)
{

 uint8_t *x = s;
 
  while(len-- > 0)
  {
    *x = (uint8_t)random();
    x++;
  }
  return s;
}

uint8_t *cs1a_hash(uint8_t *input, uint32_t len, uint8_t *output)
{
  sha256(input,len,output,0);
  return output;
}

uint8_t *cs1a_err(void)
{
  return 0;
}


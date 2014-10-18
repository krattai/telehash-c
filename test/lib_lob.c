#include "lob.h"
#include "base32.h"
#include "util.h"
#include "unit_test.h"

int main(int argc, char **argv)
{
  lob_t packet;
  packet = lob_new();
  fail_unless(packet);
  lob_free(packet);

  uint8_t buf[1024];
  char *hex = "001d7b2274797065223a2274657374222c22666f6f223a5b22626172225d7d616e792062696e61727921";
  uint8_t len = strlen(hex)/2;
  util_unhex(hex,strlen(hex),buf);
  packet = lob_parse(buf,len);
  fail_unless(packet);
  fail_unless(lob_len(packet));
  fail_unless(packet->head_len == 29);
  fail_unless(packet->body_len == 11);
  fail_unless(util_cmp(lob_get(packet,"type"),"test") == 0);
  fail_unless(util_cmp(lob_get(packet,"foo"),"[\"bar\"]") == 0);
  
  lob_free(packet);
  packet = lob_new();
  lob_set_base32(packet,"32",buf,len);
  fail_unless(lob_get(packet,"32"));
  fail_unless((int)strlen(lob_get(packet,"32")) == (base32_encode_length(len)-1));
  lob_t bin = lob_get_base32(packet,"32");
  fail_unless(bin);
  fail_unless(bin->body_len == len);

  return 0;
}

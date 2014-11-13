#ifndef chunks_h
#define chunks_h

#include <stdint.h>
#include "lob.h"

typedef struct chunks_struct *chunks_t;

// max size of each chunk (>1)
chunks_t chunks_new(uint8_t size);

chunks_t chunks_free(chunks_t chunks);

// turn this packet into chunks and append
chunks_t chunks_send(chunks_t chunks, lob_t out);

// get any packets that have been reassembled from incoming chunks
lob_t chunks_receive(chunks_t chunks);

// just a utility to see how many bytes are waiting to be sent in total
uint32_t chunks_waiting(chunks_t chunks);

// advances to the next outgoing chunk
chunks_t chunks_next(chunks_t chunks);

////// these are for sending on a transport that is message/frame based

// get the next chunk, put its length in len
uint8_t *chunks_out(chunks_t chunks, uint8_t *len);

// process an incoming individual chunk
chunks_t chunks_in(chunks_t chunks, uint8_t *chunk, uint8_t len);


////// these are for a stream-based transport

// how many bytes are there ready to write (multiple chunks)
uint32_t chunks_len(chunks_t chunks);

// return the next block of data to be written to the stream transport, len is chunks_len()
uint8_t *chunks_write(chunks_t chunks);

// advance the write this far
chunks_t chunks_written(chunks_t chunks, uint32_t len);

// process incoming stream data into any packets, every non-zero chunk will trigger a zero-chunk back
chunks_t chunks_read(chunks_t chunks, uint8_t *block, uint32_t len);

#endif

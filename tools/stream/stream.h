#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

typedef struct stream stream;

struct stream {
	// returns non-zero on error
	void(*close)(stream*);
	int (*get_more)(stream*);
	const uint8_t *(*buffered)(stream*, size_t *plen, int *atend);
	void (*consume)(stream*, size_t consumed);
};

#define HASH_BUFSZ 128

stream *open_http_downloader(const char *url, uint64_t *ptotal);
stream *open_file_stream(FILE *f);
stream *open_buffer_stream(const void *data, size_t size);
stream *open_mapped_file(const char *filename);
stream *open_limited(stream *source, uint64_t size);
stream *open_xz_decoder(stream *source);
stream *open_inflate(stream *source);
stream *open_gzip(stream *source);
stream *open_sha256_hash(stream *source, char *hash);


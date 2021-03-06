#include <openssl/evp.h>
#include "types.h"

void md5_print(u8 *buf) {
	int i;

	for(i = 0; i < 16; i++)
		printf("%02x", buf[i]);
}

void md5_buf(u8 *buf, u8 *out, size_t len) {
	EVP_MD_CTX mdctx;
	u32 md_len=0;

	EVP_DigestInit(&mdctx, EVP_md5());
	EVP_DigestUpdate(&mdctx, (void*)buf, len);
	EVP_DigestFinal_ex(&mdctx, out, &md_len);
	EVP_MD_CTX_cleanup(&mdctx);
}

void xor(u8 *in, u32 len, u8 *out, u8 *key, u32 keylen) {
	int i;
	u8 kb;

	for(i = 0; i < len; i++) {
		kb = key[i % keylen];

		if (out == NULL)
			in[i] ^= kb;
		else
			out[i] = in[i] ^ kb;
	}
}

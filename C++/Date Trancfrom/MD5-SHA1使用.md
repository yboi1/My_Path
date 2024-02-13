## MD5-SHA1使用

```c++
#include<openssl/md5.h>
#include"openssl/sha.h"
#include<iostream>
#include<string>
#include<stdlib.h>
using namespace std;
# define MD5_DIGEST_LENGTH 16
# define SHA_DIGEST_LENGTH 20
void OpensslTest_MD5()
{
	MD5_CTX c;
	MD5_Init(&c);
	MD5_Update(&c, "hello",strlen("hello"));
	MD5_Update(&c, ",world", strlen(",world"));
	unsigned char* md = new unsigned char[MD5_DIGEST_LENGTH+1];
	char* res = new char[MD5_DIGEST_LENGTH * 2 + 1];
	MD5_Final(md, &c);
	for (int i = 0; i < MD5_DIGEST_LENGTH; ++i)
	{
		sprintf(&res[i * 2], "%02x", md[i]);
	}
	cout << res << endl;
}
void OpensslTest_SHA1()
{
	SHA_CTX c;
	SHA1_Init(&c);
	SHA1_Update(&c, "hello", strlen("hello"));
	SHA1_Update(&c, ",world", strlen(",world"));
	unsigned char* buf = new unsigned char[SHA_DIGEST_LENGTH+1];
	char* buf2= new char[SHA_DIGEST_LENGTH*2+1];
	SHA1_Final(buf, &c);
	for (int i = 0; i < MD5_DIGEST_LENGTH; ++i)
	{
		sprintf(&buf2[i * 2], "%02x", buf[i]);
	}

	cout << buf2 << endl;
}
int main()
{
	OpensslTest_SHA1();
	OpensslTest_MD5();
	return 0;
}
```

## RSA--PEM生成秘钥对

```c++
#include<openssl/rsa.h>
#include<openssl/pem.h>
extern "C"
{
    #include<openssl/applink.c>
}
void generateRsaKey()
{
	RSA* rsa = RSA_new();
	BIGNUM* bn = BN_new();
	BN_set_word(bn, 12345);
	RSA_generate_key_ex(rsa, 1024, bn, NULL);
#if 0
	FILE* fd = fopen("Public.pem", "w");
	PEM_write_RSAPublicKey(fd, rsa);
	fclose(fd);
	fd = fopen("Private.pem", "w");
	PEM_write_RSAPrivateKey(fd, rsa, NULL, NULL, 0, NULL, NULL);
	fclose(fd);
#else
	BIO* bi = BIO_new_file("Public-1.pem", "w");
	PEM_write_bio_RSAPublicKey(bi, rsa);
	BIO_free(bi);
	BIO* bi2 = BIO_new_file("Private-1.pem", "w");
	PEM_write_bio_RSAPrivateKey(bi2, rsa,NULL,NULL,0,NULL,NULL);
	BIO_free(bi2);
#endif


}
```


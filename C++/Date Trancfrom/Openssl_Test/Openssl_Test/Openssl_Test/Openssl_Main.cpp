#include<openssl/md5.h>
#include"openssl/sha.h"
#include<openssl/pem.h>
#include<iostream>
#include<string>
#include<stdlib.h>
#include<openssl/aes.h>
#include<openssl/rand.h>

using namespace std;
# define MD5_DIGEST_LENGTH 16
# define SHA_DIGEST_LENGTH 20
# define AES_BLOCK_SIZE 16
extern "C"
{
#include<openssl/applink.c>
}
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
void aesCBCEncrypt()
{
	const char* in = "AES是一套对称密钥的密码术，目前已广泛使用，用于替代已经不够安全的DES算法。所谓对称密钥，就是说加密和解密用的是同一个密钥，消息的发送方和接收方在消息传递前需要享有这个密钥。和非对称密钥体系不同，这里的密钥是双方保密的，不会让任何第三方知道。";
	const char* key = "1234567887654321";
	AES_KEY encKey;
	AES_set_encrypt_key((const unsigned char*)key, 128, &encKey);
	int length = 0;
	int len = strlen((char *)in) + 1 ;
	if (len % 16 != 0)
	{
		length = ((len / 16) + 1) * 16;
	}
	else
	{
		length = len;
	}
	unsigned char* out = new unsigned char[length];
	unsigned char ivec[AES_BLOCK_SIZE];
	memset(ivec, 9, sizeof(ivec));
	
	AES_cbc_encrypt((const unsigned char*)in, out, length, &encKey, ivec, AES_ENCRYPT);
	cout << "加密后的数据为：" << out << endl;
	unsigned char* data = new  unsigned char[length];
	AES_KEY decKey;
	memset(ivec, 9, sizeof(ivec));
	AES_set_encrypt_key((const unsigned char*)key, 128, &decKey);
	AES_cbc_encrypt(out, data, length, &decKey, ivec, AES_DECRYPT);
	cout << "解密后的数据为：" << data << endl;
	delete[]out;
	delete[]data;
}


void aesCBCEncrypt2()
{
	const char* in = "AES是一套对称密钥的密码术，目前已广泛使用，用于替代已经不够安全的DES算法。所谓对称密钥，就是说加密和解密用的是同一个密钥，消息的发送方和接收方在消息传递前需要享有这个密钥。和非对称密钥体系不同，这里的密钥是双方保密的，不会让任何第三方知道。";
	const char* key = "1234567887654321";
	AES_KEY encKey, decKey;
	AES_set_encrypt_key((const unsigned char*)key, 128, &encKey);
	AES_set_decrypt_key((const unsigned char*)key, 128, &decKey); // 设置解密所需的密钥表
	int len = strlen(in);
	int length = ((len + AES_BLOCK_SIZE - 1) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE; // 使用标准的PKCS#7填充方式
	unsigned char* out = new unsigned char[length];
	unsigned char* data = new unsigned char[length];
	unsigned char ivec[AES_BLOCK_SIZE];
	RAND_bytes(ivec, AES_BLOCK_SIZE); // 生成随机IV向量
	AES_cbc_encrypt((const unsigned char*)in, out, length, &encKey, ivec, AES_ENCRYPT);
	std::cout << "加密后的数据为：";
	for (int i = 0; i < length; i++)
	{
		std::cout << std::hex << (int)out[i];
	}
	std::cout << std::endl;
	memset(data, 0, length); // 注意：解密前需要清空缓冲区
	AES_cbc_encrypt(out, data, length, &decKey, ivec, AES_DECRYPT);
	std::cout << "解密后的数据为：" << data << std::endl;
	delete[] out;
	delete[] data;
}
int main()
{
	//OpensslTest_SHA1();
	//OpensslTest_MD5();
	//generateRsaKey();
	aesCBCEncrypt2();
	return 0;
}

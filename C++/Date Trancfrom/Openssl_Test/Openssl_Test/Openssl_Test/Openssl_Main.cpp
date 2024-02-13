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
	const char* in = "AES��һ�׶Գ���Կ����������Ŀǰ�ѹ㷺ʹ�ã���������Ѿ�������ȫ��DES�㷨����ν�Գ���Կ������˵���ܺͽ����õ���ͬһ����Կ����Ϣ�ķ��ͷ��ͽ��շ�����Ϣ����ǰ��Ҫ���������Կ���ͷǶԳ���Կ��ϵ��ͬ���������Կ��˫�����ܵģ��������κε�����֪����";
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
	cout << "���ܺ������Ϊ��" << out << endl;
	unsigned char* data = new  unsigned char[length];
	AES_KEY decKey;
	memset(ivec, 9, sizeof(ivec));
	AES_set_encrypt_key((const unsigned char*)key, 128, &decKey);
	AES_cbc_encrypt(out, data, length, &decKey, ivec, AES_DECRYPT);
	cout << "���ܺ������Ϊ��" << data << endl;
	delete[]out;
	delete[]data;
}


void aesCBCEncrypt2()
{
	const char* in = "AES��һ�׶Գ���Կ����������Ŀǰ�ѹ㷺ʹ�ã���������Ѿ�������ȫ��DES�㷨����ν�Գ���Կ������˵���ܺͽ����õ���ͬһ����Կ����Ϣ�ķ��ͷ��ͽ��շ�����Ϣ����ǰ��Ҫ���������Կ���ͷǶԳ���Կ��ϵ��ͬ���������Կ��˫�����ܵģ��������κε�����֪����";
	const char* key = "1234567887654321";
	AES_KEY encKey, decKey;
	AES_set_encrypt_key((const unsigned char*)key, 128, &encKey);
	AES_set_decrypt_key((const unsigned char*)key, 128, &decKey); // ���ý����������Կ��
	int len = strlen(in);
	int length = ((len + AES_BLOCK_SIZE - 1) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE; // ʹ�ñ�׼��PKCS#7��䷽ʽ
	unsigned char* out = new unsigned char[length];
	unsigned char* data = new unsigned char[length];
	unsigned char ivec[AES_BLOCK_SIZE];
	RAND_bytes(ivec, AES_BLOCK_SIZE); // �������IV����
	AES_cbc_encrypt((const unsigned char*)in, out, length, &encKey, ivec, AES_ENCRYPT);
	std::cout << "���ܺ������Ϊ��";
	for (int i = 0; i < length; i++)
	{
		std::cout << std::hex << (int)out[i];
	}
	std::cout << std::endl;
	memset(data, 0, length); // ע�⣺����ǰ��Ҫ��ջ�����
	AES_cbc_encrypt(out, data, length, &decKey, ivec, AES_DECRYPT);
	std::cout << "���ܺ������Ϊ��" << data << std::endl;
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

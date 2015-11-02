#include <cstdio>
#include <iostream>
#include <openssl/pem.h>
#include <openssl/x509.h>

/* Generates a 2048-bit RSA key. */
EVP_PKEY * generate_key()
{
    /* Allocate memory for the EVP_PKEY structure. */
    EVP_PKEY * pkey = EVP_PKEY_new();
    if(!pkey)
    {
        std::cerr << "Unable to create EVP_PKEY structure." << std::endl;
        return NULL;
    }
    
    /* Generate the RSA key and assign it to pkey. */
    RSA * rsa = RSA_generate_key(2048, RSA_F4, NULL, NULL);
    if(!EVP_PKEY_assign_RSA(pkey, rsa))
    {
        std::cerr << "Unable to generate 2048-bit RSA key." << std::endl;
        EVP_PKEY_free(pkey);
        return NULL;
    }
    
    /* The key has been generated, return it. */
    return pkey;
}

/* Generates a self-signed x509 certificate. */
X509 * generate_x509(EVP_PKEY * pkey)
{
    /* Allocate memory for the X509 structure. */
    X509 * x509 = X509_new();
    if(!x509)
    {
        std::cerr << "Unable to create X509 structure." << std::endl;
        return NULL;
    }
    
    /* Set the serial number. */
    ASN1_INTEGER_set(X509_get_serialNumber(x509), 1);
    
    /* This certificate is valid from now until exactly one year from now. */
    X509_gmtime_adj(X509_get_notBefore(x509), 0);
    X509_gmtime_adj(X509_get_notAfter(x509), 31536000L);
    
    /* Set the public key for the certificate. */
    X509_set_pubkey(x509, pkey);
    
    /* Copy the subject name to the issuer name. */
    X509_NAME * name = X509_get_subject_name(x509);
    
    /* Set the country code and common name. */
    X509_NAME_add_entry_by_txt(name, "C",  MBSTRING_ASC, (unsigned char *)"CA",        -1, -1, 0);
    X509_NAME_add_entry_by_txt(name, "O",  MBSTRING_ASC, (unsigned char *)"MyCompany", -1, -1, 0);
    X509_NAME_add_entry_by_txt(name, "CN", MBSTRING_ASC, (unsigned char *)"localhost", -1, -1, 0);
    
    /* Now set the issuer name. */
    X509_set_issuer_name(x509, name);
    
    /* Actually sign the certificate with our key. */
    if(!X509_sign(x509, pkey, EVP_sha1()))
    {
        std::cerr << "Error signing certificate." << std::endl;
        X509_free(x509);
        return NULL;
    }
    
    return x509;
}

void send(X509 * cert, char sender, char receiver)
{
    std::cout<<"Certificate received."<<std::endl;
    std::cout<<"Sent by: "<< sender <<std::endl;
    std::cout<<"Received by: "<< receiver<< std::endl;
    std::cout<<"Certificate: "<< std::endl;
    PEM_write_X509(stdout, cert);
}

int main(int argc, char ** argv)
{
    EVP_PKEY * pkeyA;
    EVP_PKEY * pkeyB;
    X509 * x509A;
    X509 * x509B;
    std::cout<<"1. Generate RSA key for A and send to B."<<std::endl;
    std::cout<<"2. Generate RSA key for B and send to A."<<std::endl;
    std::cout<<"3. Exit."<<std::endl;
    int ch;
    std::cout<<"Enter choice:\t";
    std::cin>>ch;
    switch(ch) {
        case 1: /* Generate the key for A. */
        std::cout << "Generating RSA key for A." << std::endl;
    
        pkeyA = generate_key();
        if(!pkeyA)
            return 1;
        
        /* Generate the certificate for A. */
        std::cout << "Generating x509 certificate for A." << std::endl;
        
        x509A = generate_x509(pkeyA);
        if(!x509A)
        {
            EVP_PKEY_free(pkeyA);
            return 1;
        }
        
        send(x509A, 'A', 'B');
        EVP_PKEY_free(pkeyA);
        X509_free(x509A);
        break;
        case 2: /* Generate the key for B. */
        std::cout << "Generating RSA key for B." << std::endl;
    
        pkeyB = generate_key();
        if(!pkeyA)
            return 1;
        
        /* Generate the certificate for B. */
        std::cout << "Generating x509 certificate for B." << std::endl;
        
        x509B = generate_x509(pkeyB);
        if(!x509B)
        {
            EVP_PKEY_free(pkeyB);
            return 1;
        }
        
        send(x509B, 'B', 'A');
        EVP_PKEY_free(pkeyB);
        X509_free(x509B);
        break;
        case 3: break;
        default: std::cout<<"Incorrect input."<<std::endl;
            break;
    }
}
/*
 * synergy -- mouse and keyboard sharing utility
 * Copyright (C) 2015-2016 Symless Ltd.
 *
 * This package is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * found in the file LICENSE that should have accompanied this file.
 *
 * This package is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "SslCertificate.h"
#include "Fingerprint.h"
#include "configDirectory.h"

#include <QProcess>
#include <QDir>
#include <QCoreApplication>

#include <openssl/x509.h>
#include <openssl/evp.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/bio.h>

#if !defined(Q_OS_WIN)
#include <sys/types.h>
#include <sys/stat.h>
#endif

static const char kCertificateSubjectInfo[] = "/CN=Synergy4rk";
static const char kCertificateFilename[] = "Synergy.pem";
static const char kSslDir[] = "SSL";

#if 1 || defined(Q_OS_WIN)
static const char kOpenSslCommand[] = "synopenssl.exe";
static const char kConfigFile[] = "synopenssl.cnf";
#else
static const char kOpenSslCommand[] = "openssl";//"./synopenssl";
static const char kConfigFile[] = "synopenssl.cnf";
#endif

SslCertificate::SslCertificate(QObject *parent) :
	QObject(parent)
{
	m_ConfigDir = g_GetConfigDirectory();
	if (m_ConfigDir.isEmpty()) {
		emit error(tr("Failed to get profile directory."));
	}
}

// https://stackoverflow.com/a/16393292
X509 *CreateCertificate (
	//const unsigned char *Country,
	//const unsigned char *OrganizationName,
	const unsigned char *CommonName,
	int Serial,
	int DaysValid,
	EVP_PKEY **out_key)
{
	X509 *Cert = NULL;
	EVP_PKEY *PrivateKey = NULL;
	X509_NAME *Name = NULL;
	RSA *KeyPair = NULL;
	BIGNUM *BigNumber = NULL;
	int Success = 0;

	// Faux loop...
	do {
		// Create the certificate object
		Cert = X509_new();
		if (!Cert)
			break;

		// Set version 2, and get version 3
		X509_set_version (Cert, 2);

		// Set the certificate's properties
		ASN1_INTEGER_set (X509_get_serialNumber (Cert), Serial);
		X509_gmtime_adj (X509_get_notBefore (Cert), 0);
		X509_gmtime_adj (X509_get_notAfter (Cert), (long)(60 * 60 * 24 * (DaysValid ? DaysValid : 1)));
		Name = X509_get_subject_name (Cert);
		//if (Country && *Country)
		//	X509_NAME_add_entry_by_txt (Name, "C", MBSTRING_ASC, Country, -1, -1, 0);
		if (CommonName && *CommonName)
			X509_NAME_add_entry_by_txt (Name, "CN", MBSTRING_ASC, CommonName, -1, -1, 0);
		//if (OrganizationName && *OrganizationName)
		//	X509_NAME_add_entry_by_txt (Name, "O", MBSTRING_ASC, OrganizationName, -1, -1, 0);
		X509_set_issuer_name (Cert, Name);

		// Create the RSA key pair object
		KeyPair = RSA_new();
		if (!KeyPair)
			break;

		// Create the big number object
		BigNumber = BN_new();
		if (!BigNumber)
			break;

		// Set the word
		if (!BN_set_word (BigNumber, RSA_F4))
			break;

		// Generate the key pair; lots of computes here
		if (!RSA_generate_key_ex (KeyPair, 4096, BigNumber, NULL))
			break;

		// Now we need a private key object
		PrivateKey = EVP_PKEY_new();
		if (!PrivateKey)
			break;

		// Assign the key pair to the private key object
		if (!EVP_PKEY_assign_RSA (PrivateKey, KeyPair))
			break;

		// KeyPair now belongs to PrivateKey, so don't clean it up separately
		KeyPair = NULL;

		// Set the certificate's public key from the private key object
		if (!X509_set_pubkey (Cert, PrivateKey))
			break;

		// Sign it with SHA-1
		int x = X509_sign (Cert, PrivateKey, EVP_sha1());

		if (x != 0) {
			// but we also want this to do things with because I don't know how to
			// use libcrypto at all
			*out_key = PrivateKey;
			Success = 1;
		}

		// PrivateKey now belongs to Cert, so don't clean it up separately
		PrivateKey = NULL;

	} while (0);

	// Things we always clean up
	if (BigNumber)
		BN_free (BigNumber);
	if (PrivateKey)
		EVP_PKEY_free (PrivateKey);

	// Things we clean up only on failure
	if (!Success)
	{
		if (Cert)
			X509_free (Cert);
		if (PrivateKey)
			EVP_PKEY_free (PrivateKey);
		if (KeyPair)
			RSA_free (KeyPair);
		Cert = NULL;
	}

	// Return the certificate (or NULL)
	return (Cert);
}

void SslCertificate::generateCertificate()
{
	X509 *Cert = NULL;
	BIO *synergy_pem = NULL;

	QString sslDirPath = QString("%1%2%3")
		.arg(m_ConfigDir)
		.arg(QDir::separator())
		.arg(kSslDir);

	QString filename = QString("%1%2%3")
		.arg(sslDirPath)
		.arg(QDir::separator())
		.arg(kCertificateFilename);
	auto utf8_filename = filename.toUtf8();

	//QFile file(filename);
	if (QFile(filename).exists())
		return;

	do {
		QDir sslDir(sslDirPath);
		if (!sslDir.exists()) {
			sslDir.mkpath(".");
		}

		EVP_PKEY *PrivateKey = NULL;

		Cert = CreateCertificate(
		//	NULL, // country
		//	NULL, // org
			(const unsigned char * const)"Synergy4rk", // common-name
			1, // serial number
			365, // days valid,
			&PrivateKey
		);

		// previous ssl-gen didn't check if file was made
		// i guess it's not too important
		if (Cert == NULL)
			break;

		// BIO routines uses utf-8 on windows and we'll assume everything
		// non-windows uses utf-8 too
		synergy_pem = BIO_new_file(utf8_filename.constData(), "w+");

		// uh oh file failed to open
		if (synergy_pem == NULL)
			break;

		// TODO FIXME XXX -- PEM_write_bio_PKCS8PrivateKey
		if (PEM_write_bio_PrivateKey(synergy_pem, PrivateKey, NULL,
			NULL, 0, NULL, NULL) != 1)
			break; // ugh

		// write the file out now please
		if (PEM_write_bio_X509(synergy_pem, Cert) != 1)
			break; // damn once again i guess

		generateFingerprint(Cert);

		if (BIO_flush(synergy_pem) != 1)
			break; // that's a shame

		if (BIO_free(synergy_pem) != 1)
			break; // wow really unlucky with these errors

		synergy_pem = NULL;

#if !defined(Q_OS_WIN)
		// could check for chmod error
		// could also extract the fd from the FILE* in openssl and use fchmod
		chmod(utf8_filename.constData(), S_IRUSR|S_IWUSR);
#endif

		emit info(tr("SSL certificate generated."));

#if 0
		QStringList arguments;

		// self signed certificate
		arguments.append("req");
		arguments.append("-x509");
		arguments.append("-nodes");

		// valide duration
		arguments.append("-days");
		arguments.append("365");

		// subject information
		arguments.append("-subj");
		QString subInfo(kCertificateSubjectInfo);
		arguments.append(subInfo);

		// private key
		arguments.append("-newkey");
		arguments.append("rsa:4096");

		// key output filename
		arguments.append("-keyout");
		arguments.append(filename);

		// certificate output filename
		arguments.append("-out");
		arguments.append(filename);
#endif
	} while (0);

	if (synergy_pem)
		BIO_free(synergy_pem);

	if (Cert)
		X509_free(Cert);
}

void SslCertificate::generateFingerprint(X509 *data)
{
	unsigned int len = 0;
	unsigned char hash[EVP_MAX_MD_SIZE] = {};
	const EVP_MD *digest = EVP_get_digestbyname("sha1");

	int success = X509_digest(data, digest, hash, &len);

	// 160-bit hashes for sha1
	if (success != 1 || len != 20) {
		emit error(tr("Failed to find SSL fingerprint."));
		return;
	}

	QString fingerprint = "";

	for (int i = 0; i < 20; i++) {
		fingerprint += QString("%1").arg(hash[i], 2, 16, QLatin1Char('0')).toUpper();
		if (i != 19) {
			fingerprint += ':';
		}
	}

	Fingerprint::local().trust(fingerprint, false);
	emit info(tr("SSL fingerprint generated."));
}

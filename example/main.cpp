#include <QApplication>

#include <QCryptographicHash>
#include <QDebug>
#include "qaesencryption.h"
#include "qaestestwgt.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qAesTestWgt *pAesWgt = new qAesTestWgt;
    pAesWgt->show();

    return app.exec();

//    /****************************************************************************************************/
//    {
//        QAESEncryption encryption(QAESEncryption::AES_128, QAESEncryption::ECB , QAESEncryption::ISO);
//        QString inputStr("HELLO AES");
//        QString key("your-string-key");
//        QString iv("your-IV-vector");

//        QByteArray hashKey = QCryptographicHash::hash(key.toLocal8Bit(), QCryptographicHash::Sha256);
//        QByteArray hashIV = QCryptographicHash::hash(iv.toLocal8Bit(), QCryptographicHash::Md5);

//        QByteArray encodeText = encryption.encode(inputStr.toLocal8Bit(), hashKey, hashIV);
//        QByteArray decodeText = encryption.decode(encodeText, hashKey, hashIV);

//        QString decodedString = QString(QAESEncryption::RemovePadding(decodeText,QAESEncryption::ISO));

//        qDebug() << " \n input = " << inputStr
//                     << " \n encodeText = " << encodeText
////                     << " \n QString = " << QString(encodeText)
////                     << " \n QString(utf8) = " << QString::fromUtf8(encodeText)
////                     << " \n QString(local8bit) = " << QString::fromLocal8Bit(encodeText)
//                     << " \n decodeText = " << decodeText
//                     << " \n output = " << decodedString
//                     << " \n " ;
//    }
//    /****************************************************************************************************/
//    {
//        QString inputStr("The Advanced Encryption Standard (AES), also known by its original name Rijndael "
//                         "is a specification for the encryption of electronic data established by the U.S. "
//                         "National Institute of Standards and Technology (NIST) in 2001");
//        QString key("your-string-key");
//        QString iv("your-IV-vector");

//        QByteArray hashKey = QCryptographicHash::hash(key.toLocal8Bit(), QCryptographicHash::Sha256);
//        QByteArray hashIV = QCryptographicHash::hash(iv.toLocal8Bit(), QCryptographicHash::Md5);

//        //Static invocation
//        QByteArray encodeText = QAESEncryption::Crypt(QAESEncryption::AES_256, QAESEncryption::CBC,inputStr.toLocal8Bit(), hashKey, hashIV);
//        QByteArray decodeText = QAESEncryption::Decrypt(QAESEncryption::AES_256,QAESEncryption::CBC,encodeText, hashKey, hashIV);

//        // Removal of Padding via Static function
//        QString decodedString = QString(QAESEncryption::RemovePadding(decodeText,QAESEncryption::ISO));

//        qDebug() << " \n input = " << inputStr
//                     << " \n encodeText = " << encodeText
//                     << " \n decodeText = " << decodeText
//                     << " \n output = " << decodedString
//                     << " \n " ;
//    }
//    /****************************************************************************************************/
//    {
//        QAESEncryption encryption(QAESEncryption::AES_256, QAESEncryption::CBC);

//        QString inputStr("The Advanced Encryption Standard (AES), also known by its original name Rijndael "
//                         "is a specification for the encryption of electronic data established by the U.S. "
//                         "National Institute of Standards and Technology (NIST) in 2001");
//        QString key("your-string-key");
//        QString iv("your-IV-vector");

//        QByteArray hashKey = QCryptographicHash::hash(key.toLocal8Bit(), QCryptographicHash::Sha256);
//        QByteArray hashIV = QCryptographicHash::hash(iv.toLocal8Bit(), QCryptographicHash::Md5);

//        QByteArray encodeText = encryption.encode(inputStr.toLocal8Bit(), hashKey, hashIV);
//        QByteArray decodeText = encryption.decode(encodeText, hashKey, hashIV);

//        QString decodedString = QString(encryption.removePadding(decodeText));

//        qDebug() << " \n input = " << inputStr
//                     << " \n encodeText = " << encodeText
//                     << " \n decodeText = " << decodeText
//                     << " \n output = " << decodedString
//                     << " \n " ;
//    }

//    return 0;
}

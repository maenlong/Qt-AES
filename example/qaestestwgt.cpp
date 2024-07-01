#include "qaestestwgt.h"
#include "ui_qaestestwgt.h"

#include <QCryptographicHash>
#include <QDebug>

qAesTestWgt::qAesTestWgt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::qAesTestWgt)
{
    ui->setupUi(this);

    initTest();
}

qAesTestWgt::~qAesTestWgt()
{
    delete ui;
}

void qAesTestWgt::initTest()
{
    /****************************************************************************************************/

    {
        QAESEncryption encryption(QAESEncryption::AES_128, QAESEncryption::ECB , QAESEncryption::ISO);
        QByteArray input = QString("HELLO AES 中文").toUtf8();
		QByteArray key = QString("your-string-key").toUtf8();

		QByteArray encodeText = encryption.encode(input, key);
		QByteArray decodeText = encryption.decode(encodeText, key);

        QString decodedString = QString::fromUtf8(decodeText);

		qDebug() << " \n input = " << input
			<< " \n encodeText = " << encodeText
//                     << " \n QString = " << QString(encodeText)
//                     << " \n QString(utf8) = " << QString::fromUtf8(encodeText)
			<< " \n decodeText = " << decodeText
			<< " \n output = " << decodedString
			<< " \n ";
		return;
	}

	/****************************************************************************************************/

	{
		QString inputStr("The Advanced Encryption Standard (AES), also known by its original name Rijndael "
			"is a specification for the encryption of electronic data established by the U.S. "
			"National Institute of Standards and Technology (NIST) in 2001");
		QString key("your-string-key");
		QString iv("your-IV-vector");

		QByteArray hashKey = QCryptographicHash::hash(key.toUtf8(), QCryptographicHash::Sha256);
		QByteArray hashIV = QCryptographicHash::hash(iv.toUtf8(), QCryptographicHash::Md5);

		//Static invocation
		QByteArray encodeText = QAESEncryption::Crypt(QAESEncryption::AES_256, QAESEncryption::CBC, inputStr.toUtf8(), hashKey, hashIV);
		QByteArray decodeText = QAESEncryption::Decrypt(QAESEncryption::AES_256, QAESEncryption::CBC, encodeText, hashKey, hashIV);

		// Removal of Padding via Static function
		QString decodedString = QString(QAESEncryption::RemovePadding(decodeText, QAESEncryption::ISO));

		qDebug() << " \n input = " << inputStr
			<< " \n encodeText = " << encodeText
			<< " \n decodeText = " << decodeText
			<< " \n output = " << decodedString
			<< " \n ";
	}

	/****************************************************************************************************/

	{
		QAESEncryption encryption(QAESEncryption::AES_256, QAESEncryption::CBC);

		QString inputStr("The Advanced Encryption Standard (AES), also known by its original name Rijndael "
			"is a specification for the encryption of electronic data established by the U.S. "
			"National Institute of Standards and Technology (NIST) in 2001");
		QString key("your-string-key");
		QString iv("your-IV-vector");

		QByteArray hashKey = QCryptographicHash::hash(key.toUtf8(), QCryptographicHash::Sha256);
		QByteArray hashIV = QCryptographicHash::hash(iv.toUtf8(), QCryptographicHash::Md5);

		QByteArray encodeText = encryption.encode(inputStr.toUtf8(), hashKey, hashIV);
		QByteArray decodeText = encryption.decode(encodeText, hashKey, hashIV);

		QString decodedString = QString(encryption.removePadding(decodeText));

		qDebug() << " \n input = " << inputStr
			<< " \n encodeText = " << encodeText
			<< " \n decodeText = " << decodeText
			<< " \n output = " << decodedString
			<< " \n ";
	}
}

QString qAesTestWgt::encodeStr(AesCodeData data)
{
	QString retStr;

	QAESEncryption encryption(data.aes, data.mode, data.padding);

	QByteArray input = data.source.toUtf8();
	QByteArray key = data.key.toUtf8();
	QByteArray iv = data.iv.toUtf8();

	QByteArray encodeText = encryption.encode(input, key, iv);
//	QByteArray decodeText = encryption.decode(encodeText, key);
//	QString decodedString = QString::fromUtf8(decodeText);

	retStr = encodeText.toBase64();//以Base64生成

	qDebug() << __FUNCTION__
		<< " \n input = " << input
//		<< " \n encodeText = " << encodeText
//		<< " \n decodeText = " << decodeText
//		<< " \n output = " << decodedString
		<< " \n retStr = " << retStr
		<< " \n ";

	return retStr;
}

QString qAesTestWgt::decodeStr(AesCodeData data)
{
	QString retStr;

	QAESEncryption encryption(data.aes, data.mode, data.padding);

	QByteArray input = QByteArray::fromBase64(data.source.toUtf8());//以Base64解析
	QByteArray key = data.key.toUtf8();
	QByteArray iv = data.iv.toUtf8();

//  QByteArray encodeText = encryption.encode(input, key);
    QByteArray decodeText = encryption.decode(input, key, iv);
    QString decodedString = QString::fromUtf8(decodeText);

    retStr = decodedString;

    qDebug() << __FUNCTION__
                 << " \n input = " << input
//                 << " \n encodeText = " << encodeText
//                 << " \n decodeText = " << decodeText
//                 << " \n output = " << decodedString
				 << " \n retStr = " << retStr
                 << " \n " ;

    return retStr;
}

void qAesTestWgt::on_generateBtn_clicked(bool checked)
{
    Q_UNUSED(checked);

    AesCodeData data;
//    data.source = ui->inputValueLet->text();  //下面根据情况赋值
    data.key = ui->keyValueLet->text();
    data.iv = ui->IVValueLet->text();
    data.aes = (QAESEncryption::Aes)ui->aesValueCbb->currentIndex();
    data.mode = (QAESEncryption::Mode)ui->modeValueCbb->currentIndex();
    data.padding = (QAESEncryption::Padding)ui->paddingValueCbb->currentIndex();

    if(data.key.isEmpty())
        data.key = ui->keyValueLet->placeholderText();
    if(data.iv.isEmpty())
        data.iv = ui->IVValueLet->placeholderText();

    QString retStr = QString("");
    if(ui->codeWayValueCbb->currentIndex())
    {
        //解密
        data.source = ui->outputValueLet->text();
        retStr = decodeStr(data);
        ui->inputValueLet->setText(retStr);
    }
    else
    {
        //加密
        data.source = ui->inputValueLet->text();
        retStr = encodeStr(data);
        ui->outputValueLet->setText(retStr);
    }
}


void qAesTestWgt::on_resetBtn_clicked(bool checked)
{
    Q_UNUSED(checked);

    ui->aesValueCbb->setCurrentIndex(0);
    ui->modeValueCbb->setCurrentIndex(0);
    ui->paddingValueCbb->setCurrentIndex(0);
    ui->codeWayValueCbb->setCurrentIndex(0);

    ui->keyValueLet->clear();
    ui->IVValueLet->clear();
    ui->inputValueLet->clear();
    ui->outputValueLet->clear();
}


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

QByteArray removePadding(const QByteArray &data)
{
    if (data.isEmpty()) {
        return data;
    }

    int paddingSize = static_cast<int>(data.at(data.size() - 1));
    if (paddingSize > 0 && paddingSize <= data.size()) {
        return data.left(data.size() - paddingSize);
    }

    return data;
}

QString qAesTestWgt::decodeStrForToken(QString source)
{
    AesCodeData data;
    data.source = source;
    data.key = QString("AKlMU89D@bizconf");
    data.iv = QString("");
    data.aes = QAESEncryption::AES_128;
    data.mode = QAESEncryption::ECB;
    data.padding = QAESEncryption::PKCS7;

    QString retStr;

    QAESEncryption encryption(data.aes, data.mode, data.padding);

    // 将输入的十六进制字符串转换为字节数组
    QByteArray input = QByteArray::fromHex(data.source.toUtf8());
    QByteArray key = data.key.toUtf8();
    QByteArray iv = data.iv.toUtf8();

    // 检查密钥长度
    if (key.size() != 16) {
        qDebug() << "Error: Key length must be 16 bytes for AES-128.";
        return QString();
    }

    // 解码
    QByteArray decodeText = encryption.decode(input, key, iv);

    // 移除填充字节
    QByteArray unpaddedText = removePadding(decodeText);

    // 将字节数组转换为字符串
    QString decodedString = QString::fromUtf8(unpaddedText);
    retStr = decodedString;

//    qDebug() << __FUNCTION__
//        << " \n input (hex) = " << input.toHex()
//        << " \n decodeText (hex) = " << decodeText.toHex()
//        << " \n unpaddedText (hex) = " << unpaddedText.toHex()
//        << " \n decodedString = " << decodedString
//        << " \n retStr = " << retStr;

//    input (hex) =  "9db03c4e6fe9f3828d279c5325e68dda331a644e725d78274dd40c22c666bfe803b109339d3fe048c82c84ae6ddf68a3"
//    decodeText (hex) =  "33323561326363303532393134636565623863313930313663303931643261632e313733353039343535383436300202"
//    unpaddedText (hex) =  "33323561326363303532393134636565623863313930313663303931643261632e31373335303934353538343630"
//    decodedString =  "325a2cc052914ceeb8c19016c091d2ac.1735094558460"
//    retStr =  "325a2cc052914ceeb8c19016c091d2ac.1735094558460"

    return retStr;
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

